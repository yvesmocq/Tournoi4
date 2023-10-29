/*
 * Tirage.cpp
 *
 *  Created on: 8 sept. 2023
 *      Author: Yves
 */
using namespace std;
#include <cstdint>
#include <iostream>
#include <set>
#include <array>
#include <algorithm>

#include "Tirage.h"



//
Tirage * Tirage::instance=nullptr;

Tirage::Tirage() {
	Personne::resetSerieId();

}
Tirage::~Tirage() {
	for( auto p: allPersonnes)
		delete p;
	for( auto p: allMatches)
		delete p;
	Personne::resetSerieId();
	Tirage::instance=nullptr;

	instance=nullptr;
}

Tirage * Tirage::getInstance()
{
	if ( instance == nullptr )
	{
		instance = new Tirage();
	}
	return instance;
}


Match *Tirage::getMatch(array<int,4> ap) const
{
	array<Personne *,4> pp;
	for( int i = 0 ; i < 4 ; i++)
	{
		pp[i] = allPersonnes[ap[i]];
	}
	return new Match(pp);
}


bool Tirage::rec_appar4( vector<Personne *> &vp, const array<int,3> & dec, list<Match*> &newmatch, int *mi, bool fl2)
{
	Tools *tools=Tools::getInstance();
	const bool flagcout=false;

	flagcout && cout << "rec_appar4 dec="<< tools->to_string(dec) <<"prof="<<newmatch.size()<<" vp.size()="<<vp.size()<<endl;


	array<int,4> result={0};

	int indres=0;
	int indpers=0;
	int borne = 4;
	bool flagtittable=false;
	if ( vp.size() %4 != 0 )
	{
		flagtittable = true;
		result[indres] = 0;
		borne = (vp.size() %4) + 1;
		indpers = -1;
	}
	else
	{
		result[indres]= vp[indpers]->id_pers;
	}


	Mask<> maskdeja(result[indres]);
	indpers += dec[indres++];
	while( indres < borne )
	{
		bool fltrouve=false;
		bool flborne=false;

	//	cerr <<"trace1" <<endl;

		do
		{
			indpers++;
			flborne = (indpers >= (int)vp.size());
			if ( ! flborne )
			{
				if ( flagtittable && ! vp[indpers]->getMaskMatch1().isBit(0))
					fltrouve = true;
				else
				{
					if( fl2 )
					{
						fltrouve = !vp[indpers]->getMaskMatch2().isBits(maskdeja);
						result[indres] = vp[indpers]->id_pers;
						fltrouve = fltrouve && isGood3(result, indres+1);

					}
					else
						fltrouve = !vp[indpers]->getMaskMatch1().isBits(maskdeja);
				}

				if ( flagtittable && fltrouve && vp[indpers]->getMaskMatch1().isBit(0) )
					fltrouve =false;

			}
		} while(!fltrouve && !flborne );
//		cerr <<"trace2" <<endl;

		if ( fltrouve)
		{
			maskdeja.setBit(vp[indpers]->id_pers);
			result[indres]= vp[indpers]->id_pers;
			if ( indres != 3 )
				indpers += dec[indres];
			indres++;
		}
	//	cerr <<"trace3" <<endl;

		if ( flborne )
			break;
	}
	if ( indres == borne )
	{
	//	cerr <<"trace4" <<endl;

		*mi = max(maxIndice, indpers);
		// c'est OK
//		cerr <<"trace41" <<endl;
		vector<Personne *> newvp(((vp.size()-1)/4)*4);
//		cerr <<"trace42" <<endl;
//		cerr << "result="<< tools->to_string(result)<<endl;
		Match *match = getMatch(result);
//		cerr <<"trace43" <<endl;
		auto inewvp=newvp.begin();
//		cerr <<"trace44" <<endl;
		for ( auto  ivp=vp.rbegin()  ; ivp != vp.rend() ; ivp++)
		{
			if ( !match->isIn(*ivp) )
			{
				*inewvp++ = *ivp;
			}
		}
//		cerr <<"trace5" <<endl;
		newmatch.push_back(match);
		if ( newvp.size() == 0)
		{
			// c'est tout bon
			flagcout && cout << "OK0"<<endl;

			return true;
		}
		if ( newvp.size() == 4)
		{
			bool ret = rec_appar4(newvp, this->partInt.getList().front(), newmatch, mi, fl2);
			if ( ret == false )
			{
				flagcout && cout << "Nok1" <<endl;
				delete match;
				newmatch.pop_back();
			}
			else
				flagcout && cout << "OK0" <<endl;
			return ret;
		}
		bool ret = false;
		for( const array<int,3>  & stdec4 : this->partInt.getList() )
		{
			if ((ret = rec_appar4(newvp, stdec4, newmatch, mi, fl2)))
				break;
			if ( nbTentatives >= borneTentatives )
			{
				ret = false;
				break;
			}
		}
	//	flagcout && cout << "ret="<<ret<<endl;
		if ( ret )
		{
			flagcout && cout << "OK"<<endl;
			return true;
		}
		else
		{
			flagcout && cout <<"Nok"<<endl;
			delete match;
			newmatch.pop_back();
//			cout << "recalcul appariement vp.size()="<<vp.size()<<endl;
			return false;
		}

	}
	else
	{
//		cout <<"borne atteinte dec="<< tools->to_string(dec)<<" vp.size()="<<vp.size() <<endl;
		nbTentatives++;
		flagcout && cout <<"Nok nbTentatives++"<<endl;
		return false;
	}
}

