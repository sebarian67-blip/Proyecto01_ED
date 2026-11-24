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

	TrieNode* findNode(const string& prefix) {
		TrieNode* current = root;
		for (char ch : prefix) {
			unsigned char c = (unsigned char)ch;
			if (!current->contains(c))
				return nullptr;
			current = current->getChild(c);
		}
		return current;
	}

	void removeAux(TrieNode* current, const string& word, size_t i) {
		current->decreaseCount();
		if (i == word.size()) {
			current->setIsFinal(false);
			return;
		}
		unsigned char c = (unsigned char)word[i];
		TrieNode* child = current->getChild(c);
		removeAux(child, word, i + 1);
		if (child->getPrefixCount() == 0) {
			current->remove(c);
			delete child;
		}
	}

	void getMatchesAux(TrieNode* current, string& actual, List<string>* matches) {
		if (current->getIsFinal())
			matches->append(actual);
		List<unsigned char>* letras = current->getChildren();
		List<TrieNode*>* hijos = current->getChildrenPointers();
		letras->goToStart();
		hijos->goToStart();
		while (!letras->atEnd()) {
			actual.push_back((char)letras->getElement());
			getMatchesAux(hijos->getElement(), actual, matches);
			actual.pop_back();
			letras->next();
			hijos->next();
		}
		delete letras;
		delete hijos;
	}

	void getMatchesByLengthAux(TrieNode* current, int faltan, string& actual, List<string>* matches) {
		if (faltan == 0) {
			if (current->getIsFinal())
				matches->append(actual);
			return;
		}
		List<unsigned char>* letras = current->getChildren();
		List<TrieNode*>* hijos = current->getChildrenPointers();
		letras->goToStart();
		hijos->goToStart();
		while (!letras->atEnd()) {
			actual.push_back((char)letras->getElement());
			getMatchesByLengthAux(hijos->getElement(), faltan - 1, actual, matches);
			actual.pop_back();
			letras->next();
			hijos->next();
		}
		delete letras;
		delete hijos;
	}

public:
	Trie(const Trie&) = delete;
	void operator=(const Trie&) = delete;

	Trie() {
		root = new TrieNode();
	}

	~Trie() {
		delete root;
		root = nullptr;
	}

	void clear() {
		delete root;
		root = new TrieNode();
	}

	bool containsPrefix(string prefix) {
		if (prefix.empty())
			throw runtime_error("Empty prefix.");
		TrieNode* current = findNode(prefix);
		return current != nullptr && !current->getIsFinal();
	}

	bool containsWord(string word) {
		if (word.empty())
			throw runtime_error("Empty word.");
		TrieNode* current = findNode(word);
		return current != nullptr && current->getIsFinal();
	}

	int prefixCount(string prefix) {
		TrieNode* current = findNode(prefix);
		return current == nullptr ? 0 : current->getPrefixCount();
	}

	void insert(string word, int numeroLinea) {
		if (word.empty())
			throw runtime_error("Empty word.");
		TrieNode* current = root;
		for (char ch : word) {
			unsigned char c = (unsigned char)ch;
			if (!current->contains(c))
				current->add(c);
			current = current->getChild(c);
		}
		if (!current->getIsFinal()) {
			// palabra nueva, sube el contador en todo el camino
			TrieNode* aux = root;
			aux->increaseCount();
			for (char ch : word) {
				aux = aux->getChild((unsigned char)ch);
				aux->increaseCount();
			}
			current->setIsFinal(true);
		}
		current->addLinea(numeroLinea);
	}

	void remove(string word) {
		if (word.empty())
			throw runtime_error("Empty word.");
		if (!containsWord(word))
			throw runtime_error("Word not found.");
		removeAux(root, word, 0);
	}

	List<string>* getMatches(string prefix) {
		List<string>* matches = new DLinkedList<string>();
		TrieNode* current = findNode(prefix);
		if (current != nullptr)
			getMatchesAux(current, prefix, matches);
		return matches;
	}

	List<string>* getMatchesByLength(int cantidad) {
		List<string>* matches = new DLinkedList<string>();
		if (cantidad <= 0)
			return matches;
		string actual = "";
		getMatchesByLengthAux(root, cantidad, actual, matches);
		return matches;
	}

	List<string>* getAllWords() {
		return getMatches("");
	}

	// nullptr si la palabra no existe como palabra completa
	TrieNode* getNode(string word) {
		if (word.empty())
			return nullptr;
		TrieNode* current = findNode(word);
		if (current == nullptr || !current->getIsFinal())
			return nullptr;
		return current;
	}
};