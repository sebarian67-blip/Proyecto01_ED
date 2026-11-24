#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include"DLinkedList.h"
#include"Pair.h"
#include "Trie.h"
using namespace std;
class Texto {
private:
	static string convertir(string palabra) { //convierte las palabras a minuscula y quita todo lo que no sean leatras validas
		int contador = 0;
		string palabraLimpia; //crear un nuevo string para la palabra arreglada

		for (char c : palabra) { //Si es matuscula conviernte a minuscula restando el valor ASCII
			if (c >= 'A' && c <= 'Z')
				palabraLimpia += c + 32;
			else if (c >= 'a' && c <= 'z') //Si es minuscula solamente lo inserta
				palabraLimpia += c;



			else if (c == -61 || c == -95 || c == -87 || c == -83 || c == -77 || c == -70 || c == -68 || c == -79) {
				palabraLimpia += c;
			}

			else if (c == -127 || c == -119 || c == -115 || c == -109 || c == -102 || c == -100 || c == -111) {
				palabraLimpia += c + 32;
			}

		}
		return palabraLimpia;
	}

	
public: 
	inline static List<Pair<string, int>>* lista = nullptr;


	static void leer(string nombre) {


		ifstream archivo(nombre); //abrir el archivo


		if (!archivo.is_open()) {
			throw runtime_error("Archivo no encontrado");
		}
		lista = new DLinkedList<Pair<string, int>>(); //crear una lista de Pair
		string linea;
		int contadorLinea = 1;
		while (getline(archivo, linea)) { //conseguir cada linea del texto

			for (char& c : linea) { //revisar si hay un guion para separarlo con espacio
				if (c == '-')
					c = ' ';
			}

			stringstream ss(linea); //revisar cada palabra en cada linea
			string palabra;
			while (ss >> palabra) {
				lista->append(Pair(convertir(palabra), contadorLinea)); //inserta el return de convertir y la linea en que aparecio
			}
			contadorLinea++;
		}
		lista->print();
		archivo.close();
		delete lista;
	}

	void liberar() {
		delete lista;
		lista = nullptr;
	}
};

