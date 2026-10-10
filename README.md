# 🛡️ Projet ESGI : Infector ELF & Sécurité Offensive

> **Auteurs :** Eddy Mikhael & Klaus  
> **CLASSE:** 3SY3
> **Contexte :** Projet académique de programmation système bas niveau et de sécurité offensive.

---

## 📌 Présentation du Projet

Ce projet implémente un **infector de binaires ELF** sous Linux (architecture x86_64). L'objectif est de démontrer les mécanismes internes de la structure des fichiers exécutables ELF sous Linux et d'illustrer un scénario d'attaque complet de type **Cheval de Troie (Trojan)** intégrant des techniques d'infrastructure **C2 (Command & Control)**, de persistance et d'évasion.

L'outil modifie un binaire sain de manière furtive : 
1. Il convertit un segment inutilisé ou de métadonnées (`PT_NOTE`) en un segment de chargement mémoire exécutable (`PT_LOAD`).
2. Il redirige le point d'entrée du programme (`e_entry`) vers une charge utile (`payload`) personnalisée.
3. Il exécute un faux message de bienvenue (*effet visuel trompeur pour l'utilisateur*) tout en établissant la communication avec l'infrastructure de contrôle.

---

##  Concepts Techniques s

Ce projet met en œuvre les notions fondamentales de la sécurité offensive et de l'analyse de binaires :

* **Infector ELF & Manipulation d'En-têtes :** Modification bas niveau des structures `Elf64_Ehdr` et `Elf64_Phdr`, basculement de segments (`PT_NOTE` $\rightarrow$ `PT_LOAD`) et détournement du point d'entrée (`e_entry`).
* **C2 (Command & Control) & Reverse Shell / Bind Shell :** Mise en place d'une infrastructure de pilotage à distance permettant de reprendre la main sur la machine compromise via des sockets réseau et la duplication des flux (`sys_dup2` / `sys_execve`).
* **Port Knocking & Déclenchement furtif :** Mécanisme de dissimulation de service où le port d'écoute ou la charge utile ne s'active qu'après avoir reçu une séquence spécifique de paquets réseau, évitant la détection par les balayages de ports classiques (Nmap).
* **Furtivité & Comportement de type Trojan :** Restitution d'un affichage légitime (`sys_write` affichant *"Bienvenue en ESGI"* sur le `stdout`) pour tromper l'utilisateur pendant que le processus malveillant s'exécute en arrière-plan.
* **Techniques d'Évasion & Red Team :** Conception de charges utiles en assembleur x86_64 bas niveau visant à contourner l'analyse statique et dynamique de base au sein des environnements Linux.

---

## ⚙️ Fonctionnalités Techniques

- **Manipulation bas niveau des en-têtes ELF :** Analyse et réécriture des structures `Elf64_Ehdr` et `Elf64_Phdr`.
- **Technique `PT_NOTE` $\rightarrow$ `PT_LOAD` :** Contournement intelligent des restrictions d'espace sans corrompre la taille globale du fichier.
- **Payload Assembleur (x86_64) :**
  * Affichage d'un message standard (`sys_write`) garantissant la furtivité comportementale.
  * Initialisation d'une socket réseau (`sys_socket`, `sys_bind`, `sys_listen`, `sys_accept`).
  * Duplication des flux (`sys_dup2`) et exécution d'un shell (`sys_execve`).
- **Vérification et Traçabilité :** Outils de diagnostic intégrés pour valider l'état du binaire avant et après infection.

---

## 📂 Structure du Projet

```text
.
├── cible.c           # Programme légitime de test (affiche le message de bienvenue)
├── infector.c        # Programme principal d'infection et d'analyse des en-têtes ELF
├── serveur.asm       # Code source de la charge utile en Assembleur x86_64 (Payload / Bind Shell)
├── sc.bin            # Shellcode compilé (généré à partir de serveur.asm)
└── README.md         # Documentation du projet
