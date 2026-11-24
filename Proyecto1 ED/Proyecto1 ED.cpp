// Proyecto1 ED.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//
#include<Windows.h>
#include <iostream>
#include "Texto.h"

using namespace std;
int main()
{	
	SetConsoleOutputCP(CP_UTF8);
	Texto lectura;
	lectura.leer("prueba.txt");
}

