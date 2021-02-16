//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS251 - Oral Exam 01 - main.cpp - 02/11/2021
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <map>

using namespace std;

void digest_file(string filename, map<string, int>& index) {
    ifstream inFile(filename);

    if (inFile.good()) {
        string key;
        int value;
        getline(inFile, key);
        while (inFile >> key && inFile >> value) {
            index[key] = value;
        }
    } else {
        cout << "Please enter a valid file" << endl;
    }
}

int main() {
    map<string, int> index;

    digest_file("student7_DataFile.txt", index);

    int total = 0;
    int ctn = 0;
    for (auto & it : index) {
        cout << "key: '" << it.first << "' value: " << it.second << endl;
        total += it.second;
        ctn++;
    }
    int avg = total / ctn;

    string res;
    while (res != "q") {
        cout << "Enter an Artist or press q to quit: ";
        cin >> res;

        if (index[res]) {
            cout << "The artist '" << res << "' had " << index[res] << " views and ";

            if (index[res] > avg) {
                cout << "was higher that the average of " << avg << " views." << endl;
            } else {
                cout << "was lower that the average of " << avg << "views." << endl;
            }
        } else {
            cout << "The artist does not exist" << endl;
        }
    }

    return 0;
}
