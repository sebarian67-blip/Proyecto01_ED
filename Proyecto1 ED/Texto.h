#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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
			else if (c >= 160 && c <= 164 || c == 130) //Si es con tidle, lo inserta
				palabraLimpia += c;

		}
		return palabraLimpia;
	}

	
public:

	static void leer(string nombre) {
		List<Pair<string, int>>* lista;


		ifstream archivo(nombre); //abrir el archivo
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
		delete lista;
	}



	
};

