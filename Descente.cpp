#include "stdafx.h"
#include "Descente.h"
#include "Utilitaires.h"
#include <iostream>
#include "Genetic.h"
#include <algorithm>

void runAlgoDescente(TProblem LeProb, TDescente LAlgo)
{
	TSolution Courante;		//Solution active au cours des itérations
	TSolution Next;			//Solution voisine retenue à une itération
	TSolution Best;			//Meilleure solution depuis le début de l'algorithme //Non utilisé pour le moment 

	CreerSolutionAleatoire(Courante, LeProb);
	EvaluerSolution(Courante, LeProb, LAlgo);
	AfficherSolution(Courante, LeProb, "SolInitiale: ");
	Best = Courante;
	VerifierSolution(Courante, LeProb, true);

	do
	{
		Next = GetSolutionVoisine(Courante, LeProb, LAlgo);
		cout << "Fct Obj Courante: " << Courante.FctObj << endl;
		EvaluerSolution(Next, LeProb, LAlgo);

		if (Next.FctObj == Courante.FctObj) {
			if (Courante.FctObj < Best.FctObj) {
				Best = Courante;
			}
			CreerSolutionAleatoire(Courante, LeProb);
		}
		else if (Next.FctObj < Courante.FctObj)	//**amélioration
		{
			Courante = Next;
			cout << "Fct Obj Nouvelle Courante: " << Courante.FctObj << endl;
			//AfficherSolution(Courante, LeProb, "NouvelleCourante: ", false);
		}
	} while (LAlgo.CptEval < LAlgo.NB_EVAL_MAX && Courante.FctObj != 0);

	AfficherResultats(Best, LeProb, LAlgo);
	AfficherResultatsFichier(Best, LeProb, LAlgo, "Resultats.txt");
	VerifierSolution(Best, LeProb, true);
}

TSolution GetSolutionVoisine(const TSolution uneSol, TProblem unProb, TDescente& unAlgo)
{
	//Génération des solutions voisines
	vector<TSolution> solVoisines = vector<TSolution>();

	/*TSolution solVoisine;
	CopierSolution(uneSol, solVoisine, unProb);*/

	/*for (size_t noeud = 0; noeud < unProb.NbNoeuds; noeud++)
	{
		RechercheLocaleCouleur(solVoisine, unProb, noeud);
	}*/

	/*int noeud = rand() % unProb.NbNoeuds;
	RechercheLocaleCouleur(solVoisine, unProb, noeud);*/


	int i = 0;
	while (i < unAlgo.voisinsGeneres)
	{
		int noeud = rand() % unProb.NbNoeuds;
		int couleur = rand() % unProb.NbNoeuds;

		pair<int, int> echange = pair<int, int>(noeud, couleur);
		TSolution solVoisine;
		CopierSolution(uneSol, solVoisine, unProb);
		solVoisine.couleurNoeud[noeud] = couleur;
		VerifierSolution(solVoisine, unProb, false);

		//On ne récupère dans les voisins de notre solution que des solutions valides.
		if (solVoisine.Valide)
		{
			vector<int> couleursUtilisees = vector<int>();

			for (size_t i = 0; i < solVoisine.couleurNoeud.size(); i++)
			{
				if (find(couleursUtilisees.begin(), couleursUtilisees.end(), solVoisine.couleurNoeud[i]) == couleursUtilisees.end())
				{
					couleursUtilisees.push_back(solVoisine.couleurNoeud[i]);
				}
			}
			solVoisine.FctObj = couleursUtilisees.size();

			i++;
			solVoisines.push_back(solVoisine);
		}
	}

	//tri des solutions
	sort(solVoisines.begin(), solVoisines.end(), [](const TSolution solA, const TSolution solB) {return solA.FctObj < solB.FctObj; });

	//On retourne la meilleure solution
	return solVoisines[0];

}
