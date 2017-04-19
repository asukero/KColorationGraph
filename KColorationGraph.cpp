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

string EvaluationAleatoire(TAlgo LAlgo, TSolution Courante, TSolution Best, TProblem LeProb);

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

		cout << "Lecture du fichier de donnees..." << endl;
		LectureProbleme(NomFichier, LeProb, LeGenetic);

		
		
		cout << "Entrez une probabilite de croisement entre 0 et 1" << endl;
		cin >> reponse;
		double value = stod(reponse);

		while(value < 0 || value > 1)
		{
			cout << "Erreur : veuillez entrer une probabilite de croisement entre 0 et 1" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> reponse;
			value = stod(reponse);
		}

		
		LeGenetic.ProbCr = value;

		cout << "Entrez une probabilite de mutation entre 0 et 1" << endl;
		cin >> reponse;
		value = stod(reponse);

		while (value < 0 && value > 1)
		{
			cout << "Erreur : veuillez entrer une probabilite de mutation entre 0 et 1" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> reponse;
			value = stod(reponse);
		}

		LeGenetic.ProbMut = value;

		cout << "Entrez une taille de population" << endl;
		cin >> reponse;
		int pop = stoi(reponse);

		while (pop < 1)
		{
			cout << "Erreur : veuillez entrer une taille de population superieure à 1" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> reponse;
			pop = stod(reponse);
		}

		LeGenetic.TaillePop = pop;
		LeGenetic.TaillePopEnfant = static_cast<int>(ceil(LeGenetic.ProbCr * LeGenetic.TaillePop));
		LeGenetic.Gen = 0;
		runAlgoGen(LeProb, LeGenetic);
	}

	if (reponse == "Tabou")
	{
		TTabou LeTabou;

		LeTabou.NB_EVAL_MAX = atoi(Param[2]);

		cout << "Entrez un nombre de voisins à parcourir" << endl;
		cin >> reponse;
		int nb = stoi(reponse);

		while (nb < 1)
		{
			cout << "Erreur : veuillez entrer un nombre de voisins à parcourir superieur à 1" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> reponse;
			nb = stod(reponse);
		}

		LeTabou.voisinsGeneres = nb;

		cout << "Entrez la taille max de la liste de tabous" << endl;
		cin >> reponse;
		nb = stoi(reponse);

		while (nb < 1)
		{
			cout << "Erreur : veuillez entrer une taille max de liste de tabous superieur à 1" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> reponse;
			nb = stod(reponse);
		}

		LeTabou.listeTabous = vector<pair<int, int>>();
		LeTabou.nombreEchangesMax = nb;

		cout << "Lecture du fichier de donnees..." << endl;
		LectureProbleme(NomFichier, LeProb, LeTabou);

		runAlgoTabou(LeProb, LeTabou);
	}

	if(reponse == "Descente")
	{
		TDescente LAlgo;
		LAlgo.NB_EVAL_MAX = atoi(Param[2]);

		cout << "Entrez un nombre de voisins à parcourir" << endl;
		cin >> reponse;
		int nb = stoi(reponse);

		while (nb < 1)
		{
			cout << "Erreur : veuillez entrer un nombre de voisins à parcourir superieur à 1" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			cin >> reponse;
			nb = stod(reponse);
		}

		LAlgo.voisinsGeneres = nb;
		
		cout << "Lecture du fichier de donnees..." << endl;
		LectureProbleme(NomFichier, LeProb, LAlgo);

		runAlgoDescente(LeProb, LAlgo);
		
	}

	system("PAUSE");
	return 0;
}