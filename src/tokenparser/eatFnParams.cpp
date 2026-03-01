
#include <segvc/tokenparser.hxx>
#include <segvc/variableentry.hxx>

namespace segvc {

	int Tokenparser::eatFnParams(
		std::vector<
			std::pair<
				std::string,
				VariableEntry
		>> &params
	) {
		int result=1;
		do {
			std::string par_name;

			/*
			 * Parameter name can be empty! this type of parameters will be used for allignation
			 */
			if(c_token.ttype == Tokens::TOK_IDENTIFIER) {
				par_name = c_token.name;
			}
			eat(Tokens::TOK_IDENTIFIER);

			auto par_typer = std::make_shared<Typer>();
			if(!eatTyper(par_typer, true) && !par_name.empty()) { /* in case of having a name but catching an error when reading typer */
				result = 0;
				continue;
			}

			params.push_back(
				std::make_pair(
					par_name,
					VariableEntry{
						par_typer,
						eat(Tokens::TOK_ASSIGN) ?
							eval_single(Tokens::TOK_SYS_SKIP) :
							nullptr
					}
				)
			);

		} while(eat(Tokens::TOK_COMMA));
		return result;
	}

}
