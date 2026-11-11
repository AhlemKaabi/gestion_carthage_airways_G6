#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "ecrans.h"
#include "outils.h"
#include "auth.h"
/* Ajoutez ici le .h de votre module (ex. #include "avion.h") */


/* ======================= PARTIE COMMUNE ============================
   Fenetre, Accueil, Connexion, Admin.
   Ne modifiez ces fonctions qu'apres accord du groupe.
   =================================================================== */

/* ---------------- Fenetre ---------------- */

void
on_COMwindowPrincipale_destroy         (GtkObject       *object,
                                        gpointer         user_data)
{
  gtk_main_quit ();            /* fermer la fenetre = quitter le programme */
}

/* ---------------- Accueil ---------------- */

void
on_COMboutonAccConnexion_clicked       (GtkButton       *button,
                                        gpointer         user_data)
{
  changer_page (GTK_WIDGET (button), PAGE_CONNEXION);
}


void
on_COMboutonSecQuitter_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{
  gtk_main_quit ();
}

/* ---------------- Connexion ---------------- */

/* Ecrit "Connecte : <login>" dans le label d'en-tete d'un espace */
static void afficher_connecte (GtkWidget *w, char *nomLabel, char *login)
{
  char texte[40];
  sprintf (texte, "Connecté : %s", login);
  gtk_label_set_text (GTK_LABEL (lookup_widget (w, nomLabel)), texte);
}

void
on_COMboutonAccValiderConnexion_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *w = GTK_WIDGET (button);
  GtkWidget *labelErr = lookup_widget (w, "COMlabelErreurConnexion");
  char login[20], mdp[20], role[20];
  int res;

  lire_texte (w, "COMtextLogin", login, 20);
  lire_texte (w, "COMtextMdp", mdp, 20);

  if (strlen (login) == 0 || strlen (mdp) == 0)
    {
      gtk_label_set_text (GTK_LABEL (labelErr), "Saisissez le login et le mot de passe.");
      return;
    }

  res = verifier_login (FICHIER_UTILISATEURS, login, mdp, role);

  if (res == -1)
    gtk_label_set_text (GTK_LABEL (labelErr), "Fichier utilisateurs introuvable.");
  else if (res == 0)
    gtk_label_set_text (GTK_LABEL (labelErr), "Login ou mot de passe incorrect.");
  else
    {
      gtk_label_set_text (GTK_LABEL (labelErr), "");
      ecrire_texte (w, "COMtextMdp", "");          /* ne pas garder le mot de passe */

      memoriser_connexion (login, role);            /* qui est connecte ? */

      if (strcmp (role, "admin") == 0)
        changer_page (w, PAGE_ADMIN);
      else if (strcmp (role, "passager") == 0)
        {
          afficher_connecte (w, "COMlabelConnectePassager", login);
          changer_onglet (w, "COMnotebookPassager", ONGLET_PASSAGER_INFOS);
          changer_page (w, PAGE_PASSAGER);
        }
      else if (strcmp (role, "personnel") == 0)
        {
          afficher_connecte (w, "COMlabelConnectePersonnel", login);
          changer_onglet (w, "COMnotebookPersonnel", ONGLET_PERSONNEL_INFOS);
          changer_page (w, PAGE_PERSONNEL);
        }
      else
        gtk_label_set_text (GTK_LABEL (labelErr), "Role inconnu dans le fichier utilisateurs.");
    }
}


void
on_COMboutonSecRetour_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
  changer_page (GTK_WIDGET (button), PAGE_ACCUEIL);
}

/* ---------------- Espace Admin : un bouton par module ----------------
   Chaque bouton ouvre l'onglet "Gestion X" du module.
   Dans TOUS les espaces : le responsable du module peut ajouter UNE ligne
   dans SA fonction, avant changer_page (ex. recharger son treeview). */

void
on_COMboutonAdminPassagers_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
  changer_page (GTK_WIDGET (button), PAGE_GESTION_PASSAGERS);
}


void
on_COMboutonAdminVols_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{
  changer_page (GTK_WIDGET (button), PAGE_GESTION_VOLS);
}


void
on_COMboutonAdminReservations_clicked  (GtkButton       *button,
                                        gpointer         user_data)
{
  changer_page (GTK_WIDGET (button), PAGE_GESTION_RESERVATIONS);
}


void
on_COMboutonAdminPersonnel_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
  changer_page (GTK_WIDGET (button), PAGE_GESTION_PERSONNEL);
}


void
on_COMboutonAdminAvions_clicked        (GtkButton       *button,
                                        gpointer         user_data)
{
  changer_page (GTK_WIDGET (button), PAGE_GESTION_AVIONS);
}


void
on_COMboutonAdminAeroports_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
  changer_page (GTK_WIDGET (button), PAGE_GESTION_AEROPORTS);
}


/* ---------------- Deconnexion ----------------
   Les 3 boutons "Deconnexion" (Admin, Passager, Personnel) utilisent ce handler. */

void
on_COMboutonSecDeconnexion_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
  GtkWidget *w = GTK_WIDGET (button);

  ecrire_texte (w, "COMtextLogin", "");
  gtk_label_set_text (GTK_LABEL (lookup_widget (w, "COMlabelConnectePassager")), "");
  gtk_label_set_text (GTK_LABEL (lookup_widget (w, "COMlabelConnectePersonnel")), "");
  effacer_connexion ();
  changer_page (w, PAGE_ACCUEIL);
}


/* Bouton "Retour" des 6 onglets Gestion : revient a l'espace Admin. */

void
on_COMboutonSecRetourAdmin_clicked     (GtkButton       *button,
                                        gpointer         user_data)
{
  changer_page (GTK_WIDGET (button), PAGE_ADMIN);
}


/* ===================== FIN DE LA PARTIE COMMUNE =====================
   Glade ajoute les nouvelles fonctions vides ci-dessous, a la fin du
   fichier. Ecrivez le code de votre module dans VOS fichiers .c/.h
   et appelez-le depuis ces callbacks.
   =================================================================== */
