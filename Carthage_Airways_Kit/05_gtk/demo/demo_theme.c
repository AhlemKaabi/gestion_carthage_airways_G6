/* =====================================================================
 * demo_theme.c - Fenetre de TEST du theme Carthage Airways (GTK2)
 * But : verifier sur sa VM que polices + couleurs + images marchent
 *       AVANT de les utiliser dans son projet Glade.
 * Ce n'est PAS du code a rendre : dans le projet, les widgets sont
 * crees par interface.c (genere par Glade).
 * Compilation : make     Lancement : ./demo_theme   (depuis ce dossier)
 * ===================================================================== */
#include <gtk/gtk.h>
#include "../couleurs.h"

int main(int argc, char *argv[])
{
    GtkWidget *fenetre, *vbox, *bandeau, *titre, *entree, *hbox;
    GtkWidget *b_ajouter, *b_annuler, *b_nouveau, *tableau, *msg;
    GtkListStore *store;
    GtkTreeIter it;
    GtkCellRenderer *r;
    const char *titres[3] = {"Matricule", "Modele", "Statut"};
    int i;

    gtk_init(&argc, &argv);
    gtk_rc_parse("../carthage.gtkrc");          /* 1) charger le theme */

    fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(fenetre), "Carthage Airways - test du theme");
    gtk_window_set_icon_from_file(GTK_WINDOW(fenetre),
        "../../01_logo/icone_application_48.png", NULL);
    g_signal_connect(fenetre, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(fenetre), vbox);

    bandeau = gtk_image_new_from_file("../../03_images/bandeau_entete_900x110.png");
    gtk_box_pack_start(GTK_BOX(vbox), bandeau, FALSE, FALSE, 0);

    titre = gtk_label_new("Gestion des avions");
    gtk_widget_set_name(titre, "lbl_titre_avions");     /* -> style ca-titre */
    gtk_box_pack_start(GTK_BOX(vbox), titre, FALSE, FALSE, 0);

    entree = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(entree), "Rechercher un avion...");
    gtk_box_pack_start(GTK_BOX(vbox), entree, FALSE, FALSE, 0);

    hbox = gtk_hbox_new(FALSE, 10);
    b_ajouter = gtk_button_new_with_label("Ajouter");
    b_annuler = gtk_button_new_with_label("Annuler");
    gtk_widget_set_name(b_annuler, "btn_sec_annuler");  /* -> secondaire */
    b_nouveau = gtk_button_new_with_label("+ Nouveau");
    gtk_widget_set_name(b_nouveau, "btn_acc_nouveau");  /* -> accent dore */
    gtk_box_pack_start(GTK_BOX(hbox), b_ajouter, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), b_annuler, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), b_nouveau, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    store = gtk_list_store_new(3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);
    gtk_list_store_append(store, &it);
    gtk_list_store_set(store, &it, 0, "TS-IMA", 1, "Airbus A320", 2, "Actif", -1);
    gtk_list_store_append(store, &it);
    gtk_list_store_set(store, &it, 0, "TS-IMB", 1, "Boeing 737", 2, "Maintenance", -1);
    gtk_list_store_append(store, &it);
    gtk_list_store_set(store, &it, 0, "TS-IMC", 1, "ATR 72", 2, "Actif", -1);

    tableau = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(tableau), TRUE); /* lignes alternees */
    for (i = 0; i < 3; i++) {
        r = gtk_cell_renderer_text_new();
        gtk_tree_view_append_column(GTK_TREE_VIEW(tableau),
            gtk_tree_view_column_new_with_attributes(titres[i], r, "text", i, NULL));
    }
    gtk_box_pack_start(GTK_BOX(vbox), tableau, TRUE, TRUE, 0);

    msg = gtk_label_new("Avion ajoute avec succes.");
    gtk_widget_set_name(msg, "lbl_succes_avion");
    gtk_box_pack_start(GTK_BOX(vbox), msg, FALSE, FALSE, 6);

    gtk_widget_show_all(fenetre);
    gtk_main();
    return 0;
}
