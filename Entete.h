#ifndef __ENTETE_H_
#define __ENTETE_H_

#include <string>
#include <vector>
using namespace std;


struct TProblem							//**Définition du problème:
{
	std::string Nom;					//**Nom du fichier de données
	int NbNoeuds;						//**Nombre de noeuds dans le graphe
	int NbAretes;						//**Nombre d'arètes dans le graphe
	std::vector<vector<int>> noeudsVoisins;		//**Liste des voisons de chaque noeud. NB: Tableau de 0 à NbNoeuds-1.  
};

struct TSolution						//**Définition d'une solution: 
{
	std::vector<int> couleurNoeud;		//**Indique la couleur de chaque noeud. NB: Tableau de 0 à NbCom-1.
	long FctObj;						//**Valeur de la fonction obj: Sommation des retards pondérés
	bool Valide;						//**Indique si la solution respecte les contraintes de couelur. Vérifier lorsque la solution est évaluée.
};


class TAlgo
{
public:
	int		CptEval;					//**COMPTEUR DU NOMBRE DE SOLUTIONS EVALUEES. SERT POUR CRITERE D'ARRET.
	int		NB_EVAL_MAX;				//**CRITERE D'ARRET: MAXIMUM "NB_EVAL_MAX" EVALUATIONS.
};

#endif