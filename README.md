# Carthage Airways (Guide de démarrage)

Ce guide explique, étape par étape, comment récupérer le projet, créer votre
branche et commencer à travailler dans Glade. Suivez-le dans l'ordre, dans la
VM Ubuntu, dans un terminal.

---

## 1. Configurer Git (une seule fois sur votre machine)

```bash
git config --global user.name "Prénom Nom"
git config --global user.email "votre.email@esprit.tn"
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
Nom : `module-INITIALES` (ex. `vols-MM`, `avions-AK`).

```bash
