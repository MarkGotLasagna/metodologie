```toc
```
La seguente gerarchia di classi è scorretta dal punto di vista della gestione delle risorse. Scrivere semplici esempi di codice che evidenzino due distinti comportamenti errati del programma, spiegando il tipo di problema e indicando il punto in cui si viene a creare. Quindi applicare alle classi le modifiche minimali che consentano di evitare tali problemi.

```cpp
// C++ 2003
class Base {
	private:
		int* pi;
		// Assegnamento: privato e non implementato.
		Base& operator=(const Base&);
	public:
		Base() : pi(new int) {}
		Base(const Base& b) : pi(new int) { *pi = *(b.pi); }
		~Base() { delete pi; }
		int foo() { return *pi; }
};
class Derived : public Base {
	private:
		int* pj;
		// Assegnamento: privato e non implementato.
		Derived& operator=(const Derived&);
	public:
		Derived() : pj(new int) {}
		~Derived() { delete pj; }
		int foo() { return *pj + Base::foo(); }
};
```

Il problema che possiamo avvistare, risiede nelle linee di codice della classe `Derived`: abbiamo l'assegnamento per copia per la classe `Base`, mentre per l'altra è quello di default del compilatore che non fa quello che vogliamo (copia profonda del puntatore alla memoria contenente il dato).

Vedere una classe che ridefinisce uno dei 5 metodi speciali, ci segnala subito che qualcosa deve essere tenuto in considerazione. Per risolvere:
- possiamo dire che il costruttore di copia non può essere utilizzato, come nei commenti che sono scritti per l'assegnamento;
- possiamo ridefinire il costruttore di copia proprio come nella classe base.

---

Il codice seguente contiene errori inerenti la corretta gestione delle risorse. Individuare almeno un problema, indicando con precisione la sequenza di eventi che porta alla sua occorrenza.

```cpp
void job() {
	Res* r1 = new Res("res1");
	Res* r2 = new Res("res2");
	try {
		do_task(r1,r2);
	} catch (...) {
		delete res1;
		delete res2;
		throw;
	}
}
```

- Riscritto in base al try/catch
  ```cpp
  
  ```

- Riscritto usando smart pointers
  ```cpp
  #include <memory>
  void job() {
	  std::unique_ptr<Res> r1(new Res("res1"));
	  std::unique_ptr<Res> r2(new Res("res2"));
	  do_task(r1.get(), r2.get());
  }
  ```