//
//  morseTree.cpp
//  morseCode
//
//  Created by Christopher Swayne on 11/13/18.
//  Copyright © 2018 Christopher Swayne. All rights reserved.
//

#include "morseTree.hpp"

MorseTree::MorseTree(){
    root = NULL;
}
MorseTree::~MorseTree(){
    delete root;
    root = NULL;
}
void MorseTree::importTree(ifstream resource){
    map<char, string> morseKeyReference;
    //Create temp values for ifStream, to write to map:morseKeyReference
    char tempReadIn;
    string tempStringIn;
    
    resource >> tempReadIn;
    getline(resource, tempStringIn);
    
    morseKeyReference.insert(pair<char, string>() );
    
}
