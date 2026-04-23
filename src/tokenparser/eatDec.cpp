#include <segvc/tokenparser.hxx>
#include <segvc/expressions.hxx>
#include <segvc/util/concat.hxx>
#include <segvc/DeclarationEntry.hxx>

namespace segvc {

	std::unique_ptr<DeclarationEntry> Tokenparser::readDeclarationEntry() {
		std::unique_ptr<DeclarationEntry> decl = std::make_unique<DeclarationEntry>();
		if (eat(Tokens::TOK_DEL_PARANL)) {
			decl->type = DeclarationEntry::Type::parent;
			do {
				std::unique_ptr<DeclarationEntry> child = readDeclarationEntry();
				if (!child) {
					/* error */
					return nullptr;
				}
				decl->childs.push_back(std::move(child));
			} while (eat(Tokens::TOK_COMMA));
			if (!eat(Tokens::TOK_DEL_PARANR)) {
				/* error */
				return nullptr;
			}
		} else if (c_token.ttype == Tokens::TOK_IDENTIFIER) {
			decl->type = DeclarationEntry::Type::individual;
			decl->name = c_token.name;
			eat(Tokens::TOK_IDENTIFIER);
		} else {
			return nullptr;
		}

		std::shared_ptr<TypeEntry> c_typer = std::make_shared<TypeEntry>();

		/**
		 *  No need to check if it's nullptr or not by default,
		 *  Only if it's constant
		 */
		eatTyper(c_typer, true);

		decl->typer = c_typer;

		return decl;
	}

	/** This function reads tokens and creates a new FunctionStatement object.
	 *  If it caughts a problem it must return 0.
	 *  A successfull operation would add a DeclarationStatement instance to the param 'parent'.
	 *
	 *  @param parent Parent scope
	 *  @param dec_type Represents if variable defined as "const", "static" or by default "let".
	 */
	bool Tokenparser::eatDec(
		std::shared_ptr< BlockStatement > parent,
		DeclarationType dec_type
	) {
		std::shared_ptr<DeclarationStatement> decStm = std::make_shared<DeclarationStatement>();
		parent->childs.push_back(decStm);

		decStm->dec_type = dec_type;
		if (!((decStm->entry = readDeclarationEntry()))) {
			/* error */
			return false;
		}

		if(eat(Tokens::TOK_ASSIGN)) {
			decStm->master_initializer = eval_single(Tokens::TOK_SYS_SKIP);
		}

		return true;
	}

}
