#include <iostream>
#include <string>
#include <set>
#include <chrono>
#include "Trie.h"

using namespace std;

int fallos = 0;
void check(bool ok, string nombre) {
	if (!ok) { fallos++; cout << "FALLO: " << nombre << endl; }
}

string unir(List<string>* l) {
	string r = "";
	l->goToStart();
	while (!l->atEnd()) {
		r += l->getElement() + " ";
		l->next();
	}
	return r;
}

string unirInt(List<int>* l) {
	string r = "";
	l->goToStart();
	while (!l->atEnd()) {
		r += to_string(l->getElement()) + " ";
		l->next();
	}
	return r;
}

int main() {
	Trie t;
	bool lanzo = false;
	try { t.insert("", 1); }
	catch (runtime_error&) { lanzo = true; }
	check(lanzo, "insert vacio lanza");

	t.insert("casa", 1);
	t.insert("casa", 3);
	t.insert("casa", 3);
	check(t.getNode("casa")->getFrecuencia() == 3, "frecuencia casa");
	check(unirInt(t.getNode("casa")->getLineas()) == "1 3 3 ", "lineas casa");
	check(t.prefixCount("casa") == 1 && t.prefixCount("c") == 1 && t.prefixCount("") == 1, "prefixCount palabra repetida");

	t.insert("casas", 2);
	check(t.prefixCount("casa") == 2 && t.prefixCount("cas") == 2, "prefixCount casa/casas");
	check(t.containsWord("casa") && t.containsWord("casas") && !t.containsWord("cas"), "containsWord");
	List<string>* m = t.getMatches("cas");
	check(unir(m) == "casa casas ", "getMatches cas");
	delete m;
	check(t.containsPrefix("cas") && !t.containsPrefix("casa") && !t.containsPrefix("x"), "containsPrefix");
	check(t.getNode("cas") == nullptr && t.getNode("zzz") == nullptr && t.getNode("") == nullptr, "getNode nullptr");

	t.insert("ni\xF1" "o", 4);
	t.insert("\xE1rbol", 5);
	t.insert("zorro", 6);
	t.insert("anda", 7);
	t.insert("\xF1" "and\xFA", 8);
	t.insert("ping\xFC" "ino", 9);
	List<string>* todas = t.getAllWords();
	check(todas->getSize() == 8, "getAllWords tamano");
	string anterior = "";
	bool orden = true;
	todas->goToStart();
	while (!todas->atEnd()) {
		string w = todas->getElement();
		if (!anterior.empty()) {
			bool menor = false;
			size_t n = min(anterior.size(), w.size());
			size_t i = 0;
			while (i < n && anterior[i] == w[i]) i++;
			if (i == n) menor = anterior.size() < w.size();
			else menor = (unsigned char)anterior[i] < (unsigned char)w[i];
			if (!menor) orden = false;
		}
		anterior = w;
		todas->next();
	}
	check(orden, "orden por unsigned char");

	delete todas;

	List<string>* m4 = t.getMatchesByLength(4);
	check(unir(m4) == "anda casa ni\xF1o ", "por longitud 4");
	delete m4;
	List<string>* m5 = t.getMatchesByLength(5);
	check(unir(m5) == "casas zorro \xE1rbol \xF1" "and\xFA ", "por longitud 5");
	delete m5;
	List<string>* m0 = t.getMatchesByLength(0);
	List<string>* m99 = t.getMatchesByLength(99);
	check(m0->getSize() == 0 && m99->getSize() == 0, "longitud 0 y 99");
	delete m0; delete m99;

	t.remove("casa");
	check(!t.containsWord("casa") && t.containsWord("casas"), "remove casa conserva casas");
	check(t.prefixCount("cas") == 1 && t.getNode("casa") == nullptr, "remove casa contadores");
	check(t.getNode("casas")->getFrecuencia() == 1, "casas intacta");
	t.insert("casa", 10);
	check(t.getNode("casa")->getFrecuencia() == 1 && t.prefixCount("cas") == 2, "reinsertar casa");
	t.remove("casas");
	check(t.containsWord("casa") && !t.containsWord("casas") && t.prefixCount("casa") == 1, "remove casas");
	t.remove("casa");
	check(!t.containsPrefix("c") && t.prefixCount("c") == 0, "camino c podado");
	lanzo = false;
	try { t.remove("casa"); }
	catch (runtime_error&) { lanzo = true; }
	check(lanzo, "remove inexistente lanza");
	lanzo = false;
	try { t.remove(""); }
	catch (runtime_error&) { lanzo = true; }
	check(lanzo, "remove vacio lanza");

	t.clear();
	List<string>* vacia = t.getAllWords();
	check(vacia->getSize() == 0 && t.prefixCount("") == 0, "clear");
	delete vacia;
	t.insert("hola", 1);
	check(t.containsWord("hola"), "insertar despues de clear");

	// estres
	t.clear();
	set<string> distintas;
	unsigned long long s = 12345;
	int N = 300000;
	auto ini = chrono::steady_clock::now();
	for (int i = 0; i < N; i++) {
		s = s * 6364136223846793005ULL + 1442695040888963407ULL;
		int len = 2 + (int)((s >> 33) % 7);
		string w = "";
		for (int k = 0; k < len; k++) {
			s = s * 6364136223846793005ULL + 1442695040888963407ULL;
			int r = (int)((s >> 33) % 28);
			w += (char)(r < 26 ? 'a' + r : (r == 26 ? 0xF1 : 0xE1));
		}
		distintas.insert(w);
		t.insert(w, i + 1);
	}
	auto fin = chrono::steady_clock::now();
	cout << "insertar " << N << " palabras: " << chrono::duration_cast<chrono::milliseconds>(fin - ini).count() << " ms" << endl;
	check(t.prefixCount("") == (int)distintas.size(), "estres: total distintas");
	ini = chrono::steady_clock::now();
	List<string>* all = t.getAllWords();
	fin = chrono::steady_clock::now();
	cout << "getAllWords: " << chrono::duration_cast<chrono::milliseconds>(fin - ini).count() << " ms, " << all->getSize() << " palabras" << endl;
	check(all->getSize() == (int)distintas.size(), "estres: getAllWords tamano");
	// comparar con set (set ordena por char con signo; comparo contenido)
	all->goToStart();
	bool todasEstan = true;
	while (!all->atEnd()) { if (!distintas.count(all->getElement())) todasEstan = false; all->next(); }
	check(todasEstan, "estres: contenido");
	delete all;
	int borradas = 0;
	set<string> copia = distintas;
	for (const string& w : copia) {
		if (borradas % 2 == 0) { t.remove(w); distintas.erase(w); }
		borradas++;
	}
	check(t.prefixCount("") == (int)distintas.size(), "estres: total tras borrar");
	List<string>* resto = t.getAllWords();
	check(resto->getSize() == (int)distintas.size(), "estres: tamano tras borrar");
	delete resto;

	cout << (fallos == 0 ? "YEIIII TODAS LAS PRUEBAS OK" : "MALDITA SEA HAY FALLOS") << endl;
	return fallos;
}