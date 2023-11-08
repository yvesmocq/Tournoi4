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
	void modifPersonne();
	void suppPersonne();
	bool confirm(const string &lib );
	void retCont();
	void getLib(const string & out, string &result);
	void tournoi();

	void lister(const vector<Personne *> &s) const;

};

#endif /* IHM_H_ */
