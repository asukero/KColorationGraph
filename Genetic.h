#ifndef __GENETIC_H_
#define __GENETIC_H_
#include <vector>
#include "Entete.h"

class TGenetic : public TAlgo
{
public:
	int		TaillePop;					//**Taille de la population (nombre d'individus)
	int		TaillePopEnfant;			//**Taille de la populationEnfant (nombre d'enfants)
	double	ProbCr;						//**Probabilité de croisement [0%,100%]
	double	ProbMut;					//**Probabilité de mutation [0%,100%] 
	int		Gen;						//**Compteur du nombre de générations
};

//DESCRIPTION: Execute l'algorithme génétique
void runAlgoGen(TProblem LeProb, TGenetic LeGenetic);

//DESCRIPTION: Fonction de sélection d'un individu par tournoi
int Selection(int _Taille, double r);

//DESCRIPTION: Fonction qui gén ére une population initiale en s'assurant d'avoir des solutions valides
void CreerPopInitialeAleaValide(std::vector<TSolution> & unePop, TSolution & Best, TProblem unProb, TGenetic & unGenetic);

//DESCRIPTION: Fonction qui réalise la MUTATION (modification aléatoire) sur une solution: Inversion de sous-séquence et échange de 2 commandes.
void Mutation(TSolution & Mutant, TProblem unProb, TGenetic & unGen);

//DESCRIPTION: Fonction qui réalise le CROISEMENT (échange de genes) entre deux parents. Retourne l'enfant produit.
TSolution Croisement(TSolution Parent1, TSolution Parent2, TProblem unProb, TGenetic & unGen);

//DESCRIPTION: Fonction qui réalise le REMPLACEMENT de la population pour la prochaine génération. Cette fonction doit
//prendre les TaillePop solutions de la population "Parents" et les TaillePopEnfant solutions de la
//population "Enfants" et retenir SEULEMENT TaillePop solutions pour commencer la prochaine génération.
//Les TaillePop solutions retenues doivent être placées dans la populations "Parents".
void Remplacement(std::vector<TSolution> & Parents, std::vector<TSolution> Enfants, TProblem unProb, TGenetic unGen);

//DESCRIPTION: Fonction qui réalise la rercheche locale pour un noeud donné dans une solution, on cherche la première couleur non attribué a un noeud et ses voisins pour l'appliquer à ce noeud.
void RechercheLocaleCouleur(TSolution & uneSol, TProblem unProb, int noeud);
#endif