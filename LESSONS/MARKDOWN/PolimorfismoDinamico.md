dell'appello 05/07/2022

```cpp
struct Generatore_Doc {
	virtual void stampa(const std::string& s) = 0;
	
	virtual void hyperlink(const std::string& url, const std::string& testo) = 0;
	
	virtual void grassetto(bool mode) = 0;
	
	virtual void corsivo(bool mode) = 0;
	
	// aggiunto salto pagina
	virtual void salto_oagina() = 0;
	
	virtual ~Generatore_Doc();
}
```

```cpp
#include "Generatore_Doc.hh"

struct Generatore_PDF : public Generatore_Doc {
	void stampa(const std::string& s) override;
	void hyperlink(const std::string& url, const std::string& testo) override;
	void grassetto(bool mode) override;
	void corsivo(bool mode) override;
	void salto_pagina() override;
};
```

```cpp
#inlcude "Generatore_Doc.hh"
struct Generatore_HTML : public Generatore_Doc {
	void stampa(const std::string& s) override;
	void hyperlink(const std::string& url, const std::string& testo) override;
	void grassetto(bool mode) override;
	void corsivo(bool mode) override;
	void salto_pagina() override {
		stampa("<HR>"); // simulazione cambio pagina
	}
};
```

```cpp
#inlcude "Generatore_Doc.hh"

void codice_utente(Generatore_Doc* gdoc) {
	gdoc -> hyperlink("htpps://www.unipr.it", "UNIPR");
	gdoc -> salto_pagina();
}
```