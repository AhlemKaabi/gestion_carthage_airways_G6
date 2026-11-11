#ifndef OUTILS_H
#define OUTILS_H

#include <gtk/gtk.h>

/* Petites fonctions GTK communes a toute l'equipe.
   w = n'importe quel widget de la fenetre (ex. le bouton clique),
   nom = le nom du widget dans Glade (attention aux majuscules). */

/* Affiche une page COMMUNE par son numero (constantes de ecrans.h) */
void changer_page(GtkWidget *w, int page);

/* Affiche l'onglet numero onglet d'un notebook INTERNE
   (ex. changer_onglet(w, "COMnotebookPassager", ONGLET_PASSAGER_RESERVER)) */
void changer_onglet(GtkWidget *w, char *nomNotebook, int onglet);

/* Affiche la page dont le widget principal s'appelle nomPage
   (ex. afficher_page(w, "AKvboxAvions")). Utilisee pour les modules. */
void afficher_page(GtkWidget *w, char *nomPage);

/* Ecrit texte dans un label vert (succes = 1) ou rouge (succes = 0)
   et vide l'autre label. */
void afficher_message(GtkWidget *w, char *nomSucces, char *nomErreur,
                      char *texte, int succes);

/* Champ texte (GtkEntry) */
void lire_texte(GtkWidget *w, char *nom, char *dest, int taille);
void ecrire_texte(GtkWidget *w, char *nom, char *texte);

/* Liste deroulante (GtkComboBox texte) */
void lire_combo(GtkWidget *w, char *nom, char *dest, int taille);
void choisir_combo(GtkWidget *w, char *nom, char *valeur);

/* Spin button */
int  lire_spin(GtkWidget *w, char *nom);
void ecrire_spin(GtkWidget *w, char *nom, int v);

/* Case a cocher / bouton radio : 1 = coche, 0 = non */
int  lire_toggle(GtkWidget *w, char *nom);
void ecrire_toggle(GtkWidget *w, char *nom, int v);

#endif
