#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/qcerrors.hxx>

namespace segvc {

	int Tokenparser::eatTyper(std::shared_ptr<Typer> c_typer, bool followAll) {
		while(1) {
			if(c_token.ttype == Tokens::TOK_TYPE) {
				uint8_t vtype = getPVarT(c_token.name);
				eat(Tokens::TOK_TYPE);

				if(c_typer->vtype)
					std::cerr << "Warning! Declaration with multiple types, last one will be count!!" << std::endl;

				c_typer->vtype = vtype;
			}
			else if(eat(Tokens::TOK_KEY_NDET))
				c_typer->spec |= (1 << SPEC_NDET);
			else if(eat(Tokens::TOK_KEY_MUT))
				c_typer->spec |= (1 << SPEC_MUT);
			else if(eat(Tokens::TOK_KEY_INLINE))
				c_typer->spec |= (1 << SPEC_INL);
			else if(eat(Tokens::TOK_KEY_EXTERN))
				c_typer->spec |= (1 << SPEC_EXT);
			else if(eat(Tokens::TOK_KEY_VOLATILE))
				c_typer->spec |= (1 << SPEC_VOL);
			else if(eat(Tokens::TOK_DEL_PARANL)) {
				std::shared_ptr<Typer> ptr_typer = std::make_shared<Typer>();
				if(!eatFnParams(ptr_typer->func_params) ) {
					/* error */
					return 0;
				}

				if(!eat(Tokens::TOK_DEL_PARANR)) {
					/* error */
					std::cerr << "Expected ' ) ' but get ' " << c_token.name << " ' !";
					return 0;
				}

				if(c_typer)
					c_typer->respect_typer = ptr_typer;
				c_typer->vtype = VAR_FUN;
				c_typer = ptr_typer;
			} else if(eat(Tokens::TOK_DEL_SBRACL)) {
				ExprPtr expr = eval(Tokens::TOK_DEL_SBRACR);
				if(!expr) {
					/* error */
				}
				std::shared_ptr<Typer> ptr_typer = std::make_shared<Typer>();
				ptr_typer->sizer = expr;
				if(c_typer)
					c_typer->respect_typer = ptr_typer;
				c_typer->vtype = VAR_ARRAY;
				c_typer = ptr_typer;
			} else if(followAll && eat(Tokens::TOK_STAR)) {
				std::shared_ptr<Typer> ptr_typer = std::make_shared<Typer>();

				if(c_typer)
					c_typer->respect_typer = ptr_typer;
				c_typer->vtype = VAR_POINTER;
				c_typer = ptr_typer;
                        } else break;
		};

		return c_typer->vtype;
	};

}
