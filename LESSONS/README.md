# Cosa contiene la cartella `LESSONS`?
Tutti gli appunti presi a lezione.
Se siete interessati soltanto ai file PDF, per scaricarli eseguite:
```
git clone --filter=blob:none --depth 1 --sparse https://github.com/MarkGotLasagna/metodologie && \
    cd metodologie && \
    git sparse-checkout init --cone && \
    git sparse-checkout set LESSONS/PDF
```