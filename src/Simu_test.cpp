/*
 * Simu_test.cpp
 *
 *  Created on: 18 sept. 2023
 *      Author: Yves
 */

#include "Simu.h"

bool test_prob_gain()
{
	Simu *simu=Simu::getInstance();

	if (  simu->probGain(-1000.) >0.004 )
		{
		cout<< "erreur probGain(-1000)"<<endl;
		return false;
		}
	if (  simu->probGain(1000.) <0.996 )
		{
		cout<< "erreur probGain(1000)"<<endl;
		return false;
		}
	double res = simu->probGain(200) + simu->probGain(-200);

	if ( res < 0.9999 || res > 1.0001 )
	{
		cout<< "erreur probGain(200) +probGain(-200)"<<endl;
		return false;
	}

	cout <<"test simu->probGain OK"<<endl;


	return true;

}


bool verif_tour(int n)
{
	Tirage *pt=Tirage::getInstance();
	const list<Match *> & lm = pt->getTour(n);
	vector<int> vres(pt->getAllPersonnes().size());
	for ( const Match *pm:lm)
	{
		array<int,4> pid=pm->getPersId();
		if ( pid[0] != 0 )
		{
			for( int id:pid)
			{
				if ( vres[id] )
				{
					cout << "2 fois la meme personne dans le meme tour !!!" <<endl;
					cout << "tour="<<n<< " id="<<id<<endl;
					return false;
				}
				vres[id] = true;
			}
		}
		else
		{
			if ( vres[0] )
			{
				cout << "Deux matches degradés" << endl;
			}
			for ( int i = 1 ; i < 4 ; i++)
			{
				int &id=pid[i];
				if ( id != 0 )
				{
					if ( vres[id] )
					{
						cout << "Deux fois la meme personne dans le meme tour !!!" <<endl;
						cout << "tour="<<n<< " id="<<id<<endl;
						return false;
					}
					vres[id] = true;
				}
			}
			vres[0] = true;
		}
	}

	int deb = ((vres.size()-1)%4 == 0);

	for ( int i = deb ; i < (int)vres.size() ; i++)
	{
		if ( !vres[i])
		{
			cout <<"erreur i="<<i<<" non present" << endl;
			return false;

		}
	}
	return true;
}

bool verif_tour_3()
{
	Tirage *pt=Tirage::getInstance();

	set<Mask<>> m3;

	for ( const Match *pm: pt->getAllMatches())
	{
		if ( !pm->istittable() )
		{
			array<Mask<>,4> lm = pm->get3();
			for ( const Mask<> & mask:lm)
			{
				if ( m3.find(mask) != m3.end() )
				{
					cout << "erreur 3 personnes dans 2 match différents mask="<<mask.to_string() << endl;
					return false;
				}
				else
				{
					m3.insert(mask);
				}
			}
		}
	}
	return true;

}


bool test_simu(int nbpers)
{
	cout <<"test_simu nbpers="<<nbpers<<endl;
	Simu *simu=Simu::getInstance(nbpers);

	bool flag=false;

	for ( int i=0 ;  ; i++)
	{
		cout <<"nbpers="<<nbpers<< " tour="<<i<< " flag="<<flag<<endl;

		if ( !simu->simule(1,flag) )
			{
			return false;
			}
		cout << "fin tour="<<i<<endl;
		if ( !verif_tour(i) )
			return false;
		cout <<"nbTentatives=" << simu->getNbTentatives()<<endl;
		simu->affResult();
		if ( flag && !verif_tour_3() )
			return false;
		if ( simu->getNbTentatives() > 10 ||simu->getMaxIndice() > nbpers/3)
		{
			if ( flag )
				break;
			else
				flag = true;
		}
	}
	if ( false )
	{
	for ( int i = 0 ; i < 4 ; i++ )
	{
		if ( i)
		cout << "tour="<<(i+4)<<endl;
		simu->simule(1,true);
		if ( !verif_tour(i+4) )
			return false;
		if( !verif_tour_3() )
			return false;
	}
	cout <<"affresult1"<<endl;
	simu->affResult();
	cout <<"affresult2"<<endl;
	}

	return true;

}
void verif_borne(int nbpers, int flagcout)
{
	Simu *simu=Simu::getInstance(nbpers);
	const bool flagoutplus=false;

	flagcout && cout <<"nbpers="<<nbpers<<" i= ";

	bool flag=false;

	int i=0;
	while( i < 50)
	{
		flagoutplus && cout <<"trace i="<<i<< " flag="<<flag<< endl;
		if ( !simu->simule(1,flag) )
		{
			if( flag )
				break;
			else
			{
				flag = true;
				flagcout && cout << i <<" , ";
			}
		}
		else
		{
			flagoutplus && cout << "verif_tour="<< verif_tour(i)<<endl;
			flagoutplus && cout <<"nbTentatives=" << simu->getNbTentatives()<<endl;
//			simu->affResult();

			i++;
		}
		flagoutplus && cout <<"nbTentatives=" << simu->getNbTentatives()<<endl;


	}
	flagcout && cout <<i<<endl;



}
bool test_simubig()
{
	for ( int i = 8 ; i <= 80 ; i++)
	{

		// cout << "verf_borne i="<<i<<endl;
		verif_borne( i , true);

		Tirage *pt = Tirage::getInstance();
		for ( int j = 0 ; j < pt->getNbTours() ; j++ )
		{
			if ( !verif_tour(j) )
			{
				cout << "Erreur verif_tour nbpers="<<i<<" tour="<<j<<endl;
				return false;
			}
		}
		if ( !verif_tour_3() )
		{
			cout << "Erreur verif_tour_3 nbpers="<<i<<endl;
			return false;
		}
//		Simu *simu=Simu::getInstance(i);
//		simu->affResult();

//		if ( !test_simu(i) )
//		{
//			cout <<"Erreur test_simu nbpers="<<i<<endl;
//			return false;
//		}
	}
	return true;
}
bool test_simu()
{
	return test_simubig();
}


