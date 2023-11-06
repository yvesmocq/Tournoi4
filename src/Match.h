/*
 * Match.h
 *
 *  Created on: 7 sept. 2023
 *      Author: Yves
 */

#ifndef MATCH_H_
#define MATCH_H_
using namespace std;
#include <array>
#include <sstream>
#include <string>
#include "Personne.h"

class Personne;

struct FlatMatch
{
	bool isValid;
	bool resultInit;
	char filler[6];
	array<int,4> pers;
	array<int,4> result;
};

class Match {
	array<int,4> pers;
	array<int,4> result;
	array<int,4> score; //score de chacun avant le match;
	array<int,4> diff;

	int numTour;
	bool resultInit;
	array<Personne*,4> personnes;

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

};

#endif /* MATCH_H_ */
