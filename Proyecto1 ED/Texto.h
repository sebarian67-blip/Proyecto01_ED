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

		for (char c : palabra) { //Si es matuscula conviernte a minuscula restando el valor ANSI
			unsigned char uc = static_cast<char>(c);

			if (uc >= 'A' && uc <= 'Z')
				palabraLimpia += static_cast<char>(uc + 32);

			else if (uc >= 'a' && uc <= 'z') //Si es minuscula solamente lo inserta
				palabraLimpia += static_cast<char>(uc);



			else if (uc == 193 || uc == 201 || uc == 205 || uc == 209 || uc == 211 || uc == 218 || uc == 220) { //lo mismo pero con tildes
				palabraLimpia += static_cast<char>(uc + 32);
			}

			else if (uc == 225 || uc == 233 || uc == 237 || uc == 241 || uc == 243 || uc == 250 || uc == 252) {
				palabraLimpia += static_cast<char>(uc);
			}

		}
		return palabraLimpia;
	}

	
public: 
	inline static List<Pair<string, int>>* lista = nullptr; //poder acceder a la lista sin problemas
	inline static List<string>* listaLineas = nullptr;

	static void leer(string nombre) {


		ifstream archivo(nombre); //abrir el archivo


		if (!archivo.is_open()) {
			throw runtime_error("Archivo no encontrado");
		}
		lista = new DLinkedList<Pair<string, int>>(); //crear una lista de Pair
		listaLineas = new DLinkedList<string>();
		string linea;
		int contadorLinea = 0;
		while (getline(archivo, linea)) { //conseguir cada linea del texto
			listaLineas->append(linea);

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
	}

	void liberar() {
		delete lista;
		delete listaLineas;
		lista = nullptr;
		listaLineas = nullptr;
	}
};

