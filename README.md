# Carthage Airways (Guide de démarrage)

Ce guide explique, étape par étape, comment récupérer le projet, créer votre
branche et commencer à travailler dans Glade. Suivez-le dans l'ordre, dans la
VM Ubuntu, dans un terminal.

---

## 1. Configurer Git (une seule fois sur votre machine)

```bash
git config --global user.name "Prénom Nom"
git config --global user.email "votre email github"
```

Git signe chaque commit avec ce nom : c'est comme ça qu'on sait qui a fait quoi.

---

## 2. Cloner le dépôt (une seule fois)

```bash
cd ~
git clone <URL_DU_REPO>
cd <NOM_DU_REPO>
```

Le dépôt est **privé** : GitHub demande votre nom d'utilisateur et, à la place
du mot de passe, un **token** (GitHub → Settings → Developer settings →
Personal access tokens → *Generate new token*, cochez `repo`). Gardez-le.

Vous devez avoir accepté l'invitation au dépôt (mail de GitHub) avant de cloner.

---

## 3. Créer votre branche (une seule fois)

Chacun travaille dans **sa branche**, jamais directement dans `main`.
Nom :`votre-prenom`

```bash
git checkout -b votre-prenom
git push -u origin votre-prenom
```

- `checkout -b` crée la branche et vous place dessus.
- `push -u` l'envoie sur GitHub et la relie à votre branche locale.

Vérifier sur quelle branche vous êtes (avant de travailler) :

```bash
git branch        # la branche active a une étoile *
```

---

## 4. Installer les polices de la charte (une seule fois)

```bash
mkdir -p ~/.fonts
cp carthage_airways_G6/Carthage_Airways_Kit/04_polices/*.ttf ~/.fonts/
fc-cache -fv
fc-list | grep -iE "montserrat|roboto"     # doit afficher les polices
```

---

## 5. Ouvrir le projet dans Glade (à chaque fois)

```bash
./ouvrir_glade.sh
```

Ce script ouvre Glade **avec le thème** Carthage Airways (couleurs, polices).
Si vous lancez `glade-2` directement, tout apparaît gris.

> Si vous avez « Permission denied » : `chmod +x ouvrir_glade.sh` une fois,
> ou lancez `sh ouvrir_glade.sh`.

### Où travailler dans Glade

Vous remplissez **seulement les zones vides de VOS onglets**
(tableau complet dans section 2) :

| Module | Onglet admin | Onglet(s) passager / personnel |
|---|---|---|
| Passagers | Passagers (Gestion) | Esp. passager → Mes infos et fidélité |
| Vols | Vols (Gestion) | Esp. passager → Rechercher un vol |
| Réservations | Réservations (Gestion) | Esp. passager → Réserver un vol, Mes réservations |
| Personnel | Personnel nav. (Gestion) | Esp. personnel → Mes infos, Planning et affectations |
| Avions | Avions (Gestion) | Esp. personnel → Avions |
| Aéroports | Aéroports (Gestion) | Esp. passager → Aéroports |

Dans chaque onglet il y a une **case vide** (hachurée) :

1. Posez-y une **Vertical Box** nommée `[initiales]vbox[Onglet]`
   (ex. `MMvboxVols`), onglet *Packing* : **Expand = Yes**, **Fill = Yes**.
2. Construisez votre écran **dedans**. Tous vos widgets commencent par vos
   initiales (ex. `MMtreeviewVols`, `MMboutonAccAjouterVol`).
3. Pour chaque bouton : *Signals* → `clicked` → **Add**.
4. **Save**, puis **Build**.

**Ne touchez pas** aux widgets qui commencent par `COM` (communs à tous).

---

## 6. Compiler et tester (à chaque modification)

Toujours **depuis `src/`** :

```bash
cd carthage_airways_G6/src
make
./carthage_app
```

Comptes de test : `admin admin123` · `P0001 pass01` · `N0001 pnc01`.

Le code de vos boutons va **à la fin** de `src/callbacks.c` (Glade y ajoute
les fonctions vides). Le reste de votre code va dans **vos** fichiers
(ex. `vol.c` et `vol.h`). Détails : `README.md` §4.

---

## 7. Sauvegarder votre travail sur GitHub (souvent !)

```bash
cd ~/<NOM_DU_REPO>
git status                       # voir ce qui a changé
git add carthage_airways_G6
git commit -m "vols: formulaire d'ajout"
git push
```

Faites un commit à chaque petite étape qui marche : c'est votre **point de
sauvegarde** si quelque chose casse.

---

## 8. Récupérer les mises à jour communes

Quand on vous dit que `main` a changé (ex. une correction du squelette) :

```bash
git checkout main
git pull
git checkout vols-MM
git merge main
```

---

## 9. Règles d'or

1. Toujours vérifier `git branch` avant de travailler : jamais dans `main`.
2. Toujours ouvrir Glade avec `./ouvrir_glade.sh`.
3. Ne jamais modifier `interface.c` ni `support.c` (Glade les réécrit).
4. Ne pas toucher aux widgets `COM…` ni aux fichiers communs sans en parler au groupe.
5. Pas d'accents ni d'espaces dans les noms de fichiers et de widgets.
6. `make` puis `./carthage_app` depuis `src/`, jamais ailleurs.
