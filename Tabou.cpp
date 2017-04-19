#include "stdafx.h"
#include "Descente.h"
#include "Utilitaires.h"
#include <iostream>
#include "Tabou.h"
#include <algorithm>

void runAlgoTabou(TProblem LeProb, TTabou LAlgo)
{
	TSolution Courante;		//Solution active au cours des itérations
	TSolution Next;			//Solution voisine retenue à une itération
	TSolution Best;			//Meilleure solution depuis le début de l'algorithme //Non utilisé pour le moment 

	CreerSolutionAleatoire(Courante, LeProb);
	EvaluerSolution(Courante, LeProb, LAlgo);
	AfficherSolution(Courante, LeProb, "SolInitiale: ");
	Best = Courante;

	do
	{
		Next = GetSolutionVoisineTabou(Courante, LeProb, LAlgo);
		//AfficherSolution(Courante, LeProb, "Courante: ", false);
		//AfficherSolution(Next, LeProb, "Next: ", false);
		EvaluerSolution(Next, LeProb, LAlgo);

		if (Next.FctObj <= Courante.FctObj)	//**amélioration
		{
			//Mise à jour des Tabous
			pair<int, int> tabou = GetTabou(Courante, Next, LeProb);
			LAlgo.listeTabous.insert(LAlgo.listeTabous.begin(), tabou);
			if(LAlgo.listeTabous.size() > LAlgo.nombreEchangesMax)
			{
				//suppression du tabou le plus ancien.
				LAlgo.listeTabous.pop_back();
			}

			Courante = Next;
			cout << "Fct Obj Nouvelle Courante: " << Courante.FctObj << endl;
			//AfficherSolution(Courante, LeProb, "NouvelleCourante: ", false);
		}
		
	} while (LAlgo.CptEval < LAlgo.NB_EVAL_MAX && Courante.FctObj != 0);

	AfficherResultats(Courante, LeProb, LAlgo);
	AfficherResultatsFichier(Courante, LeProb, LAlgo, "Resultats.txt");
	VerifierSolution(Courante, LeProb, true);
}

TSolution GetSolutionVoisineTabou(const TSolution uneSol, TProblem unProb, TTabou& unAlgo)
{
	//Génération des solutions voisines
	vector<TSolution> solVoisines = vector<TSolution>();

	int i = 0;
	while(i < unAlgo.voisinsGeneres)
	{
		int noeud = rand() % unProb.NbNoeuds;
		int couleur = rand() % unProb.NbNoeuds;

		pair<int, int> echange = pair<int, int>(noeud, couleur);
		TSolution solVoisine;
		CopierSolution(uneSol, solVoisine, unProb);
		solVoisine.couleurNoeud[noeud] = couleur;
		VerifierSolution(solVoisine, unProb, false);

		//On ne récupère dans les voisins de notre solution que des solutions valides et dont l'échange noeud/nouvelle couleur ne fait pas partie de la liste des tabous.
		if (solVoisine.Valide && find(unAlgo.listeTabous.begin(), unAlgo.listeTabous.end(), echange) == unAlgo.listeTabous.end())
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

	//On retourne la meilleure solution et l'échange pour la liste des tabous
	return solVoisines[0];
	

}

pair<int,int> GetTabou(TSolution Courante, TSolution Next, TProblem unProb)
{
	for(size_t i = 0; i < unProb.NbNoeuds; i++)
	{
		if(Courante.couleurNoeud[i] != Next.couleurNoeud[i])
		{
			return pair<int, int>(i, Courante.couleurNoeud[i]);
		}
	}
	return pair<int, int>();
}
