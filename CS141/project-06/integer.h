//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 06 - integer.h - 11/30/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

//
// An Integer class for adding and shifting integers of unlimited
// digits.  Each integer is stored as a linked-list of individual
// digits.
//
// Initially by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 06
//

#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

class Integer {
private:

    //
    // Data members:
    //
    class Node {
    public:
        int Value;
        Node* Next;
        Node* Prev;
        Node() {
            Value = 0;
            Next = nullptr;
            Prev = nullptr;
        }
        Node(int value) {
            Value = value;
            Next = nullptr;
            Prev = nullptr;
        }
    };
    Node* Head;
    Node* Tail;

    //
    // Private function members:
    //

    // Push back list
    void push_back(int value) {
        Node* prev_tail = Tail;
        Node* new_tail = new Node(value);

        //Check to see if prev tail exists
        if (prev_tail == nullptr) {
            Head = new_tail;
        } else {
            new_tail->Prev = prev_tail;
            prev_tail->Next = new_tail;
        }
        Tail = new_tail;
    }
    // Push front list
    void push_front(int value) {
        Node* prev_head = Head;
        Node* new_head = new Node(value);

        //Check to see if prev head exists
        if (prev_head == nullptr) {
            Tail = new_head;
        } else {
            new_head->Next = prev_head;
            prev_head->Prev = new_head;
        }
        Head = new_head;
    }

    // Free list
    void free() {
        Node* cur = Head;
        while (cur != nullptr) {
            Node* temp = cur->Next;
            delete cur;
            cur = temp;
        }
        Head = nullptr;
        Tail = nullptr;
    }

    // Create a deep copy of a list
    void deepcopy(const Integer &other) {
        Node* cur = other.Head;
        while (cur != nullptr) {
            push_back(cur->Value);
            cur = cur->Next;
        }
    }


public:
    //
    // default constructor
    //
    // Constructs an integer object and initializes to the value 0.
    // This function is called automatically when an integer is
    // constructed; do not call this function directly.
    //
    // pre-condition: an invalid integer object.
    // post-condition: a properly initialized integer set to 0.
    // exception: none.
    //
    Integer() {
        //free();
        Head = nullptr;
        Tail = nullptr;
        push_back(0);
    }

    //
    // constructor:
    //
    // Constructs this integer based on the digits from the given
    // integer string; throws an exception if s is not an integer
    // strnig.  This function is called automatically when an integer
    // is constructed; do not call this function directly.
    //
    // Example:
    //   if s = "1234" => integer is 1234
    //   if s = "oops" => integer is 0 and throws an exception
    //
    // pre-condition: an invalid integer object.
    // post-condition: a properly initialized integer object that has
    //   the same integer value as implied by the string.
    // exception: throws invalid_argument if the string is empty or
    //   non-numeric, with integer initialized to 0.
    //
    Integer(string s) {
        Head = nullptr;
        Tail = nullptr;
        //Remove all leading zeros
        s.erase(0, min(s.find_first_not_of('0'), s.size()-1));
        //Loop through each number and add to end of list if an int
        if (!s.empty()) {
            for (unsigned int i = 0; i < s.length(); i++) {
                if (isdigit(s.at(i))) {
                    push_back(s.at(i)-48);
                } else {
                    free();
                    new Node(0);
                    throw invalid_argument("string is empty or non-numeric");
                }
            }
        } else {
            throw invalid_argument("string is empty or non-numeric");
        }
    }

    //
    // copy constructor
    //
    // Constructs this integer via a deep-copy of the other integer.
    // This function is called automatically when an integer is
    // constructed; do not call this function directly.
    //
    // pre-condition: an invalid integer object.
    // post-condition: a properly initialized integer object that has
    //   the same integer value as the other integer.
    // exception: none.
    //
    Integer(const Integer &other) {
        //free();
        Head = nullptr;
        Tail = nullptr;
        deepcopy(other);
    }

    //
    // destructor
    //
    // Frees the resources associated with this integer.  This function
    // is called automatically when an integer is being destroyed;
    // do not call this function directly.
    //
    // pre-condition: properly initialized integer objects.
    // post-condition: an invalid integer object.
    // exception: none.
    //
    ~Integer() {
        free();
    }

    //
    // operator=
    //
    // Performs a proper C++ assignment of the other integer into
    // this integer.  This implies the existing integer is freed,
    // and then a deep-copy of the other integer is made.  This
    // function is called automatically as part of an assignment
    // operation involving integer objects; do not call this function
    // directly.
    //
    // pre-condition: properly initialized integer objects.
    // post-condition: this integer is a deep-copy of the other integer.
    // exception: none.
    //
    Integer &operator=(const Integer &other) {
        if (this == &other)  // special case: check for i = i;
            return *this;     // do nothing and just return THIS object back

        //
        // TODO: free existing integer, then make a deep copy of other
        //
        free();
        deepcopy(other);

        return *this;  // done, return THIS object back
    }

