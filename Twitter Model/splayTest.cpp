#include <iostream>
#include <vector>
#include <ctime>
#include "stdlib.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include "splay_tree.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]){

    string test; 
    SplayTree<int, string> myTree;
    myTree.insert(make_pair(4, "4"));
    myTree.print();
    myTree.insert(make_pair(2, "2"));
    myTree.print();
    myTree.insert(make_pair(5, "5"));
    myTree.print();
    myTree.insert(make_pair(3, "3"));
    myTree.print();
    myTree.insert(make_pair(7, "7"));
    myTree.print();
    myTree.insert(make_pair(4, "10"));
    myTree.print();
    test = myTree[4];
    cout << "Test: " << test << endl;
    test = myTree.get(3);
    cout << "Test: " << test << endl;
    return 0;
    
}