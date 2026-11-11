#include <string.h>
#include "outils.h"
#include "support.h"   /* lookup_widget */

void changer_page(GtkWidget *w, int page)
{
    GtkWidget *nb = lookup_widget(w, "COMnotebookPrincipal");
    gtk_notebook_set_current_page(GTK_NOTEBOOK(nb), page);
}

void changer_onglet(GtkWidget *w, char *nomNotebook, int onglet)
{
    GtkWidget *nb = lookup_widget(w, nomNotebook);
    gtk_notebook_set_current_page(GTK_NOTEBOOK(nb), onglet);
}

void afficher_page(GtkWidget *w, char *nomPage)
{
    GtkWidget *nb = lookup_widget(w, "COMnotebookPrincipal");
    GtkWidget *page = lookup_widget(w, nomPage);
    /* gtk_notebook_page_num donne la position de la page dans le notebook */
    int num = gtk_notebook_page_num(GTK_NOTEBOOK(nb), page);
    if (num != -1)
        gtk_notebook_set_current_page(GTK_NOTEBOOK(nb), num);
}

void afficher_message(GtkWidget *w, char *nomSucces, char *nomErreur,
                      char *texte, int succes)
{
    GtkWidget *ok  = lookup_widget(w, nomSucces);
    GtkWidget *err = lookup_widget(w, nomErreur);
    gtk_label_set_text(GTK_LABEL(succes ? ok : err), texte);
    gtk_label_set_text(GTK_LABEL(succes ? err : ok), "");
}

void lire_texte(GtkWidget *w, char *nom, char *dest, int taille)
{
    strncpy(dest, gtk_entry_get_text(GTK_ENTRY(lookup_widget(w, nom))), taille - 1);
    dest[taille - 1] = '\0';     /* strncpy n'ajoute pas toujours le '\0' */
}

void ecrire_texte(GtkWidget *w, char *nom, char *texte)
{
    gtk_entry_set_text(GTK_ENTRY(lookup_widget(w, nom)), texte);
}

void lire_combo(GtkWidget *w, char *nom, char *dest, int taille)
{
    gchar *txt = gtk_combo_box_get_active_text(GTK_COMBO_BOX(lookup_widget(w, nom)));
    if (txt == NULL)
        dest[0] = '\0';          /* rien n'est choisi */
    else
    {
        strncpy(dest, txt, taille - 1);
        dest[taille - 1] = '\0';
        g_free(txt);             /* GTK a alloue ce texte : on le libere */
    }
}

void choisir_combo(GtkWidget *w, char *nom, char *valeur)
{
    GtkComboBox *cb = GTK_COMBO_BOX(lookup_widget(w, nom));
    GtkTreeModel *model = gtk_combo_box_get_model(cb);
    GtkTreeIter it;
    gchar *txt;
    int i = 0;

    gtk_combo_box_set_active(cb, -1);
    if (gtk_tree_model_get_iter_first(model, &it))
    {
        do {
            gtk_tree_model_get(model, &it, 0, &txt, -1);
            if (strcmp(txt, valeur) == 0)
                gtk_combo_box_set_active(cb, i);
            g_free(txt);
            i++;
        } while (gtk_tree_model_iter_next(model, &it));
    }
}

int lire_spin(GtkWidget *w, char *nom)
{
    return gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(lookup_widget(w, nom)));
}

void ecrire_spin(GtkWidget *w, char *nom, int v)
{
    gtk_spin_button_set_value(GTK_SPIN_BUTTON(lookup_widget(w, nom)), v);
}

int lire_toggle(GtkWidget *w, char *nom)
{
    return gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(lookup_widget(w, nom)));
}

void ecrire_toggle(GtkWidget *w, char *nom, int v)
{
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(lookup_widget(w, nom)), v);
}
