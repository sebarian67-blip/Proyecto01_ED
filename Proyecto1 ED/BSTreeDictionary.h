#pragma once
#include <iostream>
#include <stdexcept>

#include "BSTree.h"
#include "Pair.h"
#include "Dictionary.h"

using std::runtime_error;

template <typename K, typename V>
class BSTreeDictionary : public Dictionary<K, V> {
private:
    BSTree<Pair<K, V>>* pairs;

public:
    BSTreeDictionary() {
        pairs = new BSTree<Pair<K, V>>();
    }

    ~BSTreeDictionary() {
        delete pairs;
    }

    void insert(K key, V value) {
        Pair<K, V> p(key, value);
        pairs->insert(p);
    }

    V remove(K key) {
        Pair<K, V> p(key);
        p = pairs->remove(p);
        return p.value;
    }

    V getValue(K key) {
        Pair<K, V> p(key);
        p = pairs->find(p);
        return p.value;
    }

    void setValue(K key, V value) {
        if (!contains(key)) {
            throw runtime_error("Key not found.");
        }
        Pair<K, V> p(key, value);
        pairs->remove(Pair<K, V>(key));
        pairs->insert(p);
    }

    bool contains(K key) {
        Pair<K, V> p(key);
        return pairs->contains(p);
    }

    void clear() {
        pairs->clear();
    }

    bool isEmpty() {
        return pairs->isEmpty();
    }

    List<K>* getKeys() {
        List<Pair<K, V>>* elements = pairs->getElements();
        List<K>* keys = new DLinkedList<K>();
        elements->goToStart();
        while (!elements->atEnd()) {
            Pair<K, V> p = elements->getElement();
            keys->append(p.key);
            elements->next();
        }
        delete elements;
        return keys;
    }

    List<V>* getValues() {
        List<Pair<K, V>>* elements = pairs->getElements();
        List<V>* values = new DLinkedList<V>();
        elements->goToStart();
        while (!elements->atEnd()) {
            Pair<K, V> p = elements->getElement();
            values->append(p.value);
            elements->next();
        }
        delete elements;
        return values;
    }

    int getSize() {
        return pairs->getSize();
    }

    void update(Dictionary<K, V>* D) {
        List<K>* keys = D->getKeys();
        keys->goToStart();
        while (!keys->atEnd()) {
            K k = keys->getElement();
            V v = D->getValue(k);
            if (this->contains(k)) {
                this->setValue(k, v);
            }
            else {
                this->insert(k, v);
            }
            keys->next();
        }
        delete keys;
    }

    void zip(List<K>* keys, List<V>* values) {
        keys->goToStart();
        values->goToStart();
        while (!keys->atEnd() && !values->atEnd()) {
            K k = keys->getElement();
            V v = values->getElement();
            if (this->contains(k)) {
                this->setValue(k, v);
            }
            else {
                this->insert(k, v);
            }
            keys->next();
            values->next();
        }
    }

    void print() {
        pairs->print();
    }
};