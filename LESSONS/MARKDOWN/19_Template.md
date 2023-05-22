```toc
```
# Template
Nello standard del '98 chiamato `class`, il `template` di oggi definisce:
- una famiglia di classi (**class template**), che potrebbero essere "nested";
- una famiglia di funzioni (**function template**), che potrebbero essere "funzioni membro".
## Template di funzione
Si dice di funzione, un template che consente di scrivere un "modello" parametrico per una funzione. Il *nome del template* della funzione sottostante sarebbe `max`; i *parametri di template* invece sono i parametri della funzione, che in questo caso possono essere di qualunque tipo, anche built-in.
```cpp
// dichiarazione pura di un template di funzione
template <typename T>
T max(T a, T b);
```

L'istanza di un template <u>è una funzione</u>, possiamo prendere l'indirizzo di questa istanza per lavorarci ma non possiamo prendere l'indirizzo a cui è associata l'implementazione. Quando istanziamo un template di funzione, lo facciamo fornendo *argomento* del tipo appropriato:
```cpp
void foo(int i0, int i1, double d0, double d1) {
	int m = max<int>(i0,i1);
	double d = max<double>(d0, d1);
}
```

Tecnicamente, c'è un altro procedimento per istanziare un template e ha nome di **specializzazione esplicita**. Ci torna utile quando per esempio ci sono eccezioni alla regola che utilizza la funzione `max()`: l'esempio sotto non funziona bene se abbiamo puntatori a caratteri che vogliamo siano ordinati in modo lessicale ('a' viene prima di 'b'), funziona bene solo per numeri o puntatori.
```cpp
template <typename T>
T max(T a, T b){ return (a>b) ? a : b; }
```
Possiamo fornire versione speciale alternativa in questo modo:
```cpp
// specializzazione esplicita (T = const char*) del template
template <>
const char* max<const char*>(const char* a, const char* b) {
	return strcmp(a,b) > 0;
}
```
`template <>` indica una *specializzazione totale*, perché del tipo parziale non sono ammesse. La versione specializzata viene fatta per questioni di *overloading* che vedremo più avanti: scrivere questi due modi è generalmente equivalente (anzi, consigliato fare il secondo dei casi):
```cpp
// con template totale
template <>
const char* max(const char* a, const char* b) {}
// senza template
const char* max(const char* a, const char* b) {}
```

## Template di classe
```cpp
// dichiarazione pura di template di classe
template <typename T>
class Stack;

// definizione di template di classe
template <typename T>
class Stack {
	public:
		// ...
		void push(const T& t);
		void pop();
		// ...
};
```
Sempre importante distinguere il nome della classe da quello del template.
Una differenza importante è che nel caso delle classi <u>non funziona</u> la <u>deduzione dei parametri di funzione</u>.
```cpp
Stack<int> s1; // istanziazione implicita del tipo Stack<int>

Stack s2 = s1; // ERRORE: tipo non deducibile
auto s2 = s1; // CORRECT: tipo dedotto automaticamente
```
Ovvia a questa regola una sola eccezione: soltanto quando siamo dentro la classe.
```cpp
template <typename T>
class Stack{
	// ...
	Stack& operator=(const Stack&);
};

// out of line definition
template <typename T>
	Stack<T>& // il tipo di ritorno è fuori scope di classe, devo scrivere <T>
	Stack<T>::operator=(const Stack& y) { // parametro in scope di classe
	  Stack tmp = y; // in scope di classe, è sufficiente Stack
	  swap(tmp);
	  return *this;
}
```
## Differenze tra template di funzione e classe
L'istanziazione della funzione viene fatta nell'immediato, quando istanziamo la classe invece, <u>vengono istanziate soltanto le cose che stiamo utilizzando</u>. Si dice che l'istanziazione avviene **on demand** per le classi quando solo i metodi chiamati vengono presi in considerazione.

- Conseguenze negative
  Il codice corrispondente ai calcoli effettuati tra funzioni, potrebbe non essere generato; significa che se non siamo bravi a scrivere test che controllino che le istanziazioni vengano effettuate, il codice compilerà ma senza prelevare tutto il necessario.
- Conseguenze positive
  L'istanziazione avviene solo per funzioni che rispettano i tipi forniti; possono essere usato template che soddisfano meno proprietà di quelle generali.

## Note sulla compilazione
Per il processo di compilazione dei template, vogliamo che il compilatore riesca a vederle. I template seguono le stesse regole delle funzioni inline: tipicamente per risolvere il problema, questi verranno messi negli header file.