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
#include "Tools.h"
#include "Mask.h"
#include "Personne.h"
#include "Match.h"
#include "PartitionInt.h"

struct FlatTirage
{
	array<FlatPers,Tools::sizeMax> allPers;
	array<FlatMatch,Tools::matchMax> allMatches;
};

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

	int nbPersonnes;

	array<Personne *, 4> convArray(array<int,4> arr) const;

	string nomFichier;

	int maxIndice;

	int nbTentatives;
	const int borneTentatives=20000;
public:
	void save(string fileName) const;
	static Tirage *getInstance();
	static Tirage * getInstance(const FlatTirage &ft);
	static Tirage * getInstance( const string &nomFichier);
	static bool isInstance();

	void initInstance();
	void initInstance(const FlatTirage &ft);

	~Tirage();
	int id_match=0;

	bool makeTirage(bool fl2=false);
	void deletePersonne(Personne *p);
	void addPersonne(Personne *p);
	int addMatch(Match *m);
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
	FlatTirage getFlat() const;


	void getPersSortNum( vector<Personne *> &result, function<bool(Personne *,Personne *)> fct );

	void setNomFichier( const string &nomFichier );

	int getNbPersonnes() const;

	void save() const;

};

#endif /* TIRAGE_H_ */
