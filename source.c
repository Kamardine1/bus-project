#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

#include "source.h"
#include "ligneBus.h"

int isBissextile(int year){
    if (((year % 4 ==0)&& !(year % 100==0)) || (year % 400==0)){
        return 1; //retourne 1 si l'année est bissextile
    }
    else{
        return 0; //0 sinon
    }
}

int nbDayOfMonth(t_month myMonth,int year){

    switch(myMonth){
    case JANVIER :
    case MARS :
    case MAI :
    case JUILLET :
    case AOUT :
    case OCTOBRE :
    case DECEMBRE :
        {
            return 31;
        }
        break;
    case FEVRIER :
        {
             if(isBissextile(year)==1){
                    return 29;
             }else {return 28; }
        }
        break;
    case AVRIL :
    case JUIN :
    case SEPTEMBRE :
    case NOVEMBRE :
        {
            return 30;
        }
        break;
    default :
        {
        return 0;
        }
    }
}

t_month RandomMonth(){
    return ((rand()%(12-1))+1); //genere un mois aléatoire
}

int RandomYear(){
    return ((rand()%(2025-2000))+2000); //une année aleatoire entre 2000 et 2025
}

int RandomDay(t_month myMonth,int year){
    return ((rand()%(nbDayOfMonth(myMonth,year)-1))+1);
}

t_date RandomDate(){
    t_date theDate;
    srand(time(NULL));
    theDate.month=RandomMonth();    //((rand()%(12-1))+1); //genere un mois aléatoire
    theDate.year=RandomYear();      //((rand()%(2025-2000))+2000); //une année aleatoire entre 2000 et 2025
    theDate.day=RandomDay(theDate.month,theDate.year);

    return theDate;
}
// Pour tester qu'on a bien une date aléatoire
void printDate(t_date theDate){
    printf("le jour : %d", theDate.day);
    printf("le mois : %d", theDate.month);
    printf("l'année : %d", theDate.year);
}

int RandomCoutMaintenance(){   //Genere un nombre entre 10 et 100 pour le cout de la maintenance
    return ((rand()%(99-10))+10);
}

float DistanceBetween2Station(Tstation* station1,Tstation* station2){ //Distance et Temps

    float enX,enY;

    enX=((float)getPosXStation(station2)-(float)getPosXStation(station1));
    enY=((float)getPosYStation(station2)-(float)getPosYStation(station1));
    enX=powf(enX,2);
    enY=powf(enY,2);

    return sqrtf(enX+enY);
}

//Fonction inutile mais juste la pour faire un test rapide.
//fonction comparaison des id de 2 stations
bool compid_S1_inf_S2(Tstation* station1,Tstation* station2){
    if(getIdLigneTroncon(station1)<getIdLigneTroncon(station2)){
        return true;
    }
    else return false;
}

//fonction comparaison cout maintenance
bool compCout_S1_sup_S2(Tstation* station1,Tstation* station2){
    if(getCoutMaintenance(station1)>getCoutMaintenance(station2)){
        return true;
    }
    else return false;
}

//fonction qui compare 2 date et renvoie true si la premiere est avant la 2e
bool compLastDate_S1_Avant_S2(Tstation* station1,Tstation* station2){ //getDateLastMaintenance(station1)<getDateLastMaintenance(station2)

    bool res = false;

    if (getYearOfADate(getDateLastMaintenance(station1))<getYearOfADate(getDateLastMaintenance(station2))){
        return res=true;
    }
    else if(getYearOfADate(getDateLastMaintenance(station1))>getYearOfADate(getDateLastMaintenance(station2))){
        return res=false;
    }
    else if(getYearOfADate(getDateLastMaintenance(station1))==getYearOfADate(getDateLastMaintenance(station2))){

        if(getMonthOfADate(getDateLastMaintenance(station1))<getMonthOfADate(getDateLastMaintenance(station2))){
            return res=true;
        }
        else if(getMonthOfADate(getDateLastMaintenance(station1))>getMonthOfADate(getDateLastMaintenance(station2))){
            return res=false;
        }
        else if(getMonthOfADate(getDateLastMaintenance(station1))==getMonthOfADate(getDateLastMaintenance(station2))){

            if(getDayOfADate(getDateLastMaintenance(station1))<getDayOfADate(getDateLastMaintenance(station2))){
                return res=true;
            }
            else if(getMonthOfADate(getDateLastMaintenance(station1))>getMonthOfADate(getDateLastMaintenance(station2))){
                return res=false;
            }
        }
    }

    return res;
}

//prend en parametre une liste de stations et le numéro de la ligne qu'on veut creer et on cree la ligne en creant les troncons dans cette fonction
TlisteStation creer1LigneBus(TlisteStation listeOfStations,int ligneBus){
    TlisteStation nouvelleLigne;
    TlisteStation listTemp;
    TlisteStation listeViide;
    initListe(&nouvelleLigne);
    initListe(&listTemp);
    initListe(&listeViide);

    listTemp=creatNewListeFromFusion(listeOfStations,listeViide);
    nouvelleLigne=creatNewListeFromFusion(listeOfStations,listeViide);

    int tailleList=getNbreCell(listeOfStations);
    //printf("\nOn va charger les troncons\n");
    for(int i=1;i<=tailleList-1;i++){
        //afficheListe(nouvelleLigne);
        //printf("iteration %d\n",i);
        Tstation* theTroncon;
        theTroncon=creeTroncon(ligneBus,getPtrData(listTemp),getPtrData(getNextCell(listTemp))); //Correct
        nouvelleLigne=ajoutEnN(nouvelleLigne,(i*2)-1,theTroncon);
        listTemp=getNextCell(listTemp);
    }

    return nouvelleLigne;
}

