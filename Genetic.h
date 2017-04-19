#ifndef __GENETIC_H_
#define __GENETIC_H_
#include <vector>
#include "Entete.h"

class TGenetic : public TAlgo
{
public:
	int		TaillePop;					//**Taille de la population (nombre d'individus)
	int		TaillePopEnfant;			//**Taille de la populationEnfant (nombre d'enfants)
	double	ProbCr;						//**Probabilit� de croisement [0%,100%]
	double	ProbMut;					//**Probabilit� de mutation [0%,100%] 
	int		Gen;						//**Compteur du nombre de g�n�rations
};

//DESCRIPTION: Execute l'algorithme g�n�tique
void runAlgoGen(TProblem LeProb, TGenetic LeGenetic);

//DESCRIPTION: Fonction de s�lection d'un individu par tournoi
int Selection(int _Taille, double r);

//DESCRIPTION: Fonction qui g�n �re une population initiale en s'assurant d'avoir des solutions valides
void CreerPopInitialeAleaValide(std::vector<TSolution> & unePop, TSolution & Best, TProblem unProb, TGenetic & unGenetic);

//DESCRIPTION: Fonction qui r�alise la MUTATION (modification al�atoire) sur une solution: Inversion de sous-s�quence et �change de 2 commandes.
void Mutation(TSolution & Mutant, TProblem unProb, TGenetic & unGen);

//DESCRIPTION: Fonction qui r�alise le CROISEMENT (�change de genes) entre deux parents. Retourne l'enfant produit.
TSolution Croisement(TSolution Parent1, TSolution Parent2, TProblem unProb, TGenetic & unGen);

//DESCRIPTION: Fonction qui r�alise le REMPLACEMENT de la population pour la prochaine g�n�ration. Cette fonction doit
//prendre les TaillePop solutions de la population "Parents" et les TaillePopEnfant solutions de la
//population "Enfants" et retenir SEULEMENT TaillePop solutions pour commencer la prochaine g�n�ration.
//Les TaillePop solutions retenues doivent �tre plac�es dans la populations "Parents".
void Remplacement(std::vector<TSolution> & Parents, std::vector<TSolution> Enfants, TProblem unProb, TGenetic unGen);

//DESCRIPTION: Fonction qui r�alise la rercheche locale pour un noeud donn� dans une solution, on cherche la premi�re couleur non attribu� a un noeud et ses voisins pour l'appliquer � ce noeud.
void RechercheLocaleCouleur(TSolution & uneSol, TProblem unProb, int noeud);
#endif