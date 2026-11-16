#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "avion.h"

/* ================== Lire / ecrire une ligne ================== */

/* Lit un avion ; retourne 1 si la ligne est complete (18 valeurs) */
static int lire_avion(FILE *f, Avion *a)
{
    int n = fscanf(f, "%9s %19s %19s %d %d %d %19s %3s %d %d %d %d/%d/%d %d/%d/%d %d",
                   a->immatriculation, a->constructeur, a->modele,
                   &a->capacite, &a->annee_service, &a->type,
                   a->etat, a->aeroport_attache,
                   &a->wifi, &a->divertissement, &a->business,
                   &a->derniere_revision.jour, &a->derniere_revision.mois,
                   &a->derniere_revision.annee,
                   &a->prochaine_echeance.jour, &a->prochaine_echeance.mois,
                   &a->prochaine_echeance.annee,
                   &a->heures_vol);
    return n == 18;
}

static void ecrire_avion(FILE *f, Avion a)
{
    fprintf(f, "%s %s %s %d %d %d %s %s %d %d %d %02d/%02d/%04d %02d/%02d/%04d %d\n",
            a.immatriculation, a.constructeur, a.modele,
            a.capacite, a.annee_service, a.type,
            a.etat, a.aeroport_attache,
            a.wifi, a.divertissement, a.business,
            a.derniere_revision.jour, a.derniere_revision.mois, a.derniere_revision.annee,
            a.prochaine_echeance.jour, a.prochaine_echeance.mois, a.prochaine_echeance.annee,
            a.heures_vol);
}

/* ============================ CRUD ============================ */

/*******  CREATE ********/
int ajouter_avion(char *fichier, Avion a, char *message)
{
    FILE *f;
    Avion a_bf; // avion in base de fichier
    int trouver = 0;
    
    /* 1. controles de saisie */
    if (!verifier_avion(a, message))
        return 0;      /* message deja rempli par verifier_avion */

    /* 2. unicite */
    f = fopen(fichier, "r");
    if (f != NULL)
    {
        while (lire_avion(f, &a_bf))
        {
            if (strcmp(a.immatriculation, a_bf.immatriculation) == 0)
	        {
	        
	            trouver = 1; // already existe!
		        break; // break the read of the rest of the file
	        }
        }
	    fclose(f); // close the file after the read AKA after the end of the while loop
    }
    
    if (trouver)
    {
         strcpy(message, "Cette immatriculation existe deja.");
    	return 0; // already exist!
    }
    
    /* 3. ajout a la fin */
    f = fopen(fichier, "a");      /* "a" : (append )ajoute a la fin, cree le fichier si absent (we already checked with the while and the trouve) */ 
    if (f == NULL)
    {
        strcpy(message, "Erreur d'acces au fichier.");
        return -1; // problem opening the file
    }
    
    ecrire_avion(f, a);
    fclose(f);
    
    strcpy(message, "Avion ajoute avec succes.");
    
    return 1;
}

/* Modifier et supprimer : on recopie tout dans un fichier temporaire,
   en remplacant (ou en sautant) la ligne voulue, puis on renomme. */  
   
/*******  UPDATE ********/
int modifier_avion(char *fichier, char *immat, Avion nouv)
{
    FILE *f, *t;
    Avion x;
    int trouve = 0;

    f = fopen(fichier, "r");
    t = fopen(FICHIER_TMP, "w");
    if (f == NULL || t == NULL)
    {
        if (f) fclose(f);
        if (t) fclose(t);
        return -1;
    }
    while (lire_avion(f, &x)) // 
    {
        if (strcmp(x.immatriculation, immat) == 0) // str compare!!
        {
            ecrire_avion(t, nouv);   /* nouvelle version */
            trouve = 1;
        }
        else
            ecrire_avion(t, x);      /* ligne inchangee */
    }
    fclose(f);
    fclose(t);
    remove(fichier);
    rename(FICHIER_TMP, fichier);
    return trouve; // we just modified the avion line! if it is 1.
}

/*******  DELETE ********/
int supprimer_avion(char *fichier, char *immat)
{
    FILE *f, *t;
    Avion x;
    int trouve = 0;

    f = fopen(fichier, "r");
    t = fopen(FICHIER_TMP, "w");
    if (f == NULL || t == NULL)
    {
        if (f) fclose(f);
        if (t) fclose(t);
        return -1;
    }
    while (lire_avion(f, &x))
    {
        if (strcmp(x.immatriculation, immat) == 0)
            trouve = 1;         /* on ne la recopie pas = supprimee */
		// like we just passed that line !
        else
            ecrire_avion(t, x);
    }
    fclose(f);
    fclose(t);
    remove(fichier);
    rename(FICHIER_TMP, fichier);
    return trouve; // the done ! if it is 1.
}

/* ====================== Controles de saisie ====================== */

