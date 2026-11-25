#include <iostream>
#include <string>
#include <set>
#include <chrono>
#include <Windows.h>
#include "Trie.h"
#include "Texto.h"

using namespace std;
int main() {
	SetConsoleOutputCP(1252); //ponerlo en la codificacion de ANSI Windows 1252
	Texto lectura;
	lectura.leer("prueba.txt");
	lectura.liberar();
}