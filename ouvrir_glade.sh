#!/bin/sh
# ---------------------------------------------------------------------
# ouvrir_glade.sh - Ouvre le projet dans Glade AVEC le theme Carthage Airways
#
# Pourquoi ce script ?
#   Le theme (couleurs, polices) est charge par main.c avec
#   gtk_rc_parse("../carthage.gtkrc"). Glade n'execute jamais main.c :
#   lance normalement, il affiche donc des widgets gris.
#   Ce script donne le fichier de theme a Glade des son demarrage.
#
# Utilisation (une fois : chmod +x ouvrir_glade.sh) :
#   ./ouvrir_glade.sh
# ---------------------------------------------------------------------

# Ligne 1 du script (#!/bin/sh) : dit a Linux d'executer ce fichier
# avec le shell /bin/sh.

# cd "$(dirname "$0")"
#   $0         = le chemin de ce script (ex. ~/projet/carthage_airways_G6/ouvrir_glade.sh)
#   dirname    = garde seulement le dossier (ex. ~/projet/carthage_airways_G6)
#   $( ... )   = remplace la commande par son resultat
#   cd         = on se place dans ce dossier
#   -> le script marche quel que soit le dossier d'ou on le lance.
cd "$(dirname "$0")"

# GTK2_RC_FILES="$PWD/carthage.gtkrc" glade-2 carthage_airways_g6.glade &
#   GTK2_RC_FILES=...         variable lue par GTK2 au demarrage : la liste
#                             des fichiers de theme a charger. Ecrite AVANT
#                             la commande, elle ne vaut que pour cette commande
#                             (le reste du systeme n'est pas modifie).
#   $PWD                      le dossier courant (carthage_airways_G6), donc
#                             "$PWD/carthage.gtkrc" = chemin complet du theme.
#   glade-2                   lance Glade 2.12.2.
#   carthage_airways_g6.glade le projet a ouvrir.
#   &                         lance Glade en arriere-plan : le terminal reste
#                             libre (pour make, git...).
GTK2_RC_FILES="$PWD/carthage.gtkrc" glade-2 carthage_airways_g6.glade &
