#pragma once

#include <string>
#include <fstream>
#include "AVLTree.h"

using std::string;
using std::ifstream;
using std::getline;

class ListaIgnorar {
private:
    AVLTree<string>* arbol;

    bool esEspacioBasico(unsigned char c) const {
        return (c == ' ' || c == '\t' || c == '\r' || c == '\n');
    }

    string recortarBordes(const string& texto) const {
        size_t inicio = 0;
        while (inicio < texto.size() && esEspacioBasico(static_cast<unsigned char>(texto[inicio]))) {
            inicio = inicio + 1;
        }

        size_t fin = texto.size();
        while (fin > inicio && esEspacioBasico(static_cast<unsigned char>(texto[fin - 1]))) {
            fin = fin - 1;
        }

        return texto.substr(inicio, fin - inicio);
    }

    string normalizar(const string& palabra) const {
        string recortada = recortarBordes(palabra);
        string resultado = "";
        size_t i = 0;
        while (i < recortada.size()) {
            unsigned char c = static_cast<unsigned char>(recortada[i]);
            if (c >= 'A' && c <= 'Z') {
                resultado += static_cast<char>(c + ('a' - 'A'));
            }
            else {
                resultado += static_cast<char>(c);
            }
            i = i + 1;
        }
        return resultado;
    }

public:
    ListaIgnorar() {
        arbol = new AVLTree<string>();
    }

    ~ListaIgnorar() {
        delete arbol;
    }

    void limpiar() {
        arbol->clear();
    }

    bool cargarDesdeArchivo(const string& rutaArchivo) {
        ifstream archivo(rutaArchivo.c_str());
        bool abierto = archivo.is_open();
        if (abierto) {
            string linea;
            while (getline(archivo, linea)) {
                agregar(linea);
            }
            archivo.close();
        }
        return abierto;
    }

    void agregar(const string& palabra) {
        string limpia = normalizar(palabra);
        if (!limpia.empty()) {
            if (!arbol->contains(limpia)) {
                arbol->insert(limpia);
            }
        }
    }

    bool contiene(const string& palabra) const {
        string limpia = normalizar(palabra);
        bool encontrada = false;
        if (!limpia.empty()) {
            encontrada = arbol->contains(limpia);
        }
        return encontrada;
    }

    int getCantidad() const {
        return arbol->getSize();
    }
};