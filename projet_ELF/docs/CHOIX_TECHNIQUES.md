# Choix techniques

## 1. Langage C
Le C a été utilisé pour les programmes de démonstration et les exercices de lecture de fichiers. Il permet de travailler avec les fonctions standard d'ouverture et de lecture, tout en donnant accès aux structures ELF définies par le système.

**Avantages :**
- langage adapté à la programmation système ;
- accès aux fichiers et aux données binaires ;
- compilation native avec GCC ;
- possibilité d'activer les avertissements du compilateur.

## 2. Assembleur NASM x86-64
NASM permet d'écrire des instructions assembleur pour l'architecture x86-64. Le programme de démonstration utilise les appels système Linux pour afficher un message puis quitter.

**Pourquoi ce choix :**
- voir le lien entre registres, instructions et appels système ;
- comprendre le point d'entrée `_start` ;
- observer la production d'un fichier objet puis l'édition de liens.

## 3. GCC
GCC compile les sources C en exécutables natifs.

Commande utilisée comme modèle :

```bash
gcc -Wall -Wextra -Werror bienvenue.c -o bienvenue
```

Les options activent plusieurs avertissements et demandent de traiter les avertissements comme des erreurs, ce qui aide à repérer des problèmes pendant l'apprentissage.

## 4. NASM et GNU ld
NASM transforme le fichier assembleur en fichier objet ELF :

```bash
nasm -f elf64 serveur_test.asm -o serveur_test.o
```

GNU `ld` lie ensuite le fichier objet pour produire l'exécutable :

```bash
ld serveur_test.o -o serveur_test
```

## 5. Outils d'inspection ELF
- `file` : identifie le type de fichier et son format général.
- `readelf -h` : affiche l'en-tête ELF.
- `readelf -l` : affiche les en-têtes de programme.

Ces outils servent à comparer les informations affichées par les programmes d'analyse avec celles des utilitaires système.

## 6. Environnement de travail
Ubuntu sous WSL a été utilisé dans les exercices Linux. Visual Studio Code peut être utilisé pour modifier les fichiers et ouvrir un terminal intégré. Les commandes ci-dessus supposent un environnement Linux compatible ELF.

## 7. Sécurité et périmètre
La démonstration assembleur documentée ici est volontairement limitée à l'affichage d'un message et à la terminaison du processus. Elle ne fournit pas de shell distant. Les essais réseau doivent rester dans un environnement autorisé et contrôlé.

## 8. Points à compléter avant la remise
- relever les versions exactes de GCC, NASM et `ld` ;
- confirmer les noms des fichiers présents ;
- ajouter les résultats réels des tests ;
- préciser la distribution Ubuntu et sa version.
