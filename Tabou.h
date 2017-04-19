#ifndef __TABOU_H_
#define __TABOU_H_
#include "Entete.h"

class TTabou : public TAlgo
{
public:
	int		voisinsGeneres;						//**Compteur du nombre de voisins générés
	int		nombreEchangesMax;						//**Compteur du nombre d'échanges sauvegardé dans la liste Tabou
	vector<pair<int, int>> listeTabous;			//**Liste des tabous avec une paire contenant le noeud modifié et sa précédente couleur.
};


//DESCRIPTION: Execute l'algorithme de recherche tabou
void runAlgoTabou(TProblem LeProb, TTabou LAlgo);

//DESCRIPTION:	Création d'une solution voisine à partir de la solution uneSol. NB:uneSol ne doit pas être modifiée
TSolution GetSolutionVoisineTabou(const TSolution uneSol, TProblem unProb, TTabou &unAlgo);

//DESCRIPTION: Fonction qui retourne le tabou sous forme de paire (noeud,couleur) qui correspond au noeud modifié et à son ancienne couleur
pair<int, int> GetTabou(TSolution Courante, TSolution Next, TProblem unProb);

#endif

