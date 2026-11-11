# makefile - Carthage Airways (Projet C, ESPRIT)
# Lancer depuis src/ :   make   puis   ./carthage_app
# Rappel : les lignes de commande commencent par une TABULATION.

CC = gcc
CFLAGS = -g -Wall `pkg-config --cflags gtk+-2.0`
LIBS = `pkg-config --libs gtk+-2.0`

# ---- Fichiers communs (ne pas modifier seul) ----
OBJ_COMMUN = main.o interface.o callbacks.o support.o outils.o auth.o

# ---- Fichiers des modules ----
# Chacun remplit SEULEMENT sa ligne (ex. MOD_AVIONS = avion.o)
# et decommente SA regle plus bas.

MOD_PASSAGERS =

MOD_VOLS =

MOD_RESERVATIONS =

MOD_PERSONNEL =

MOD_AVIONS =

MOD_AEROPORTS =

OBJ = $(OBJ_COMMUN) $(MOD_PASSAGERS) $(MOD_VOLS) $(MOD_RESERVATIONS) \
      $(MOD_PERSONNEL) $(MOD_AVIONS) $(MOD_AEROPORTS)

# Edition des liens : tous les .o -> l'executable
carthage_app: $(OBJ)
	$(CC) -o carthage_app $(OBJ) $(LIBS)

# ---- Compilation des fichiers communs (gcc -c) ----
main.o: main.c interface.h support.h
	$(CC) $(CFLAGS) -c main.c

interface.o: interface.c interface.h callbacks.h support.h
	$(CC) $(CFLAGS) -c interface.c

callbacks.o: callbacks.c callbacks.h interface.h support.h ecrans.h outils.h auth.h
	$(CC) $(CFLAGS) -c callbacks.c

support.o: support.c support.h
	$(CC) $(CFLAGS) -c support.c

outils.o: outils.c outils.h support.h
	$(CC) $(CFLAGS) -c outils.c

auth.o: auth.c auth.h
	$(CC) $(CFLAGS) -c auth.c

# ---- Regles des modules (decommentez la votre) ----

# passager.o: passager.c passager.h commun.h
#	$(CC) $(CFLAGS) -c passager.c

# vol.o: vol.c vol.h commun.h
#	$(CC) $(CFLAGS) -c vol.c

# reservation.o: reservation.c reservation.h commun.h
#	$(CC) $(CFLAGS) -c reservation.c

# personnel.o: personnel.c personnel.h commun.h
#	$(CC) $(CFLAGS) -c personnel.c

# avion.o: avion.c avion.h commun.h
#	$(CC) $(CFLAGS) -c avion.c

# aeroport.o: aeroport.c aeroport.h commun.h
#	$(CC) $(CFLAGS) -c aeroport.c

clean:
	rm -f *.o carthage_app
