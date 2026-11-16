#ifndef AVION_H
#define AVION_H

#define FICHIER_AVIONS "avions.txt"   /* projet complet : "../data/avions.txt" */
#define FICHIER_TMP "avion-tmp.txt" /* un fichier temporaire pour avion.txt */
/* Projet complet : Date est dans commun.h (partage par l'equipe).
   Ici, version terminal seule : on la met dans avion.h. */
typedef struct {
    int jour, mois, annee;
} Date;

typedef struct {
    char immatriculation[10];   /* cle unique, ex : TS-IMB */
    char constructeur[20];
    char modele[20];
    int  capacite;              /* CapaciteMax de la fonction specifique */
    int  annee_service;
    int  type;                  /* 1 Regional, 2 Moyen-courrier, 3 Long-courrier */
    char etat[20];              /* Operationnel, En_Maintenance, Hors_service */
    char aeroport_attache[4];   /* code IATA, ex : TUN */
    int  wifi, divertissement, business;   /* 0 = non, 1 = oui */
    /* option 1 : suivi de maintenance */
    Date derniere_revision;
    Date prochaine_echeance;
    int  heures_vol;
} Avion;

/* --- CRUD sur le fichier --- */
int ajouter_avion(char *fichier, Avion a);                  /* 1 ok, 0 deja present, -1 fichier */
int modifier_avion(char *fichier, char *immat, Avion nouv); /* 1 ok, 0 introuvable, -1 fichier */
int supprimer_avion(char *fichier, char *immat);            /* 1 ok, 0 introuvable, -1 fichier */
int chercher_avion(char *fichier, char *immat, Avion *a);   /* 1 trouve, 0 sinon */

/* --- Controles de saisie : 1 si valide, sinon 0 + message --- */
int verifier_avion(Avion a, char *message);

/* --- Affichage dans le terminal (filtre "" = tout) ---
   Projet complet : afficher_avions(GtkWidget *treeview, char *fichier, char *filtre) */
void afficher_avions(char *fichier);

#endif
