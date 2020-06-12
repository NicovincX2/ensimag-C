# Table de Hachage Dynamique

Auteur : Nicolas VINCENT

---

Le sujet se trouve [ici](https://formationc.pages.ensimag.fr/prepa/prof/filrouge/sujetHash/).

Normalement tout se compile avec le `Makefile` d'origine auquel j'ai ajouté quelques flags.

Dans le dossier `src/` il y a un exécutable de mes tests de `directory.c`. Ces tests sont rédigés dans le `main` de `directory.c` qui se trouve après `#ifdef UNIT_TEST`. Il ne compile pas avec les tests du dossier `tests/`. Il faut compiler le fichier `directory.c` avec le flag `-DUNIT_TEST`.

Je n'ai pas effectué de test unitaire des fichiers `hash.c`, `contact.c` et `utils.c`. Les fonctions de ces fichiers sont simples et font leur taff.

J'ai inclu dans `src/` un fichier résultant de `valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./directory`.

Toutes mes structures sont définies et déclarées dans les fichier `.h` présents dans le dossier `include/`. Normalement je n'ai pas modifié de signature mais je ne men rappelle plus trop...

---

Je remercie ceux qui vont réaliser une review de mon code. Certaines parties ne devraient pas poser trop de problème mais d'autres sont moins commentées.

Pour toute question sur mon implémentation n'hésitez pas à me contacter sur `riot` ou par mail (nicolas.vincent@grenoble-inp.org).

---

 - [ ] Séparer le module `contact` en `contact` et `liste_contacts`.