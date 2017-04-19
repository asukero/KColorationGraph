#ifndef __ENTETE_H_
#define __ENTETE_H_

#include <string>
#include <vector>
using namespace std;


struct TProblem							//**D�finition du probl�me:
{
	std::string Nom;					//**Nom du fichier de donn�es
	int NbNoeuds;						//**Nombre de noeuds dans le graphe
	int NbAretes;						//**Nombre d'ar�tes dans le graphe
	std::vector<vector<int>> noeudsVoisins;		//**Liste des voisons de chaque noeud. NB: Tableau de 0 � NbNoeuds-1.  
};

struct TSolution						//**D�finition d'une solution: 
{
	std::vector<int> couleurNoeud;		//**Indique la couleur de chaque noeud. NB: Tableau de 0 � NbCom-1.
	long FctObj;						//**Valeur de la fonction obj: Sommation des retards pond�r�s
	bool Valide;						//**Indique si la solution respecte les contraintes de couelur. V�rifier lorsque la solution est �valu�e.
};


class TAlgo
{
public:
	int		CptEval;					//**COMPTEUR DU NOMBRE DE SOLUTIONS EVALUEES. SERT POUR CRITERE D'ARRET.
	int		NB_EVAL_MAX;				//**CRITERE D'ARRET: MAXIMUM "NB_EVAL_MAX" EVALUATIONS.
};

#endif