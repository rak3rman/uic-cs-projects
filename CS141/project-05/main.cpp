//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 05 - main.cpp - 11/11/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//#include "list.h"
#include "oper.h"

using namespace std;

//Ingest command and execute appropriate function
void execute_cmd(string cmd_line, List& L1, List& L2, List& L3) {
    //Ingest command
    string cmd = cmd_line.substr(0, cmd_line.find(" "));
    cmd_line.erase(0, cmd_line.find(" ") + 1);

    //Interpret command
    if (cmd == "l") { //load commandfile: load and execute commands from a file instead of having to type them
        bool at_exit = false;
        string file_line = "";
        ifstream infile(cmd_line.substr(0, cmd_line.find(" ")));
        if (!infile.good()) {
            cout << "File does not exist, try again..." << endl;
        } else {
            cout << "Load: loading '" + cmd_line.substr(0, cmd_line.find(" ")) + "'" << endl;
            while (getline(infile, file_line) && !at_exit) {
                //Pre check for exit command
                if (file_line.substr(0, file_line.find(" ")) == "x") {
                    at_exit = true;
                } else {
                    //Execute command if not exit
                    execute_cmd(file_line, L1, L2, L3);
                    cout << endl;
                }
            }
            cout << "Load: done '" + cmd_line.substr(0, cmd_line.find(" ")) + "'" << endl;
        }
    } else {
        //Ingest remaining input values
        int input_a, input_b, input_c, input_count = 0;
        istringstream input_stream(cmd_line);
        while (input_stream && input_count < 3) {
            if (input_count == 0) {
                input_stream >> input_a;
            } else if (input_count == 1) {
                input_stream >> input_b;
            } else {
                input_stream >> input_c;
            }
            input_count++;
        }

        //Interpret command
        if (cmd == "p") { // print list: print the contents of a list
            if (input_a == 1) {
                doPrint(L1);
            } else if (input_a == 2) {
                doPrint(L2);
            } else if (input_a == 3) {
                doPrint(L3);
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "s") { // search list value: search list for first occurrence of a value, output position if found
            if (input_a == 1) {
                doSearch(L1, input_b);
            } else if (input_a == 2) {
                doSearch(L2, input_b);
            } else if (input_a == 3) {
                doSearch(L3, input_b);
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "i") { // insert list position value: insert the value in the list at the given position
            if (input_a == 1) {
                doInsert(L1, input_b, input_c);
            } else if (input_a == 2) {
                doInsert(L2, input_b, input_c);
            } else if (input_a == 3) {
                doInsert(L3, input_b, input_c);
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "r") { // remove list position: remove the node at the given position from the list, output node’s value
            if (input_a == 1) {
                doRemove(L1, input_b);
            } else if (input_a == 2) {
                doRemove(L2, input_b);
            } else if (input_a == 3) {
                doRemove(L3, input_b);
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "rl") { // rotate-left list: rotate the elements left, i.e. head element goes to the tail
            if (input_a == 1) {
                doRotateLeft(L1);
            } else if (input_a == 2) {
                doRotateLeft(L2);
            } else if (input_a == 3) {
                doRotateLeft(L3);
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "rr") { // rotate-right list: rotate the elements right, i.e. tail element goes to the head
            if (input_a == 1) {
                doRotateRight(L1);
            } else if (input_a == 2) {
                doRotateRight(L2);
            } else if (input_a == 3) {
                doRotateRight(L3);
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "f") { // free list: free the elements of the list, reset to empty
            if (input_a == 1) {
                doFree(L1);
            } else if (input_a == 2) {
                doFree(L2);
            } else if (input_a == 3) {
                doFree(L3);
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "a") { // append list other: append other to the end of list, reset other to empty
            if (input_a == 1) {
                if (input_b == 1) {
                    cout << "Error, you cannot append a list to itself, try again..." << endl;
                } else if (input_b == 2) {
                    doAppend(L1, L2);
                } else if (input_b == 3) {
                    doAppend(L1, L3);
                } else {
                    cout << "Invalid list, try again..." << endl;
                }
            } else if (input_a == 2) {
                if (input_b == 1) {
                    doAppend(L2, L1);
                } else if (input_b == 2) {
                    cout << "Error, you cannot append a list to itself, try again..." << endl;
                } else if (input_b == 3) {
                    doAppend(L2, L3);
                } else {
                    cout << "Invalid list, try again..." << endl;
                }
            } else if (input_a == 3) {
                if (input_b == 1) {
                    doAppend(L3, L1);
                } else if (input_b == 2) {
                    doAppend(L3, L2);
                } else if (input_b == 3) {
                    cout << "Error, you cannot append a list to itself, try again..." << endl;
                } else {
                    cout << "Invalid list, try again..." << endl;
                }
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "m") { // merge list other: merge other into list by alternating values, reset other to empty
            if (input_a == 1) {
                if (input_b == 1) {
                    cout << "Error, you cannot merge a list with itself, try again..." << endl;
                } else if (input_b == 2) {
                    doMerge(L1, L2);
                } else if (input_b == 3) {
                    doMerge(L1, L3);
                } else {
                    cout << "Invalid list, try again..." << endl;
                }
            } else if (input_a == 2) {
                if (input_b == 1) {
                    doMerge(L2, L1);
                } else if (input_b == 2) {
                    cout << "Error, you cannot merge a list with itself, try again..." << endl;
                } else if (input_b == 3) {
                    doMerge(L2, L3);
                } else {
                    cout << "Invalid list, try again..." << endl;
                }
            } else if (input_a == 3) {
                if (input_b == 1) {
                    doMerge(L3, L1);
                } else if (input_b == 2) {
                    doMerge(L3, L2);
                } else if (input_b == 3) {
                    cout << "Error, you cannot merge a list with itself, try again..." << endl;
                } else {
                    cout << "Invalid list, try again..." << endl;
                }
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "cp") { // cp dest src: free dest and then store a deep copy of src into dest
            if (input_a == 1) {
                if (input_b == 1) {
                    cout << "Error, you cannot copy a list onto itself, try again..." << endl;
                } else if (input_b == 2) {
                    doCopy(L1, L2);
                } else if (input_b == 3) {
                    doCopy(L1, L3);
                } else {
                    cout << "Invalid list, try again..." << endl;
                }
            } else if (input_a == 2) {
                if (input_b == 1) {
                    doCopy(L2, L1);
                } else if (input_b == 2) {
                    cout << "Error, you cannot copy a list onto itself, try again..." << endl;
                } else if (input_b == 3) {
                    doCopy(L2, L3);
                } else {
                    cout << "Invalid list, try again..." << endl;
                }
            } else if (input_a == 3) {
                if (input_b == 1) {
                    doCopy(L3, L1);
                } else if (input_b == 2) {
                    doCopy(L3, L2);
                } else if (input_b == 3) {
                    cout << "Error, you cannot copy a list onto itself, try again..." << endl;
                } else {
                    cout << "Invalid list, try again..." << endl;
                }
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else if (cmd == "cl") { // clean list: remove duplicates from the list
            if (input_a == 1) {
                doClean(L1);
            } else if (input_a == 2) {
                doClean(L2);
            } else if (input_a == 3) {
                doClean(L3);
            } else {
                cout << "Invalid list, try again..." << endl;
            }
        } else { // invalid command: received an invalid command
            cout << "Invalid command, try again..." << endl;
        }
    }
}

int main() {
    //Prepare lists
    List L1;
    List L2;
    List L3;
    init(L1);
    init(L2);
    init(L3);

    //Print title to console
    cout << "** Program for working with linked-lists **" << endl;

    //Prompt user for command until we receive exit command
    while (1==1) {
        //Prompt the user for a command
        cout << endl << "Enter a command (l,p,s,i,r,rl,rr,f,a,m,cp,cl,x): ";
        string cmd_line = "";
        getline(cin, cmd_line);

        //Pre check for exit command
        if (cmd_line.substr(0, cmd_line.find(" ")) == "x") {
            cout << endl << "** Done **" << endl;
            free(L1);
            free(L2);
            free(L3);
            return 0;
        }

        //Execute command if not exit
        execute_cmd(cmd_line, L1, L2, L3);
    }
}
