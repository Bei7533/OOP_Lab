#include <iostream>
#include <stdexcept>
#include "Vector.h"

using namespace std;

int main() {
    // Test default constructor
    Vector<int> v1;
    cout << "v1.size() = " << v1.size() << endl;  // expect 0

    // Test constructor with size parameter
    Vector<int> v2(3);
    cout << "v2.size() = " << v2.size() << endl;  // expect 3
    for(int i=0; i<v2.size(); i++){
        v2[i] = i + 1;
        cout << "v2[" << i << "] = " << v2[i] << endl;
    }

    // Test copy constructor
    Vector<int> v3(v2);
    cout << "v3.size() = " << v3.size() << endl;  // expect 3
    for(int i=0; i<v3.size(); i++){
        cout << "v3[" << i << "] = " << v3[i] << endl;
    }

    // Test push_back
    v3.push_back(4);
    cout << "v3.size() = " << v3.size() << endl;  // expect 4
    cout << "v3[3] = " << v3[3] << endl;          // expect 4

    // Test clear
    v3.clear();
    cout << "v3.size() = " << v3.size() << endl;  // expect 0

    // Test empty
    cout << "v3.empty() = " << v3.empty() << endl;  // expect 1

    // Test at with out of range index
    try{
        v2.at(3);
    }catch(out_of_range& e) {
        cout << "Exception: " << e.what() << endl;  // expect "Index out of range."
    }
    return 0;
}