#include "stdafx.h"
#include "Utilitaires.h"
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iostream>

vector<string> split(const string &s, char delim) {
	vector<string> result = vector<string>();
	stringstream ss;
	ss.str(s);
	string item;
	while (getline(ss, item, delim)) {
		result.push_back(item);
	}
	return result;
}

void LectureProbleme(string FileName, TProblem & unProb, TAlgo &unAlgo)
{
	unProb.Nom = FileName;
	ifstream infile(FileName);
	string line;

	while (infile)
	{
		getline(infile, line);
		vector<string> problem;
		vector<string> node;
		if (line != "")
		{
			switch (line.at(0))
			{
			case 'c':
				break;
			case 'p':
				problem = split(line, ' ');
				unProb.NbNoeuds = stoi(problem.at(2));
				unProb.NbAretes = stoi(problem.at(3));
				unProb.noeudsVoisins = vector<vector<int>>(unProb.NbNoeuds);
				break;
			case 'e':
				node = split(line, ' ');
				unProb.noeudsVoisins.at(stoi(node.at(1)) - 1).push_back(stoi(node.at(2)) - 1);
				unProb.noeudsVoisins.at(stoi(node.at(2)) - 1).push_back(stoi(node.at(1)) - 1);
				break;
			default:
				break;
			}
		}
	}
	
	unAlgo.CptEval = 0;

}

void CreerSolutionAleatoire(TSolution & uneSolution, TProblem unProb)
{
	//initialise la couleur de chaque noeud à -1
	uneSolution.couleurNoeud = vector<int>(unProb.NbNoeuds, -1);

	for (size_t i = 0; i < unProb.NbNoeuds; i++)
	{
		vector<int> couleursDisponibles = vector<int>();

		//initialise toutes les couleurs disponibles pour le noeud i
		for (size_t j = 0; j < unProb.NbNoeuds; j++)
		{
			couleursDisponibles.push_back(j);
		}

		// si dans les noeuds voisins de i, une couleur a déjà été attribuée (donc != -1) alors on l'enlève de la liste des couleurs disponibles
		for (size_t j = 0; j < unProb.noeudsVoisins[i].size(); j++)
		{
			int couleur = uneSolution.couleurNoeud[unProb.noeudsVoisins[i][j]];
			if (couleur != -1)
			{
				couleursDisponibles.erase(remove(couleursDisponibles.begin(), couleursDisponibles.end(), couleur), couleursDisponibles.end());
			}
		}

		//on tire une couleur aléatoire dans la liste des couleurs restantes pour l'attribuer à notre noeud i, il y a forcément une couleur disponible car on démarre avec un nombre de couleur égal au nombre de noeud
		if (couleursDisponibles.size() > 0)
		{
			int couleurIndex = rand() % couleursDisponibles.size();
			uneSolution.couleurNoeud[i] = couleursDisponibles[couleurIndex];
		}
		else
		{
			printf("ERROR NOT ENOUGH COLOR\n");
		}
	}
}

void CopierSolution(const TSolution uneSol, TSolution& Copie, TProblem unProb)
{
	Copie.FctObj = uneSol.FctObj;
	Copie.Valide = uneSol.Valide;
	Copie.couleurNoeud = uneSol.couleurNoeud;
}

void VerifierSolution(TSolution & uneSol, TProblem unProb, bool afficheMessage)
{
	for (size_t i = 0; i < uneSol.couleurNoeud.size(); i++)
	{
		for (size_t j = 0; j < unProb.noeudsVoisins[i].size(); j++)
		{
			int noeudVoisin = unProb.noeudsVoisins[i][j];
			if (uneSol.couleurNoeud[i] == uneSol.couleurNoeud[noeudVoisin])
			{
				uneSol.Valide = false;
				//On affiche tout les noeuds ayant la même couleur ou break car on juste déterminer si la solution est valide.
				if (afficheMessage)
				{
					cout << "2 NOEUDS ONT LA MEME COULEUR ! Le noeud " << i << " et son voisin le noeud " << noeudVoisin << endl;
				}else
				{
					break;
				}
				
			}
		}
	}
}

