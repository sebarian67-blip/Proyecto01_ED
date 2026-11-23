#pragma once

#include <iostream>
#include <stdexcept>
#include <string>
#include "TrieNode.h"
#include "List.h"
#include "DLinkedList.h"

using namespace std;

class Trie {
private:
	TrieNode* root;

	TrieNode* findNode(string prefix) {
		TrieNode* current = root;
		for (char c : prefix) {
			if (!current->contains(c)) {
				return nullptr;
			}
			current = current->getChild(c);
		}
		return current;
	}

	void clearAux(TrieNode* current) {
		if (current == nullptr) return;
		List<char>* children = current->getChildren();
		children->goToStart();
		while (!children->atEnd()) {
			clearAux(current->getChild(children->getElement()));
			children->next();
		}
		delete children;
		delete current;
	}

	void getMatchesAux(TrieNode* current, string prefix, List<string>* matches) {
		if (current == nullptr) return;
		if (current->isFinal) {
			matches->append(prefix);
		}
		List<char>* children = current->getChildren();
		children->goToStart();
		while (!children->atEnd()) {
			char c = children->getElement();
			getMatchesAux(current->getChild(c), prefix + c, matches);
			children->next();
		}
		delete children;
	}

public:
	Trie() {
		root = new TrieNode();
	}

	~Trie() {
		clearAux(root);
		root = nullptr;
	}

	void clear() {
		clearAux(root);
		root = new TrieNode();
	}

	bool containsPrefix(string prefix) {
		TrieNode* current = findNode(prefix);
		return current != nullptr;
	}

	bool containsWord(string word) {
		TrieNode* current = findNode(word);
		return current != nullptr && current->isFinal;
	}

	int prefixCount(string prefix) {
		TrieNode* current = findNode(prefix);
		return current == nullptr ? 0 : current->prefixCount;
	}

	void insert(string word) {
		if (containsWord(word))
			throw runtime_error("Duplicated word");
		TrieNode* current = root;
		for (char c : word) {
			current->prefixCount++;
			if (!current->contains(c))
				current->addChild(c);
			current = current->getChild(c);
		}
		current->prefixCount++;
		current->isFinal = true;
	}

	void remove(string word) {
		if (!containsWord(word))
			throw runtime_error("Word not found.");
		TrieNode* current = root;
		for (char c : word) {
			TrieNode* child = current->getChild(c);
			current->prefixCount--;
			if (child->prefixCount == 1) {
				current->removeChild(c);
				clearAux(child);
				return;
			}
			current = child;
		}
		current->prefixCount--;
		current->isFinal = false;
		if (current->prefixCount == 0 && current != root) {
			delete current;
		}
	}

	List<string>* getMatches(string prefix) {
		List<string>* matches = new DLinkedList<string>();
		TrieNode* current = findNode(prefix);
		if (current != nullptr) {
			getMatchesAux(current, prefix, matches);
		}
		return matches;
	}
};