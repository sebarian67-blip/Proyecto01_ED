#pragma once
#include "BSTreeDictionary.h"
#include "List.h"

class TrieNode {
public:
	int prefixCount;
	bool isFinal;
	Dictionary<char, TrieNode*>* children;

	TrieNode() {
		prefixCount = 0;
		isFinal = false;
		children = new BSTreeDictionary<char, TrieNode*>();
	}

	~TrieNode() {
		delete children;
	}

	bool contains(char child) {
		return children->contains(child);
	}

	TrieNode* getChild(char child) {
		return children->getValue(child);
	}

	void addChild(char child) {
		children->insert(child, new TrieNode());
	}

	void removeChild(char child) {
		children->remove(child);
	}

	List<char>* getChildren() {
		return children->getKeys();
	}
};