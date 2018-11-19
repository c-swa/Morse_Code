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
#include <vector>

using namespace std;

struct node
{
	char data;
	struct node *left = NULL;
	struct node *right = NULL;
};



void placeNode(string s, node * n, char data, int pos) {
	if (pos >= s.size()) {
		n->data = data;
	}

	if (s[pos] == '.') {
		if (n->left == NULL)
			n->left = new node;
		placeNode(s, n->left, data, ++pos);
	}

	else if (s[pos] == '_') {
		if (n->right == NULL)
			n->right = new node;
		placeNode(s, n->right, data, ++pos);
	}
	return;
}

void createTree(map<char, string> & m, node * n) {
	for (std::map<char, string>::iterator it = m.begin(); it != m.end(); ++it) {
		placeNode(it->second, n, it->first, 0);
	}
}

char searchMorse(string s, node * n, int pos) {
	if ((pos >= s.size()) || (n->right == NULL & n->left == NULL)) {
		return n->data;
	}
	if (s[pos] == '.') {
		return searchMorse(s, n->left, ++pos);
	}
	else if (s[pos] == '_') {
		return searchMorse(s, n->right, ++pos);
	}
	else
		return -1;
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
	}
	node * root;
	root = new node;
	root->data = NULL;


	vector<string> e;
	vector<string> temp;
	vector<char> d;
	std::string encode = "ass hello bass";


	std::string delimiter = " ";
	std::string token;
	int pos = 0;
	string s;

	while ((pos = encode.find(delimiter)) != std::string::npos) {

		token = encode.substr(0, pos);
		std::cout << token << std::endl;

		for (int i = token.length(); i > 0; i--) {
			s = morse[token[token.size() - 1]];
			e.push_back(s);
			token.pop_back();
		}

		encode.erase(0, pos + delimiter.length());
	}

	for (int i = encode.length(); i > 0; i--) {
		s = morse[encode[encode.size() - 1]];
		e.push_back(s);
		encode.pop_back();
	}
	std::reverse(e.begin(), e.end());


	for (int i = 0; i < e.size(); i++) {
		std::cout << e[i] << endl;
	}

	createTree(morse, root);

	while (e.size() != 0) {
		d.push_back(searchMorse(string(e[e.size()-1]), root, 0));
		e.pop_back();
	}
	std::reverse(d.begin(), d.end());

	for (int i = 0; i < d.size(); i++) {
		std::cout << d[i];
	}
	std::cout << endl;

	getchar();
	morseCode.close();
    return 0;
}