    //
    // toRawStr
    //
    // Converts this integer to a string, with no leading zeros.
    // The string is returned.
    //
    // Example:
    //   if i = 123456 => returns "123456"
    //   if i = 0 => return "0"
    //
    // pre-condition: a properly initialized integer object.
    // post-condition: integer string is returned with no leading zeros.
    // exception: none.
    //
    string toRawStr() {
        string s = "";
        Node* cur = Head;
        while (cur != nullptr) {
            s += to_string(cur->Value);
            cur = cur->Next;
        }
        return s;
    }

    //
    // toStr()
    //
    // Converts this integer to a string with USA-style commas
    // inserted at every thousandth location, with no leading
    // zeros.  The string is returned.
    //
    // Example:
    //   if i = 123456 => returns "123,456"
    //   if i = 789 => returns "789"
    //   if i = 0 => return "0"
    //
    // pre-condition: a properly initialized integer object.
    // post-condition: USA-style integer string is returned, with
    //   no leading zeros.
    // exception: none.
    //
    string toStr() {
        string s = "";
        int count  = 0;
        Node* cur = Tail;
        while (cur != nullptr) {
            if (count == 3) {
                s.insert(0, ",");
                s.insert(0, to_string(cur->Value));
                count = 0;
            } else {
                s.insert(0, to_string(cur->Value));
            }
            cur = cur->Prev;
            count++;
        }
        return s;
    }

    //
    // add
    //
    // Adds the other integer to this integer, in effect computing
    // this += other.  Nothing is returned, the integer is internally
    // updated.
    //
    // pre-condition: properly initialized integer objects.
    // post-condition: this integer increased by other integer.
    // exception: none.
    //
    void add(const Integer &other) {
        //Gather info about lists
        string s_this = "";
        int c_this = 0;
        string s_other = "";
        int c_other = 0;
        Node* cur = Tail;
        while (cur != nullptr) {
            s_this += to_string(cur->Value);
            cur = cur->Prev;
            c_this++;
        }
        cur = other.Tail;
        while (cur != nullptr) {
            s_other += to_string(cur->Value);
            cur = cur->Prev;
            c_other++;
        }
        //Determine max length
        int max_length = max(c_this,c_other);
        //Calculate total
        free();
        int remainder = 0;
        for (int i = 0; i < max_length; i++) {
            //Make sure we include leading zeros
            int value_this = 0;
            int value_other = 0;
            if (i < c_this) {
                value_this = s_this.at(i)-48;
            }
            if (i < c_other) {
                value_other = s_other.at(i)-48;
            }
            //Calculate total between column
            int added = value_this + value_other + remainder;
            //Store remainder
            remainder = added/10;
            //Add digit to this total
            push_front(added%10);
        }
        if (remainder != 0) {
            push_front(remainder);
        }
    }

    //
    // shift_left
    //
    // Shifts the integer digits left by the given amount N,
    // in effect multiplying the integer by 10^N.  If the integer
    // is 0, then the result remains 0.  Nothing is returned,
    // the integer is internally updated.
    //
    // Example:
    //   if i = 1234 then shift_left(i, 2) => 123400
    //   if i = 0 then shift_left(i, x) => 0
    //
    // pre-condition: a properly initialized integer object.
    // post-condition: if non-zero to start, the integer has
    //   N lower-order 0's added.
    // exception: throws invalid_argument if N < 0.
    //
    void shift_left(int N) {
        //Check if N is less than 0
        if (N >= 0) {
            //Check if 0
            if (Head->Value != 0) {
                for (int i = 0; i < N; i++) {
                    push_back(0);
                }
            }
        } else {
            throw invalid_argument("N < 0");
        }
    }

    //
    // shift_right
    //
    // Shifts the integer digits right by the given amount N,
    // in effect dividing the integer by 10^N.  If the integer
    // contains <= N digits, then the integer is shifted right
    // until 1 digit remains.  Nothing is returned, the integer
    // is internally updated.
    //
    // Example:
    //   if i = 1234 then shift_right(i, 2) => 12
    //   if i = 1234 then shift_right(i, 4) => 1
    //   if i = 0 then shift_right(i, x) => 0
    //
    // pre-condition: a properly initialized integer object.
    // post-condition: if non-zero to start, the integer has
    //   N lower-order digits removed.
    // exception: throws invalid_argument if N < 0.
    //
    void shift_right(int N) {
        int digits = 0;
        Node* cur = Tail;
        int last_value = 0;
        while (cur != nullptr) {
            digits++;
            last_value = cur->Value;
            cur = cur->Prev;
        }
        //Check if N is less than 0
        if (N >= 0) {
            //Check if 0
            if (last_value != 0) {
                for (int i = 0; i < N && i < digits-1; i++) {
                    //Rearrange pointers
                    Node* cur = Tail;
                    Node* next = cur->Next;
                    Node* prev = cur->Prev;
                    if (prev != nullptr) {
                        prev->Next = nullptr;
                        Tail = prev;
                    } else {
                        Tail = nullptr;
                    }
                    //Check head pointers
                    if (prev == nullptr) {
                        if (next != nullptr) {
                            next->Prev = nullptr;
                            Head = next;
                        } else {
                            Head = nullptr;
                        }
                    }
                    //Get value and delete node
                    delete cur;
                }
            }
        } else {
            throw invalid_argument("N < 0");
        }
    }
};