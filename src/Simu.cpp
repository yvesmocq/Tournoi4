/*
 * Simu.cpp
 *
 *  Created on: 18 sept. 2023
 *      Author: Yves
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

Simu::Simu(int nbPers): nbPers(nbPers), instTirage(Tirage::getInstance()) {

	Tools *instTools=Tools::getInstance();

	Personne::resetSerieId();

	struct PSim ps;
	ps.p = new Personne(0);

	instTirage->addPersonne(ps.p);

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
	delete instTirage;
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
	for( int i=0; i < nbtour ; i++)
	{
//		cout <<"trace simule i="<<i<<endl;

		if ( !instTirage->makeTirage(fl2) )
		{
//			cout << "Erreur tirage!!!"<<endl;
			return false;
		}

//		cout <<"trace simule1 i="<<i<<endl;

		for( Match * m:instTirage->getLastTour() )
		{
			this->calResult(m);
		}

//		cout << "maxIndice="<<instTirage->getMaxIndice()<<endl;

	}
	return true;
}

