#include <segvc/tokenparser.hxx>

namespace segvc {

	ExprPtr Tokenparser::evalPrimary(std::vector< std::pair<Tokens::Type, OPE>>&, int) {
		ExprPtr main_expr;
		if(c_token.ttype == Tokens::TOK_IDENTIFIER) {
			main_expr = std::make_shared<VariableExpression>(c_token.name);
			eat(Tokens::TOK_IDENTIFIER);
		} else if(c_token.ttype == Tokens::TOK_NUMBER_LITERAL) {
			main_expr = std::make_shared<LiteralExpression>(LiteralType::LIT_NUMBER, c_token.name);
			eat(Tokens::TOK_NUMBER_LITERAL);
		} else if(c_token.ttype == Tokens::TOK_CHAR_LITERAL) {
			main_expr = std::make_shared<LiteralExpression>(LiteralType::LIT_CHAR, c_token.name);
			eat(Tokens::TOK_CHAR_LITERAL);
		} else if(c_token.ttype == Tokens::TOK_STRING_LITERAL) {
			main_expr = std::make_shared<LiteralExpression>(LiteralType::LIT_STRING, c_token.name);
			eat(Tokens::TOK_STRING_LITERAL);
		} else if(eat(Tokens::TOK_DEL_PARANL)) {
			main_expr = eval(Tokens::TOK_DEL_PARANR);
			if(!main_expr) {
				/* error */
				return 0;
			}
		} else if(eat(Tokens::TOK_DEL_SBRACL)) {
			main_expr = eval_tuple(Tokens::TOK_DEL_SBRACR);
			if(!main_expr) {
				/* error */
				return 0;
			}
		}

		while(true) {
			if(eat(Tokens::TOK_DEL_PARANL)) {
				std::shared_ptr<TupleExpression> params = eval_tuple(Tokens::TOK_DEL_PARANR);
				if(!params) {
					/* error */
					return 0;
				}
				main_expr = std::make_shared<FunctionCallExpression>(main_expr, params);
				continue;
			} else if(eat(Tokens::TOK_DEL_SBRACL)) {
				ExprPtr sizer = eval(Tokens::TOK_DEL_SBRACR);
				main_expr = std::make_shared<SubscriptExpression>(main_expr, sizer);
				continue;
			} else if(c_token.ttype == Tokens::TOK_DOT || c_token.ttype == Tokens::TOK_ARROW) {
				bool isPointer = c_token.ttype == Tokens::TOK_ARROW;
				eat(c_token.ttype);
				if(
					c_token.ttype == Tokens::TOK_IDENTIFIER ||
					c_token.ttype == Tokens::TOK_NUMBER_LITERAL // This would be used to get tuple elements and it's going to evaulated at compile time
				) {
					std::string member_name = c_token.name;
					eat(c_token.ttype);

					auto sexpr = std::make_shared<MemberExpression>(main_expr, member_name);
					sexpr->isPointer = isPointer;
					main_expr = sexpr;
					continue;
				} else {
					/* error */
					return 0;
				}
			}
			break;
		}
		return main_expr;
	}

}
