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

//DESCRIPTION:	Cr�ation d'une solution voisine � partir de la solution uneSol. NB:uneSol ne doit pas �tre modifi�e
TSolution GetSolutionVoisine(const TSolution uneSol, TProblem unProb, TDescente &unAlgo);

#endif

