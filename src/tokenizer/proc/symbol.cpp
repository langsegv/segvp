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

	void Tokenizer::procSymbol(Token& arg) {
		const std::string& name = arg.name;
		Tokens::Type type;
		if(name == "(")
			type = Tokens::TOK_DEL_PARANL;
		else if(name == ")")
			type = Tokens::TOK_DEL_PARANR;
		else if(name == "{")
			type = Tokens::TOK_DEL_CBRACL;
		else if(name == "}")
			type = Tokens::TOK_DEL_CBRACR;
		else if(name == "[")
			type = Tokens::TOK_DEL_SBRACL;
		else if(name == "]")
	                type = Tokens::TOK_DEL_SBRACR;
		else if(name == "=")
			type = Tokens::TOK_ASSIGN;
		else if(name == "+")
	                type = Tokens::TOK_PLUS;
		else if(name == "-")
	                type = Tokens::TOK_MINUS;
		else if(name == "*")
	                type = Tokens::TOK_STAR;
		else if(name == "/")
	                type = Tokens::TOK_SLASH;
		else if(name == ":")
	                type = Tokens::TOK_COLON;
		else if(name == ";")
	                type = Tokens::TOK_SEMICOLON;
	        else if(name == "%")
	                type = Tokens::TOK_MOD;
	        else if(name == "?")
	                type = Tokens::TOK_QUESTION;
		else if(name == "==")
	                type = Tokens::TOK_OP_EQEQ;
		else if(name == "!=")
	                type = Tokens::TOK_OP_NEQ;
		else if(name == "<")
	                type = Tokens::TOK_OP_LT;
		else if(name == ">")
	                type = Tokens::TOK_OP_RT;
		else if(name == "<=")
	                type = Tokens::TOK_OP_LTE;
	        else if(name == ">=")
	                type = Tokens::TOK_OP_RTE;
		else if(name == "&&")
	                type = Tokens::TOK_OP_AND;
	        else if(name == "||")
	                type = Tokens::TOK_OP_OR;
		else if(name == "!")
			type = Tokens::TOK_OP_NOT;
		else if(name == "&")
			type = Tokens::TOK_OP_BIT_AND;
		else if(name == "|")
	                type = Tokens::TOK_OP_BIT_OR;
		else if(name == "^")
	                type = Tokens::TOK_OP_XOR;
		else if(name == "~")
	                type = Tokens::TOK_NEG;
		else if(name == "<<")
			type = Tokens::TOK_SHL;
		else if(name == ">>")
	                type = Tokens::TOK_SHR;
	        else if(name == "<>")
	                type = Tokens::TOK_ASSIGN_SWAP;
		else if(name == ",")
	                type = Tokens::TOK_COMMA;
		else if(name == ".")
	                type = Tokens::TOK_DOT;
		else if(name == "++")
			type = Tokens::TOK_INC;
	        else if(name == "--")
	                type = Tokens::TOK_DEC;
	        else if(name == "->")
	                type = Tokens::TOK_ARROW;
	        else if(name == "..")
	        	type = Tokens::TOK_OP_RANGE_EXCLUSIVE;
	        else if(name == "..=")
	        	type = Tokens::TOK_OP_RANGE_INCLUSIVE;
	        else if(name == "...")
	        	type = Tokens::TOK_ELLIPSIS;
	        else if(name == "+=")
	                type = Tokens::TOK_ASSIGN_PLUS;
	        else if(name == "-=")
	                type = Tokens::TOK_ASSIGN_MINUS;
	        else if(name == "*=")
	                type = Tokens::TOK_ASSIGN_MUL;
	        else if(name == "/=")
	                type = Tokens::TOK_ASSIGN_DIV;
	        else if(name == "%=")
	                type = Tokens::TOK_ASSIGN_MOD;
	        else if(name == "&=")
	                type = Tokens::TOK_ASSIGN_AND;
	        else if(name == "|=")
	                type = Tokens::TOK_ASSIGN_OR;
	        else if(name == "^=")
	                type = Tokens::TOK_ASSIGN_XOR;
	        else if(name == "<<=")
	                type = Tokens::TOK_ASSIGN_SHL;
	        else if(name == ">>=")
	                type = Tokens::TOK_ASSIGN_SHR;

		arg.ttype = type;
	}

}
