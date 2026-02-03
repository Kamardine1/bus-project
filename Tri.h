#ifndef TRI_H_INCLUDED
#define TRI_H_INCLUDED

#include <stdbool.h>
#include "types.h"
#include "listeDouble.h"

void triSelectionListeParPointeur(T_liste l,bool (*fcomp)(Tstation* a,Tstation* b),TypeNoeud theType);

#endif // TRI_H_INCLUDED
