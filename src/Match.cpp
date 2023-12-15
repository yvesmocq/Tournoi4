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
 * Match.cpp
 *
 *  Created on: 7 sept. 2023
 *      Author: Yves Mocquard
 */

#include "Match.h"

//
const Match::M_More Match::MatchMore=M_More();

// la creation du match ne veut pas dire sa validation
// on ne touche pas à Personne lors de cette creation
Match::Match(array<Personne *,4> personnes ):
resultInit(false),
result({0,0,0,0})
{
	double sumscore=0.;
	for( int i = 0 ; i < 4 ; i++)
	{
		Personne *p =  personnes[i];
		this->personnes[i] = p;
		pers[i] = p->id_pers;
		score[i] = p->getResult();
		sumscore += p->getResult();
	}
	sumscore /= 4.;
	for( int i=0 ; i < 4 ; i++)
	{
		diff[i] = double(score[i]) - sumscore;
	}
}

Match::~Match() {
	// Rien à faire
}

bool Match::isIn(const Personne *p) const
{
	for ( int i = 0 ; i < 4 ; i++)
	{
		if ( pers[i] == p->id_pers)
			return true;
	}
	return false;
}

int Match::getScore(const Personne *p, int *diff) const
{
	if (resultInit)
	{
		for( int i = 0 ; i < 4 ; i++ )
		{
			if ( p->id_pers == pers[i] )
			{
				if ( diff != nullptr )
				{
					*diff = this->diff[i];
				}
				return result[i];
			}
		}
	}
	// Erreur
	return -1;
}


array<Mask<>, 4> Match::get3() const
{
	array<Mask<>, 4> res;
	for ( int i = 0 ; i < 4 ; i++ )
	{
		Mask<> &v=res[i];
		for ( int j = 0 ; j < 4 ; j++ )
		{
			if ( j != i )
			{
				v.setBit(this->pers[j]);
			}
		}

	}
	return res;
}
bool Match::istittable() const
{
	return pers[0] == 0;
}
array<array<Mask<>,6>, 2> Match::get2() const
{
	array<array<Mask<>,6>, 2> res;
	const array<array<int,4>,6> tab{{ {{1,2,3,4}},{{1,3,2,4}},{{1,4,2,3}},
		{{2,3,1,4}},{{2,4,1,3}},{{3,4,1,2}} }};
	for( int i = 0 ; i < 6 ; i++ )
	{
		Mask<> & m1=res[i][0];
		Mask<> & m2=res[i][1];
		const array<int, 4> & t=tab[i];
		m1.setBit(pers[t[0]]);
		m1.setBit(pers[t[1]]);
		m2.setBit(pers[t[2]]);
		m2.setBit(pers[t[3]]);
	}
	return res;
}
array<int,4> Match::getPersId() const
{
	return pers;
}
array<Personne *,4> Match::getPersonnes() const
{
	return personnes;
}
bool Match::isResultInit() const
{
	return resultInit;
}
void Match::setResult(array<int,4> res)
{
	result = res;
	resultInit = true;
}
array<int,4> Match::getResult() const
{
	return result;
}
array<int,4> Match::getScore() const
{
	return score;
}
array<int,4> Match::getDiff() const
{
	return diff;
}
void Match::setNumTour(int numTour)
{
	this->numTour = numTour;
}
int Match::getNumTour() const
{
	return numTour;
}
FlatMatch Match::getFlat() const
{
	FlatMatch fm={};
	fm.isValid = true;
	fm.resultInit = this->resultInit;
	fm.pers = this->pers;
	fm.result = this->result;
	fm.numTour = this->numTour;
	return fm;
}
bool Match::is3sameClub() const
{
	int nbSame=0;
	for ( const Personne *p1:personnes)
	{
		if ( p1 == nullptr || p1->id_pers == 0 )
			return false;
		for ( const Personne *p2:personnes)
		{
			p1->isSameClub(p2) && nbSame++;
		}
	}
	return nbSame >= 9;

}
int Match::nbClub() const
{
	set<string> sc;

	for ( const Personne *p:personnes)
	{
		if ( p == nullptr || p->id_pers == 0 )
			return 0;
		sc.insert(p->club());
	}
	return sc.size();


}



