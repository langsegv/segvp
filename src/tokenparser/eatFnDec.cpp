#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace segvc {

	int Tokenparser::eatFnDec(
		std::shared_ptr<BlockStatement> parent,
		DeclarationType dec_type
	) {
		if(c_token.ttype != Tokens::TOK_IDENTIFIER) {
			/* error */
			return 0;
		}

		std::string var_name = c_token.name;
		eat(Tokens::TOK_IDENTIFIER);

		std::vector<std::pair<
			DeclarationEntry,
			ExprPtr
		>> params;

		if(eat(Tokens::TOK_DEL_PARANL)) {
			if(!eatFnParams(params)) {
				/* error */
				return 0;
			}
			if(!eat(Tokens::TOK_DEL_PARANR)) {
				/* error */
				return 0;
			}
		}

		std::shared_ptr<TypeEntry> c_typer = std::make_shared<TypeEntry>();
		if (!eatTyper(c_typer, true)) {
			/* error */
			return 0;
		}

		// If therese no parameters specified, set it as 0 parameters
		if(c_typer->vtype != VAR_FUN) {
			std::shared_ptr<TypeEntry> ptr_typer = std::make_shared<TypeEntry>();
			ptr_typer->vtype = VAR_FUN;
			if(c_typer)
				c_typer->respect_typer = ptr_typer;
			c_typer = ptr_typer;
		}

		if(!eat(Tokens::TOK_DEL_CBRACL)) {
			/* error */
			return 0;
		}
		std::shared_ptr<FunctionDeclarationStatement> decStm = std::make_shared<FunctionDeclarationStatement>();
		decStm->name = var_name;
		decStm->dec_type = dec_type;
		decStm->type_spec = c_typer;
		decStm->body = std::make_shared<BlockStatement>();
		decStm->params = std::move(params);

		if(proc_body(decStm->body, Tokens::TOK_DEL_CBRACR)) {
			/* error */
			return 0;
		}
		parent->childs.push_back(decStm);
		return 1;
	}

}
