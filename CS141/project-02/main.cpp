//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 02 - 9/19/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string nextToken(istream& inProgramFile);  // defined in "token.cpp"

//Function: Determine if given operand is a memory location or literal integer
bool determine_memory_literal(string passed_operand) {
    if (passed_operand.at(0) == 'M') {
        return true;
    } else {
        return false;
    }
}

//Function: Return memory value from literal string value
int get_memory_value(string memory_string, int* mem_loc, string& config_value) {
    return mem_loc[stoi(memory_string.substr(config_value.find("M") + 2))];
}

//Function: Let PC equal PC plus operand
void add_pc_operand(int& PC, string* pc_operand) {
    PC = PC + stoi(pc_operand[PC]);
}

//Function: Clear all memory locations
void clear_mem_loc(int& mem_size, int* mem_loc) {
    for (int i = 0; i < mem_size; i++) {
        mem_loc[i] = 0;
    }
}

//Function: Generate trace string
void generate_trace(int& PC, int& ACC, int& AR, int& CF, string* pc_instruct, string* pc_operand) {
    cout << "**Trace: PC=" << PC << ",ACC=" << ACC << ",AR=" << AR << ",CF=" << CF << "," << pc_instruct[PC] << " " << pc_operand[PC] << endl;
}

//Function: Clean up pointers
void clean_pointers(int* mem_loc, string* pc_instruct, string* pc_operand) {
    delete[] mem_loc;
    delete[] pc_instruct;
    delete[] pc_operand;
}

