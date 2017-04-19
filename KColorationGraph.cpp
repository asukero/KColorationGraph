// KColorationGraph.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <windows.h>
#include "Entete.h"
#include "Utilitaires.h"
#include "Genetic.h"
#include "Descente.h"
#include <iostream>
#include <regex>
#include "Tabou.h"

void EvaluationAleatoire(TAlgo LAlgo, TSolution Courante, TSolution Best, TProblem LeProb);
TSolution GetSolutionVoisine(TSolution Courante, TProblem LeProb, TAlgo LAlgo);

//******************************************************************************************
// Fonction main
//*****************************************************************************************
int main(int NbParam, char *Param[])
{
	TProblem LeProb;		//Définition de l'instance de problème
	string NomFichier;

	//**Lecture des paramètres
	NomFichier.assign(Param[1]);
	
	//AfficherProbleme(LeProb);

	//**Création de la solution initiale 
	//EvaluationAleatoire(LAlgo, Courante, Best, LeProb);
	cout << "Executer l'algorithme genetique, la recherche par tabou ou la descente ? [Genetic/Tabou/Descente]" << endl;
	string reponse;
	cin >> reponse;

	regex reg("Genetic|Tabou|Descente");

	while(!regex_match(reponse, reg))
	{
		cout << "Erreur : veuillez choisir la metaheurstique a executer [Genetic/Tabou/Descente]" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		cin >> reponse;
	}

	if(reponse == "Genetic")
	{
		TGenetic LeGenetic;
		LeGenetic.NB_EVAL_MAX = atoi(Param[2]);

		//**Lecture du fichier de donnees
		LectureProbleme(NomFichier, LeProb, LeGenetic);

		
		LeGenetic.ProbCr = 0.1;
		LeGenetic.ProbMut = 0.2;
		LeGenetic.TaillePop = 10;
		LeGenetic.TaillePopEnfant = static_cast<int>(ceil(LeGenetic.ProbCr * LeGenetic.TaillePop));
		LeGenetic.Gen = 0;
		runAlgoGen(LeProb, LeGenetic);
	}

	if (reponse == "Tabou")
	{
		TTabou LeTabou;

		LeTabou.NB_EVAL_MAX = atoi(Param[2]);
		LeTabou.voisinsGeneres = 10;
		LeTabou.listeTabous = vector<pair<int, int>>();
		LeTabou.nombreEchangesMax = 20;
		//**Lecture du fichier de donnees
		LectureProbleme(NomFichier, LeProb, LeTabou);

		runAlgoTabou(LeProb, LeTabou);
	}

	if(reponse == "Descente")
	{
		TDescente LAlgo;
		LAlgo.NB_EVAL_MAX = atoi(Param[2]);
		LAlgo.voisinsGeneres = 10;
		//**Lecture du fichier de donnees
		LectureProbleme(NomFichier, LeProb, LAlgo);

		runAlgoDescente(LeProb, LAlgo);
		
	}

	system("PAUSE");
	return 0;
}

void EvaluationAleatoire(TAlgo LAlgo, TSolution Courante, TSolution Best, TProblem LeProb)
{
	int best = MAXINT;
	for (size_t i = 0; i < LAlgo.NB_EVAL_MAX / 5; i++)
	{
		CreerSolutionAleatoire(Courante, LeProb);
		Best = Courante;
		EvaluerSolution(Best, LeProb, LAlgo);
		cout << "FCT OBJ : " << Best.FctObj << endl;
		if (Best.FctObj < best) best = Best.FctObj;
	}
	cout << "BEST : " << best << endl;
}