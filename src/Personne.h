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
#include "Mask.h"
#include "Match.h"
#include "Tools.h"

class Match;
class Personne {
private:
	static int serie_id_pers;
	string name;
	list<Match*> matches; // matches ou la personne apparait
public:
	Personne();
	Personne( const string &n);
	Personne(int id);
	~Personne();
	const int id_pers;

	int id_prov;

	double result;
	double diff;
	double note;
	Mask<> maskMatch1;
	Mask<> maskMatch2;
	int nbScore;

	int getResult();
	double setNote();
	void mkMaskMatch();
	void setName(const string & name);
	const string & getName() const;

	const list<Match *> &getMatches() const;
	void addMatch(Match *m);
	string toStr();
	string toStrName();
	string mkLigne();

	static void resetSerieId();

};

#endif /* PERSONNE_H_ */
