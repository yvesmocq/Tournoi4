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
 * Ihm.h
 *
 *  Created on: 25 oct. 2023
 *      Author: Yves Mocquard
 */

#ifndef IHM_H_
#define IHM_H_
using namespace std;
#include <string>
#include <vector>
#include <algorithm>
#include "Personne.h"

#define VT_BLACK    0
#define VT_RED      1
#define VT_GREEN    2
#define VT_YELLOW   3
#define VT_BLUE     4
#define VT_MAGENTA  5
#define VT_CYAN     6
#define VT_WHITE    7
#define VT_DEFAULT  9

class Ihm final {
	Ihm();
	static Ihm *instance;
	~Ihm();
	const string lib_repnum1;
	const string lib_repnum2;
	const string lib_repnum3;

	string set_colors( int fg, int bg) const;



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
	void gesPresenceAjout();
	void presence();
	void presence( const vector<Personne *> &vp);
	bool confirm(const string &lib );
	string getStrTour(int n ) const;
	void retCont() const;
	void getLib(const string & out, string &result) const;
	void saisieResultats();
	void afficheMatches();
	void affMatch( const Match *m, string table="") const;

	vector<int> getList(const string & str) const;
	void saisieExvol( const vector<Personne *> & vp, vector<Personne *> &exvol) const;


	void tournoi();
	string strTable(int ind) const;
	void lister(const vector<Personne *> &s) const;
	void lister(const vector<Match *> &vm) const;
	void lister(const vector<Personne*> &s, function<void(const Personne *)> fct) const;
	static void affPers( const Personne *p);
	static void affPersTable(const Personne *p);
	string nameSize( const Personne *p) const;
	string toStr( const Personne *p) const;
	string toStrName(const Personne *p, int lg) const;
	string mkLigne(const Personne *p, int nc_result, int nc_dep) const;
	string toStr( const Match *m, const Personne *) const;
	string toStr( int val, int lg) const;
	string toStr( string s, int lg) const;
	string strPres( const Personne *p) const;
	void affResult() const;
	int nbChif(int n) const;


};

#endif /* IHM_H_ */
