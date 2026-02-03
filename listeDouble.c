#include <stdio.h>
#include <stdlib.h>

#include "listeDouble.h"


//initListe ne fait pas de malloc, juste une initialisation à NULL du pointeur de liste
void initListe(T_liste *l){
*l=NULL;
}


bool listeVide( T_liste l){
    return (l==NULL);
}

void afficheListe( T_liste l){
    T_liste courant = l;
    while (courant!=NULL){
        afficheStation(courant->pdata);//fourni par types.h
        courant=courant->suiv;
    }
}

T_liste ajoutEnTete(T_liste l, Tstation* mydata){
    T_liste nouv = (T_liste)malloc(sizeof(struct T_cell));

    //CHANGEMENT par rapport à la partie2 d'updago
    //nouv->pdata = (int*)malloc(sizeof(int)); ATTENTION PLUS DE RECOPIE de mydata, donc plus d'allocation mémoire sur ce champ

    //SIMPLE BRANCHEMENT EN MEMOIRE ENTRE POINTEURS (SUR LA STATION EXISTANTE)
    nouv->pdata=mydata;

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        nouv->suiv = NULL;  //sécurise la présence de NULL sur le champ suiv, au cas où le ptr l n'aurait pas été  initialisé correctement via initListe
        nouv->prec = NULL;
    }
    else  // la lste n'etait pas vide, on doit donc faire les branchements
    {
        nouv->suiv = l;
        nouv->prec = NULL;
        l->prec = nouv;
    }
    return nouv;
}

T_liste ajoutEnFin(T_liste l, Tstation* mydata){
    T_liste nouv, courant=l;  //remarque: pas de malloc si on appelle ajoutEnTete

    if (l==NULL) // on cree en fait la premiere cellule de la liste
    {
        return ajoutEnTete(l, mydata);
    }
    else  // la liste n'etant pas vide,déplacment sur la derniere cellule, malloc et branchements
    {
        while (courant->suiv != NULL){
            courant=courant->suiv;
        }
        nouv = (T_liste)malloc(sizeof(struct T_cell));
        nouv->pdata=mydata;

        nouv->suiv = NULL;
        nouv->prec = courant;
        courant->suiv = nouv;
    }
    return l;  //la tête d'origine, qui n'a pas changé
}

T_liste ajoutEnN(T_liste l,int pos, Tstation* mydata) {

    if (pos ==0) {
        return ajoutEnTete(l,mydata);
    }

    T_liste liste = (T_liste)malloc(sizeof(struct T_cell));
    (liste->pdata)=mydata;
    T_liste temp = l;

    for(int i=1 ; i < pos && (!listeVide(temp));i++){
        temp = temp->suiv;
    }

    if (temp == NULL ) {
        return l;
    }

    liste->suiv = temp->suiv;
    liste->prec = temp->prec;
    temp->suiv = liste;
    liste->prec = temp;

    return l;
}



/*
T_liste ajoutEnN(T_liste l, int pos, Tstation * val){
    if(pos==0){
        return (ajoutEnTete(l,val));
    }else if(pos>0){
        T_liste p=l;
        int i=0;
        while (pos>i++ && !listeVide(p)){
            p=p->suiv;
        }
        if(listeVide(p)){
            printf("position out of bounds\n");
            return l;
        }else if(listeVide(p->suiv)){
            return(ajoutEnFin(l,val));
        }
        else{
            T_liste c = (T_liste)malloc(sizeof(T_cellule));
            c->prec=p->prec;
            p->prec->suiv=c;
            p->prec = c;
            c->suiv = p;
            c->pdata=val;
            return l;
        }

    }else{
        printf("position out of bounds\n");
        return l;
    }
}
*/

Tstation* getPtrData(T_liste l){
    if (l==NULL)
    {
        printf("\nERREUR ptr pdata non alloué");
        return NULL;
    }
    else
    {
        return l->pdata;
    }
}

Tstation* getPtrDataFromList(T_liste l, Tstation* mydata){ //l c'est le début de la liste

    T_liste courant = l;

    while((courant->pdata)!=mydata){
        courant=courant->suiv;
    }

    if((courant->suiv==NULL) && ((courant->pdata)!=mydata)){
        return NULL; // element pas sur la liste
    }else{
        return courant->pdata;
    }

}
T_liste getNextCell(T_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->suiv;
    }
}

