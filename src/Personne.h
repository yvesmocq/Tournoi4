/*
 * Personne.h
 *
 *  Created on: 7 sept. 2023
 *      Author: Yves
 */

#ifndef PERSONNE_H_
#define PERSONNE_H_
using namespace std;
#include <cstdint>
#include <cstring>
#include <list>
#include <vector>
#include <algorithm>
#include "Mask.h"
#include "Match.h"
#include "Tools.h"

class Match;

struct FlatPers
{
	bool isValid;
	bool present;
	char filler[2];
	int id;
	array<char,40> name;
};

class Personne {
private:
	static int serie_id_pers;

	string name;
	string nameSimple;
	list<Match*> matches; // matches ou la personne apparait
	int id_prov;

	bool present;

	double result;
	double diff;
	double note;
	Mask<> maskMatch1;
	Mask<> maskMatch2;
	int nbScore;
	int calculResult();


	struct P_Less
	    {
	        bool operator()(Personne *p1, Personne *p2) const { return p1->getNote() < p2->getNote();}
	    };
	 struct P_More
		    {
		        bool operator()(Personne *p1, Personne *p2) const { return p1->getNote() > p2->getNote();}
		    };
	struct P_NameLess
	{
			bool operator()(Personne *p1, Personne *p2) const { return p1->getNameSimple() < p2->getNameSimple();}
	};


public:
	const int id_pers;

	Personne();
	Personne( const string &n);
	Personne(int id);
	Personne( const FlatPers &fp );
	~Personne();


	void setPresent( bool flag);
	bool isPresent() const;


	double calculNote();
	void mkMaskMatch();
	void setName(const string & name);
	const string & getName() const;
	const string & getNameSimple() const;

	const list<Match *> &getMatches() const;
	int addMatch(Match *m);
	string toStr() const;
	string toStrName() const;
	string mkLigne() const;

	string numName() const;

	const Mask<> &getMaskMatch1() const;
	const Mask<> &getMaskMatch2() const;
	double getNote() const;

	void setId_prov(int id_prov);
	double getResult() const;

	static void resetSerieId();

	static P_Less PersonneLess;
	static P_More PersonneMore;
	static P_NameLess PNameLess;


	static void sortnum( vector<Personne *> & v, function<bool(Personne *,Personne *)> fct);

	FlatPers getFlat() const;
};


#endif /* PERSONNE_H_ */
