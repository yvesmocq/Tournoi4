//
// Copyright 2023 Yves Mocquard
//
//This file is part of Tournoi4.
//
// Tournoi4 is free software: you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// Tournoi4 is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
// A PARTICULAR PURPOSE. See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with
// Tournoi4. If not, see <https://www.gnu.org/licenses/>. 4
//
/*
 * Tirage.h
 *
 *  Created on: 8 sept. 2023
 *      Author: Yves Mocquard
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
	bool flagPresAjout;
	char filler[31];
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
	bool rec_appar4(vector<Personne *> &vp, const array<int,3> & dec, vector<Match*> &newmatch, int *mi, bool fl2,
			const vector<Personne *> *vtt);
	vector<Personne *> allPersonnes;
	list<Match *> allMatches;
	vector<vector<Match*>> allTours;

	bool flagNouveauTour;
	bool flagPresAjout;

	int maxNameAffLength;

	int nbPersonnes;

	array<Personne *, 4> convArray(array<int,4> arr) const;

	string nomFichier;
	string nomFichierAdd;


	int maxIndice;

	int nbTentatives;
	const int borneTentatives=20000;

	void save(const string & nomfic, bool flag_plus=false) const;

	int resMedian=0;

public:
	void save(string fileName) const;
	static Tirage *getInstance();
	static Tirage * getInstance(const FlatTirage &ft);
	static Tirage * getInstance( const string &nomFichier);
	static bool isInstance();

	void initInstance();
	void initInstance(const FlatTirage &ft);

	void initMaxNameAffLength();
	int getMaxNameAffLength() const;
	int getLengthAff(const Personne * p) const;


	~Tirage();
	int id_match=0;

	bool makeTirage(bool fl2=false, const vector<Personne *> *vtt=nullptr);
	void deletePersonne(const Personne *p);
	void modifPersonne(const Personne *p);
	void addPersonne(Personne *p);
	void addMatch(Match *m);
	const vector<Match *> &getLastTour() const;
	const vector<Match *> &getTour(int n) const;
	const vector<Personne *> & getAllPersonnes() const;
	const list<Match *> & getAllMatches() const;

	int nbMatchNonSaisie() const;
	int getNbTentatives() const;
	int getMaxIndice() const;
	int getNbTours() const
	{
		return allTours.size();
	}
	FlatTirage getFlat() const;



	void getPersSortNum( vector<Personne *> &result, function<bool(Personne *,Personne *)> fct, function<bool(const Personne*)> filtre = Personne::stAll );

	void setNomFichier( const string &nomFichier );
	void setNomFichierAdd( const string &nomFichier );

	int getNbPersonnes() const;

	void save(bool flag_plus=false) const;

	bool isRerenc() const;

	bool isPresAjout() const;
	void setPresAjout( bool fl);

	int nb3SameClub( const vector<Match *> &vm) const;
	int nb4SameClub( const vector<Match *> &vm) const;

	int getNote(const vector<Match *> &vm) const;

	int getResMedian() const;
	void setResMedian(int v);

};

#endif /* TIRAGE_H_ */