static int date_valide(Date d) // avoiding multiple definitions!!!! we make sure the function is only accessible by through this file !!!
{
    int jours[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (d.annee % 4 == 0 && (d.annee % 100 != 0 || d.annee % 400 == 0))
        jours[1] = 29;                       /* annee bissextile */
    if (d.mois < 1 || d.mois > 12) return 0; // mois should be between 1 on 12 
    if (d.jour < 1 || d.jour > jours[d.mois - 1]) return 0; // the day should be between 1 and the number in the jours table !!
    return 1;
}

/* -1 si a < b, 0 si egales, 1 si a > b */
static int comparer_dates(Date a, Date b)
{
	/* Making sure the dates are logical a date a should be before date b*/
    long x = a.annee * 10000L + a.mois * 100 + a.jour;
    long y = b.annee * 10000L + b.mois * 100 + b.jour;
    if (x < y) return -1; 
    if (x > y) return 1;
    return 0;
}

static Date aujourdhui(void) // takes no parametrs !!
{
    /* Goal: We need to ask the system about tody's date !!*/

    Date d;
    time_t t = time(NULL); // time() comes from <time.h>
    // It returns the current time as one big number:
    // the number of seconds since 01/01/1970
    // time_t is the type made for that number.
    struct tm *now = localtime(&t); // strauct tm : declared in time.h
    // localtime splits the seconds (the returned number from time() ) into a readable date, in the machine’s time zone.
    d.jour  = now->tm_mday; 
    d.mois  = now->tm_mon + 1;       /* tm_mon va de 0 a 11 */
    d.annee = now->tm_year + 1900;   /* tm_year compte depuis 1900 */
    return d;
}

int verifier_avion(Avion a, char *message)
{
    int i;

    /* immatriculation : TS- suivi de 3 lettres majuscules */
    if (strlen(a.immatriculation) != 6 || strncmp(a.immatriculation, "TS-", 3) != 0)
    {
        strcpy(message, "Immatriculation : format TS-XXX attendu.");
        return 0;
    }
    for (i = 3; i < 6; i++)
        if (a.immatriculation[i] < 'A' || a.immatriculation[i] > 'Z')
        {
            strcpy(message, "Immatriculation : 3 lettres majuscules apres TS-.");
            return 0;
        }
    if (strlen(a.constructeur) == 0 || strlen(a.etat) == 0
        || strlen(a.aeroport_attache) == 0) // should not be vide!
    {
        strcpy(message, "Choisissez constructeur, etat et aeroport.");
        return 0;
    }
    if (strlen(a.modele) == 0 || strchr(a.modele, ' ') != NULL)
    {
        strcpy(message, "Modele obligatoire, sans espace (ex : A320neo).");
        return 0;
    }
    if (a.capacite < 10 || a.capacite > 500)
    {
        strcpy(message, "Capacite entre 10 et 500 places.");
        return 0;
    }
    if (a.annee_service < 1990 || a.annee_service > aujourdhui().annee)
    {
        strcpy(message, "Annee de mise en service invalide.");
        return 0;
    }
    if (!date_valide(a.derniere_revision) || !date_valide(a.prochaine_echeance))
    {
        strcpy(message, "Date de revision ou d'echeance invalide.");
        return 0;
    }
    if (comparer_dates(a.derniere_revision, aujourdhui()) > 0)
    {
        strcpy(message, "La derniere revision ne peut pas etre dans le futur.");
        return 0;
    }
    if (comparer_dates(a.prochaine_echeance, a.derniere_revision) <= 0)
    {
        strcpy(message, "L'echeance doit etre apres la derniere revision.");
        return 0;
    }
    if (a.heures_vol < 0)
    {
        strcpy(message, "Heures de vol >= 0.");
        return 0;
    }
    return 1;
}

/* ================== Affichage (terminal) ================== */


/*******  READ ********/
void afficher_avions(char *fichier)
{
    FILE *f; // at the fopen it will have a cursor 
    Avion a;
    char *types[] = {"?", "Regional", "Moyen-courrier", "Long-courrier"};/* "read only" we won't modify the words .. just a space optimization.. */
    int nb_avion = 0;

    f = fopen(fichier, "r");
    if (f == NULL)
    {
        printf("Fichier %s introuvable (aucun avion cree).\n", fichier);
        return;
    }
    printf("%-7s %-9s %-9s %4s %-15s %-15s %-4s %s\n", "IMMAT", "CONSTR.", "MODELE",
           "CAP", "TYPE", "ETAT", "AERO", "ECHEANCE");
    while (lire_avion(f, &a))
    {
        if (a.type < 1 || a.type > 3) a.type = 0; // if type is not knowen .. should be "?"
        printf("%-7s %-9s %-9s %4d %-15s %-15s %-4s %02d/%02d/%04d\n",
               a.immatriculation, a.constructeur, a.modele, a.capacite,
               types[a.type], a.etat, a.aeroport_attache,
               a.prochaine_echeance.jour, a.prochaine_echeance.mois,
               a.prochaine_echeance.annee);
        nb_avion++;
    }
    fclose(f);
    printf("--> %d avion(s)\n", nb_avion);
}
