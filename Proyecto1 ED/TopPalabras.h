#pragma once

#include <string>
#include "MaxHeap.h"
#include "Pair.h"
#include "ArrayList.h"
#include "ListaIgnorar.h"

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
        if (frecuencia <= 0 || palabra.empty()) {
            return;
        }
        if (ignorar != nullptr && ignorar->contiene(palabra)) {
            return;
        }
        heap->insert(Pair<int, string>(frecuencia, palabra));
    }

    void limpiar() {
        heap->clear();
    }

    int getCantidad() const {
        return heap->getSize();
    }

    ArrayList<Pair<int, string>>* obtenerTop(int n) {
        ArrayList<Pair<int, string>>* resultado = new ArrayList<Pair<int, string>>(n > 0 ? n : 1);
        if (n <= 0 || heap->isEmpty()) {
            return resultado;
        }

        ArrayList<Pair<int, string>>* extraidos = new ArrayList<Pair<int, string>>(heap->getSize());
        int contador = 0;

        while (!heap->isEmpty() && contador < n) {
            Pair<int, string> actual = heap->removeFirst();
            resultado->append(actual);
            extraidos->append(actual);
            contador++;
        }

        for (int i = 0; i < extraidos->getSize(); i++) {
            heap->insert(extraidos->get(i));
        }

        delete extraidos;
        return resultado;
    }
};