#ifndef AUTH_H
#define AUTH_H

#define FICHIER_UTILISATEURS "../data/utilisateurs.txt"

/* Cherche login + mot de passe dans le fichier.
   Retourne 1 si trouve (et copie le role dans role), 0 sinon,
   -1 si le fichier ne s'ouvre pas. */
int verifier_login(char *fichier, char *login, char *mdp, char *role);

/* Utilisateur connecte (cahier des charges : "identifier le passager /
   le membre connecte"). Rempli a la connexion, vide a la deconnexion. */
void  memoriser_connexion(char *login, char *role);
void  effacer_connexion(void);
char *login_connecte(void);   /* ex. "P0001" ; "" si personne */
char *role_connecte(void);    /* "admin", "passager" ou "personnel" */

#endif
