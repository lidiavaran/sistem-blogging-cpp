# Sistem Blogging C++

Proiect C++ pentru gestionarea unui sistem de blogging simplu, care permite crearea, modificarea și ștergerea postărilor, precum și interacțiunea cititorilor prin comentarii și reacții.

---

## Descriere

Acest sistem de blogging este implementat în C++ folosind programare orientată pe obiecte. Aplicația oferă funcționalități esențiale pentru gestionarea postărilor și interacțiunea utilizatorilor:

- Crearea, editarea și ștergerea postărilor.
- Adăugarea comentariilor pe postări.
- Reacții tip „love”, „like” și „dislike” la postări.
- Listarea și vizualizarea detaliată a postărilor.
- Salvarea și încărcarea datelor dintr-un fișier text.

---

## Tehnologii și concepte utilizate

- C++17
- Programare orientată pe obiecte (OOP)
- Smart pointers (`std::unique_ptr`)
- Manipularea fișierelor pentru persistența datelor
- STL (Standard Template Library): vectori, string-uri
- Tratarea excepțiilor

---

## Structura proiectului

- **app1.cpp** — Aplicația pentru gestionarea postărilor (Student 1)  
- **app2.cpp** — Aplicația pentru interacțiuni cititor (Student 2)  
- **shared/**  
  - `BlogSystem.cpp` — Implementarea clasei BlogSystem  
  - `BlogSystem.h` — Definiția clasei BlogSystem  
  - `Post.cpp` — Implementarea clasei Post  
  - `Post.h` — Definiția clasei Post  
- **blog_data.txt** — Fișier pentru stocarea postărilor (generat la rulare)  
- **.gitignore** — Fișiere și foldere ignorate de Git  
- **README.md** — Documentația proiectului  

## Compilare

Folosește următoarea comandă pentru a compila proiectul:

```bash
g++ -std=c++17 -Wall -Wextra -g3 app1.cpp shared/BlogSystem.cpp shared/Post.cpp -o output/app1
g++ -std=c++17 -Wall -Wextra -g3 app2.cpp shared/BlogSystem.cpp shared/Post.cpp -o output/app2
```

## Utilizare

### Aplicația pentru gestionarea postărilor (app1)

```bash
./output/app1 create_post "<autor>" "<titlu>" "<conținut>"
./output/app1 edit_post <id> "<titlu_nou>" "<conținut_nou>"
./output/app1 delete_post <id>
./output/app1 view_interactions
```

### Aplicația pentru interacțiuni cititor (app2)

```bash
./output/app2 list_posts
./output/app2 view_post <id>
./output/app2 add_comment <id> "<comentariu>"
./output/app2 react <id> <love|like|dislike>
```

### Exemple:
Adaugă o postare: ./output/app1 create_post "Ion Popescu" "Titlu Postare" "Acesta este conținutul postării."
Adaugă un comentariu la postarea cu id 3: ./output/app2 add_comment 3 "Foarte interesantă postarea!"
Adaugă o reacție de tip "like" la postarea cu id 2: ./output/app2 react 2 like

## Autor
Văran Lidia - https://github.com/lidiavaran

