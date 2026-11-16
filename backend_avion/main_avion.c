#include <stdio.h>
#include <string.h>
#include "avion.h"

/* Teste un avion avec verifier_avion puis ajouter_avion
   (meme enchainement que le callback du bouton Ajouter) */
   
static void tester_ajout(Avion a)
{
    char msg[100];
    int res;

    if (!verifier_avion(a, msg)) // if return is 0 -> 1  
    {
        printf("ajout de l'avion avec immatriculation : %-7s est - REFUSE - (message de controle) -> %s\n", a.immatriculation, msg);
        return;
    }
    res = ajouter_avion(FICHIER_AVIONS, a);
    if (res == 1)
        printf("ajout %-7s : OK\n", a.immatriculation);
    else if (res == 0)
        printf("ajout %-7s : REFUSE (immatriculation deja presente)\n", a.immatriculation);
    else
        printf("ajout %-7s : ERREUR fichier\n", a.immatriculation);
}

int main(void)
{
    Avion a1 = {"TS-IMB", "Airbus", "A320neo", 186, 2022, 2, "Operationnel", "TUN", 1, 1, 1, {15, 3, 2026}, {15, 9, 2026}, 4200};
    
    Avion a2 = {"TS-LBF", "ATR", "72-600", 70, 2020, 1, "Operationnel", "DJE", 0, 0, 0, {2, 5, 2026}, {2, 11, 2026}, 9800};
    
    Avion faux = {"ts-abc", "Boeing", "737", 160, 2018, 2, "Operationnel", "TUN", 0, 0, 0, {1, 1, 2026}, {1, 6, 2026}, 100};
    

    remove(FICHIER_AVIONS);   /* on repart d'un fichier vide a chaque test */

    printf("=== 1. AJOUTER (+ controles de saisie et unicite) ===\n");
    
    
    tester_ajout(a1);
    afficher_avions(FICHIER_AVIONS); // AJOUT!
    
    tester_ajout(a2);
    afficher_avions(FICHIER_AVIONS); // AJOUT!
    
    tester_ajout(a1);         /* doublon */
    afficher_avions(FICHIER_AVIONS); // PAS D AJOUT!
    
    tester_ajout(faux);       /* immatriculation en minuscules */
    afficher_avions(FICHIER_AVIONS); // PAS D AJOUT !
    
    
    faux.capacite = 900; 
    strcpy(faux.immatriculation, "TS-ABC");
    tester_ajout(faux);       /* capacite hors limites */
    afficher_avions(FICHIER_AVIONS); // PAS D AJOUT !

    printf("\n=== 2. RECHERCHER ===\n");
    
    Avion trouve;
    
    // test recherche cas trouve
    if (chercher_avion(FICHIER_AVIONS, "TS-LBF", &trouve))
        printf("TS-LBF trouve : %s %s, capacite %d\n", trouve.constructeur, trouve.modele, trouve.capacite);
    
    // test recherche cas non trouve
    if (!chercher_avion(FICHIER_AVIONS, "TS-XXX", &trouve))
        printf("TS-XXX : introuvable\n");
    
    printf("\n=== 3. AFFICHER ===\n");
    
    afficher_avions(FICHIER_AVIONS);

    printf("\n=== 4. MODIFIER ===\n");
    
    Avion nouv;
    
    nouv = a2; // take an old avion
    nouv.capacite = 72; // edit it
    strcpy(nouv.etat, "En_Maintenance"); // edit it more
    if (verifier_avion(nouv, msg)) // check the new avion 
        printf("modif TS-LBF : %s\n", modifier_avion(FICHIER_AVIONS, "TS-LBF", nouv) == 1 ? "OK" : "ECHEC");
    
    afficher_avions(FICHIER_AVIONS, "");

    printf("\n=== 4. SUPPRIMER ===\n");
    
    printf("suppr TS-IMB : %s\n", supprimer_avion(FICHIER_AVIONS, "TS-IMB") == 1 ? "OK" : "ECHEC");
    printf("suppr TS-XXX : %s\n", supprimer_avion(FICHIER_AVIONS, "TS-XXX") == 1 ? "OK" : "introuvable");
    
    afficher_avions(FICHIER_AVIONS, "");

    return 0;
}
