/* =====================================================================
 * couleurs.h  -  Palette Carthage Airways (commune aux 6 modules)
 * Utilisation : #include "couleurs.h" puis appliquer_couleur_fond(...)
 * Les valeurs DOIVENT rester identiques a carthage.gtkrc.
 * ===================================================================== */
#ifndef COULEURS_H
#define COULEURS_H

#include <gtk/gtk.h>

/* Couleurs principales */
#define CA_BLEU_MARINE     "#0B3D6B"   /* principal : boutons, titres, menu  */
#define CA_BLEU_MOYEN      "#2E6EB7"   /* secondaire : survol, selection     */
#define CA_BLEU_CLAIR      "#A7C7E7"   /* accent : en-tetes de tableau       */
#define CA_BLEU_TRES_CLAIR "#F2F7FC"   /* fond des fenetres                  */
#define CA_GRIS_FONCE      "#1F1F1F"   /* texte courant                      */

/* Couleurs d'accent */
#define CA_DORE            "#F5B301"   /* bouton important (Nouveau...)      */
#define CA_VERT            "#2ECC71"   /* succes, statut "Actif"             */
#define CA_ROUGE           "#C0392B"   /* erreur, statut "Bloque"            */

/* Polices (chaine Pango : "Famille Style Taille") */
#define CA_POLICE_TITRE    "Montserrat Bold 18"
#define CA_POLICE_BOUTON   "Montserrat SemiBold 10"
#define CA_POLICE_TEXTE    "Roboto 10"

/* Change la couleur de fond d'un widget (fenetre, eventbox, bouton...).
 * static inline : definie dans le .h sans erreur "multiple definition"
 * quand plusieurs .c incluent ce fichier. */
static inline void appliquer_couleur_fond(GtkWidget *w, const char *hex)
{
    GdkColor c;
    if (gdk_color_parse(hex, &c))
        gtk_widget_modify_bg(w, GTK_STATE_NORMAL, &c);
}

/* Change la couleur du texte d'un label. */
static inline void appliquer_couleur_texte(GtkWidget *label, const char *hex)
{
    GdkColor c;
    if (gdk_color_parse(hex, &c))
        gtk_widget_modify_fg(label, GTK_STATE_NORMAL, &c);
}

#endif /* COULEURS_H */
