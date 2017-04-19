#ifndef __TABOU_H_
#define __TABOU_H_
#include "Entete.h"

class TTabou : public TAlgo
{
public:
	int		voisinsGeneres;						//**Compteur du nombre de voisins g�n�r�s
	int		nombreEchangesMax;						//**Compteur du nombre d'�changes sauvegard� dans la liste Tabou
	vector<pair<int, int>> listeTabous;			//**Liste des tabous avec une paire contenant le noeud modifi� et sa pr�c�dente couleur.
};


//DESCRIPTION: Execute l'algorithme de recherche tabou
void runAlgoTabou(TProblem LeProb, TTabou LAlgo);

//DESCRIPTION:	Cr�ation d'une solution voisine � partir de la solution uneSol. NB:uneSol ne doit pas �tre modifi�e
TSolution GetSolutionVoisineTabou(const TSolution uneSol, TProblem unProb, TTabou &unAlgo);

//DESCRIPTION: Fonction qui retourne le tabou sous forme de paire (noeud,couleur) qui correspond au noeud modifi� et � son ancienne couleur
pair<int, int> GetTabou(TSolution Courante, TSolution Next, TProblem unProb);

#endif

