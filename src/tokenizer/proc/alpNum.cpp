#include <segvc/tokens.hxx>
#include <segvc/tokenizer.hxx>
#include <string>
#include <cstring>
#include <cstdint>
#include <cctype>
#include <segvc/qcerrors.hxx>
#include <iostream>
#include <unordered_map>

namespace segvc {

	void Tokenizer::procAlpNum(Token& arg) {
		const std::string& name = arg.name;
		Tokens::Type type;
		if(name == "struct")
			type = Tokens::TOK_STRUCT;
		else if(name == "in")
			type = Tokens::TOK_KEY_IN;
		else if(name == "let")
			type = Tokens::TOK_KEY_LET;
		else if(name == "fn")
			type = Tokens::TOK_KEY_FN;
		else if(name == "if")
			type = Tokens::TOK_KEY_IF;
		else if(name == "for")
		    type = Tokens::TOK_KEY_FOR;
		else if(name == "while")
			type = Tokens::TOK_KEY_WHILE;
		else if(name == "return")
			type = Tokens::TOK_KEY_RETURN;
		else if(name == "else")
            type = Tokens::TOK_KEY_ELSE;
	    else if(name == "do")
            type = Tokens::TOK_KEY_DO;
		else if(name == "then")
    		type = Tokens::TOK_KEY_THEN;
        else if(name == "switch")
            type = Tokens::TOK_KEY_SWITCH;
        else if(name == "case")
            type = Tokens::TOK_KEY_CASE;
        else if(name == "default")
            type = Tokens::TOK_KEY_DEFAULT;
        else if(name == "break")
            type = Tokens::TOK_KEY_BREAK;
        else if(name == "continue")
            type = Tokens::TOK_KEY_CONTINUE;
        else if(name == "goto")
            type = Tokens::TOK_KEY_GOTO;
        else if(name == "sizeof")
            type = Tokens::TOK_KEY_SIZEOF;
        else if(name == "typedef")
            type = Tokens::TOK_KEY_TYPEDEF;
        else if(name == "mut")
            type = Tokens::TOK_KEY_MUT;
        else if(name == "const")
            type = Tokens::TOK_KEY_CONST;
        else if(name == "vol")
            type = Tokens::TOK_KEY_VOL;
        else if(name == "extern")
            type = Tokens::TOK_KEY_EXTERN;
        else if(name == "pub")
            type = Tokens::TOK_KEY_PUB;
        else if(name == "priv")
            type = Tokens::TOK_KEY_PRIV;
        else if(name == "defer")
            type = Tokens::TOK_KEY_DEFER;
        else if(name == "static")
            type = Tokens::TOK_KEY_STATIC;
        else if(name == "enum")
            type = Tokens::TOK_KEY_ENUM;
        else if(name == "union")
            type = Tokens::TOK_KEY_UNION;
		else type = Tokens::TOK_IDENTIFIER;

		arg.ttype = type;
	};

}
