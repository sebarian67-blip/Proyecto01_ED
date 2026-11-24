#pragma once
#include <stdexcept>
#include "BSTreeDictionary.h"
#include "DLinkedList.h"
#include "List.h"

class TrieNode {
private:
	int prefixCount;
	bool isFinal;
	Dictionary<unsigned char, TrieNode*>* children;
	DLinkedList<int>* lineas;

public:
	TrieNode(const TrieNode&) = delete;
	void operator=(const TrieNode&) = delete;

	TrieNode() {
		prefixCount = 0;
		isFinal = false;
		children = new BSTreeDictionary<unsigned char, TrieNode*>();
		lineas = nullptr;
	}

	// Borra todo el subárbol
	~TrieNode() {
		List<TrieNode*>* hijos = children->getValues();
		hijos->goToStart();
		while (!hijos->atEnd()) {
			delete hijos->getElement();
			hijos->next();
		}
		delete hijos;
		delete children;
		delete lineas;
	}

	bool getIsFinal() {
		return isFinal;
	}

	// La lista de líneas solo existe mientras el nodo es final.
	void setIsFinal(bool isFinal) {
		if (isFinal && lineas == nullptr)
			lineas = new DLinkedList<int>();
		if (!isFinal && lineas != nullptr) {
			delete lineas;
			lineas = nullptr;
		}
		this->isFinal = isFinal;
	}

	int getPrefixCount() {
		return prefixCount;
	}

	void setPrefixCount(int prefixCount) {
		this->prefixCount = prefixCount;
	}

	void increaseCount() {
		prefixCount++;
	}

	void decreaseCount() {
		prefixCount--;
	}

	bool contains(unsigned char c) {
		return children->contains(c);
	}

	void add(unsigned char c) {
		children->insert(c, new TrieNode());
	}

	// Solo quita la entrada del diccionario
	void remove(unsigned char c) {
		children->remove(c);
	}

	TrieNode* getChild(unsigned char c) {
		return children->getValue(c);
	}

	List<unsigned char>* getChildren() {
		return children->getKeys();
	}

	List<TrieNode*>* getChildrenPointers() {
		return children->getValues();
	}

	void addLinea(int numeroLinea) {
		if (!isFinal)
			throw std::runtime_error("Node is not final.");
		lineas->append(numeroLinea);
	}

	// Lista interna del nodo (nullptr si no es final). No se borra desde afuera.
	List<int>* getLineas() {
		return lineas;
	}

	int getFrecuencia() {
		return lineas == nullptr ? 0 : lineas->getSize();
	}
};