#include <iostream>
#include <string>
#include "MaxHeap.h"
#include "Pair.h"

using namespace std;

int main() {
	MaxHeap<Pair<int, string>> heap(2); // empieza pequeño para probar que crece
	heap.insert(Pair<int, string>(3, "casa"));
	heap.insert(Pair<int, string>(10, "perro"));
	heap.insert(Pair<int, string>(7, "árbol"));
	heap.insert(Pair<int, string>(15, "sol"));

	while (!heap.isEmpty()) {
		Pair<int, string> top = heap.removeFirst();
		cout << top.value << " -> " << top.key << endl;
	}
	return 0;
}
