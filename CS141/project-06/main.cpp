//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 06 - main.cpp - 11/30/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "integer.h"

using namespace std;

//Ingest command and execute appropriate function
void execute_cmd(string cmd_line, int mem_size, Integer* integers) {
    //Ingest command
    string cmd = cmd_line.substr(0, cmd_line.find(" "));
    cmd_line.erase(0, cmd_line.find(" ") + 1);

    //Interpret command
    if (cmd == "") { // invalid command: received an invalid command
        cout << "Invalid command, try again..." << endl;
    } else if (cmd == "l") { //load commandfile: load and execute commands from a file instead of having to type them
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
                    execute_cmd(file_line, mem_size, integers);
                }
            }
            cout << "Load: done '" + cmd_line.substr(0, cmd_line.find(" ")) + "'" << endl;
        }
    } else if (cmd.at(0) == 'i') { // i<var> : execute a command for an integer
        cmd.erase(0, 1);
        if (stoi(cmd) > mem_size || stoi(cmd) < 1) {
            cout << "Invalid variable, try again..." << endl;
        } else {
            //Determine operator
            string oper = cmd_line.substr(0, cmd_line.find(" "));
            cmd_line.erase(0, cmd_line.find(" ") + 1);
            if (oper == "?") {
                cout << integers[stoi(cmd)-1].toStr() << endl;
            } else {
                string value = cmd_line.substr(0, cmd_line.find(" "));
                cmd_line.erase(0, cmd_line.find(" ") + 1);
                if (oper == "=") {
                    if (value.at(0) == 'i') {
                        value.erase(0, 1);
                        integers[stoi(cmd)-1] = integers[stoi(value)-1];
                    } else {
                        integers[stoi(cmd)-1] = value;
                    }
                } else if (oper == "+=") {
                    if (value.at(0) == 'i') {
                        value.erase(0, 1);
                        integers[stoi(cmd)-1].add(integers[stoi(value)-1]);
                    } else {
                        integers[stoi(cmd)-1].add(value);
                    }
                } else if (oper == "<<") {
                    integers[stoi(cmd)-1].shift_left(stoi(value));
                } else if (oper == ">>") {
                    integers[stoi(cmd)-1].shift_right(stoi(value));
                }
            }
        }
    } else { // invalid command: received an invalid command
        cout << "Invalid command, try again..." << endl;
    }
}

int main() {
    //Prompt and dynamically set for memory size
    cout << "Memory size? ";
    int mem_size = 0;
    cin >> mem_size;
    Integer* integers;
    integers = new Integer[mem_size];

    //Prompt user for command until we receive exit command
    string cmd_line = "";
    getline(cin, cmd_line);
    while (1==1) {
        //Prompt the user for a command
        cout << "> ";
        getline(cin, cmd_line);

        //Pre check for exit command
        if (cmd_line.substr(0, cmd_line.find(" ")) == "x") {
            delete[] integers;
            return 0;
        }

        //Execute command if not exit
        execute_cmd(cmd_line, mem_size, integers);
    }
}