bool Tirage::makeTirage(bool fl2)
{

	bool flagok = false;
	const bool flagcout=false;

	list<Match *> newmatch;

	for( int i= 0 ;  !flagok && i < 100 ; i++ )
	{

		vector<Personne *> vp(allPersonnes.begin()+1, allPersonnes.end());

		for ( Personne * p : allPersonnes)
		{
			p->calculNote();
			p->mkMaskMatch();
		}

		sort(vp.begin(), vp.end(), Personne::PersonneLess);





		maxIndice=0;

		nbTentatives = 0;

		for( auto dec:this->partInt.getList())
		{
//			if ( rec_appar4(vp, dec, newmatch,  &maxIndice, fl2) && maxIndice < double(vp.size())/2  )
			if ( rec_appar4(vp, dec, newmatch,  &maxIndice, fl2) )
			{
				flagcout && cout <<"rec_app true"<<endl;
				flagok = true;
				break;
			}
			else
			{
				flagcout && cout <<"rec_app false maxIndice="<< maxIndice << endl;
				newmatch.clear();
			}
			if ( nbTentatives >= borneTentatives )
			{
				flagcout && cout <<"nbTentative = "<<nbTentatives <<endl;
				return false;

			}
		}
		flagcout && cout <<"MaxIndice="<<maxIndice<<endl;

	}
	if ( !flagok )
		return false;

	allTours.push_back(newmatch);

	for ( Match *m: newmatch)
	{
		addMatch(m, allTours.size()-1);
	}

	return true;
}

// il s'agit de la validation definitve du match on meme à jour l'objet Personne
void Tirage::addMatch(Match *m, int numTour)
{
	int nbzero=0;
	for ( auto p: m->getPersonnes() )
	{
		if ( p->id_pers == 0 )
			nbzero++;
		if ( nbzero > 1)
			break;
		p->addMatch(m);
	}
	allMatches.push_back(m);
	if ( !m->istittable() )
	{
		for ( Mask<> mask:m->get3())
		{
			mask_3set.insert(mask);
		}
	}
	m->setNumTour(numTour);
}
bool Tirage::isGood3(array<int,4> arr, int nb ) const
{
	int deb = 0;
	if ( nb < 3 )
		return true;
	if ( nb == 3 )
	{
		deb = 3;
	}
	for ( int i = deb ; i < 4 ; i++)
	{
		Mask<> m;
		for ( int j = 0 ; j < 4 ; j++)
		{
			if ( j != i )
				m.setBit(arr[j]);
		}
		if ( mask_3set.find(m) != mask_3set.end())
			return false;
	}
	return true;
}

void Tirage::addPersonne(Personne *p)
{
	allPersonnes.push_back(p);
}



void Tirage::affResult()
{
	vector<Personne *> vp(allPersonnes.begin(), allPersonnes.end());

	vector<int> newId(vp.size());

	for ( Personne * p : allPersonnes)
	{
		p->calculNote();
	}

	sort(vp.begin(), vp.end(), Personne::PersonneMore);

	vp.pop_back();

	for( int i = 0 ; i < (int)vp.size() ; i++ )
	{
		vp[i]->setId_prov(i);
	}


	for ( Personne *p:vp)
	{
		cout << p->mkLigne() << endl;
	}

}
const list<Match *> & Tirage::getLastTour() const
{
	return allTours.back();
}

const list<Match *> & Tirage::getTour( int n) const
{
	return allTours[n];
}
const vector<Personne *> & Tirage::getAllPersonnes() const
		{
	return allPersonnes;
		}
const list<Match *> & Tirage::getAllMatches() const
		{
	return allMatches;
		}
int Tirage::getNbTentatives() const
{
	return nbTentatives;
}
int Tirage::getMaxIndice() const
{
	return maxIndice;
}
