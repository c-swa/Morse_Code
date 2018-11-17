//
//  morseTree.hpp
//  morseCode
//
//  Created by Christopher Swayne on 11/13/18.
//  Copyright © 2018 Christopher Swayne. All rights reserved.
//

#ifndef morseTree_hpp
#define morseTree_hpp

#include <string>
#include <fstream>
#include <iostream>
#include <map>

using namespace std;

struct Node{
    Node* left;
    Node* right;
    
    char data;
    string code;
    
};

class MorseTree{
private:
    Node* root = NULL;
    
    
public:
    MorseTree();
    ~MorseTree();
    Node* getRoot(){
        return root;
    }
    void importTree(ifstream resource);
    
    
};


#endif /* morseTree_hpp */
