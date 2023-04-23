```toc
```

# Dichiarazione vs Definizione
## Tipi di dato
- **Dichiarazione** intesa come costrutto del linguaggio che introduce un nome per una entità (abbiamo visto l'esempio di `cout` in `HelloWorld.cpp`). La struttura non la conosco, non posso creare oggetti di tipo `S`.
  ```cpp
  // dichiarazione pura del tipo S
  struct S; // ERROR: incomplete type
  ```
- **Definizione** sottintesa come dichiarazione (siccome introduce un nome), per fornire ulteriore elemento per caratterizzare l'entità (implementazione di `foo()`). Di `T` conosco la struttura e posso creare oggetti di quel tipo.
  ```cpp
  // definizione del tipo T
  struct T { int a; }; // CORRECT
  ```

Essendo linguaggio denso, C++ insiste sul fatto di usare gli stessi caratteri per indicare situazioni totalmente diverse. Nel caso sotto, il compilatore si può chiedere:
```cpp
nome1 * nome2
```
1) `nome1` è puntato dal puntatore `nome2`?
2) operatore binario (moltiplicazione) tre i due valori?

Al compilatore servono indizi sui tipi delle variabili dichiarate (per default assume sia valore), altrimenti ambiguità sussistono alla compilazione, che non andrebbe a buon fine.
> [!example] `enum` del C++ 2011
> Con lo standard introdotto nel 2011, il C++ implementa la possibilità di *dichiarare puramente* un tipo di enumerazione che prima necessitava obbligatoriamente la definizione
> ```cpp
 > enum E : int; // opaque enum declaration
 > enum E : int { a, b, c, d }; // definition
> ```

## Variabili
- dichiarazione pura
  ```cpp
  extern int a; // dichiarazione pura di variabile (globale)
  ```
  Il compilatore sa che esiste una variabile di tipo `int` a nome `a`, che tuttavia ha forma (verrà creata) in qualche altra parte del codice (unità di traduzione)
  ```mermaid
  classDiagram
  mainFile <-- extFile: references
  mainFile <-- extFile1: references
  mainFile <-- extFile2: references
  mainFile : int a = 1
  extFile : extern int a
  extFile1 : extern int a
  extFile2 : extern int a
  ```
  >[!code] `extern "C"`
  >Una situazione simile con l'uso della parola chiave `extern` è il caso in cui volessimo riferirci a una variabile/funzione, dichiarata in un'altra un'unità di traduzione, che usa la convenzione del linguaggio `"C"`
  >```cpp
  >// dichiara variabile globale con C linkage
  >extern "C" int errno;
  >```
- definizione
  ```cpp
  int b; // zero-inizialization 
  int c = 1;
  extern int d = 2; // definizione, perché inizializzata
  ```
  Vengono create le variabili accordate, inizializzate se richiesto

## Funzioni
- dichiarazione pura
  ```cpp
  void foo(int a);
  extern void foo(int a);
  ```
  Commentiamo il fatto che `foo()` ha due dichiarazioni.
  Il *numero* e *tipo* di argomenti della funzione, sono identificanti la stessa: questo permette di distinguere univocamente funzioni che hanno lo stesso nome (cosa a cui al compilatore non importa). Detto "bruttamente": le dichiarazioni pure possono ripetersi tante volte, mentre le definizioni sono uniche (**One Definition Rule**).
- definizione
  ```cpp
  void foo(int a) { // presente il corpo, quindi definizione
	  std::cout << a;
  }
  ```
  Hanno un corpo
## Template
- dichiarazione pura
  ```cpp
  template <typename T> struct S;
  ```
- definizione di template di classe
  ```cpp
  template <typename T>
  struct S {
	  T t;
  };
  ```
- dichiarazione pura di template di funzione
  ```cpp
  template <typename T>
  T add(T t1, T t2);
  ```
- definizione di template di funzione
  ```cpp
  template <typename T>
  T add(T t1, T t2) {
	  return t1 + t2;
  }
  ```

---
`ris:FolderZip` metodologie > `fas:Folder` CODE > `fas:Folder` Declaration_vs_Definition > `fas:FileCode` DeclDef.cpp

---
28/02/2023