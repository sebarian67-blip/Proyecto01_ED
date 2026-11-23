#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include "ArrayList.h"
#include "Pair.h"

using std::string;
using std::cout;
using std::endl;
using std::ofstream;

class Salida {
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

        if (!guardarEnArchivo) {
            cout << " TOP " << total << " PALABRAS MAS UTILIZADAS " << endl;
            for (int i = 0; i < total; i++) {
                Pair<int, string> item = topPalabras->get(i);
                cout << (i + 1) << ". " << item.value << " - " << item.key << endl;
            }
            return;
        }

        string nombreArchivo = generarNombreArchivoFechaHora();
        string rutaCompleta = rutaCarpeta.empty() ? nombreArchivo : (rutaCarpeta + nombreArchivo);

        ofstream archivo(rutaCompleta.c_str());
        if (!archivo.is_open()) {
            cout << "Error al crear el archivo de salida: " << rutaCompleta << endl;
            return;
        }

        archivo << " TOP " << total << " PALABRAS MAS UTILIZADAS " << endl;
        for (int i = 0; i < total; i++) {
            Pair<int, string> item = topPalabras->get(i);
            archivo << (i + 1) << ". " << item.value << " - " << item.key << endl;
        }
        archivo.close();

        cout << "Salida guardada en: " << rutaCompleta << endl;
    }
};