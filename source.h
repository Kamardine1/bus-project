#ifndef NOS_FONCTIONS_H_INCLUDED
#define NOS_FONCTIONS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "types.h"
#include "listeDouble.h"
#include "Tri.h"

bool compCout_S1_sup_S2(Tstation* s1,Tstation* s2);
bool compLastDate_S1_Avant_S2(Tstation* s1,Tstation* s2);
bool compid_S1_inf_S2(Tstation* station1,Tstation* station2);

int isBissextile(int year);

int nbDayOfMonth(t_month myMonth,int year);

t_month RandomMonth();

int RandomYear();

int RandomDay(t_month month,int year);

t_date RandomDate();

int RandomCoutMaintenance();

void printDate(t_date theDate);

float DistanceBetween2Station(Tstation* station1,Tstation* station2); //Distance et Temps

TlisteStation creer1LigneBus(TlisteStation listeOfStations,int ligneBus);

TlisteStation* creerAllLigne();

TlisteStation rattacherL1L2(TlisteStation l1,TlisteStation l2);

void supprimerEnNTableau(TlisteStation* monReseau,int taille,int n);

int Fusion2Ligne(TlisteStation* monReseau,int nblignetotal,int n,int m);

TlisteStation supprimerArret(TlisteStation ligne,int n);

TlisteStation supprimerStationParId(TlisteStation l,int idligne, int idstation);

TlisteStation TransformCirculaire(TlisteStation ligne, int idLigne);

#endif // NOS_FONCTIONS_H_INCLUDED
