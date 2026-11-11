#include <stdio.h>
#include <string.h>
#include "auth.h"

int verifier_login(char *fichier, char *login, char *mdp, char *role)
{
    FILE *f;
    char l[20], m[20], r[20];

    f = fopen(fichier, "r");
    if (f == NULL)
        return -1;    /* fichier introuvable */

    /* une ligne du fichier = login mot_de_passe role */
    while (fscanf(f, "%19s %19s %19s", l, m, r) == 3) // read entred data!
    {
        if (strcmp(l, login) == 0 && strcmp(m, mdp) == 0) // compare entred data with what we have in the utilisateurs.txt file
        {
            strcpy(role, r); // usning pointers i will store the role of the user logged in
            fclose(f);
            return 1;                   /* trouve */
        }
    }
    fclose(f);
    return 0;                           /* login ou mot de passe faux */
}

/* ---------- Utilisateur connecte ----------
   static : ces 2 variables ne sont visibles que dans auth.c ;
   les autres fichiers passent par les fonctions ci-dessous. */
static char login_actuel[20] = "";
static char role_actuel[20]  = "";

void memoriser_connexion(char *login, char *role)
{
    strncpy(login_actuel, login, 19);
    login_actuel[19] = '\0';
    strncpy(role_actuel, role, 19);
    role_actuel[19] = '\0';
}

void effacer_connexion(void)
{
    login_actuel[0] = '\0';
    role_actuel[0]  = '\0';
}

char *login_connecte(void)
{
    return login_actuel;
}

char *role_connecte(void)
{
    return role_actuel;
}
