#ifndef __UTILITAIRES_H_
#define __UTILITAIRES_H_
#include <string>
#include "Entete.h"

//DESCRIPTION:	Lecture du Fichier probleme et initialiation de la structure Problem
void LectureProbleme(std::string FileName, TProblem & unProb, TAlgo &unAlgo);

//DESCRIPTION:	Fonction d'affichage � l'�cran permettant de voir si les donn�es du fichier probl�me ont �t� lues correctement
void AfficherProbleme(TProblem unProb);

//DESCRIPTION: Affichage d'une solution a l'�cran pour validation
void AfficherSolution(const TSolution uneSolution, TProblem unProb, std::string Titre);

//DESCRIPTION: Affichage � l'�cran de la solution finale, du nombre d'�valuations effectu�es et de certains param�tres
void AfficherResultats(const TSolution uneSol, TProblem unProb, TAlgo unAlgo);

//DESCRIPTION: Affichage dans un fichier(en append) de la solution finale, du nombre d'�valuations effectu�es et de certains param�tres
void AfficherResultatsFichier(const TSolution uneSol, TProblem unProb, TAlgo unAlgo, std::string FileName);

//DESCRIPTION:	�valuation de la fonction objectif d'une solution et MAJ du compteur d'�valuation. 
//				Fonction objectif repr�sente le retard total pond�r�
void EvaluerSolution(TSolution & uneSol, TProblem unProb, TAlgo &unAlgo);

//DESCRIPTION:	Cr�ation d'une s�quence al�atoire de coloration de graphe
void CreerSolutionAleatoire(TSolution & uneSolution, TProblem unProb);

//DESCRIPTION: Copie de la s�quence et de la fonction objectif dans une nouvelle TSolution. La nouvelle TSolution est retourn�e.
void CopierSolution(const TSolution uneSol, TSolution &Copie, TProblem unProb);

//DESCRIPTION: V�rifie la solution en contr�lant si deux noeuds adjacent n'ont pas la m�me couleur
void VerifierSolution(TSolution & uneSol, TProblem unProb, bool afficheMessage);
#endif

