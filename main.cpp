//
//  main.cpp
//  morseCode
//
//  Created by Christopher Swayne on 11/13/18.
//    Last edited By Michael Cu on 11/17/18.
//  Copyright © 2018 Christopher Swayne. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <stack>

using std::vector;
using std::string;
using std::map;
using std::ifstream;

using std::cout;
using std::endl;

using std::stack;


struct node
{
    char data;
    struct node *left = NULL;
    struct node *right = NULL;
};



void placeNode(string placeString, node * n, char data, int placePosition) {
    if (placePosition >= placeString.size()) {
        n->data = data;
    }
    
    if (placeString[placePosition] == '.') {
        if (n->left == NULL)
            n->left = new node;
        placeNode(placeString, n->left, data, ++placePosition);
    }
    
    else if (placeString[placePosition] == '_') {
        if (n->right == NULL)
            n->right = new node;
        placeNode(placeString, n->right, data, ++placePosition);
    }
    return;
}

void createTree(std::map<char, string> & m, node * n) {
    for (std::map<char, string>::iterator it = m.begin(); it != m.end(); ++it) {
        placeNode(it->second, n, it->first, 0);
    }
}

char searchMorse(string searchString, node * n, int searchPosition) {
    if ((searchPosition >= searchString.size()) || (n->right == NULL & n->left == NULL)) {
        return n->data;
    }
    if (searchString[searchPosition] == '.') {
        return searchMorse(searchString, n->left, ++searchPosition);
    }
    else if (searchString[searchPosition] == '_') {
        return searchMorse(searchString, n->right, ++searchPosition);
    }
    else
        return -1;
}

int main() {
    
    //Setup input file Stream
    ifstream morseCode;
    morseCode.open("morse.txt");
    if(morseCode.fail()){
        cout << "failed to open file - 'morse.txt'" << endl;
        getchar();
        return 1;
    }
    std::map<char, string> morseMap;
    
    //Reads in from file to the morseMap
    char letter;
    string morseStr;
    while (morseCode.good()) {
        morseCode >> letter >> morseStr;
        morseMap[tolower(letter)] = morseStr;
    }
    node * root;
    root = new node;
    root->data = NULL;
    
    //----------------------------------------------------------
    //Variables defined
    //String to encode
    vector<string> encoder;
    //temp String to store transitional information
    vector<string> temp;
    //Used to decode from morse to 'english'
    vector<char> decoder;
    string encodeString = "hello bass";
    
    
    string delimiter = " ";
    string token;
    int pushPosition = 0;
    string pushString;
    
    while ((pushPosition = encodeString.find(delimiter)) != std::string::npos) {
        
        token = encodeString.substr(0, pushPosition);
        std::cout << token << std::endl;
        
        while (token.length() != 0){
            pushString = morseMap[token[token.size() - 1]];
            encoder.push_back(pushString);
            token.pop_back();
        }
        
        encodeString.erase(0, pushPosition + delimiter.length());
    }
    
    while (encodeString.length() != 0) {
        pushString = morseMap[encodeString[encodeString.size() - 1]];
        encoder.push_back(pushString);
        encodeString.pop_back();
    }
    std::reverse(encoder.begin(), encoder.end());
    
    //prints out the morse code.
    for (int i = 0; i < encoder.size(); i++) {
        std::cout << encoder[i] << endl;
    }
    
    createTree(morseMap, root);
    
    while (encoder.size() != 0) {
        decoder.push_back(searchMorse(string(encoder[encoder.size()-1]), root, 0));
        encoder.pop_back();
    }
    std::reverse(decoder.begin(), decoder.end());
    
    for (int i = 0; i < decoder.size(); i++) {
        std::cout << decoder[i];
    }
    std::cout << endl;
    
    getchar();
    morseCode.close();
    return 0;
}
