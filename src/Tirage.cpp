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
#include <string>

#include "Tirage.h"





//
Tirage * Tirage::instance=nullptr;

Tirage::Tirage():allPersonnes(Tools::getInstance()->sizeMax), maxNameAffLength(0), nbPersonnes(0), maxIndice(0),nbTentatives(0)  {
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

// static function
Tirage * Tirage::getInstance()
{
	if ( instance == nullptr )
	{
		instance = new Tirage();
		instance->initInstance();
	}
	return instance;
}
void Tirage::initInstance()
{
	allPersonnes[0] = new Personne(0);
}
void Tirage::initInstance( const FlatTirage &ft)
{
	initInstance();
	for( const FlatPers & fp:ft.allPers)
	{
		if ( fp.isValid )
		{
			Personne *p = new Personne(fp);
			allPersonnes[p->id_pers] = p;
			maxNameAffLength = max(maxNameAffLength, p->getAffLength());
			nbPersonnes++;
		}
	}
	nbPersonnes--; // pour ne pas prendre en compte l'id 0
	for( const FlatMatch &fm:ft.allMatches )
	{
		if ( fm.isValid)
		{
			Match *m = new Match(convArray(fm.pers));
			if ( fm.resultInit )
			{
				m->setResult(fm.result);
			}
			addMatch(m);
		}

	}

}

// static function
Tirage * Tirage::getInstance(const FlatTirage &ft)
{
	if ( instance != nullptr )
	{
		delete instance;
	}
	instance = new Tirage();

	instance->initInstance(ft);
	Personne::resetSerieId();

	return instance;
}
// static function
Tirage *Tirage::getInstance( const string & nomFichier)
{
	FILE *fd=fopen(nomFichier.c_str(),"rb");
	Tirage *pt=nullptr;
	FlatTirage ft;
	if ( fd == NULL )
	{
		cout <<"Il n'y a pas de fichier de sauvegarde on repart à zéro"<<endl;
		pt =Tirage::getInstance();
	}
	if ( pt == nullptr )
	{

		int res = fread(&ft, sizeof(FlatTirage), 1, fd);
		if ( res != 1 )
		{
			cout << "Problème lecture fichier on repart à zéro"<<endl;
			pt =  getInstance();
		}
		fclose(fd);
	}

	if ( pt == nullptr )
	{
		pt =Tirage::getInstance(ft);
	}

	pt->setNomFichier( nomFichier );

	return pt;

}

// static function
bool Tirage::isInstance()
{
	return Tirage::instance != nullptr;
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



bool Tirage::rec_appar4( vector<Personne *> &vp, const array<int,3> & dec, vector<Match*> &newmatch, int *mi, bool fl2,
		const vector<Personne *> *vtt)
{
	Tools *tools=Tools::getInstance();
	const bool flagcout=false;

	flagcout && cout << "rec_appar4 dec="<< tools->to_string(dec) <<"prof="<<newmatch.size()<<" vp.size()="<<vp.size()<<endl;


	array<int,4> result={0};

	int indres=0;
	int indpers=0;
	int borne = 4;
	bool flagtittable=false;
	Mask<> maskdeja;
	if ( vp.size() %4 != 0 )
	{
		flagtittable = true;
		result[indres] = 0;
		maskdeja.setBit(result[indres]);
		if ( vtt != nullptr )
		{
			for( const Personne * p: *vtt)
			{
				result[++indres] = p->id_pers;
				maskdeja.setBit(result[indres]);
			}
		}
		borne = (vp.size() %4) + 1;
		indpers = -1;
	}
	else
	{
		result[indres]= vp[indpers]->id_pers;
		maskdeja.setBit(result[indres]);
	}


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
				if ( flagtittable )
				{
					fltrouve = ! vp[indpers]->getMaskMatch1().isBit(0) && !maskdeja.isBit(vp[indpers]->id_pers);
				}
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
			bool ret = rec_appar4(newvp, this->partInt.getList().front(), newmatch, mi, fl2, vtt);
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
			if ((ret = rec_appar4(newvp, stdec4, newmatch, mi, fl2, vtt)))
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

bool Tirage::makeTirage(bool fl2, const vector<Personne *> *vtt)
{
//cerr << "mttrace1"<<endl;
	bool flagok = false;
	const bool flagcout=false;

	vector<Match *> newmatch;

	for( int i= 0 ;  !flagok && i < 1 ; i++ )
	{

//		cerr << "mttrace2"<<endl;
		vector<Personne *> vp;

//		for ( Personne * p : allPersonnes)
//		{
//			if ( p != nullptr  && p->id_pers != 0 )
//			{
//
//				p->calculNote();
//				p->mkMaskMatch();
//				vp.push_back(p);
//				cerr<<" id_pers="<<p->id_pers<<endl;
//			}
//		}
//
//		sort(vp.begin(), vp.end(), Personne::PersonneLess);

		for ( Personne * p : allPersonnes)
		{
			if ( p != nullptr )
			{
				p->calculNote();
				p->mkMaskMatch();
			}
		}

		getPersSortNum(vp,Personne::PersonneLess );


//		cerr << "mttrace3"<<endl;


		maxIndice=0;

		nbTentatives = 0;

		for( auto dec:this->partInt.getList())
		{
//			if ( rec_appar4(vp, dec, newmatch,  &maxIndice, fl2) && maxIndice < double(vp.size())/2  )
			if ( rec_appar4(vp, dec, newmatch,  &maxIndice, fl2, vtt) )
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

//	allTours.push_back(newmatch);
// allTour est maintenant géré dans addMatch

	sort(newmatch.begin(),newmatch.end(),Match::MatchMore);

	for ( Match *m: newmatch)
	{
		addMatch(m);
	}

	return true;
}

// il s'agit de la validation definitve du match on met à jour l'objet Personne
int Tirage::addMatch(Match *m)
{
	int nbzero=0;
	int rang=0;
	for ( auto p: m->getPersonnes() )
	{
		if ( p->id_pers == 0 )
			nbzero++;
		if ( nbzero > 1)
			break;
		int r = p->addMatch(m);
		rang = max(r, rang);
	}
	if ( rang > (int)allTours.size() )
	{
		allTours.push_back(vector<Match *>());
	}
	allTours.back().push_back(m);
	allMatches.push_back(m);
	if ( !m->istittable() )
	{
		for ( Mask<> mask:m->get3())
		{
			mask_3set.insert(mask);
		}
	}
	m->setNumTour(allTours.size()-1);
	return rang;
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
	allPersonnes[p->id_pers] = p;
	maxNameAffLength = max(maxNameAffLength, p->getAffLength());
	nbPersonnes++;
}
// private
void Tirage::initMaxNameAffLength()
{
	maxNameAffLength = 0;
	for ( Personne *p:allPersonnes )
	{
		if ( p != nullptr && p->id_pers != 0 )
		{
			maxNameAffLength = max(maxNameAffLength, p->getAffLength());
		}
	}

}
int Tirage::getMaxNameAffLength() const
{
	return maxNameAffLength;
}
int Tirage::getLengthAff(const Personne * p) const
{
	return maxNameAffLength+p->getDiffAccent();
}

void Tirage::deletePersonne(const Personne *p)
{
	if ( p->getMatches().size() != 0 )
	{
		cerr << "On ne peut supprimer une personne dont il existe des matches"<<endl;
	}
	else
	{
		allPersonnes[p->id_pers] = nullptr;
		delete p;
		nbPersonnes--;
		initMaxNameAffLength();
	}
}



void Tirage::affResult()
{

	for ( Personne * p : allPersonnes)
	{
		if ( p != nullptr ) p->calculNote();
	}

	vector<Personne *> vp;
	getPersSortNum(vp,Personne::PersonneMore);

//	sort(vp.begin(), vp.end(), Personne::PersonneMore );
//
//	vp.pop_back();
//
//	for( int i = 0 ; i < (int)vp.size() ; i++ )
//	{
//		vp[i]->setId_prov(i);
//	}


	for ( Personne *p:vp)
	{
		cout << p->mkLigne() << endl;
	}

}
const vector<Match *> & Tirage::getLastTour() const
{
	return allTours.back();
}

const vector<Match *> & Tirage::getTour( int n) const
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

FlatTirage Tirage::getFlat() const
{
	FlatTirage ft={0};
	int i_pers=0;
	for ( Personne *p : allPersonnes )
	{
		if ( p != nullptr )
		{
			ft.allPers[i_pers] = p->getFlat();
		}
		i_pers++;
	}
	int i_match=0;
	for ( Match *m : allMatches )
	{
		ft.allMatches[i_match++] = m->getFlat();
	}
	return ft;
}
array<Personne *,4> Tirage::convArray(array<int,4> arr) const
{
	array<Personne *,4> res;
	for ( int i= 0 ; i < 4 ; i++ )
	{
		res[i] = allPersonnes[arr[i]];
	}
	return res;
}

void Tirage::setNomFichier(const string &nomFichier)
{
	this->nomFichier = nomFichier;
}

void Tirage::save(bool flag_plus) const
{
	FlatTirage ft = getFlat();
	FILE *fd = fopen(nomFichier.c_str(), "wb+");

	fwrite(&ft,sizeof(FlatTirage), 1, fd);

	fclose(fd);

	if ( flag_plus )
	{
		size_t pos=nomFichier.rfind(".");
		stringstream ss;
		ss << nomFichier.substr(0,pos);
		string milieu;
		if ( allTours.size() == 0 )
		{
			ss <<"_0_";
		}
		else
		{
			ss << "_"<<allTours.size()<<"_"<< (nbMatchNonSaisie()==0);
		}
		ss << nomFichier.substr(pos);
		fd = fopen(ss.str().c_str(), "wb+");
		fwrite(&ft,sizeof(FlatTirage), 1, fd);

		fclose(fd);

	}


}
void Tirage::getPersSortNum( vector<Personne *> &result, function<bool(Personne *,Personne *)> fct )
{
	result.clear();
	for ( int i = 1 ; i < (int)allPersonnes.size() ; i++ )
	{
		if ( allPersonnes[i] != nullptr )
		{
			result.push_back(allPersonnes[i]);
		}
	}
	sort(result.begin(),result.end(),fct);
	for ( int i = 0 ; i < (int)result.size() ; i++)
	{
		result[i]->setId_prov(i);
	}

}
int Tirage::nbMatchNonSaisie() const
{
	int nb=-1;
	if ( allTours.size() != 0 )
	{
		nb = 0;
		for ( const Match *m : allTours.back())
		{
			if ( !m->isResultInit() )
			{
				nb++;
			}
		}
	}
	return nb;

}
int Tirage::getNbPersonnes() const
{
	return nbPersonnes;
}
bool Tirage::isRerenc() const
{
	const array<int,5> tab={0,15,24,36,60};
	return nbPersonnes <= tab[min(tab.size()-1,allTours.size())];
}

