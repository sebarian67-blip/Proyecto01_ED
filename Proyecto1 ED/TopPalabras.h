#pragma once

#include <string>
#include "MaxHeap.h"
#include "Pair.h"
#include "ArrayList.h"
#include "List.h"
#include "ListaIgnorar.h"
#include "Trie.h"
#include "TrieNode.h"

using std::string;

class TopPalabras {
private:
    MaxHeap<Pair<int, string>>* heap;

public:
    TopPalabras(int capacidadInicial = 1024) {
        heap = new MaxHeap<Pair<int, string>>(capacidadInicial);
    }

    ~TopPalabras() {
        delete heap;
    }

    void agregarPalabra(const string& palabra, int frecuencia, const ListaIgnorar* ignorar = nullptr) {
        if (frecuencia > 0 && !palabra.empty()) {
            bool estaIgnorada = (ignorar != nullptr && ignorar->contiene(palabra));
            if (!estaIgnorada) {
                heap->insert(Pair<int, string>(frecuencia, palabra));
            }
        }
    }

    void cargarDesdeTrie(Trie* trie, const ListaIgnorar* ignorar = nullptr) {
        limpiar();
        if (trie != nullptr) {
            List<string>* palabras = trie->getAllWords();
            if (palabras != nullptr) {
                palabras->goToStart();
                while (!palabras->atEnd()) {
                    string palabra = palabras->getElement();
                    TrieNode* nodo = trie->getNode(palabra);
                    if (nodo != nullptr) {
                        agregarPalabra(palabra, nodo->getFrecuencia(), ignorar);
                    }
                    palabras->next();
                }
                delete palabras;
            }
        }
    }

    void limpiar() {
        heap->clear();
    }

    int getCantidad() const {
        return heap->getSize();
    }

    ArrayList<Pair<int, string>>* obtenerTop(int n) {
        ArrayList<Pair<int, string>>* resultado = new ArrayList<Pair<int, string>>(n > 0 ? n : 1);
        if (n > 0 && !heap->isEmpty()) {
            ArrayList<Pair<int, string>>* extraidos = new ArrayList<Pair<int, string>>(heap->getSize());
            int contador = 0;

            while (!heap->isEmpty() && contador < n) {
                Pair<int, string> actual = heap->removeFirst();
                resultado->append(actual);
                extraidos->append(actual);
                contador++;
            }

            int i = 0;
            while (i < extraidos->getSize()) {
                heap->insert(extraidos->get(i));
                i = i + 1;
            }

            delete extraidos;
        }
        return resultado;
    }
};