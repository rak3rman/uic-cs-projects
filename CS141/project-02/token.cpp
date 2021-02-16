//
// Parsing function that reads a UIC 1.0 language file and
// returns the contents (instructions and operands) one by
// one.
//
// Author: Prof. Hummel, U. of Illinois Chicago, Fall 2020
//
// Version 2.0: fixed checking for EOF, and REM @ end of line.
//
// NOTE: do not modify this code, the grading script will
// be using the original version of this function and ignore
// any changes that you make.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>  // isspace

using namespace std;


//
// nextToken
//
// Returns the next token in the input stream; returns the empty
// string "" if there is no more input (i.e. end of stream).
// Comments (i.e. REM ...) are discarded by this function, and
// never returned.
//
string nextToken(istream& stream)
{
    char  c;
    string token = "";

    while (token == "")
    {
        // skip initial whitespace:
        stream.get(c);
        while (!stream.eof() && isspace(c))
        {
            stream.get(c);
        }

        // did we reach end of file?  If so, there's no token:
        if (stream.eof())
        {
            return "";
        }

        if (c == '"')  // a string literal, loop until end of string:
        {
            stream.get(c);
            while (!stream.eof() && c != '"')
            {
                if (c == '\\')  // escape char?  Then read next done
                {
                    stream.get(c);

                    if (c == 'n')
                        c = '\n';
                    else if (c == 't')
                        c = '\t';
                    else if (c == 'f')
                        c = '\f';
                    else if (c == 'r')
                        c = '\r';
                    else
                        token += '\\';  // not sure what it is, so leave alone:
                }

                token += c;
                stream.get(c);
            }
        }
        else  // we have a word or numeric literal:
        {
            token += c;  // append that first char

            // now append remaining chars up until next whitespace:
            stream.get(c);
            while (!stream.eof() && !isspace(c))
            {
                token += c;
                stream.get(c);
            }
        }

        //
        // was the token REM?  If so, this denotes a comment, so discard
        // rest of line and try again:
        //
        if (token == "REM")
        {
            //
            // we want to discard the rest of the line, except when
            // REM already comes at the end of the line (in which case
            // we do nothing):
            //
            if (c == '\n' || c == '\r')  // REM @ end of line, do nothing
            {
                // nothing
            }
            else
            {
                getline(stream, token);  // discard rest of line:
            }

            token = "";  // try again:
        }
    }//while

    //
    // done, we have a token to return:
    //
    return token;
}