#include <segvc/tokens.hxx>
#include <segvc/tokenizer.hxx>
#include <string>
#include <map>

namespace segvc {

    std::map<std::string, Tokens::Type> tokenmap = {
        {"struct", Tokens::TOK_STRUCT},
        {"in", Tokens::TOK_KEY_IN},
        {"let", Tokens::TOK_KEY_LET},
        {"fn", Tokens::TOK_KEY_FN},
        {"if", Tokens::TOK_KEY_IF},
        {"for", Tokens::TOK_KEY_FOR},
        {"while", Tokens::TOK_KEY_WHILE},
        {"return", Tokens::TOK_KEY_RETURN},
        {"else", Tokens::TOK_KEY_ELSE},
        {"do", Tokens::TOK_KEY_DO},
        {"then", Tokens::TOK_KEY_THEN},
        {"switch", Tokens::TOK_KEY_SWITCH},
        {"case", Tokens::TOK_KEY_CASE},
        {"default", Tokens::TOK_KEY_DEFAULT},
        {"break", Tokens::TOK_KEY_BREAK},
        {"continue", Tokens::TOK_KEY_CONTINUE},
        {"goto", Tokens::TOK_KEY_GOTO},
        {"sizeof", Tokens::TOK_KEY_SIZEOF},
        {"typedef", Tokens::TOK_KEY_TYPEDEF},
        {"mut", Tokens::TOK_KEY_MUT},
        {"const", Tokens::TOK_KEY_CONST},
        {"vol", Tokens::TOK_KEY_VOL},
        {"extern", Tokens::TOK_KEY_EXTERN},
        {"pub", Tokens::TOK_KEY_PUB},
        {"priv", Tokens::TOK_KEY_PRIV},
        {"defer", Tokens::TOK_KEY_DEFER},
        {"static", Tokens::TOK_KEY_STATIC},
        {"enum", Tokens::TOK_KEY_ENUM},
        {"union", Tokens::TOK_KEY_UNION},
    };

	void Tokenizer::procAlpNum(Token& arg) {
		for (auto [name, type] : tokenmap) {
			if (arg.name == name) {
				arg.ttype = type;
				return;
			}
		}

		arg.ttype = Tokens::TOK_IDENTIFIER;
	}

}
