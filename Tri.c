#include <stdio.h>
#include <stdlib.h>

#include "Tri.h"

void triSelectionListeParPointeur(T_liste l,bool (*fcomp)(Tstation* a,Tstation* b),TypeNoeud theType){ //tri par deplacement des pointeurs

    T_liste en_cours, plus_petit, j, fin;
    fin = getptrLastCell(l);

    for(en_cours=l;en_cours!=fin;en_cours=getptrNextCell(en_cours)){

        plus_petit=en_cours;
        for(j=en_cours;j!=fin;j=getptrNextCell(j)){
            if(fcomp(getPtrData(j),getPtrData(plus_petit)) && getTypeNoeud(getPtrData(j))==getTypeNoeud(getPtrData(plus_petit))){ //ca equivaut à *getPtrData(j)<*getPtrData(plus_petit)
                plus_petit=j;
            }
        }
        if(fcomp(getPtrData(j),getPtrData(plus_petit)) && getTypeNoeud(getPtrData(j))==getTypeNoeud(getPtrData(plus_petit))){
            plus_petit=fin;
        }  //*getPtrData(fin)<*getPtrData(plus_petit)
        swapPtrData(en_cours, plus_petit);
    }
}
