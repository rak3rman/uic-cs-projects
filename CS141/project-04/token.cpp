//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 04 - Part 1 - 10/25/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

/*token.cpp*/

//
// nextToken function needed for parsing of SimpleC programming language
//
// ???
//
// Originally written by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 04
//

#include <iostream>
#include <istream>
#include <string>
#include <cctype>  // isdigit, isalpha

#include "token.h"

using namespace std;


//
// overload << for Token so we can output tokens easily for debugging:
//
ostream& operator<<(ostream& os, const Token& T)
{
   os << "Token(" << T.ID << "," << T.Value << "," << T.Line << "," << T.Col << ")";
   return os;
}


//
// nextToken
//
// Summary: finds and returns the next SimpleC token as 
// defined in "token.h" and by the SimpleC programming 
// language.  If the input stream does not contain another
// token, TokenID::EOS (End-Of-Stream) is returned.  The
// longest possible token is always returned, e.g. the 
// input ">=" would be returned as TokenID::GTE instead
// of TokenID::GT followed by TokenID::EQUAL.  If the input
// stream contains a character that is not recognized as 
// part of SimpleC, TokenID::UNKNOWN is returned with 
// the token's value set to the unknown character.
//
// Pre-condition: input must be an open stream denoting
// the source of tokens, with line and col set to current 
// line and column position in this stream.
//
// Post-condition: input stream is advanced based on token 
// that is returned, with line and col advanced similarly.
//
Token nextToken(istream& input, int& line, int& col) {
    Token T;
    int c;
    c = input.peek();  // look ahead at the next char:

    //Loop endlessly until we reach the End-Of-Stream
    while (1 == 1) {
        //Check to see if c matches the start of any TokenID, whitespace, newline, or comment
        if (c == EOF) {
            //EOS (End-Of-Stream)
            //Set Token
            T.ID = TokenID::EOS;
            T.Value = "$";
            T.Line = line;
            T.Col = col;
            return T;
        } else if (c == ' ' || c == '\t' || c == '\r' || c == '\f') {
            //WHITESPACE
            c = input.get();  // input and consume char
            c = input.peek();  // look ahead at the next char
            col++; // proceed to next column
        } else if (c == '\n') {
            //NEWLINE
            c = input.get();  // input and consume char
            c = input.peek();  // look ahead at the next char
            line++; // proceed to next line
            col = 1; // reset column
        } else if (c == ';') {
            //SEMICOLON (;)
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::SEMICOLON;
            T.Value = ";";
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        } else if (c == '(') {
            //LEFT_PAREN (()
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::LEFT_PAREN;
            T.Value = "(";
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        } else if (c == ')') {
            //RIGHT_PAREN ())
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::RIGHT_PAREN;
            T.Value = ")";
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        } else if (c == '{') {
            //LEFT_BRACE ({)
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::LEFT_BRACE;
            T.Value = "{";
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        } else if (c == '}') {
            //RIGHT_BRACE ({)
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::RIGHT_BRACE;
            T.Value = "}";
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        } else if (c == '+') {
            //PLUS (+)
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::PLUS;
            T.Value = "+";
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        } else if (c == '-') {
            //MINUS (-)
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::MINUS;
            T.Value = "-";
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        } else if (c == '*') {
            //MULT (*)
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::MULT;
            T.Value = "*";
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        } else if (c == '/') {
            //DIV (/) and COMMENTS (//)
            c = input.get();  // input and consume char
            c = input.peek(); // peek ahead and see what is next
            if (c == '/') {
                c = input.get();  // input and consume char
                //Consume until we find a newline
                bool in_comment = true;
                while (in_comment) {
                    c = input.peek(); // peek ahead and see what is next
                    if (c == '\n') {
                        in_comment = false;
                    } else {
                        c = input.get();  // input and consume char
                    }
                }
            } else {
                //Set Token
                T.ID = TokenID::DIV;
                T.Value = "/";
                T.Line = line;
                T.Col = col;
                col++; // proceed to next column
                return T;
            }
        } else if (c == '%') {
            //MOD (%)
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::MOD;
            T.Value = "%";
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        } else if (c == '>') {
            //GT (>) and GTE (>=) and INPUT (>>)
            c = input.get();  // input and consume char
            c = input.peek(); // peek ahead and see what is next
            if (c == '=') {
                c = input.get();  // input and consume char
                //Set Token
                T.ID = TokenID::GTE;
                T.Value = ">=";
                T.Line = line;
                T.Col = col;
                col += 2; // advance by 2 columns
                return T;
            } else if (c == '>') {
                c = input.get();  // input and consume char
                //Set Token
                T.ID = TokenID::INPUT;
                T.Value = ">>";
                T.Line = line;
                T.Col = col;
                col += 2; // advance by 2 columns
                return T;
            } else {
                //Set Token
                T.ID = TokenID::GT;
                T.Value = ">";
                T.Line = line;
                T.Col = col;
                col++; // proceed to next column
                return T;
            }
        } else if (c == '<') {
            //LT (<) and LTE (<=) and OUTPUT (<<)
            c = input.get();  // input and consume char
            c = input.peek(); // peek ahead and see what is next
            if (c == '=') {
                c = input.get();  // input and consume char
                //Set Token
                T.ID = TokenID::LTE;
                T.Value = "<=";
                T.Line = line;
                T.Col = col;
                col += 2; // advance by 2 columns
                return T;
            } else if (c == '<') {
                c = input.get();  // input and consume char
                //Set Token
                T.ID = TokenID::OUTPUT;
                T.Value = "<<";
                T.Line = line;
                T.Col = col;
                col += 2; // advance by 2 columns
                return T;
            } else {
                //Set Token
                T.ID = TokenID::LT;
                T.Value = "<";
                T.Line = line;
                T.Col = col;
                col++; // proceed to next column
                return T;
            }
        } else if (c == '=') {
            //EQUAL (=) and EQUAL_EQUAL (==)
            c = input.get();  // input and consume char
            c = input.peek(); // peek ahead and see what is next
            if (c == '=') {
                c = input.get();  // input and consume char
                //Set Token
                T.ID = TokenID::EQUAL_EQUAL;
                T.Value = "==";
                T.Line = line;
                T.Col = col;
                col += 2; // advance by 2 columns
                return T;
            } else {
                //Set Token
                T.ID = TokenID::EQUAL;
                T.Value = "=";
                T.Line = line;
                T.Col = col;
                col++; // proceed to next column
                return T;
            }
        } else if (c == '!') {
            //NOT_EQUAL (!=)
            c = input.get();  // input and consume char
            c = input.peek(); // peek ahead and see what is next
            if (c == '=') {
                c = input.get();  // input and consume char
                //Set Token
                T.ID = TokenID::NOT_EQUAL;
                T.Value = "!=";
                T.Line = line;
                T.Col = col;
                col += 2; // advance by 2 columns
                return T;
            } else {
                //UNKNOWN (a character that is not part of SimpleC)
                //Set Token
                T.ID = TokenID::UNKNOWN;
                T.Value = "";
                T.Value += "!";
                T.Line = line;
                T.Col = col;
                col++; // proceed to next column
                return T;
            }
        } else if (isdigit(c)) {
            //INT_LITERAL (e.g. 123)
            c = input.get();  // input and consume char
            //Handle col before loop
            T.Col = col;
            col++; // proceed to next column
            //Get the rest of the integer literal using a while loop
            bool in_literal = true;
            string concat_literal(1, c);
            while (in_literal) {
                c = input.peek(); // peek ahead and see what is next
                if (isdigit(c)) {
                    string s(1, c);
                    concat_literal += s;
                    c = input.get();  // input and consume char
                    col++; // proceed to next column
                } else {
                    in_literal = false;
                }
            }
            //Set Token
            T.ID = TokenID::INT_LITERAL;
            T.Value = concat_literal;
            T.Line = line;
            return T;
        } else if (c == '"') {
            //STR_LITERAL (e.g. "hello cs141")
            c = input.get();  // input and consume char
            //Handle col before loop
            T.Col = col;
            col++; // proceed to next column
            //Get the rest of the string literal using a while loop
            bool in_literal = true;
            string concat_literal(1, c);
            while (in_literal) {
                c = input.peek(); // peek ahead and see what is next
                if (c == '"') {
                    in_literal = false;
                    string s(1, c);
                    concat_literal += s;
                    c = input.get();  // input and consume char
                    col++; // proceed to next column
                } else {
                    string s(1, c);
                    concat_literal += s;
                    c = input.get();  // input and consume char
                    col++; // proceed to next column
                }
            }
            //Set Token
            T.ID = TokenID::STR_LITERAL;
            T.Value = concat_literal;
            T.Line = line;
            return T;
        } else if (isalpha(c) || c == '_') {
            //IDENTIFIER (e.g. count)
            c = input.get();  // input and consume char
            //Handle col before loop
            T.Col = col;
            col++; // proceed to next column
            //Get the rest of the identifier using a while loop
            bool in_identifier = true;
            string concat_identifier(1, c);
            while (in_identifier) {
                c = input.peek(); // peek ahead and see what is next
                if (isalpha(c) || isdigit(c) || c == '_') {
                    string s(1, c);
                    concat_identifier += s;
                    c = input.get();  // input and consume char
                    col++; // proceed to next column
                } else {
                    in_identifier = false;
                }
            }
            //Set Token
            T.Value = concat_identifier;
            T.Line = line;
            //Check for keywords
            if (concat_identifier == "void") {
                T.ID = TokenID::VOID_KEYW;
            } else if (concat_identifier == "main") {
                T.ID = TokenID::MAIN_KEYW;
            } else if (concat_identifier == "int") {
                T.ID = TokenID::INT_KEYW;
            } else if (concat_identifier == "cin") {
                T.ID = TokenID::CIN_KEYW;
            } else if (concat_identifier == "cout") {
                T.ID = TokenID::COUT_KEYW;
            } else if (concat_identifier == "endl") {
                T.ID = TokenID::ENDL_KEYW;
            } else if (concat_identifier == "while") {
                T.ID = TokenID::WHILE_KEYW;
            } else if (concat_identifier == "if") {
                T.ID = TokenID::IF_KEYW;
            } else if (concat_identifier == "else") {
                T.ID = TokenID::ELSE_KEYW;
            } else {
                T.ID = TokenID::IDENTIFIER;
            }
            return T;
        } else {
            //UNKNOWN (a character that is not part of SimpleC)
            c = input.get();  // input and consume char
            //Set Token
            T.ID = TokenID::UNKNOWN;
            T.Value = "";
            T.Value += static_cast<char>(c);
            T.Line = line;
            T.Col = col;
            col++; // proceed to next column
            return T;
        }
    }
}
