/*
 * Tirage.h
 *
 *  Created on: 8 sept. 2023
 *      Author: Yves
 */

#ifndef TIRAGE_H_
#define TIRAGE_H_
#include <cstdlib>
#include <cstdint>
#include <vector>
#include <list>
#include <set>
#include "Mask.h"
#include "Personne.h"
#include "Match.h"
#include "PartitionInt.h"

class Tirage {
private:
	PartitionInt partInt;
	Tirage();
	static Tirage *instance;

	set<Mask<>> mask_3set;

	bool isGood3(array<int,4> arr, int nb ) const;

	Match * getMatch(array<int,4>) const;
	bool rec_appar4(vector<Personne *> &vp, const array<int,3> & dec, list<Match*> &newmatch, int *mi, bool fl2);
	vector<Personne *> allPersonnes;
	list<Match *> allMatches;
	vector<list<Match*>> allTours;
	struct
	    {
	        bool operator()(Personne *p1, Personne *p2) const { return p1->note < p2->note;}
	    }
	    PersonneLess;
		struct
		    {
		        bool operator()(Personne *p1, Personne *p2) const { return p1->note > p2->note;}
		    }
		PersonneMore;

	int maxIndice;

	int nbTentatives;
	const int borneTentatives=20000;
public:
	static Tirage *getInstance();
	~Tirage();
	int id_match=0;

	bool makeTirage(bool fl2=false);

	void addPersonne(Personne *p);
	void addMatch(Match *m);
	void affResult();
	const list<Match *> &getLastTour() const;
	const list<Match *> &getTour(int n) const;
	const vector<Personne *> & getAllPersonnes() const;
	const list<Match *> & getAllMatches() const;
	int getNbTentatives() const;
	int getMaxIndice() const;
	int getNbTours() const
	{
		return allTours.size();
	}

};

#endif /* TIRAGE_H_ */
