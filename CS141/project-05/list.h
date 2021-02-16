//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 05 - list.h - 11/11/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

//
// Declarations of structs, and core functions, for two-way linked-lists.
//
// Initially by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 05
//

//#pragma once

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;

//
// One node in a two-way linked-list:
//
struct Node
{
    int   Value;
    Node* Next;
    Node* Prev;
};

//
// A two-way linked-list with Head and Tail pointers:
//
struct List
{
    Node* Head;
    Node* Tail;
};

//
// Core linked-list functions:
//

//
// init
//
// Initializes the list to empty.
//
// pre-condition: L is uninitialized and has not been used.
// post-condition: L is properly initialized to denote empty.
//
void init(List& L) {
    L.Head = nullptr;
    L.Tail = nullptr;
}

//
// free
//
// Frees the memory associated with the nodes in the list,
// and then sets the list to empty.
//
// pre-condition: a properly initialized list.
// post-condition: L is properly set to denote empty.
//
void free(List& L) {
    Node* cur = L.Head;
    while (cur != nullptr) {
        Node* temp = cur;
        cur = cur->Next;
        delete temp;
    }
    L.Head = nullptr;
    L.Tail = nullptr;
}

//
// empty
//
// Returns true if the list is empty, false if not.
//
// pre-condition: a properly initialized list.
// post-condition: L is unchanged.
//
bool empty(List L) {
    if (L.Head == nullptr && L.Tail == nullptr) {
        return true;
    } else {
        return false;
    }
}

//
// size
//
// Returns the number of nodes in the list.
//
// pre-condition: a properly initialized list.
// post-condition: L is unchanged.
//
int  size(List L) {
    int count = 0;
    Node* cur = L.Head;
    while (cur != nullptr) {
        count += 1;
        cur = cur->Next;
    }
    return count;
}

//
// ith
//
// Returns the value in the node at the given position.
// Positions are 0-based, which means a position of 0
// denotes the head of the list, and a position of N-1
// denotes the tail of the list (where N=size(L)).
//
// Example: if L=[10,20,30] then
//    ith(L,2) => 30
//
// pre-condition: a properly initialized list.
// post-condition: L is unchanged.
// exception: throws invalid_argument if position invalid.
//
int  ith(List L, int position) {
    int count = 0;
    Node* cur = L.Head;
    while (cur != nullptr) {
        if (count == position) {
            return cur->Value;
        }
        count += 1;
        cur = cur->Next;
    }
    throw invalid_argument("ith: invalid position");
}

//
// search
//
// Searches the list for the first occurence of value.
// If found, the position of this value is returned.
// If not found, -1 is returned.
//
// Positions are 0-based, which means a position of 0
// denotes the head of the list, and a position of N-1
// denotes the tail of the list (where N=size(L)).
//
// Example: if L=[10,20,30,20] then
//    search(L,20) => 1
//
// pre-condition: a properly initialized list.
// post-condition: L is unchanged.
//
int  search(List L, int value) {
    int count = 0;
    Node* cur = L.Head;
    while (cur != nullptr) {
        if (value == cur->Value) {
            return count;
        }
        count += 1;
        cur = cur->Next;
    }
    return -1;
}

//
// insert
//
// Inserts the given value in the list such that after
// the insertion, the value is now at the given
// position.
//
// Positions are 0-based, which means a position of 0
// denotes the value will end up at the head of the list,
// and a position of N denotes the value will end up at
// the tail of the list.  N=size(L) before insertion.
//
// Examples: if L=[10,20] then
//    insert(L,0,30) => [30,10,20]
//    insert(L,1,30) => [10,30,20]
//    insert(L,2,30) => [10,20,30]
//
// pre-condition: a properly initialized list.
// post-condition: L contains value at given position.
// exception: throws invalid_argument if position invalid.
//
void insert(List& L, int position, int value) {
    //Get ready for traversal
    int count = 0;
    bool found_match = false;
    Node* cur = L.Head;
    Node* prev = nullptr;
    //Traverse until we find position
    while (cur != nullptr && !found_match) {
        if (count == position) {
            found_match = true;
        } else {
            prev = cur;
            cur = cur->Next;
        }
        count += 1;
    }
    //Check to see if position is valid
    if (position >= 0 && position <= count) {
        //Initialize new node
        Node* new_node = new Node();
        new_node->Value = value;
        new_node->Next = nullptr;
        new_node->Prev = nullptr;
        //Determine insertion point
        if (prev == nullptr) { //Insert at head
            new_node->Next = cur;
            if (cur != nullptr) {
                cur->Prev = new_node;
            }
            L.Head = new_node;
        }
        if (cur == nullptr) { //Insert at tail
            new_node->Prev = prev;
            if (prev != nullptr) {
                prev->Next = new_node;
            }
//            cur = new_node;
//            while (cur != nullptr) {
//                cout << "CUR: " << cur->Value << " " << cur->Prev << "-" << cur << "-" << cur->Next << endl;
//                cur = cur->Prev;
//            }
            L.Tail = new_node;
        }
        if (prev != nullptr && cur != nullptr) { //Insert between prev and cur
            new_node->Next = cur;
            new_node->Prev = prev;
            prev->Next = new_node;
            cur->Prev = new_node;
        }
    } else {
        throw invalid_argument("insert: invalid position");
    }
}
å
//
// remove
//
// Removes the node at the given position from the list,
// and returns the value stored in this node.
//
// Positions are 0-based, which means a position of 0
// denotes the head of the list, and a position of N-1
// denotes the tail of the list.  N=size(L) before removal.
//
// Examples: if L=[10,20,30] then
//    remove(L,1) => returns 20 with L=[10,30]
//
// pre-condition: a properly initialized list.
// post-condition: L with node at given position removed.
// exception: throws invalid_argument if position invalid.
//
int  remove(List& L, int position) {
    //Get ready for traversal
    int count = 0;
    bool found_match = false;
    Node* cur = L.Head;
    Node* prev = nullptr;
    //Traverse until we find position
    while (cur != nullptr && !found_match) {
        if (count == position) {
            found_match = true;
        } else {
            prev = cur;
            cur = cur->Next;
        }
        count += 1;
    }
    //Check to see if position is valid
    if (position >= 0 && position < count) {
        //Determine removal point
        Node* next = cur->Next;
        if (prev == nullptr) { //Remove at head
            if (next != nullptr) {
                next->Prev = nullptr;
                L.Head = next;
            } else {
                L.Head = nullptr;
            }
        }
        if (next == nullptr) { //Remove at tail
            if (prev != nullptr) {
                prev->Next = nullptr;
                L.Tail = prev;
            } else {
                L.Tail = nullptr;
            }
        }
        if (prev != nullptr && next != nullptr) { //Remove cur between prev and next
            next->Prev = prev;
            prev->Next = next;
        }
        //Get value and delete node
        int temp_value = cur->Value;
        delete cur;
        return temp_value;
    } else {
        throw invalid_argument("remove: invalid position");
    }
}

