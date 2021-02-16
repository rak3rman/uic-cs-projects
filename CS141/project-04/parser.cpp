//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 04 - Part 3 - 10/29/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

/*parser.cpp*/

//
// Recursive-descent parsing functions for SimpleC programming language
//
// ???
//
// Originally written by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 04
//

#include <iostream>
#include <istream>
#include <string>
#include <list>

#include "token.h"
#include "parser.h"

using namespace std;

//
// helper functions:
//

//
// handle syntax errors
//
void syntax_error(string expected, Token found) {
    cout << "Syntax error: expecting '" << expected << "', found '" << found.Value << "' @ (" << found.Line << ", " << found.Col << ")" << endl;
}

//
// recursive-descent functions:
//

//
// <simplec> ::= void main ( ) <block> $
//
bool simplec(list<Token>& tokens, bool trace)
{
    if (trace)
    {
        cout << "<simplec>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if token exists, return false if not, consume
    T = tokens.front();
    if (T.ID != TokenID::VOID_KEYW) {
        syntax_error("void", T);
        return false;
    }
    tokens.pop_front();
    //Check to see if token exists, return false if not, consume
    T = tokens.front();
    if (T.ID != TokenID::MAIN_KEYW) {
        syntax_error("main", T);
        return false;
    }
    tokens.pop_front();
    //Check to see if token exists, return false if not, consume
    T = tokens.front();
    if (T.ID != TokenID::LEFT_PAREN) {
        syntax_error("(", T);
        return false;
    }
    tokens.pop_front();
    //Check to see if token exists, return false if not, consume
    T = tokens.front();
    if (T.ID != TokenID::RIGHT_PAREN) {
        syntax_error(")", T);
        return false;
    }
    tokens.pop_front();
    //Check to see if element exists, return false if not, function consumes
    if (!block(tokens, trace)) {
        return false;
    }
    //Check to see if token exists, return false if not, consume
    T = tokens.front();
    if (T.ID != TokenID::EOS) {
        syntax_error("EOS", T);
        return false;
    }
    tokens.pop_front();
    //Return true because we did not error out
    return true;
}

//
// <stmts> ::= <stmt> <stmts>
//          | EMPTY
//
bool stmts(list<Token>& tokens, bool trace)
{
    if (trace)
    {
        cout << "<stmts>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    //Do pre check for stmt
    if (T.ID == TokenID::SEMICOLON || T.ID == TokenID::INT_KEYW || T.ID == TokenID::CIN_KEYW || T.ID == TokenID::COUT_KEYW || T.ID == TokenID::IDENTIFIER || T.ID == TokenID::LEFT_BRACE || T.ID == TokenID::WHILE_KEYW || T.ID == TokenID::IF_KEYW) {
        if (stmt(tokens, trace)) {
            if (stmts(tokens, trace)) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}



//
// <stmt> ::= ...
//
bool stmt(list<Token>& tokens, bool trace)
{
    if (trace)
    {
       cout << "<stmt>" << endl;
    }
    //Prepare token
    Token T;
    //First check to see if we match a stmt characteristic
    T = tokens.front();
    if (T.ID == TokenID::SEMICOLON) {
        if (missing(tokens, trace)) {return true;}
    } else if (T.ID == TokenID::INT_KEYW) {
        if (vardecl(tokens, trace)) {return true;}
    } else if (T.ID == TokenID::CIN_KEYW) {
        if (input(tokens, trace)) {return true;}
    } else if (T.ID == TokenID::COUT_KEYW) {
        if (output(tokens, trace)) {return true;}
    } else if (T.ID == TokenID::IDENTIFIER) {
        if (assignment(tokens, trace)) {return true;}
    } else if (T.ID == TokenID::LEFT_BRACE) {
        if (block(tokens, trace)) {return true;}
    } else if (T.ID == TokenID::WHILE_KEYW) {
        if (whileloop(tokens, trace)) {return true;}
    } else if (T.ID == TokenID::IF_KEYW) {
        if (ifthenelse(tokens, trace)) {return true;}
    } else {
        //Return a syntax error and false because the conditions were not met
        syntax_error("stmt", T);
        return false;
    }
    return false;
}


//
// <missing> ::= ;
//
bool missing(list<Token>& tokens, bool trace)
{
    if (trace)
    {
       cout << "<missing>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if token exists, return true if so, consume
    T = tokens.front();
    if (T.ID == TokenID::SEMICOLON) {
        tokens.pop_front();
        return true;
    }
    //Return false because we did not find a valid case
    return false;
}


//
// <vardecl> ::= int IDENTIFIER ;
//
bool vardecl(list<Token>& tokens, bool trace)
{
    if (trace)
    {
        cout << "<vardecl>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    if (T.ID == TokenID::INT_KEYW) {
        tokens.pop_front();
        T = tokens.front();
        if (T.ID == TokenID::IDENTIFIER) {
            tokens.pop_front();
            T = tokens.front();
            if (T.ID == TokenID::SEMICOLON) {
                tokens.pop_front();
                return true;
            } else {
                syntax_error(";", T);
                return false;
            }
        } else {
            syntax_error("IDENTIFIER", T);
            return false;
        }
    }
    //Return false because we did not find a valid case
    return false;
}


//
// <input> ::= cin >> IDENTIFIER ;
//
bool input(list<Token>& tokens, bool trace)
{
    if (trace)
    {
       cout << "<input>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    if (T.ID == TokenID::CIN_KEYW) {
        tokens.pop_front();
        T = tokens.front();
        if (T.ID == TokenID::INPUT) {
            tokens.pop_front();
            T = tokens.front();
            if (T.ID == TokenID::IDENTIFIER) {
                tokens.pop_front();
                T = tokens.front();
                if (T.ID == TokenID::SEMICOLON) {
                    tokens.pop_front();
                    return true;
                } else {
                    syntax_error(";", T);
                    return false;
                }
            } else {
                syntax_error("IDENTIFIER", T);
                return false;
            }
        } else {
            syntax_error(">>", T);
            return false;
        }
    }
    //Return false because we did not find a valid case
    return false;
}


//
// <output> ::= cout << <output_elem> ;
//
bool output(list<Token>& tokens, bool trace)
{
    if (trace)
    {
       cout << "<output>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    if (T.ID == TokenID::COUT_KEYW) {
        tokens.pop_front();
        T = tokens.front();
        if (output_elem(tokens, trace)) {
            if (more_elems(tokens, trace)) {
                T = tokens.front();
                if (T.ID == TokenID::SEMICOLON) {
                    tokens.pop_front();
                    return true;
                } else {
                    syntax_error(";", T);
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    //Return false because we did not find a valid case
    return false;
}


//
// <output_elem> ::= << <expr>
//                 | << endl
//
bool output_elem(list<Token>& tokens, bool trace)
{
    if (trace)
    {
       cout << "<output_elem>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if elements exist, return true if so, function consumes
    T = tokens.front();
    if (T.ID == TokenID::OUTPUT) {
        tokens.pop_front();
        T = tokens.front();
        if (T.ID == TokenID::ENDL_KEYW) {
            tokens.pop_front();
            return true;
        } else if (expr(tokens, trace)) {
            return true;
        } else {
            return false;
        }
    } else {
        syntax_error("<<", T);
        return false;
    }
    //Return a syntax error and false because the conditions were not met
    return false;

}

//
// <more_elems> ::= <output_elem> <more_elems>
//                | EMPTY
//
bool more_elems(list<Token>& tokens, bool trace)
{
    if (trace)
    {
        cout << "<more_elems>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    //Do pre check for output-elem
    if (T.ID == TokenID::OUTPUT) {
        if (output_elem(tokens, trace)) {
            if (more_elems(tokens, trace)) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}



//
// <assignment> ::= IDENTIFIER = <expr> ;
//
bool assignment(list<Token>& tokens, bool trace)
{
    if (trace)
    {
       cout << "<assignment>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    if (T.ID == TokenID::IDENTIFIER) {
        tokens.pop_front();
        T = tokens.front();
        if (T.ID == TokenID::EQUAL) {
            tokens.pop_front();
            T = tokens.front();
            if (expr(tokens, trace)) {
                T = tokens.front();
                if (T.ID == TokenID::SEMICOLON) {
                    tokens.pop_front();
                    return true;
                } else {
                    syntax_error(";", T);
                    return false;
                }
            } else {
                return false;
            }
        } else {
            syntax_error("=", T);
            return false;
        }
    }
    //Return false because we did not find a valid case
    return false;
}


//
// <block> ::= { <stmt> }
//
bool block(list<Token>& tokens, bool trace)
{
    if (trace)
    {
        cout << "<block>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    if (T.ID == TokenID::LEFT_BRACE) {
        tokens.pop_front();
        T = tokens.front();
        if (stmts(tokens, trace)) {
            T = tokens.front();
            if (T.ID == TokenID::RIGHT_BRACE) {
                tokens.pop_front();
                return true;
            } else {
                syntax_error("}", T);
                return false;
            }
        } else {
            //syntax_error("stmt1", T);
            return false;
        }
    }
    //Return false because we did not find a valid case
    return false;
}


//
// <whileloop> ::= while ( <expr> ) <block>
//
bool whileloop(list<Token>& tokens, bool trace)
{
    if (trace)
    {
        cout << "<whileloop>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    if (T.ID == TokenID::WHILE_KEYW) {
        tokens.pop_front();
        T = tokens.front();
        if (T.ID == TokenID::LEFT_PAREN) {
            tokens.pop_front();
            T = tokens.front();
            if (expr(tokens, trace)) {
                T = tokens.front();
                if (T.ID == TokenID::RIGHT_PAREN) {
                    tokens.pop_front();
                    T = tokens.front();
                    if (T.ID == TokenID::LEFT_BRACE) {
                        if (block(tokens, trace)) {
                            return true;
                        } else {
                            return false;
                        }
                    } else {
                        syntax_error("{", T);
                        return false;
                    }
                } else {
                    syntax_error(")", T);
                    return false;
                }
            } else {
                return false;
            }
        } else {
            syntax_error("(", T);
            return false;
        }
    }
    //Return false because we did not find a valid case
    return false;
}


//
// <ifthenelse> ::= if ( <expr> ) <block> <elseblock>
//
bool ifthenelse(list<Token>& tokens, bool trace)
{
    if (trace)
    {
       cout << "<ifthenelse>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    if (T.ID == TokenID::IF_KEYW) {
        tokens.pop_front();
        T = tokens.front();
        if (T.ID == TokenID::LEFT_PAREN) {
            tokens.pop_front();
            T = tokens.front();
            if (expr(tokens, trace)) {
                T = tokens.front();
                if (T.ID == TokenID::RIGHT_PAREN) {
                    tokens.pop_front();
                    T = tokens.front();
                    if (T.ID == TokenID::LEFT_BRACE) {
                        if (block(tokens, trace)) {
                            T = tokens.front();
                            if (elseblock(tokens, trace)) {
                                return true;
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    } else {
                        syntax_error("{", T);
                        return false;
                    }
                } else {
                    syntax_error(")", T);
                    return false;
                }
            } else {
                return false;
            }
        } else {
            syntax_error("(", T);
            return false;
        }
    }
    //Return false because we did not find a valid case
    return false;
}


//
// <elseblock> ::= else <block>
//               | EMPTY
//
bool elseblock(list<Token>& tokens, bool trace)
{
    if (trace)
    {
      cout << "<elseblock>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if correct path exists, if so, return syntax errors
    T = tokens.front();
    if (T.ID == TokenID::ELSE_KEYW) {
        tokens.pop_front();
        T = tokens.front();
        if (T.ID == TokenID::LEFT_BRACE) {
            if (block(tokens, trace)) {
                return true;
            } else {
                return false;
            }
        } else {
            syntax_error("{", T);
            return false;
        }
    }
    return true;
}


//
// <expr> ::= <term> <oper> <expr>
//          | <term>
//
bool expr(list<Token>& tokens, bool trace)
{
    if (trace)
    {
        cout << "<expr>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if term, return error if invalid
    T = tokens.front();
    if (term(tokens, trace)) {
        T = tokens.front();
        if (T.ID == TokenID::PLUS || T.ID == TokenID::MINUS || T.ID == TokenID::MULT || T.ID == TokenID::DIV || T.ID == TokenID::MOD || T.ID == TokenID::GT || T.ID == TokenID::GTE || T.ID == TokenID::LT || T.ID == TokenID::LTE || T.ID == TokenID::EQUAL_EQUAL || T.ID == TokenID::NOT_EQUAL) {
            tokens.pop_front();
            T = tokens.front();
            if (expr(tokens, trace)) {
                return true;
            } else {
                return false;
            }
        } else {
            return true;
        }
    } else {
        //syntax_error("term", T);
        return false;
    }
}

//
// <term> ::= ( <expr> )
//          | IDENTIFIER
//          | INT_LITERAL
//          | STR_LITERAL
//
bool term(list<Token>& tokens, bool trace)
{
    if (trace)
    {
        cout << "<term>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if token exists, return true if so, consume
    T = tokens.front();
    if (T.ID == TokenID::LEFT_PAREN) {
        tokens.pop_front();
        T = tokens.front();
        if (expr(tokens, trace)) {
            T = tokens.front();
            if (T.ID == TokenID::RIGHT_PAREN) {
                tokens.pop_front();
                return true;
            } else {
                syntax_error(")", T);
                return false;
            }
        } else {
            return false;
        }
    } else if (T.ID == TokenID::IDENTIFIER) {
        tokens.pop_front();
        return true;
    } else if (T.ID == TokenID::INT_LITERAL) {
        tokens.pop_front();
        return true;
    } else if (T.ID == TokenID::STR_LITERAL) {
        tokens.pop_front();
        return true;
    } else {
        syntax_error("term", T);
        return false;
    }
    //Return false because we did not find a valid case
    return false;
}

//
// <oper> ::= +, -, *, /, %, <, <=, >, >=, ==, !=
//
bool oper(list<Token>& tokens, bool trace)
{
    if (trace)
    {
        cout << "<oper>" << endl;
    }
    //Prepare token
    Token T;
    //Check to see if token exists, return true if so, consume
    T = tokens.front();
    if (T.ID == TokenID::PLUS || T.ID == TokenID::MINUS || T.ID == TokenID::MULT || T.ID == TokenID::DIV || T.ID == TokenID::MOD || T.ID == TokenID::GT || T.ID == TokenID::GTE || T.ID == TokenID::LT || T.ID == TokenID::LTE || T.ID == TokenID::EQUAL_EQUAL || T.ID == TokenID::NOT_EQUAL) {
        tokens.pop_front();
        return true;
    } else {
        syntax_error("oper", T);
        return false;
    }
}
