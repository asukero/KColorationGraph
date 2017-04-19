#ifndef __UTILITAIRES_H_
#define __UTILITAIRES_H_
#include <string>
#include "Entete.h"

//DESCRIPTION:	Lecture du Fichier probleme et initialiation de la structure Problem
void LectureProbleme(std::string FileName, TProblem & unProb, TAlgo &unAlgo);

//DESCRIPTION:	Fonction d'affichage à l'écran permettant de voir si les données du fichier problème ont été lues correctement
void AfficherProbleme(TProblem unProb);

//DESCRIPTION: Affichage d'une solution a l'écran pour validation
void AfficherSolution(const TSolution uneSolution, TProblem unProb, std::string Titre);

//DESCRIPTION: Affichage à l'écran de la solution finale, du nombre d'évaluations effectuées et de certains paramètres
void AfficherResultats(const TSolution uneSol, TProblem unProb, TAlgo unAlgo);

//DESCRIPTION: Affichage dans un fichier(en append) de la solution finale, du nombre d'évaluations effectuées et de certains paramètres
void AfficherResultatsFichier(const TSolution uneSol, TProblem unProb, TAlgo unAlgo, std::string FileName);

//DESCRIPTION:	Évaluation de la fonction objectif d'une solution et MAJ du compteur d'évaluation. 
//				Fonction objectif représente le retard total pondéré
void EvaluerSolution(TSolution & uneSol, TProblem unProb, TAlgo &unAlgo);

//DESCRIPTION:	Création d'une séquence aléatoire de coloration de graphe
void CreerSolutionAleatoire(TSolution & uneSolution, TProblem unProb);

//DESCRIPTION: Copie de la séquence et de la fonction objectif dans une nouvelle TSolution. La nouvelle TSolution est retournée.
void CopierSolution(const TSolution uneSol, TSolution &Copie, TProblem unProb);

//DESCRIPTION: Vérifie la solution en contrôlant si deux noeuds adjacent n'ont pas la même couleur
void VerifierSolution(TSolution & uneSol, TProblem unProb, bool afficheMessage);
#endif

