#pragma once

#include <string>
#include <fstream>
#include "AVLTree.h"

using std::string;
using std::ifstream;

class ListaIgnorar {
private:
    AVLTree<string>* arbol;

    string normalizar(const string& palabra) const {
        string resultado = "";
        for (size_t i = 0; i < palabra.size(); i++) {
            unsigned char c = static_cast<unsigned char>(palabra[i]);
            if (c >= 'A' && c <= 'Z') {
                resultado += static_cast<char>(c + ('a' - 'A'));
            }
            else {
                resultado += static_cast<char>(c);
            }
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

    bool cargarDesdeArchivo(const string& rutaArchivo) {
        ifstream archivo(rutaArchivo.c_str());
        if (!archivo.is_open()) {
            return false;
        }

        string palabra;
        while (archivo >> palabra) {
            agregar(palabra);
        }

        archivo.close();
        return true;
    }

    void agregar(const string& palabra) {
        string limpia = normalizar(palabra);
        if (limpia.empty()) {
            return;
        }
        if (!arbol->contains(limpia)) {
            arbol->insert(limpia);
        }
    }

    bool contiene(const string& palabra) const {
        string limpia = normalizar(palabra);
        if (limpia.empty()) {
            return false;
        }
        return arbol->contains(limpia);
    }

    int getCantidad() const {
        return arbol->getSize();
    }
};