```toc
```
# Gestione delle risorse
Una **risorsa** è un qualcosa che vogliamo tracciare, in quantità limitata.
Proprio perché la cosa la vogliamo tracciare, questa è importante perché non vogliamo che scompaia o subisca improvvisa modifica senza nostra volontà.
Linee guida sono specificate per la nostra risorsa, 3 punti vanno seguiti:
1) acquisiamo la risorsa;
2) usiamo la risorsa;
3) restituiamo (rilasciamo) la risorsa.

Esempi di risorse sono:
- i descrittori dei file del file system;
- i lock per l'accesso condiviso o esclusivo a risorse condivise;
- connessioni di rete a server;
- la memoria (`new` & `delete`).

Per aiutarci nella gestione delle risorse, possiamo usare 2 acronimi:
- **RAII** (Resource Acquisition Is Initialization)
  Parla di come una risorsa abbia un lifetime strettamente legato al momento in cui l'oggetto che ne ha bisogno, viene creato. Avere una risorsa con acquisizione e rilascio espliciti, permette di crearci molti meno problemi, specialmente nelle fasi quali debugging o risoluzione dei problemi in generale.
- **RRID** (Resource Release Is Destruction)
  Una risorsa viene distrutta quando è completato il suo uso e non è più necessaria (rilasciata), nell'immediato. Questo ci evita sprechi di memoria, dovuti dal fatto che magari ci siamo dimenticati di distruggere manualmente: una funzione lo fa in automatico.

```cpp
void user_code() { // esempio di codice 'RAII' e 'RRID'
  Resource_management r1;
  use_resource(r1.get());
  {
	  Resource_management r2;
	  use_resource(r1.get(), r2.get());
  }
  Resource_management r3;
  use_resource(r1.get(), r3.get());
}
```

## Exception safety
Se i 3 punti sono seguiti correttamente, abbiamo buona probabilità che la risorsa con cui stiamo lavorando è al sicuro. Siccome tuttavia è anche molto probabile che in qualche modo, qualcosa vada storto, dobbiamo applicare delle "barriere" di sicurezza e in particolare *gestire gli errori* associati alle risorse, per evitare disastri.

Esistono tanti modi per catturare una eccezione; l'esempio più tipico è quello dell'uso del blocco `try-catch`. Scrivere codice che sia **exception safe** è comunque sempre meglio che costruire codice che cattura eccezioni, che sappiamo avrà errori.
Naturalmente, qual'ora il nostro codice necessiti di usare risorse, saremo costretti a  non rispettare la regola e potremmo addirittura non badare a *memory leak*.

> [!warning] Nulla assicura che `do_the_job()` vada a buon fine
>```cpp
>void foo() {
>	int* pi = new int(42); // aquisition
>	do_the_job(pi); // use
>	delete pi; // release
>}
>```

### Livello base
Un codice si può definire sicuro rispetto le eccezioni se sono soddisfatte le condizioni:
- non si hanno perdite di risorse;
- si è neutrali rispetto le eccezioni;
- in caso di uscita eccezionale, gli oggetti con cui si stava lavorando sono distruggibili senza causare comportamenti non definiti.

### LIvello forte
Vengono date granzie aggiuntive: se io scrivo codice sicuro a livello forte, sicuramente ho quelle di livello basi più qualcosa in più, l'*atomicità*. 

### Livello no-throw