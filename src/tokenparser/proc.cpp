#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace segvc {

	/*
	* Return values and their meanings:
	*   0 : No catch
	*   1 : Problem caught
	*   2 : Finish
	*/
	int Tokenparser::proc(std::shared_ptr<BlockStatement> parent, const bool _inline, const bool subscope) {
		if(subscope && eat(Tokens::TOK_DEL_CBRACL)) {
			if(proc_body(parent, Tokens::TOK_DEL_CBRACR)) return 1;
			return 0;
		}

		DeclarationType dec_type = DeclarationType::UNDEFINED;

		if(eat(Tokens::TOK_KEY_CONST)) {
			dec_type = DeclarationType::CONST;
		} else if(eat(Tokens::TOK_KEY_STATIC)) {
			dec_type = DeclarationType::STATIC;
		}

		if(eat(Tokens::TOK_KEY_FN)) {
			if(!eatFnDec(parent, dec_type)) {
				/* error */
				return 1;
			}

			return 0;
		} else if(((dec_type != DeclarationType::UNDEFINED) || eat(Tokens::TOK_KEY_LET)) && eatDec(parent, dec_type)) {
			if(_inline) {
				/* Warning */
				/* Maybe can be solved with -O1 or -O2 (I'll add these options later) */
			}
			return 0;
		}

		if(dec_type) {
			/* error */
			return 1;
		}

		if(eat(Tokens::TOK_KEY_DO)) {
			std::shared_ptr<BlockStatement> scopeBlock = std::make_shared<BlockStatement>();
			if(proc(scopeBlock, true, true)) {
				/* error */
				return 1;
			} else if(eat(Tokens::TOK_KEY_FOR)) {
				if(!eatForStatement(parent, scopeBlock)) {
					/* error */
					return 1;
				}
			} else if(eat(Tokens::TOK_KEY_WHILE)) {
				if(!eatWhileStatement(parent, scopeBlock)) {
					/* error */
					return 1;
				}
			} else {
				parent->childs.push_back(scopeBlock); // create new scope by default
			}
			return 0;
		} else if(eat(Tokens::TOK_KEY_FOR)) {
			if(!eatForStatement(parent)) {
				/* error */
				return 1;
			}
			return 0;
		}


		if(eat(Tokens::TOK_KEY_RETURN)) {
			std::shared_ptr<ReturnStatement> stm = std::make_shared<ReturnStatement>();
			stm->expr = eval(Tokens::TOK_SYS_SKIP);
			parent->childs.push_back(stm);
			return 0;
		}

		ExprPtr expr = eval(Tokens::TOK_SYS_SKIP);
		if(expr) {
			std::shared_ptr<ExpressionStatement> stm = std::make_shared<ExpressionStatement>();
			stm->expr = expr;
			parent->childs.push_back(stm);
			return 0;
		}

		if(eat(Tokens::TOK_SEMICOLON))
			return 0;
		return 2;
	}

	int Tokenparser::proc_body(std::shared_ptr<BlockStatement> parent, Tokens::Type end_token) {
		while(true) {
			int cons = proc(parent, false, false);
			if(cons == 1)
				return 0;
			else if(cons == 2) break;
		}

		if(!eat(end_token)) { /* Error */
			std::cout << "Unexpected token: " << c_token.name << std::endl;
			return 1;
		}
		return 0;
	}

	int Tokenparser::proc() {
		if(!_input_pipe || !stm_root) return 1;
		*_input_pipe >> c_token;

		return proc_body(stm_root);
	}
}