T_liste getPrevCell(T_liste l){
    if (l==NULL)
    {
        return NULL;  //convention
    }
    else{
        return l->prec;
    }
}

T_liste suppEnTete(T_liste l){

    if(listeVide(l)){
        return NULL;
    }
    if(l->suiv==NULL){
        return NULL;
    }
    else{
        l=l->suiv;
        free(l->prec->pdata);
        free(l->prec);
        l->prec=NULL;
    return l;
    }
}

T_liste suppEnFin(T_liste l){

    if(listeVide(l)){
        return NULL;
    }
    else{

    T_liste nouvelleListe ;
    nouvelleListe = l;

    while(l->suiv!=NULL){
        l=l->suiv;
    }
    l->prec->suiv=NULL;
    free(l);

    return nouvelleListe;
    }
}

T_liste suppEnN(T_liste l,int pos){

    T_liste nouvelleList ;
    nouvelleList=l;
    int counter=0;

    while(counter!=pos){
        l=l->suiv;
        counter++;
    }
    l->prec->suiv=l->suiv;
    l->suiv->prec=l->prec;
    free(l);

    return nouvelleList;
}

T_liste getptrFirstCell(T_liste l){

    T_liste ptrFirstCell = l;
    if(!(listeVide(ptrFirstCell)))
    {
        while(!listeVide(ptrFirstCell->prec)){
            ptrFirstCell=ptrFirstCell->prec;
        }
        return ptrFirstCell;
    }
    else{
        return ptrFirstCell;
    }

}

T_liste getptrLastCell(T_liste l){

    T_liste ptrLastCell = l;
    if(!(listeVide(ptrLastCell)))
    {
        while(!listeVide(ptrLastCell->suiv)){
            ptrLastCell=ptrLastCell->suiv;
        }
        return ptrLastCell;
    }
    else{
        return ptrLastCell;
    }

}

T_liste getptrNextCell(T_liste l)
{
    T_liste NextCell = l;

    if (listeVide(NextCell)) {
        return NextCell;
    }
    else {
        NextCell=NextCell->suiv;
        return NextCell;
    }
}

T_liste getptrPrevCell(T_liste l)
{
    T_liste PrevCell = l;

    if (listeVide(PrevCell)) {
        return PrevCell;
    }
    else {
        PrevCell=PrevCell->prec;
        return PrevCell;
    }
}

void swapPtrData( T_liste source, T_liste destination ){

    Tstation * ptrTemp;
    ptrTemp=source->pdata;
    source->pdata=destination->pdata;
    destination->pdata=ptrTemp;
}

int getNbreCell(T_liste l){
    int size = 0;
    T_liste courant = l;
    while (!listeVide(courant)){
        size++;
        courant = getptrNextCell(courant);
    }
    return size;
}

int getSizeBytes(T_liste l){

    return (sizeof(T_cellule)*getNbreCell(l));
}


T_liste creatNewListeFromFusion(T_liste l1, T_liste l2){

    T_liste l3;
    initListe(&l3);

    T_liste temp=l1;
    while(temp!=NULL){
        l3=ajoutEnFin(l3,(temp->pdata));
        temp= getNextCell(temp); //suppEnTete(temp);
    }
    temp=l2;
    while(temp!=NULL){
        l3=ajoutEnFin(l3,(temp->pdata));
        temp= getNextCell(temp);
    }

    return l3;
}

T_liste addBehind(T_liste debut, T_liste suite){ //Concaténation de 2 listes

    T_liste listTemp = debut;

    while(listTemp->suiv!=NULL){
        listTemp=listTemp->suiv;
    }

    listTemp->suiv=suite;
    suite->prec=listTemp;
    return debut;
}

T_liste findCell(T_liste l, Tstation * data){
    T_liste theCell = l;
    if(listeVide(l)){
        return NULL;
    }
    else{
        while(theCell!=NULL){
            if((theCell->pdata)==data){
                return theCell;
            }
            else{
                theCell=theCell->suiv;
            }
        }
    }
    return theCell;
}

int getOccurences(T_liste l, Tstation* data){
    if(listeVide(l)){
        return 0;
    }
    else{
        int count=0;
        T_liste listTemp =l;
        while(listTemp->suiv!=NULL){
            if((listTemp->pdata)==data){
                listTemp=listTemp->suiv;
                count++;
            }else listTemp=listTemp->suiv;
        }
        if((listTemp->pdata)==data) count++;
        free(listTemp);

        return count;
    }
}
