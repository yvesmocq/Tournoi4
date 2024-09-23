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
 * Match.h
 *
 *  Created on: 7 sept. 2023
 *      Author: Yves Mocquard
 */

#ifndef MATCH_H_
#define MATCH_H_
using namespace std;
#include <array>
#include <sstream>
#include <string>
#include <set>
#include "Personne.h"

class Personne;

struct FlatMatch
{
	bool isValid;
	bool resultInit;
	char filler[2];
	int numTour;
	array<int,4> pers;
	array<int,4> result;
};

class Match {
	bool resultInit;
	array<int,4> pers;
	array<int,4> result;
	array<int,4> score; //score de chacun avant le match;
	array<int,4> diff;

	int numTour;
	array<Personne*,4> personnes;


	int sumScore() const
	{
		return score[0]+score[1]+score[2]+score[3];
	}

	struct M_More
	    {
	        bool operator()(Match *m1, Match *m2) const {
	        	return m1->istittable() ? false : m2->istittable() ? true : m1->sumScore() > m2->sumScore();}
	    };

public:
	Match(array<Personne *,4> personnes );
	Match(const FlatMatch &fm);
	~Match();
	bool isIn(const Personne *p) const;
	int getScore(const Personne *p, int *diff=nullptr) const;
	string toStr( const Personne *p) const;
	array<Mask<>, 4> get3() const;
	array<array<Mask<>,6>, 2> get2() const;

	array<int,4> getPersId() const;
	array<Personne*,4> getPersonnes() const;
	bool isResultInit() const;
	void setResult( array<int,4> res);
	array<int,4> getResult() const;

	array<int,4> getScore() const; //score de chacun avant le match;
	array<int,4> getDiff() const;
	bool istittable() const;

	void setNumTour( int numTour );
	int getNumTour() const;

	FlatMatch getFlat() const;

	static const M_More MatchMore;

	bool is3sameClub() const;
	bool is4sameClub() const;
	int nbClub() const;

};

#endif /* MATCH_H_ */
