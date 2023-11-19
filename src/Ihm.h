/*
 * Ihm.h
 *
 *  Created on: 25 oct. 2023
 *      Author: Yves
 */

#ifndef IHM_H_
#define IHM_H_
using namespace std;
#include <string>
#include <vector>
#include "Personne.h"

class Ihm final {
	Ihm();
	static Ihm *instance;
	~Ihm();
	const string lib_repnum1;
	const string lib_repnum2;
	const string lib_repnum3;

public:
	static Ihm *getInstance();

	void lancement();

	void menuPrincipal();

	int getChoixNum(string phrase, int from, int to);
	int getChoix( vector<string> lib) const;

	void gesPersonne();
	void ajoutPersonne();
	void modifPersonne(const vector<Personne *> & vp);
	void suppPersonne(const vector<Personne *> & vp);
	bool confirm(const string &lib );
	string getStrTour(int n ) const;
	void retCont() const;
	void getLib(const string & out, string &result) const;
	void saisieResultats();
	void afficheMatches();
	void affMatch( const Match *m) const;

	vector<int> getList(const string & str) const;
	void saisieExvol( const vector<Personne *> & vp, vector<Personne *> &exvol) const;


	void tournoi();

	void lister(const vector<Personne *> &s) const;
	string nameSize( const Personne *p) const;
	string toStr( const Personne *p) const;
	string toStrName(const Personne *p, int lg) const;
	string mkLigne(const Personne *p) const;
	string toStr( const Match *m, const Personne *) const;
	void affResult() const;


};

#endif /* IHM_H_ */
