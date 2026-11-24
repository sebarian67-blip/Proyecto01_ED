#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include "ArrayList.h"
#include "List.h"
#include "Pair.h"
#include "Trie.h"
#include "TrieNode.h"

using std::string;
using std::cout;
using std::endl;
using std::ofstream;
using std::ostream;

class Salida {
private:
    void imprimirDetallePalabra(
        ostream& out,
        const string& palabra,
        TrieNode* nodo,
        bool incluirLineasCompletas,
        ArrayList<string>* lineasOriginales
    ) const {
        if (nodo == nullptr) {
            out << palabra << " (0 apariciones)" << endl;
            return;
        }

        int frecuencia = nodo->getFrecuencia();
        out << "- " << palabra << " | Apariciones: " << frecuencia << endl;

        List<int>* numsLinea = nodo->getLineas();
        if (numsLinea == nullptr || numsLinea->getSize() == 0) {
            return;
        }

        out << "  Lineas: ";
        numsLinea->goToStart();
        while (!numsLinea->atEnd()) {
            out << numsLinea->getElement();
            numsLinea->next();
            if (!numsLinea->atEnd()) {
                out << ", ";
            }
        }
        out << endl;

        if (incluirLineasCompletas && lineasOriginales != nullptr) {
            int ultimaMostrada = -1;
            numsLinea->goToStart();
            while (!numsLinea->atEnd()) {
                int num = numsLinea->getElement();
                // Evita repetir la misma línea si la palabra sale varias veces en ella
                if (num != ultimaMostrada && num >= 1 && num <= lineasOriginales->getSize()) {
                    out << "    [" << num << "] " << lineasOriginales->get(num - 1) << endl;
                    ultimaMostrada = num;
                }
                numsLinea->next();
            }
        }
    }

public:
    Salida() {}

    string generarNombreArchivoFechaHora() const {
        time_t ahora = time(nullptr);
        tm tiempoLocal;
#if defined(_MSC_VER)
        localtime_s(&tiempoLocal, &ahora);
#else
        tiempoLocal = *localtime(&ahora);
#endif
        char buffer[32];
        std::snprintf(
            buffer,
            sizeof(buffer),
            "%04d-%02d-%02d_%02d_%02d_%02d.txt",
            tiempoLocal.tm_year + 1900,
            tiempoLocal.tm_mon + 1,
            tiempoLocal.tm_mday,
            tiempoLocal.tm_hour,
            tiempoLocal.tm_min,
            tiempoLocal.tm_sec
        );
        return string(buffer);
    }

    //Para la consulta de Top N palabras más utilizadas
    void escribirTop(
        ArrayList<Pair<int, string>>* topPalabras,
        bool guardarEnArchivo,
        const string& rutaCarpeta = ""
    ) const {
        if (topPalabras == nullptr) {
            cout << "No hay datos para mostrar." << endl;
            return;
        }

        int total = topPalabras->getSize();
        ofstream archivo;
        string rutaCompleta;

        if (guardarEnArchivo) {
            string nombreArchivo = generarNombreArchivoFechaHora();
            rutaCompleta = rutaCarpeta.empty() ? nombreArchivo : (rutaCarpeta + nombreArchivo);
            archivo.open(rutaCompleta.c_str());
            if (!archivo.is_open()) {
                cout << "Error al crear el archivo de salida: " << rutaCompleta << endl;
                return;
            }
        }

        ostream& destino = guardarEnArchivo ? static_cast<ostream&>(archivo) : static_cast<ostream&>(cout);

        destino << "=== TOP " << total << " PALABRAS MAS UTILIZADAS ===" << endl;
        for (int i = 0; i < total; i++) {
            Pair<int, string> item = topPalabras->get(i);
            destino << (i + 1) << ". " << item.value << " - " << item.key << endl;
        }

        if (guardarEnArchivo) {
            archivo.close();
            cout << "Salida guardada en: " << rutaCompleta << endl;
        }
    }

    // Para buscar una sola palabra
    void escribirPalabra(
        const string& palabra,
        Trie* trie,
        bool incluirLineasCompletas,
        ArrayList<string>* lineasOriginales,
        bool guardarEnArchivo,
        const string& rutaCarpeta = ""
    ) const {
        ofstream archivo;
        string rutaCompleta;

        if (guardarEnArchivo) {
            string nombreArchivo = generarNombreArchivoFechaHora();
            rutaCompleta = rutaCarpeta.empty() ? nombreArchivo : (rutaCarpeta + nombreArchivo);
            archivo.open(rutaCompleta.c_str());
            if (!archivo.is_open()) {
                cout << "Error al crear el archivo de salida: " << rutaCompleta << endl;
                return;
            }
        }

        ostream& destino = guardarEnArchivo ? static_cast<ostream&>(archivo) : static_cast<ostream&>(cout);
        TrieNode* nodo = (trie != nullptr) ? trie->getNode(palabra) : nullptr;

        if (nodo == nullptr) {
            destino << "La palabra '" << palabra << "' no se encuentra en el texto." << endl;
        }
        else {
            destino << "=== RESULTADO DE BUSQUEDA ===" << endl;
            imprimirDetallePalabra(destino, palabra, nodo, incluirLineasCompletas, lineasOriginales);
        }

        if (guardarEnArchivo) {
            archivo.close();
            cout << "Salida guardada en: " << rutaCompleta << endl;
        }
    }

    //Para listas de palabras 
    void escribirListaPalabras(
        const string& titulo,
        List<string>* palabras,
        Trie* trie,
        bool incluirLineasCompletas,
        ArrayList<string>* lineasOriginales,
        bool guardarEnArchivo,
        const string& rutaCarpeta = ""
    ) const {
        ofstream archivo;
        string rutaCompleta;

        if (guardarEnArchivo) {
            string nombreArchivo = generarNombreArchivoFechaHora();
            rutaCompleta = rutaCarpeta.empty() ? nombreArchivo : (rutaCarpeta + nombreArchivo);
            archivo.open(rutaCompleta.c_str());
            if (!archivo.is_open()) {
                cout << "Error al crear el archivo de salida: " << rutaCompleta << endl;
                return;
            }
        }

        ostream& destino = guardarEnArchivo ? static_cast<ostream&>(archivo) : static_cast<ostream&>(cout);

        destino << "=== " << titulo << " ===" << endl;
        if (palabras == nullptr || palabras->getSize() == 0) {
            destino << "No se encontraron coincidencias." << endl;
        }
        else {
            palabras->goToStart();
            while (!palabras->atEnd()) {
                string p = palabras->getElement();
                TrieNode* nodo = (trie != nullptr) ? trie->getNode(p) : nullptr;
                imprimirDetallePalabra(destino, p, nodo, incluirLineasCompletas, lineasOriginales);
                palabras->next();
            }
        }

        if (guardarEnArchivo) {
            archivo.close();
            cout << "Salida guardada en: " << rutaCompleta << endl;
        }
    }
};