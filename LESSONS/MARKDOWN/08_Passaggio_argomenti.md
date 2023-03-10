```toc
```

# Passaggio degli argomenti
Gli argomenti in C++ così sono passati:
1) per valore tipo `T`
   viene effettuata una copia del valore dell'argomento nel parametro funzione;
   ```cpp
   int main(int argc, char* argv[]) {}
   ```
1) per riferimento a lvalue `const T&` o `T&`
   il parametro della funzione è un riferimento che viene inizializzato con l'argomento stesso, senza effettuare copia
   ```cpp
   void swap(int& a, int& b) {}
   ```

Passiamo per copia oggetti di modeste dimensioni.
Il valore di ritorno della funzione è di solito un passaggio per valore: nel caso dovessimo lavorare con il risultato, una copia dello stesso è necessaria per evitare situazioni "dangling". Possiamo restituire per riferimento, laddove siamo sicuri che il tempo di vita del detto risultato si perpetui.
```cpp
// redefining operator []
class Array {
	public:
		int size() const;
		float& operator[] (int index);
};
int main() {
	Array a;
	for (int i=0; i<a.size(); ++i)
		a[i] = 7;
}

```

---
07/03/2023