TlisteStation* creerAllLigne() {
    int nbStations,nbLignes;
    FILE* pFichier=fopen("StationsEtLignesDeBus.data","r");

    fscanf(pFichier,"%d %d\n",&nbStations,&nbLignes);

    TlisteStation* monReseau=(TlisteStation*)malloc(sizeof(TlisteStation)*nbLignes);

    for(int i=0;i<nbLignes;i++){
        int actualLineId,departLine,arriveeLine;
        fscanf(pFichier,"%d %d %d\n",&actualLineId,&departLine,&arriveeLine);

        TlisteStation listeOfStations;
        initListe(&listeOfStations);

        for(int j=departLine;j<=arriveeLine;j++){
            int tempIdStation, tempPosX, tempPosY;
            char tempNomStation[50];

            fscanf(pFichier,"%d %d %d %[^\n]\n",&tempIdStation,&tempPosX,&tempPosY,tempNomStation);

            Tstation* theStation=creeArret(tempPosX,tempPosY,tempNomStation,tempIdStation);
            listeOfStations=ajoutEnFin(listeOfStations,theStation);
        }

        monReseau[i]=creer1LigneBus(listeOfStations,actualLineId);
    }
    fclose(pFichier);
    return monReseau;
}

void supprimerEnNTableau(TlisteStation* monReseau, int taille, int n) {
    if(n<0||n>=taille){
        printf("indice pas dans le tableau : %d\n",n);
        return;
    }
    for(int i=n;i<taille-1;i++) {
        monReseau[i]=monReseau[i+1];
    }
    monReseau[taille-1]=NULL;
}

TlisteStation rattacherL1L2(TlisteStation l1,TlisteStation l2){

    TlisteStation l2Temp = l2;

    Tstation* tronconLiantL1L2 = creeTroncon(getPtrData(getNextCell(l1))->idLigneBus,getPtrData(getptrLastCell(l1)),getPtrData(l2));
    l2=ajoutEnTete(l2,tronconLiantL1L2);

    while(l2Temp->suiv != NULL){ //pour changer les idLigneBus des troncons de L2 pour qu'ils appartiennent à l1
        getPtrData(l2Temp)->idLigneBus=getPtrData(getNextCell(l1))->idLigneBus;
        l2Temp=l2Temp->suiv;
    }

    l1 = addBehind(l1,l2);

    return l1;

}

//fonctionnalité pour rattacher et supprimer la ligne rattaché //Question 5.1
int Fusion2Ligne(TlisteStation* monReseau,int nblignetotal,int n,int m){//n et m sont les indices des listes à concatener

    monReseau[n] = rattacherL1L2(monReseau[n-1], monReseau[m-1]);
    supprimerEnNTableau(monReseau, nblignetotal, m-1);
    nblignetotal=nblignetotal-1;
    return nblignetotal;

}

// VERSION QUI MARCHE O(N²) en pire
TlisteStation supprimerStationParId(TlisteStation ligne,int idligne, int idstation) {//idstation est l'id de la station à supprimer

    int pos = 0;

    TlisteStation listTemp = getptrFirstCell(ligne);

    Tstation * previousStation;
    Tstation * nextStation;
    Tstation * newtroncon;

    Tstation* station = getPtrData(listTemp);

    if(getIdStation(station)==idstation){ //Si c'est la premiere station de la ligne O(1)

        ligne=suppEnTete(ligne);
        ligne=getNextCell(ligne);

        return ligne;
    }

    station=getPtrData(getptrLastCell(listTemp));

    if(getIdStation(station)==idstation){ //Si c'est la derniere station de la ligne O(N)
        ligne=suppEnFin(ligne);
        return ligne;
    }

    while((listTemp)!=NULL) { //Si la station est autre part dans la ligne O(N²)

        station = getPtrData(listTemp);

        if(getIdStation(station)==idstation){

            ligne=suppEnN(ligne,pos+1);
            ligne=suppEnN(ligne,pos);

            previousStation=getPtrData(getPreviousStation(listTemp));
            nextStation=getPtrData(getNextStation(listTemp));

            newtroncon=creeTroncon(idligne,previousStation,nextStation);

            ligne=ajoutEnN(ligne,pos-1,newtroncon);
            break;
        }
        listTemp=listTemp->suiv;
        pos++;
    }
    return ligne;
}


//Question 5.3

TlisteStation TransformCirculaire(TlisteStation ligne, int idLigne){

    TlisteStation firstCell = getptrFirstCell(ligne);
    TlisteStation lastCell = getptrLastCell(ligne);

    Tstation* firstStation = getPtrData(firstCell);
    Tstation* lastStation = getPtrData(lastCell);

    Tstation* newTroncon = creeTroncon(idLigne, lastStation, firstStation);
    ligne = ajoutEnFin(ligne, newTroncon);

    lastCell = getptrLastCell(ligne);

    ligne=addBehind(ligne,ligne);
    /*
    C'est comme si on faisait :
    lastCell->suiv=firstCell;
    firstCell->prec=lastCell;
    */

    return ligne;
}


