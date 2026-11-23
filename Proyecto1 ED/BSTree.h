#pragma once
#include <iostream>
#include <stdexcept>
#include "BSTNode.h"
#include "DLinkedList.h"

using namespace std;

template <typename E>
class BSTree {
private:
    BSTNode<E>* root;

    BSTNode<E>* insertAux(BSTNode<E>* current, E element) {
        if (current == nullptr)
            return new BSTNode<E>(element);
        if (element == current->element)
            throw runtime_error("Duplicated element.");
        if (element < current->element)
            current->left = insertAux(current->left, element);
        else
            current->right = insertAux(current->right, element);
        return current;
    }

    BSTNode<E>* findNode(BSTNode<E>* current, E element) {
        if (current == nullptr)
            return nullptr;
        if (element == current->element)
            return current;
        if (element < current->element)
            return findNode(current->left, element);
        else
            return findNode(current->right, element);
    }

    BSTNode<E>* findMin(BSTNode<E>* current) {
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    void swapNodes(BSTNode<E>* n1, BSTNode<E>* n2) {
        E temp = n1->element;
        n1->element = n2->element;
        n2->element = temp;
    }

    BSTNode<E>* removeAux(BSTNode<E>* current, E element, E& result) {
        if (current == nullptr)
            throw runtime_error("Element not found.");

        if (element < current->element) {
            current->left = removeAux(current->left, element, result);
            return current;
        }
        if (element > current->element) {
            current->right = removeAux(current->right, element, result);
            return current;
        }

        result = current->element;

        // Caso 0 o 1 hijo
        if (current->childrenCount() == 0) {
            delete current;
            return nullptr;
        }
        if (current->childrenCount() == 1) {
            BSTNode<E>* child = current->onlyChild();
            delete current;
            return child;
        }

        // Caso dos hijos
        E originalResult = result;
        BSTNode<E>* successor = findMin(current->right);
        E temp = successor->element;

        E dummyResult;
        current->right = removeAux(current->right, temp, dummyResult);
        current->element = temp;

        result = originalResult;
        return current;
    }

    void clearAux(BSTNode<E>* current) {
        if (current == nullptr)
            return;
        clearAux(current->left);
        clearAux(current->right);
        delete current;
    }

    void getElementsAux(BSTNode<E>* current, List<E>* elements) {
        if (current == nullptr)
            return;
        getElementsAux(current->left, elements);
        elements->append(current->element);
        getElementsAux(current->right, elements);
    }

    int getSizeAux(BSTNode<E>* current) {
        if (current == nullptr)
            return 0;
        return 1 + getSizeAux(current->left) + getSizeAux(current->right);
    }

public:
    BSTree() {
        root = nullptr;
    }

    ~BSTree() {
        clear();
    }

    void insert(E element) {
        root = insertAux(root, element);
    }

    bool contains(E element) {
        return findNode(root, element) != nullptr;
    }

    E find(E element) {
        BSTNode<E>* result = findNode(root, element);
        if (result == nullptr)
            throw runtime_error("Element not found.");
        return result->element;
    }

    E remove(E element) {
        E result;
        root = removeAux(root, element, result);
        return result;
    }

    void clear() {
        clearAux(root);
        root = nullptr;
    }

    List<E>* getElements() {
        List<E>* elements = new DLinkedList<E>();
        getElementsAux(root, elements);
        return elements;
    }

    bool isEmpty() {
        return root == nullptr;
    }

    int getSize() {
        return getSizeAux(root);
    }

    void print() {
        List<E>* elements = getElements();
        elements->print();
        delete elements;
    }
};