void EvaluerSolution(TSolution & uneSol, TProblem unProb, TAlgo &unAlgo)
{
	vector<int> couleursUtilisees = vector<int>();

	for (size_t i = 0; i < uneSol.couleurNoeud.size(); i++)
	{
		if (find(couleursUtilisees.begin(), couleursUtilisees.end(), uneSol.couleurNoeud[i]) == couleursUtilisees.end())
		{
			couleursUtilisees.push_back(uneSol.couleurNoeud[i]);
		}
	}

	uneSol.FctObj = couleursUtilisees.size();
	unAlgo.CptEval++;
}

void AfficherProbleme(TProblem unProb)
{
	cout << "********************************************************" << endl;
	cout << "NOM FICHIER  : " << unProb.Nom << endl;
	cout << "NB NOEUDS : " << unProb.NbNoeuds << endl;
	cout << "NB ARCS : " << unProb.NbAretes << endl;
	cout << "NOUEDS :" << endl;

	for (size_t i = 0; i < unProb.noeudsVoisins.size(); i++)
	{
		cout << "    NOEUD " << i << " :" << endl;
		cout << "\t";
		for(size_t j = 0; j < unProb.noeudsVoisins[i].size(); j++)
		{
			cout << " " << unProb.noeudsVoisins[i][j];
			if(j % 10 == 0 && j != 0 && j < unProb.noeudsVoisins[i].size()-1)
			{
				cout << endl;
				cout << "\t";
			}
		}
		cout << endl;
	}
	cout << "********************************************************" << endl;
}

void AfficherSolution(const TSolution uneSolution, TProblem unProb, std::string Titre)
{
	cout << "\n" << Titre << endl;
	cout << "MODELE : [Noeud]/[Couleur]" << endl;
	for(size_t i = 0; i < uneSolution.couleurNoeud.size(); i++)
	{
		cout << " " << i << "/" << uneSolution.couleurNoeud[i] << " ";
		if (i % 8 == 0 && i != 0 && i < uneSolution.couleurNoeud.size() * 1)
		{
			cout << endl;
		}
	}
	cout << endl;
	cout << "FCT OBJ : " << uneSolution.FctObj << endl;
}

void AfficherResultats(const TSolution uneSol, TProblem unProb, TAlgo unAlgo)
{
	cout << "********************************************************" << endl;
	cout << unProb.Nom << endl;
	AfficherSolution(uneSol, unProb, "SOLUTION FINALE :");
	cout << "NOMBRE D'EVALUATIONS : " << unAlgo.CptEval << "/" << unAlgo.NB_EVAL_MAX << endl;
	cout << "********************************************************" << endl;
 }

void AfficherResultatsFichier(const TSolution uneSol, TProblem unProb, TAlgo unAlgo, std::string FileName)
{
	ofstream outFile = ofstream(FileName, ios_base::app | ios_base::out);
	outFile << endl;
	outFile << "********************************************************" << endl;
	outFile << unProb.Nom << endl;
	outFile << "\n" << "SOLUTION FINALE" << endl;
	for (size_t i = 0; i < uneSol.couleurNoeud.size(); i++)
	{
		outFile << " " << i << "/" << uneSol.couleurNoeud[i] << " ";
		if (i % 8 == 0 && i != 0 && i < uneSol.couleurNoeud.size() * 1)
		{
			outFile << endl;
		}
	}
	outFile << endl;
	outFile << "FCT OBJ : " << uneSol.FctObj << endl;
	outFile << "NOMBRE D'EVALUATIONS : " << unAlgo.CptEval << "/" << unAlgo.NB_EVAL_MAX << endl;
	outFile << "********************************************************" << endl;
}