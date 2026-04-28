#include <segvc/tokens.hxx>
#include <segvc/tokenizer.hxx>
#include <segvc/util/io.hxx>
#include <string>
#include <cstring>
#include <cstdint>
#include <cctype>
#include <segvc/qcerrors.hxx>
#include <iostream>
#include <unordered_map>

namespace segvc {

	bool isSymbol(const char &c);

	int Tokenizer::proc() {
		std::istream& in = *_input_stream;

		line_beg = 0;
		line = 1;
		char curr;

	        while(in && in.peek() != EOF) {
			curr = in.peek();
			Token c_token;

	        if(std::isalpha(curr) || curr == '_') { // Identifiers/keyword must start with an alphabetic char or an '_' char
				c_token = readAlpNum(in);
				procAlpNum(c_token);
			} else if(std::isdigit(curr) || curr == '.') { // Number literal
				c_token = readNum(in);
			} else if(curr == '\'') { // Character literal
				c_token = readChar(in);
			} else if(curr == '"') { // String literal
				c_token = readString(in);
			} else if(isSymbol(curr)) {
				c_token = readSymbol(in);
				if(c_token.name == "//") {
					while(in.get() != '\n'); // Skip all chracters till new line when '//' appeared.

					continue; // This continue belogns to upper loop, not this ^^ while loop
				} else if(c_token.name == "/*") { /* I'm adding this line so GNU nano wouldn't get fucked up because of '/*' in string, LOL */
					while(in.peek() != EOF ) /* When '/*' appeared skip all chracters till: */
						if(in.get() == '*' && in.get() == '/')
							break;
					continue; // This continue belogns to upper loop, not this ^^ while loop

				} else
					procSymbol(c_token);
			} else if(curr == '\n' || curr == ' ' || curr == '\t') {
				size_t start_index = static_cast<size_t>(in.tellg());
				size_t start_col = start_index - line_beg + 1;
				int curr = in.peek();

				while (curr == ' ' || curr == '\t' || curr == '\n') {
					in.get();
					if (curr == '\n') {
						++line;
						line_beg = static_cast<size_t>(in.tellg());
					}
					curr = in.peek();
				}

				continue;
			} else if(curr == '\0') {
				return 0;
			} else return( unrecognizedTokenError("the file",
							line,
							static_cast<size_t>(in.tellg()) - line_beg + 1,
							readLine(in)), 1);

			c_token.lineStartOffset = line_beg;

			*_output_pipe << std::move(c_token);
	        }

		Token eof_token;
		eof_token.ttype = Tokens::TOK_SYS_EOF;
		*_output_pipe << std::move(eof_token);

		return 0;
	}

	bool isSymbol(const char &c) {
		switch(c) {
			case '(':
			case ')':
			case '{':
			case '}':
			case '[':
			case ']':
			case '=':
			case '+':
			case '-':
			case '*':
			case '/':
			case '%':
			case ':':
			case ';':
			case '!':
			case '<':
			case '>':
			case '&':
			case '|':
			case '^':
			case '~':
			case '.':
			case ',':
			        return true;
		}
		return false;
	}

}
