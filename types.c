#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "types.h"
#include "source.h"

void afficheStation( Tstation *station){
    if (station == NULL){
        printf("\nerreur station non allouée!\n");
    }
    else{
        if (station->arret_ou_troncon == ARRET){
            printf("\nSTATION idStation: %d, Station : %s, posX = %d, posY = %d,cout de la maintenance = %d, annee last main = %d, mois last main = %d, day last main = %d", station->idStation, station->nomStation, station->posX, station->posY,station->coutMaintenance,station->dateDerniereMaintenance.year,station->dateDerniereMaintenance.month,station->dateDerniereMaintenance.day);
        }
        else{ //alors le noeud est un tronçon
            printf("\nTRONCON idLigneBus: %d, temps: %d sec, distance à parcourir: %d mètres", station->idLigneBus, station->coutTemps, station->coutDistance);
            //afficheStation(station->depart);
            //afficheStation(station->arrivee);
            printf("\nfin tronçon\n");
        }
    }
}

// Getteurs

int getIdStation( Tstation *myStation){
    return myStation->idStation;
}

char *getNomStation( Tstation *myStation){
    return myStation->nomStation;
}

int getPosXStation( Tstation *myStation ){
    return myStation->posX;
}
int getPosYStation( Tstation *myStation ){
    return myStation->posY;
}

int getIdLigneTroncon(Tstation *myStation){
    //une station n'est pas liée à une ligne, seulement le troncon
    if (getTypeNoeud(myStation)==TRONCON)
        return myStation->idLigneBus;
    else{
        printf("\n(getIdLigneTroncon) Erreur algo, vous n etes pas sur un troncon");
        return -1;
    }
}

TypeNoeud getTypeNoeud(Tstation *myStation){
    return myStation->arret_ou_troncon;
}

int getPosXBus( Tbus myBus ){
    return myBus->posXBus;
}
int getPosYBus( Tbus myBus ){
    return myBus->posYBus;
}
int getIdBus( Tbus myBus ){
    return myBus->idBus;
}
int getIdLigneActuelleDuBus( Tbus myBus ){
    return myBus->idLigneBusActuelle;
}

int getIdLigneBus(Tbus myBus){
    return myBus->idLigneBusActuelle;
}

TsensParcours getSensParcours(Tbus myBus){
    return myBus->sensParcours;
}

t_date getDateLastMaintenance(Tstation * mystation){
    return (mystation->dateDerniereMaintenance);
}

int getYearOfADate(t_date date){
    return date.year;
}

t_month getMonthOfADate(t_date date){
    return date.month;
}

int getDayOfADate(t_date date){
    return date.day;
}

int getCoutMaintenance(Tstation *mystation){
    return (mystation->coutMaintenance);
}


// Setteurs

void setActualStation( Tbus myBus, TlisteStation arrivalStation ){
    myBus->positionSurLaLigneDeBus = arrivalStation;
}

TlisteStation getActualStation( Tbus myBus ){
    return myBus->positionSurLaLigneDeBus;
}

void setPosXBus(Tbus myBus, int newX){
    myBus->posXBus = newX;
}

void setPosYBus(Tbus myBus, int newY){
    myBus->posYBus = newY;
}

void setIdLigneBus(Tbus myBus, int idLigne){
    myBus->idLigneBusActuelle = idLigne;
}

void setSensParcours(Tbus myBus, TsensParcours sens ){
    myBus->sensParcours = sens;
}

void setPositionSurLaLigneDeBus( Tbus myBus, TlisteStation myStation){
    myBus->positionSurLaLigneDeBus = myStation;
}

void setCoutMaintenance(Tstation *theStation){
    theStation->coutMaintenance=RandomCoutMaintenance();
}

void setDateLastMaintenance(Tstation *theStation){
    theStation->dateDerniereMaintenance=RandomDate();
}

