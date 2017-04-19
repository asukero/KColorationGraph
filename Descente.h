#ifndef __DESCENTE_H_
#define __DESCENTE_H_
#include "Entete.h"

class TDescente : public TAlgo
{
public:
	int		voisinsGeneres;
};
//DESCRIPTION: Execute l'algorithme de descente
void runAlgoDescente(TProblem LeProb, TDescente LAlgo);

//DESCRIPTION:	Création d'une solution voisine à partir de la solution uneSol. NB:uneSol ne doit pas être modifiée
TSolution GetSolutionVoisine(const TSolution uneSol, TProblem unProb, TDescente &unAlgo);

#endif

