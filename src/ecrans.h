#ifndef ECRANS_H
#define ECRANS_H

/* Numeros des pages COMMUNES du notebook COMnotebookPrincipal.
   Elles existent deja dans le squelette : leur ordre ne change jamais.
   Ne pas modifier seul. */

/* --- Accueil, connexion et les 3 espaces --- */
#define PAGE_ACCUEIL               0
#define PAGE_CONNEXION             1
#define PAGE_ADMIN                 2
#define PAGE_PASSAGER              3
#define PAGE_PERSONNEL             4

/* --- Onglets "Gestion X" ouverts depuis l'espace Admin --- */
#define PAGE_GESTION_PASSAGERS     5
#define PAGE_GESTION_VOLS          6
#define PAGE_GESTION_RESERVATIONS  7
#define PAGE_GESTION_PERSONNEL     8
#define PAGE_GESTION_AVIONS        9
#define PAGE_GESTION_AEROPORTS    10

/* --- Onglets INTERNES des espaces (notebooks dans la page) --- */
/* COMnotebookPassager */
#define ONGLET_PASSAGER_INFOS         0   /* module passagers    */
#define ONGLET_PASSAGER_VOLS          1   /* module vols         */
#define ONGLET_PASSAGER_RESERVER      2   /* module reservations */
#define ONGLET_PASSAGER_RESERVATIONS  3   /* module reservations */
#define ONGLET_PASSAGER_AEROPORTS     4   /* module aeroports    */

/* COMnotebookPersonnel */
#define ONGLET_PERSONNEL_INFOS        0   /* module personnel    */
#define ONGLET_PERSONNEL_PLANNING     1   /* module personnel    */
#define ONGLET_PERSONNEL_AVIONS       2   /* module avions       */

#endif
