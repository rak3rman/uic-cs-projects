//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 01 - 9/5/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string nextToken(istream& infile);  // defined in "token.cpp"

//
// main:
//
int main()
{
    string filename;
    cout << "Filename> ";
    cin >> filename;
    
    //
    // open the program file:
    //
    ifstream infile(filename);
    
    if (!infile.good())
    {
        cout << "**Error: unable to open input file '" << filename << "'." << endl;
        return 0;
    }
    
    //
    // read the contents of the file and echo to the console:
    //
    string token, operand;
    
    int ACC, M0, M1, M2, M3, M4, M5, M6, M7, M8, M9;
    string operand_instruction = "none";
    bool expect_operand = false;
    
    token = nextToken(infile);
    while (token != "")
    {
        if (expect_operand) {
            if (operand_instruction == "out_s") {
                cout << token;
            } else if (operand_instruction == "add_i") {
                if (token == "M0") {
                    ACC = ACC + M0;
                } else if (token == "M1") {
                    ACC = ACC + M1;
                } else if (token == "M2") {
                    ACC = ACC + M2;
                } else if (token == "M3") {
                    ACC = ACC + M3;
                } else if (token == "M4") {
                    ACC = ACC + M4;
                } else if (token == "M5") {
                    ACC = ACC + M5;
                } else if (token == "M6") {
                    ACC = ACC + M6;
                } else if (token == "M7") {
                    ACC = ACC + M7;
                } else if (token == "M8") {
                    ACC = ACC + M8;
                } else if (token == "M9") {
                    ACC = ACC + M9;
                } else {
                    ACC = ACC + stoi(token);
                }
            } else if (operand_instruction == "sub_i") {
                if (token == "M0") {
                    ACC = ACC - M0;
                } else if (token == "M1") {
                    ACC = ACC - M1;
                } else if (token == "M2") {
                    ACC = ACC - M2;
                } else if (token == "M3") {
                    ACC = ACC - M3;
                } else if (token == "M4") {
                    ACC = ACC - M4;
                } else if (token == "M5") {
                    ACC = ACC - M5;
                } else if (token == "M6") {
                    ACC = ACC - M6;
                } else if (token == "M7") {
                    ACC = ACC - M7;
                } else if (token == "M8") {
                    ACC = ACC - M8;
                } else if (token == "M9") {
                    ACC = ACC - M9;
                } else {
                    ACC = ACC - stoi(token);
                }
            } else if (operand_instruction == "mult_i") {
                if (token == "M0") {
                    ACC = ACC * M0;
                } else if (token == "M1") {
                    ACC = ACC * M1;
                } else if (token == "M2") {
                    ACC = ACC * M2;
                } else if (token == "M3") {
                    ACC = ACC * M3;
                } else if (token == "M4") {
                    ACC = ACC * M4;
                } else if (token == "M5") {
                    ACC = ACC * M5;
                } else if (token == "M6") {
                    ACC = ACC * M6;
                } else if (token == "M7") {
                    ACC = ACC * M7;
                } else if (token == "M8") {
                    ACC = ACC * M8;
                } else if (token == "M9") {
                    ACC = ACC * M9;
                } else {
                    ACC = ACC * stoi(token);
                }
            } else if (operand_instruction == "div_i") {
                if (token == "M0") {
                    ACC = ACC / M0;
                } else if (token == "M1") {
                    ACC = ACC / M1;
                } else if (token == "M2") {
                    ACC = ACC / M2;
                } else if (token == "M3") {
                    ACC = ACC / M3;
                } else if (token == "M4") {
                    ACC = ACC / M4;
                } else if (token == "M5") {
                    ACC = ACC / M5;
                } else if (token == "M6") {
                    ACC = ACC / M6;
                } else if (token == "M7") {
                    ACC = ACC / M7;
                } else if (token == "M8") {
                    ACC = ACC / M8;
                } else if (token == "M9") {
                    ACC = ACC / M9;
                } else {
                    ACC = ACC / stoi(token);
                }
            } else if (operand_instruction == "mod_i") {
                if (token == "M0") {
                    ACC = ACC % M0;
                } else if (token == "M1") {
                    ACC = ACC % M1;
                } else if (token == "M2") {
                    ACC = ACC % M2;
                } else if (token == "M3") {
                    ACC = ACC % M3;
                } else if (token == "M4") {
                    ACC = ACC % M4;
                } else if (token == "M5") {
                    ACC = ACC % M5;
                } else if (token == "M6") {
                    ACC = ACC % M6;
                } else if (token == "M7") {
                    ACC = ACC % M7;
                } else if (token == "M8") {
                    ACC = ACC % M8;
                } else if (token == "M9") {
                    ACC = ACC % M9;
                } else {
                    ACC = ACC % stoi(token);
                }
            } else if (operand_instruction == "load_i") {
                if (token == "M0") {
                    ACC = M0;
                } else if (token == "M1") {
                    ACC = M1;
                } else if (token == "M2") {
                    ACC = M2;
                } else if (token == "M3") {
                    ACC = M3;
                } else if (token == "M4") {
                    ACC = M4;
                } else if (token == "M5") {
                    ACC = M5;
                } else if (token == "M6") {
                    ACC = M6;
                } else if (token == "M7") {
                    ACC = M7;
                } else if (token == "M8") {
                    ACC = M8;
                } else if (token == "M9") {
                    ACC = M9;
                } else {
                    ACC = stoi(token);
                }
            } else if (operand_instruction == "store_i") {
                if (token == "M0") {
                    M0 = ACC;
                } else if (token == "M1") {
                    M1 = ACC;
                } else if (token == "M2") {
                    M2 = ACC;
                } else if (token == "M3") {
                    M3 = ACC;
                } else if (token == "M4") {
                    M4 = ACC;
                } else if (token == "M5") {
                    M5 = ACC;
                } else if (token == "M6") {
                    M6 = ACC;
                } else if (token == "M7") {
                    M7 = ACC;
                } else if (token == "M8") {
                    M8 = ACC;
                } else if (token == "M9") {
                    M9 = ACC;
                }
            }
            expect_operand = false;
        } else {
            //Parse if operand not required
            if (token == "out_s" || token == "add_i" || token == "add_i" || token == "sub_i" || token == "mult_i" || token == "div_i" || token == "mod_i" || token == "load_i" || token == "store_i") {
                expect_operand = true;
                operand_instruction = token;
            } else if (token == "in_i") {
                cin >> ACC;
            } else if (token == "out_i") {
                cout << ACC;
            } else if (token == "clear") {
                ACC = 0;
                M0 = 0;
                M1 = 0;
                M2 = 0;
                M3 = 0;
                M4 = 0;
                M5 = 0;
                M6 = 0;
                M7 = 0;
                M8 = 0;
                M9 = 0;
            } else if (token == "end") {
                return 0;
            }
        }

        token = nextToken(infile);
    }
    
    //
    // done:
    //
    return 0;
}
