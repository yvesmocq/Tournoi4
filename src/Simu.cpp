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
 * Simu.cpp
 *
 *  Created on: 18 sept. 2023
 *      Author: Yves Mocquard
 */

#include "Simu.h"

// static
Simu * Simu::instance=nullptr;

// static
Simu *Simu::getInstance(int nbPers)
{
	if ( Simu::instance != nullptr && Simu::instance->nbPers != nbPers)
	{
		delete Simu::instance;
	}
	if ( Simu::instance == nullptr )
	{
		Simu::instance = new Simu(nbPers);
	}
	return Simu::instance;
}

Simu::Simu(int nbPers): nbPers(nbPers)  {

	Tools *instTools=Tools::getInstance();

	Tirage *instTirage(Tirage::getInstance());

	struct PSim ps;
	ps.p = instTirage->getAllPersonnes()[0];


	allPS.push_back(ps);


	// populate
	for ( int i=0 ; i <nbPers ; i++ )
	{
		stringstream s;
		ps.elo = instTools->genElo();

		s << i <<" "<< ps.elo;


		ps.p = new Personne(s.str());

		instTirage->addPersonne(ps.p);

		allPS.push_back(ps);
	}

}

Simu::~Simu()
{
	delete Tirage::getInstance();
	Simu::instance = nullptr;
}

double Simu::probGain(double diffElo)
{
	return 1./(1.+pow(10.,-diffElo/400));
}
void Simu::calResult(Match *pm)
{
	array<array<int,4>,3> tabmatch{{ {{0,1,2,3}},{{0,2,1,3}},{{0,3,1,2}}}};


	array<int,4> result{0};
	const array<int,4> pers(pm->getPersId());

	if ( pers[0] == 0 )
	{
		for ( int i = 1 ; i < 4 ; i++)
		{
			if ( pers[i] != 0 )
			{
				result[i] =2;
			}
		}
	}
	else
	{
		Tools *instTools=Tools::getInstance();
		for( array<int,4> &t : tabmatch )
		{
			double elofirst = double(allPS[pers[t[0]]].elo + allPS[pers[t[1]]].elo)/2.;
			double elosecond = double(allPS[pers[t[2]]].elo + allPS[pers[t[3]]].elo)/2.;
			double pg = probGain(elofirst-elosecond);
			if ( instTools->bernoulli(pg) )
			{
				result[t[0]]++;
				result[t[1]]++;
			}
			else
			{
				result[t[2]]++;
				result[t[3]]++;
			}
		}
	}
	pm->setResult(result);
}

bool Simu::simule( int nbtour, bool fl2 )
{
	Tirage *instTirage(Tirage::getInstance());

	for( int i=0; i < nbtour ; i++)
	{
//		cerr <<"trace simule i="<<i<<" nbtour="<<nbtour<<endl;

		if ( !instTirage->makeTirage(fl2) )
		{
//			cerr << "Erreur tirage!!!"<<endl;
			return false;
		}

//		cerr <<"trace simule1 i="<<i<<endl;

		for( Match * m:instTirage->getLastTour() )
		{
			this->calResult(m);
		}

//		cout << "maxIndice="<<instTirage->getMaxIndice()<<endl;

	}
	return true;
}

