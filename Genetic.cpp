#include "stdafx.h"
#include "Genetic.h"
#include "Utilitaires.h"
#include <algorithm>
#include <iostream>

void runAlgoGen(TProblem LeProb, TGenetic LeGenetic)
{
	int Pere, Mere;
	TSolution Best;
	vector<TSolution> population = vector<TSolution>();
	vector<TSolution> populationEnfant = vector<TSolution>();

	population.resize(LeGenetic.TaillePop);
	populationEnfant.resize(LeGenetic.TaillePopEnfant);

	CreerPopInitialeAleaValide(population, Best, LeProb, LeGenetic);

	do
	{
		LeGenetic.Gen++;
		for (size_t i = 0; i < LeGenetic.TaillePopEnfant; i++)
		{
			Pere = Selection(LeGenetic.TaillePop, 2);
			Mere = Selection(LeGenetic.TaillePop, 2);
			populationEnfant[i] = Croisement(population[Pere], population[Mere], LeProb, LeGenetic);

			double Alea = double(rand()) / double(RAND_MAX);
			if (Alea < LeGenetic.ProbMut)
			{
				if (Best.FctObj > populationEnfant[i].FctObj)
				{
					CopierSolution(populationEnfant[i], Best, LeProb);
				}
				Mutation(populationEnfant[i], LeProb, LeGenetic);
				EvaluerSolution(populationEnfant[i], LeProb, LeGenetic);
			}
			
		}

		//**REMPLACEMENT de la population pour la prochaine génération
		Remplacement(population, populationEnfant, LeProb, LeGenetic);

		if (Best.FctObj > population[0].FctObj)				//**NE PAS ENLEVER
			CopierSolution(population[0], Best, LeProb);
		cout << "Meilleure solution trouvee (Generation# " << LeGenetic.Gen << "): " << Best.FctObj << endl;
	} while (LeGenetic.CptEval < LeGenetic.NB_EVAL_MAX);




	AfficherResultats(Best, LeProb, LeGenetic);		//**NE PAS ENLEVER
	AfficherResultatsFichier(Best, LeProb, LeGenetic, "Resutats.txt");
	VerifierSolution(Best, LeProb, true);


}
int Selection(int _Taille, double r)
{
	double R = 1 / r;
	int Alea = rand() % int(pow(_Taille, R));
	return Alea;
}

void CreerPopInitialeAleaValide(std::vector<TSolution> & unePop, TSolution & Best, TProblem unProb, TGenetic & unGenetic)
{
	//Génération de la première population triée
	for (size_t i = 0; i < unGenetic.TaillePop; i++)
	{
		TSolution SolAleatoire;
		CreerSolutionAleatoire(SolAleatoire, unProb);
		double Alea = double(rand()) / double(RAND_MAX);

		if (Alea < unGenetic.ProbMut)
		{
			if (Best.FctObj > SolAleatoire.FctObj)
			{
				CopierSolution(SolAleatoire, Best, unProb);
			}
			Mutation(SolAleatoire, unProb, unGenetic);
		}
		EvaluerSolution(SolAleatoire, unProb, unGenetic);
		unePop[i] = SolAleatoire;
	}
	//tri population
	sort(unePop.begin(), unePop.end(), [](const TSolution solA, const TSolution solB) {return solA.FctObj < solB.FctObj; });
	
	//Meilleure solution non attribuée
	if(Best.FctObj < 0)
	{
		CopierSolution(unePop[0], Best, unProb);
	}
}

void Mutation(TSolution & Mutant, TProblem unProb, TGenetic & unGen)
{
	//on parcourt tout les noeuds d'individu
	for (size_t i = 0 ; i < unProb.NbNoeuds; i++)
	{
		//probabilité de modifier un noeud
		double Alea = double(rand()) / double(RAND_MAX);
		if (Alea < unGen.ProbMut)
		{
			RechercheLocaleCouleur(Mutant, unProb, i);
		}
	}
}

TSolution Croisement(TSolution Parent1, TSolution Parent2, TProblem unProb, TGenetic & unGen)
{
	TSolution Enfant;

	vector<int> splitPos = vector<int>();
	splitPos.push_back((int(rand()) % (Parent1.couleurNoeud.size() - 1)) + 1);
	splitPos.push_back((int(rand()) % (Parent1.couleurNoeud.size() - 1)) + 1);
	sort(splitPos.begin(), splitPos.end());

	vector<int> leftSeqParent1(Parent1.couleurNoeud.begin(), Parent1.couleurNoeud.begin() + splitPos[0]);
	vector<int> middleSeqParent2(Parent2.couleurNoeud.begin() + splitPos[0], Parent2.couleurNoeud.begin() + splitPos[1]);
	vector<int> rightSeqParent1(Parent1.couleurNoeud.begin() + splitPos[1], Parent1.couleurNoeud.end());

	Enfant.couleurNoeud = leftSeqParent1;
	Enfant.couleurNoeud.insert(Enfant.couleurNoeud.end(), middleSeqParent2.begin(), middleSeqParent2.end());
	Enfant.couleurNoeud.insert(Enfant.couleurNoeud.end(), rightSeqParent1.begin(), rightSeqParent1.end());

	for (size_t node = 0; node < Enfant.couleurNoeud.size(); node++)
	{
		bool corrigerCouleurNoeud = false;
		for (size_t noeudVoisin = 0; noeudVoisin < unProb.noeudsVoisins[node].size(); noeudVoisin++)
		{
			if (Enfant.couleurNoeud[node] == Enfant.couleurNoeud[unProb.noeudsVoisins[node][noeudVoisin]])
			{
				corrigerCouleurNoeud = true;
				break;
			}
		}

		if (corrigerCouleurNoeud)
		{
			RechercheLocaleCouleur(Enfant, unProb, node);

		}
	}



	//**NE PAS ENLEVER
	EvaluerSolution(Enfant, unProb, unGen);
	return (Enfant);

}


void Remplacement(std::vector<TSolution> & Parents, std::vector<TSolution> Enfants, TProblem unProb, TGenetic unGen)
{
	vector<TSolution> newParents = vector<TSolution>();

	newParents = Parents;
	newParents.insert(newParents.end(), Enfants.begin(), Enfants.end());
	sort(newParents.begin(), newParents.end(), [](const TSolution solA, const TSolution solB) {return solA.FctObj < solB.FctObj; });

	int i = 0;
	while(i < unGen.TaillePopEnfant)
	{
		newParents.pop_back();
		i++;
	}
	
	Parents = newParents;

}

void RechercheLocaleCouleur(TSolution & uneSol, TProblem unProb, int noeud) {

	//recherche locale, on parcout les couleurs
	for (size_t couleur = 0; couleur < unProb.NbNoeuds; couleur++)
	{
		//on regarde si la couleur que l'on veut attribuer a notre noeud n'est pas déjà présent chez ses voisins
		bool newColor = true;
		for (size_t noeudVoisin = 0; noeudVoisin < unProb.noeudsVoisins[noeud].size(); noeudVoisin++)
		{
			//si oui passage à la couleur suivante (break pour éviter de parcourir tout les noeuds voisins)
			if (couleur == uneSol.couleurNoeud[unProb.noeudsVoisins[noeud][noeudVoisin]])
			{
				newColor = false;
				break;
			}
		}
		//si non on attribue la couleur à notre noeud (et on break pour éviter de parcourir les autres couleurs)
		if (newColor)
		{
			uneSol.couleurNoeud[noeud] = couleur;
			break;
		}
	}
}