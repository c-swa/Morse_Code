//
//  main.cpp
//  morseCode
//
//  Created by Christopher Swayne on 11/13/18.
//	Last edited By Michael Cu on 11/17/18.
//  Copyright © 2018 Christopher Swayne. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "morseTree.hpp"
using namespace std;



void placeNode(string s, node * n, char data, int pos) {
	if (pos >= s.size()) {
		n->data = data;
		cout << "Data: "<< n->data << endl;
		return;
	}

	if (s[pos] == '.') {
		n->left = new node;
		placeNode(s, n->left, data, ++pos);
	}

	else if (s[pos] == '_') {
		n->right = new node;
		placeNode(s, n->right, data, ++pos);
	}
}

void createTree(map<char, string> m, node * n) {
	for (std::map<char, string>::iterator it = m.begin(); it != m.end(); ++it) {
		placeNode(it->second, n, it->first, 0);
	}
}

char searchMorse(string s, node * n, int pos) {
	if (pos >= s.size()) {
		cout << "This is the data: " << n->data << endl;
		return n->data;
	}
	if (s[pos] == '.') {
		searchMorse(s, n->left, ++pos);
	}
	else if (s[pos] == '_') {
		searchMorse(s, n->right, ++pos);
	}
	else {
		return -1;
	}
}

int main() {
	
	ifstream morseCode;
	morseCode.open("morse.txt");
	std::map<char, string> morse;
	string word = "Hello";

	char letter;
	string morseStr;
	while (morseCode.good()) {
		morseCode >> letter >> morseStr;
		morse[tolower(letter)] = morseStr;
		//std::cout << morse.find(letter)->first << " " << morse.find(letter)->second << endl;
	}
	node * root;
	root = new node;
	root->data = NULL;

	createTree(morse, root);
	searchMorse("._", root, 0);
	//cout << root->left->data;
	//cout << endl << "Hello " << searchMorse("._", root, 0)<<endl;


	system("pause");
	morseCode.close();
    return 0;
}
