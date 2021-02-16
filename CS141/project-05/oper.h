//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//
// CS141 - Project 05 - oper.h - 11/11/2020
//
// Author: Radison Akerman
// Affiliation: University of Illinois at Chicago
//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//\\//

//
// Declarations of command functions manipulating linked-lists.
//
// Initially by: Prof. Hummel, U. of Illinois Chicago, Fall 2020
// Project 05
//

#include <iostream>
#include <string>

#include "list.h"

using namespace std;

//
// doPrint
//
// Prints each element, one after another, on a single line;
// a space follows each element.
//
void doPrint(List L) {
    cout << "Print: ";
    Node* cur = L.Head;
    while (cur != nullptr) {
        cout << cur->Value << " ";
        cur = cur->Next;
    }
    cout << endl;
}

//
// doSearch
//
// Searches the list for the given value.  If found, a message with
// the value and list position is output on the console.  If not
// found, a "not found" message is output.
//
void doSearch(List L, int value) {
    int pos = search(L, value);
    if (search(L, value) == -1) {
        cout << "Search: value " << value << " " << " not found" << endl;
    } else {
        cout << "Search: value " << value << " " << " found at position " << pos << endl;
    }
}

//
// doInsert
//
// Attempts to insert the value in the List at the specified
// position.  If successful, a message is output on the console
// containing the value and position.  If unsuccessful, the
// exception is caught and the error msg is output to the
// console.  Either way, the list is printed afterwards.
//
void doInsert(List& L, int position, int value) {
    try {
        insert(L, position, value);
        cout << "Insert: value " << value << " successfully inserted at position " << position << endl;
        doPrint(L);
    } catch (const invalid_argument& ia) {
        cout << "Insert: failed ('" << ia.what() << "')" << endl;
        doPrint(L);
    }
}

//
// doRemove
//
// Attempts to remove the node at the specified position from
// the list.  If successful, a message containing the node's
// value and position is output on the console.  If unsuccessful,
// the exception is caught and the error msg is output to the
// console.  Either way, the list is printed afterwards.
//
void doRemove(List& L, int position) {
    try {
        int value = remove(L, position);
        cout << "Remove: value " << value << " successfully removed from position " << position << endl;
        doPrint(L);
    } catch (const invalid_argument& ia) {
        cout << "Remove: failed ('" << ia.what() << "')" << endl;
        doPrint(L);
    }
}

//
// doRotateLeft
//
// Rotates the given list left, meaning the head element is removed
// and then inserted at the tail. The result is that all elements move
// forward ("left") one place.  If the list is empty, nothing happens;
// an empty list is not considered an error.
//
// The list is printed before and after the rotation, with a success
// message in-between.
//
void doRotateLeft(List& L) {
    doPrint(L);
    try {
        push_back(L, pop_front(L));
        cout << "Rotate left: success" << endl;
        doPrint(L);
    } catch (const runtime_error& ia) {
        cout << "Rotate left: success" << endl;
        doPrint(L);
        //cout << "Rotate left: failed ('" << ia.what() << "')" << endl;
    }
}

//
// doRotateRight
//
// Rotates the given list right, meaning the tail element is removed
// and then inserted at the head. The result is that all elements move
// backward ("right") one place.  If the list is empty, nothing happens;
// an empty list is not considered an error.
//
// The list is printed before and after the rotation, with a success
// message in-between.
//
void doRotateRight(List& L) {
    doPrint(L);
    try {
        push_front(L, pop_back(L));
        cout << "Rotate right: success" << endl;
        doPrint(L);
    } catch (const runtime_error& ia) {
        cout << "Rotate right: success" << endl;
        doPrint(L);
        //cout << "Rotate right: failed ('" << ia.what() << "')" << endl;
    }
}

//
// doFree
//
// Frees the nodes in the given list, resetting the list to empty.
// A success message is output to the console, followed by the
// contents of the list to confirm it's empty.
//
void doFree(List& L) {
    free(L);
    cout << "Free: success" << endl;
    doPrint(L);
}

//
// doAppend
//
// Appends the "Other" list to the end of "L".  Afterwards, the
// "Other" list will be empty.  The lists are printed before and
// after the operation, with a success message in-between.
//
void doAppend(List& L, List& Other) {
    doPrint(L);
    doPrint(Other);
    int N = size(Other);
    for (int i = 0; i < N; i++) {
        push_back(L, pop_front(Other));
    }
    cout << "Append: success" << endl;
    doPrint(L);
    doPrint(Other);
}

//
// doMerge
//
// Merges the "Other" list into "L".  Afterwards, the "Other" list
// will be empty.  By merge this means the elements of Other are
// alternated with those of L.  Example: suppose we start with
//    L = [10, 30, 20, 90, 80] and Other = [15, 5, 25]
// Then after doMerge(L, Other):
//    L = [10, 15, 30, 5, 20, 25, 90, 80] and Other = [ ]
// Extra elements after the merge appear at the end of L.
//
// The lists are printed before and after the operation, with a
// success message in-between.
//
void doMerge(List& L, List& Other) {
    doPrint(L);
    doPrint(Other);
    int position = 1;
    int N = size(Other);
    for (int i = 0; i < N; i++) {
        if (size(L) == 0) {
            position = 0;
        }
        insert(L, position, pop_front(Other));
        if (position+1 >= size(L)) {
            position += 1;
        } else {
            position += 2;
        }
    }
    cout << "Merge: success" << endl;
    doPrint(L);
    doPrint(Other);
}

//
// doCopy
//
// The current contents of Dest are free, and then a "deep" copy
// of Src is stored in Dest.  A deep copy means that for each node
// in Dest, a new node is dynamically-allocated and stored in Src.
// This means that after doCopy returns, Dest is a complete and
// distinct copy of Src.
//
// The lists are printed before and after the operation, with a
// success message in-between.
//
void doCopy(List& Dest, List Src) {
    doPrint(Dest);
    doPrint(Src);
    free(Dest);
    int N = size(Src);
    for (int i = 0; i < N; i++) {
        push_back(Dest, ith(Src, i));
    }
    cout << "Copy: success" << endl;
    doPrint(Dest);
    doPrint(Src);
}

//
// doClean
//
// Removes duplicates from L, while preserving the original order.
// The list is printed before and after, along with the # of
// duplicate values that were removed.
//
void doClean(List& L) {
    doPrint(L);
    int count = 0;
    int N = size(L);
    //For each value in the list
    for (int i = 0; i < N; i++) {
        //Loop over the rest of the values in the list
        for (int j = i+1; j < N; j++) {
            //If we find any value after the current position, remove it
            if (ith(L, i) == ith(L, j)) {
                remove(L, j);
                j--;
                N--;
                count++;
            }
        }
    }
    cout << "Clean: success, with " << count << " node(s) removed" << endl;
    doPrint(L);
}

