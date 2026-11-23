#pragma once

#include <stdexcept>
#include <iostream>
#include "List.h"
#include "Util.h"

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class ArrayList : public List<E> {
private:
	E* elements;
	int max;
	int size;
	int pos;

	void resize() { // Se agrega la función de resize para cambiar el tamaño del arreglo y se duplique cuando llegue al maximo de 1024
		int newMax = max * 2;
		E* newElements = new E[newMax];
		for (int i = 0; i < size; i++) {
			newElements[i] = elements[i];
		}
		delete[] elements;
		elements = newElements;
		max = newMax;
	}

public:
	ArrayList(int max = DEFAULT_MAX) {
		if (max < 1)
			throw runtime_error("Invalid max size.");
		elements = new E[max];
		this->max = max;
		size = pos = 0;
	}

	~ArrayList() {
		delete[] elements;
	}

	void insert(E element) {
		if (size == max)
			resize(); // se llama acá 
		for (int i = size - 1; i >= pos; i--)
			elements[i + 1] = elements[i];
		elements[pos] = element;
		size++;
	}

	void append(E element) {
		if (size == max)
			resize(); // acá tambine se llama
		elements[size] = element;
		size++;
	}

	void setElement(E element) {
		if (size == 0)
			throw runtime_error("List is empty");
		if (pos == size)
			throw runtime_error("No ocurrent element.");
		elements[pos] = element;
	}

	E remove() {
		if (size == 0)
			throw runtime_error("List is empty");
		if (pos == size)
			throw runtime_error("No ocurrent element.");
		E result = elements[pos];
		for (int i = pos; i < size - 1; i++)
			elements[i] = elements[i + 1];
		size--;
		return result;
	}

	void clear() {
		pos = size = 0;
	}

	E getElement() {
		if (size == 0)
			throw runtime_error("List is empty");
		if (pos == size)
			throw runtime_error("No ocurrent element.");
		return elements[pos];
	}

	E get(int index) {
		if (index < 0 || index >= size)
			throw runtime_error("Index out of bounds.");
		return elements[index];
	}

	void goToStart() {
		pos = 0;
	}

	void goToEnd() {
		pos = size;
	}

	void goToPos(int pos) {
		if (pos < 0 || pos > size)
			throw runtime_error("Index out of bounds.");
		this->pos = pos;
	}

	void next() {
		if (pos < size)
			pos++;
	}

	void previous() {
		if (pos > 0)
			pos--;
	}

	bool atStart() {
		return pos == 0;
	}

	bool atEnd() {
		return pos == size;
	}

	int getPos() {
		return pos;
	}

	int getSize() {
		return size;
	}

	void print() {
		int y = 1;
		for (int i = 0; i < size; i++) {
			cout << y << ". " << elements[i] << endl;
			y++;
		}
	}
};