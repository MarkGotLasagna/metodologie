```toc
```
# Smart Pointers
Un **puntatore intelligente** è un puntatore che applica una soltanto delle regole di gestione delle risorse, che è quella dell'acronimo RRID. Esistono alcuni tipi di puntatori intelligenti:
- unique pointer
  ```cpp
  #include <memory>
  void foo() {
	  std::unique_ptr<int> pi(new int(42));
	  std::unique_ptr<double> pd(new double(3.1415));
	  *pd *= *pi;
  }
  ```
  Un puntatore è unico quando è l'*unico proprietario della risorsa*: nessun altro oggetto associato al puntatore, può lavorare con questo, ma al massimo può essere spostato da un proprietario a un altro.
  ```cpp
  void foo(std::unique_ptr<int> pi);
  void bar() {
	  std::unique<int> pj(new int(42));
	  // foo(pj); ERR: copy not permitted
	  foo(std::move(pj));
  }
  ```
- shared pointer
  Se una risorsa arriva e disponibile, questa risorsa viene gestita da tanti puntatori tenendo conto dell'ultimo che maneggia il dato, tramite un così detto *reference counter*.
  ```cpp
  #include <memory>
  void foo(){
	  std::shared_ptr<int> pi;
	  {
		  std::shared_ptr<int> pj(new int(42));
		  pi = pj;
		  ++()
	  }
  }
  ```