//
// pop_front
//
// Removes the node at the head of the list and returns
// the value from this node.
//
// pre-condition: a properly initialized list.
// post-condition: L with head node removed.
// exception: throws runtime_error if list empty.
//
int  pop_front(List& L) {
    //Check to see if list is empty
    if (L.Head != nullptr && L.Tail != nullptr) {
        //Rearrange pointers
        Node* cur = L.Head;
        Node* next = cur->Next;
        Node* prev = cur->Prev;
        if (next != nullptr) {
            next->Prev = nullptr;
            L.Head = next;
        } else {
            L.Head = nullptr;
        }
        //Check tail pointers
        if (next == nullptr) {
            if (prev != nullptr) {
                prev->Next = nullptr;
                L.Tail = prev;
            } else {
                L.Tail = nullptr;
            }
        }
        //Get value and delete node
        int temp_value = cur->Value;
        delete cur;
        return temp_value;
    } else {
        throw runtime_error("pop_front: invalid list");
    }
}

//
// pop_back
//
// Removes the node at the tail of the list and returns
// the value from this node.
//
// pre-condition: a properly initialized list.
// post-condition: L with tail node removed.
// exception: throws runtime_error if list empty.
//
int  pop_back(List& L) {
//Check to see if list is empty
    if (L.Head != nullptr && L.Tail != nullptr) {
        //Rearrange pointers
        Node* cur = L.Tail;
        Node* next = cur->Next;
        Node* prev = cur->Prev;
        if (prev != nullptr) {
            prev->Next = nullptr;
            L.Tail = prev;
        } else {
            L.Tail = nullptr;
        }
        //Check head pointers
        if (prev == nullptr) {
            if (next != nullptr) {
                next->Prev = nullptr;
                L.Head = next;
            } else {
                L.Head = nullptr;
            }
        }
        //Get value and delete node
        int temp_value = cur->Value;
        delete cur;
        return temp_value;
    } else {
        throw runtime_error("pop_back: invalid list");
    }
}

//
// push_front
//
// Inserts the given value at the head of the list.
//
// pre-condition: a properly initialized list.
// post-condition: L with value inserted at head.
//
void push_front(List& L, int value) {
    Node* prev_head = L.Head;
    Node* new_head = new Node();

    //Initialize new head
    new_head->Value = value;
    new_head->Next = nullptr;
    new_head->Prev = nullptr;

    //Check to see if prev head exists
    if (prev_head == nullptr) {
        L.Tail = new_head;
    } else {
        new_head->Next = prev_head;
        prev_head->Prev = new_head;
    }
    L.Head = new_head;
}

//
// push_back
//
// Inserts the given value at the tail of the list.
//
// pre-condition: a properly initialized list.
// post-condition: L with value inserted at tail.
//
void push_back(List& L, int value) {
    Node* prev_tail = L.Tail;
    Node* new_tail = new Node();

    //Initialize new tail
    new_tail->Value = value;
    new_tail->Next = nullptr;
    new_tail->Prev = nullptr;

    //Check to see if prev tail exists
    if (prev_tail == nullptr) {
        L.Head = new_tail;
    } else {
        new_tail->Prev = prev_tail;
        prev_tail->Next = new_tail;
    }
    L.Tail = new_tail;
}

