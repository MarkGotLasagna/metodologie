```toc
```
# Hello, world!
Con la speranza di avere impostato correttamente il nostro ambiente di programmazione, usando per esempio Visual Studio Code, proviamo a creare un file a nome `helloworld.ccp` contenente le seguenti linee.
```cpp
// g++ -Wall -Wextra helloworld.cpp -o helloworld
#include <iostream>

int main() {
	std::cout << "Hello, world!" << std::endl;
}
```
![[Pasted image 20230221120733.png]]
## Conosciamo il codice?
Poniamoci domande (Q) banali a primo avviso, a cui proviamo a dar risposta (R):
- Q: come mai scrivere parentesi `()` nel `main`? E se mettessimo come "assegnatura" una stringa o un intero?
  R: Quì il linguaggio è stato deciso come essere il più compatibile possibile, seguendo le tecniche ormai passate nel tempo.
- Q: perché il `main` restituisce `int` se non viene restituito nulla a fine funzione?
  R: Il `main` permette di darci la libertà di evitare il *tipo di ritorno*, siccome il compilatore lo inserirà a modo automaticamente (`return 0` per un successo).
- Q: l'operatore `<<` serve per stampare output al terminale, come mai non segnala errore?
  R: perché già incluso nei tipi, siccome automaticamente viene preso in carico avendo passato come parametro un `cout` (come se stessimo aprendo una matriosca)
- Q: come mai includiamo `iostream`?
  R: `iostream` non è una libreria, è un *header file* che ci dice cosa possiamo trovare nella libreria, dove possiamo trovare le *dichiarazioni* associategli (definizione $\neq$ dichiarazione).
  - `cout` non è parte del linguaggio C++, ma piuttosto della libreria (per questo non ha syntax highlighting);
  - la libreria non fa parte del linguaggio, siccome questa raggruppa codice utente;
  - usiamo `< >` per dire al *precompilatore*, di usare il file contenuto nelle cartelle base in cui vengono installate le librerie;
  - al campo di visibilità *scope*, se eliminassimo la dicitura `std`, il compilatore darebbe errore in quanto il *namespace* non sarebbe specificato.
    
    ![[Pasted image 20230221120321.png|600]]


## Conosciamo la compilazione?
Cosa succede quando noi diamo il comando di compilazione?
```
g++ -Wall -Wextra helloworld.cpp -o helloworld
 ^    ^                 ^               ^
 |    |                 |               |
 |    opzioni         sorgente        oggetto
compilatore
```

Quando parliamo di *compilazione*, parliamo del senso in ampiezza:
1) **preprocessing**, guarda i file da compilare come semplici sequenze di caratteri, quindi pochi controlli sono effettuati; prende il file sorgente `helloworld.cpp` e produce un altro file sorgente a nome *unità di traduzione*, la cosa effettiva passata al compilatore per la compilazione. La verità è che sono tanti i sorgenti acquisiti.
2) **processing**, eseguito dal compilatore, che produce codice *assembler* per la nostra macchina (l'oggetto compilato non è "portabile").
3) **assembling**, il codice *assembler* viene preso e generato il *codice oggetto*.
4) **linking**, producente codice *eseguibile* o libreria.

### Preprocessing
Precisare a `g++` l'opzione `-E` ci permette di vedere il file di preprocessing che verrà dato in pasto al compilatore, che se troverà errore, mi dovrà dire dove si trova.

![[Pasted image 20230221123931.png]]
```bash
g++ -E helloworld.cpp -o helloworld.preproc.cpp
```
Il compilatore, compilerà tutte le linee di codice incluse in questo file (che solitamente sono migliaia).
![[Pasted image 20230221123645.png|550]]

### Assembling
Dando l'opzione `-S`, diciamo al compilatore di fermarsi al codice assembler.
Non esistono gli overloading di operatori, non esistono namespace, siccome vengono tutti codificati sul posto.

![[Pasted image 20230221124131.png]]
```bash
g++ -S helloworld.cpp -o helloworld.assembler.cpp
```
Il file in assembly è decisamente più piccolo siccome c'è soltanto il necessario per l'esecuzione.

![[Pasted image 20230221124622.png|550]]

### Compilation
Dando l'opzione `-c`, che dovrebbe essere quella più comune, compilo fino al file binario che poi verrà passato al *linker*.

![[Pasted image 20230221124837.png]]
```bash
g++ -c helloworld.cpp -o helloworld.o
```
Se andiamo a vedere, è tutto in binario.
Possiamo tradurre i simboli con il comando di *name mangling*:
```bash
nm -C helloworld.o
```
![[Pasted image 20230221125127.png]]
> [!note] BIN to HEX usando `hexdump`
> In terminale, possiamo tradurre il codice binario in uno esadecimale usando il comando:
> ```bash
> hexdump -C helloworld.o
> ```
> Notiamo come la stringa "Hello, world!" sia presente, con la sola differenza che è ora in linguaggio macchina, decisamente difficile da leggere se non siamo delle macchine.
> 
> ![[Pasted image 20230221163550.png]]

### Linking
Ultima fase, che possiamo visualizzare con il comando originale visto all'inizio.
```bash
g++ -Wall -Wextra helloworld.cpp -o helloworld
```
Oppure usando il file oggetto:
```bash
g++ -Wall -Wextra helloworld.o -o helloworld
```
Molto piccolo: non c'è dentro tutto perché di default viene usato il *collegamento dinamico*. Possiamo elencare le dipendenze (da soddisfare a tempo di esecuzione) con il comando:
```bash
ldd helloworld
```
![[Pasted image 20230221125854.png]]

---
21-02-2023