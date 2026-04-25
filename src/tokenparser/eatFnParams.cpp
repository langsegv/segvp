
#include <segvc/tokenparser.hxx>
#include <segvc/DeclarationEntry.hxx>

namespace segvc {

	int Tokenparser::eatFnParams(
		std::vector<std::pair<
			DeclarationEntry,
			ExprPtr
		>> &params
	) {
		do {
			std::string par_name;

			/*
			 * Parameter name can be empty! this type of parameters will be used for allignation
			 */
			if(c_token.ttype == Tokens::TOK_IDENTIFIER) {
				par_name = c_token.name;
				eat(Tokens::TOK_IDENTIFIER);
			}

			auto par_typer = std::make_shared<TypeEntry>();
			if(!eatTyper(par_typer, true) && !par_name.empty()) { /* in case of having a name but catching an error when reading typer */
				return 0;
			}

			params.emplace_back(
				DeclarationEntry{
					DeclarationEntry::Type::individual,
					par_name,
					par_typer
				},
				eat(Tokens::TOK_ASSIGN) ?
					eval_single(Tokens::TOK_SYS_SKIP) :
					nullptr
			);

		} while(eat(Tokens::TOK_COMMA));
		return 1;
	}

}
