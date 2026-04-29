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
    Token Tokenizer::readSymbol(std::istream &in) {
        Token tok;
        tok.startOffset = tok.endOffset = in.tellg();
        tok.line = line;
        tok.column = tok.startOffset - line_beg + 1;

        char p = in.get();
        tok.name = std::string(1, p);

        if (p == '+') {
            p = in.peek();
            switch (p) {
                case '+':
                case '=':
                    tok.name += in.get();
                    break;
            }
        } else if (p == '-') {
            p = in.peek();
            switch (p) {
                case '-':
                case '>':
                case '=':
                    tok.name += in.get();
                    break;
            }
        } else
            switch (p) {
                case '/':
                    p = in.peek();
                    if (p == '=' || p == '/' || p == '*')
                        tok.name += in.get();
                    break;
                case '*':
                case '%':
                case '^':
                    p = in.peek();
                    if (p == '=')
                        tok.name += in.get();
                    break;
                case '&':
                    p = in.peek();
                    if (p == '&' || p == '=')
                        tok.name += in.get();
                    break;
                case '|':
                    p = in.peek();
                    if (p == '|' || p == '=')
                        tok.name += in.get();
                    break;
                case '.':
                    p = in.peek();
                    if (p == '.') {
                        tok.name += in.get();
                        p = in.peek();
                        if ( p == '.' || p == '=' ) tok.name += in.get();
                    }
                    break;
                case '<':
                    p = in.peek();
                    if (p == '<') {
                        tok.name += in.get();
                        p = in.peek();
                        if (p == '=')
                            tok.name += in.get();
                    } else if (p == '>') tok.name += in.get();
                    break;
                case '>':
                    p = in.peek();
                    if (p == '>') {
                        tok.name += in.get();
                        p = in.peek();
                        if (p == '=')
                            tok.name += in.get();
                    }
                    break;
            }

        return tok;
    }
}
