# Projet SY — C, assembleur x86-64 et analyse ELF
EDDY ET CLAUSS
## Présentation
Ce projet pédagogique regroupe des exercices de programmation en C, d'assembleur NASM x86-64 sous Linux et d'observation du format exécutable ELF.

L'objectif est de comprendre les étapes de compilation et d'édition de liens, puis de lire certaines informations contenues dans les fichiers ELF produits.

## Objectifs
- Compiler et exécuter un programme C simple.
- Assembler et lier un programDme NASM x86-64 sous Linux.
- Lire des champs de l'en-tête ELF.
- Parcourir les en-têtes de programme ELF.
- Vérifier les résultats à l'aide des outils système.

## Documentation
- [Architecture du projet](ARCHITECTURE.md)
- [Choix techniques](CHOIX_TECHNIQUES.md)
- [Installation de l'environnement](INSTALLATION.md)
- [Rapport du projet](RAPPORT.md)
- [Simulation et tests](SIMULATION.md)

## Fichiers de code évoqués
Les fichiers ci-dessous ont été évoqués pendant le travail. Vérifier leur présence dans le dossier avant d'exécuter les commandes :
- `bienvenue.c` : affiche `BIENVENUE EN SY`.
- `cible.c` : programme de démonstration affichant `Hello ELF`.
- `lecture_elf.c` : lit certains champs de l'en-tête ELF.
- `analyse_phdr.c` : affiche les en-têtes de programme ELF.
- `serveur_test.asm` : démonstration NASM qui affiche un message puis termine.

Les noms peuvent varier selon la version finale du dossier.

## Démarrage rapide

### Programme C
Si le fichier `bienvenue.c` est présent :

```bash
gcc -Wall -Wextra -Werror bienvenue.c -o bienvenue
./bienvenue
```

Résultat attendu :

```text
BIENVENUE EN SY
```

### Programme assembleur NASM de test
Si le fichier `serveur_test.asm` est présent :

```bash
nasm -f elf64 serveur_test.asm -o serveur_test.o
ld serveur_test.o -o serveur_test
./serveur_test
```

Résultat attendu :

```text
Serveur de test demarre
```

### Inspection d'un exécutable ELF
Après avoir compilé un programme Linux :

```bash
file ./bienvenue
readelf -h ./bienvenue
readelf -l ./bienvenue
```

## Périmètre et sécurité
Les exemples documentés sont destinés à l'apprentissage local. La démonstration assembleur de test affiche un message et se termine ; elle ne crée pas de serveur réseau et n'exécute pas de shell distant.

## Remarque
Les commandes sont prévues pour Ubuntu/WSL. Les versions exactes des logiciels, les chemins et la présence effective des fichiers doivent être vérifiés sur la machine utilisée.