int main() {
    //Gather input files from user
    string config_file;
    string program_file;
    cout << "Config file> ";
    cin >> config_file;
    cout << "Program file> ";
    cin >> program_file;

    //Open the config file
    ifstream inConfigFile(config_file);
    //Check to see if file is valid
    if (!inConfigFile.good()) {
        cout << "**Error: unable to open config file '" << config_file << "'." << endl;
        return 0;
    }

    //Parse config variables
    string config_value;
    int mem_size, code_size, tracing_option;
    while (getline(inConfigFile, config_value)) {
        //Get key and value for each config variable
        string key = config_value.substr(0, config_value.find(": "));
        string value = config_value.substr(config_value.find(": ") + 2);
        if (key == "memory") {
            mem_size = stoi(value);
            cout << "**Memory area: " << mem_size << endl;
        } else if (key == "code") {
            code_size = stoi(value);
            cout << "**Code area: " << code_size << endl;
        } else if (key == "trace") {
            tracing_option = stoi(value);
            cout << "**Tracing: " << tracing_option << endl;
        }
    }

    //Open the program file
    ifstream inProgramFile(program_file);
    //Check to see if file is valid
    if (!inProgramFile.good()) {
        cout << "**Error: unable to open program file '" << program_file << "'." << endl;
        return 0;
    }

    //Declare memory size
    int* mem_loc;
    mem_loc = new int[mem_size];
    
    //Parse through program instructions
    int pc_size = 0;
    string * pc_instruct;
    string * pc_operand;
    pc_instruct = new string[code_size - 1];
    pc_operand = new string[code_size - 1];

    //Handle operands and tokens
    string token;
    string operand_instruction = "none";
    bool expect_operand = false;

    //Loop through .asm file
    token = nextToken(inProgramFile);
    while (token != "") {
        if (expect_operand) {
            //Add operand to pc_operand array
            pc_operand[pc_size] = token;
            expect_operand = false;
            pc_size++;
        } else {
            if (token == "out_s" || token == "add_i" || token == "add_i" || token == "sub_i" || token == "mult_i" || token == "div_i" || token == "mod_i" || token == "load_i" || token == "store_i" || token == "loada_i" || token == "jump" || token == "jeq" || token == "jne" || token == "jlt" || token == "jle" || token == "jgt" || token == "jge" || token == "cmp_i") {
                //When an operand is expected
                expect_operand = true;
                pc_instruct[pc_size] = token;
            } else if (token == "in_i" || token == "out_i" || token == "loadind_i" || token == "storeind_i" || token == "clear" || token == "end") {
                //When an operand is not expected
                expect_operand = false;
                pc_instruct[pc_size] = token;
                pc_operand[pc_size] = "";
                pc_size++;
            }
        }
        token = nextToken(inProgramFile);
    }

    //Output program size to console
    cout << "**Program size: " << pc_size << endl;
    cout << "**Executing..." << endl;

    //Initialize system variables
    int ACC = 0;
    int AR = 0;
    int CF = 0;
    int PC = 0;

    //Parse through pc array
    while (PC < pc_size) {
        //Add tracing if enabled
        if (tracing_option == 1) {
            generate_trace(PC, ACC, AR, CF, pc_instruct, pc_operand);
        }
        //Determine if operand is expected
        if (pc_instruct[PC] == "in_i") {
            cin >> ACC;
            PC++;
        } else if (pc_instruct[PC] == "out_i") {
            cout << ACC;
            PC++;
        } else if (pc_instruct[PC] == "out_s") {
            cout << pc_operand[PC];
            PC++;
        } else if (pc_instruct[PC] == "add_i") {
            if (determine_memory_literal(pc_operand[PC])) {
                ACC = ACC + get_memory_value(pc_operand[PC], mem_loc, config_value);
            } else {
                ACC = ACC + stoi(pc_operand[PC]);
            }
            PC++;
        } else if (pc_instruct[PC] == "sub_i") {
            if (determine_memory_literal(pc_operand[PC])) {
                ACC = ACC - get_memory_value(pc_operand[PC], mem_loc, config_value);
            } else {
                ACC = ACC - stoi(pc_operand[PC]);
            }
            PC++;
        } else if (pc_instruct[PC] == "mult_i") {
            if (determine_memory_literal(pc_operand[PC])) {
                ACC = ACC * get_memory_value(pc_operand[PC], mem_loc, config_value);
            } else {
                ACC = ACC * stoi(pc_operand[PC]);
            }
            PC++;
        } else if (pc_instruct[PC] == "div_i") {
            if (determine_memory_literal(pc_operand[PC])) {
                ACC = ACC / get_memory_value(pc_operand[PC], mem_loc, config_value);
            } else {
                ACC = ACC / stoi(pc_operand[PC]);
            }
            PC++;
        } else if (pc_instruct[PC] == "mod_i") {
            if (determine_memory_literal(pc_operand[PC])) {
                ACC = ACC % get_memory_value(pc_operand[PC], mem_loc, config_value);
            } else {
                ACC = ACC % stoi(pc_operand[PC]);
            }
            PC++;
        } else if (pc_instruct[PC] == "load_i") {
            if (determine_memory_literal(pc_operand[PC])) {
                ACC = get_memory_value(pc_operand[PC], mem_loc, config_value);
            } else {
                ACC = stoi(pc_operand[PC]);
            }
            PC++;
        } else if (pc_instruct[PC] == "store_i") {
            mem_loc[stoi(pc_operand[PC].substr(config_value.find("M") + 2))] = ACC;
            PC++;
        } else if (pc_instruct[PC] == "loada_i") {
            if (determine_memory_literal(pc_operand[PC])) {
                AR = get_memory_value(pc_operand[PC], mem_loc, config_value);
            } else {
                AR = stoi(pc_operand[PC]);
            }
            PC++;
        } else if (pc_instruct[PC] == "loadind_i") {
            ACC = mem_loc[AR];
            PC++;
        } else if (pc_instruct[PC] == "storeind_i") {
            mem_loc[AR] = ACC;
            PC++;
        } else if (pc_instruct[PC] == "jump") {
            PC = PC + stoi(pc_operand[PC]);
        } else if (pc_instruct[PC] == "jeq") {
            if (CF == 0) {
                add_pc_operand(PC, pc_operand);
            } else {
                PC++;
            }
        } else if (pc_instruct[PC] == "jne") {
            if (CF != 0) {
                add_pc_operand(PC, pc_operand);
            } else {
                PC++;
            }
        } else if (pc_instruct[PC] == "jlt") {
            if (CF < 0) {
                add_pc_operand(PC, pc_operand);
            } else {
                PC++;
            }
        } else if (pc_instruct[PC] == "jle") {
            if (CF <= 0) {
                add_pc_operand(PC, pc_operand);
            } else {
                PC++;
            }
        } else if (pc_instruct[PC] == "jgt") {
            if (CF > 0) {
                add_pc_operand(PC, pc_operand);
            } else {
                PC++;
            }
        } else if (pc_instruct[PC] == "jge") {
            if (CF >= 0) {
                add_pc_operand(PC, pc_operand);
            } else {
                PC++;
            }
        } else if (pc_instruct[PC] == "cmp_i") {
            if (determine_memory_literal(pc_operand[PC])) {
                CF = ACC - get_memory_value(pc_operand[PC], mem_loc, config_value);
            } else {
                CF = ACC - stoi(pc_operand[PC]);
            }
            PC++;
        } else if (pc_instruct[PC] == "clear") {
            ACC = 0;
            clear_mem_loc(mem_size, mem_loc);
            PC++;
        } else if (pc_instruct[PC] == "end") {
            //If end command given, clean up storage and exit
            clean_pointers(mem_loc, pc_instruct, pc_operand);
            return 0;
        } else {
            cout << "INVALID INSTRUCTION: " << pc_instruct[PC] << endl << endl;
            //If invalid instruction given, clean up storage and exit
            clean_pointers(mem_loc, pc_instruct, pc_operand);
            return 0;
        }
    }
    //If while loop completed, clean up storage and exit
    clean_pointers(mem_loc, pc_instruct, pc_operand);
    return 0;
}
