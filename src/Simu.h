/*
 * Simu.h
 *
 *  Created on: 18 sept. 2023
 *      Author: Yves
 */

#ifndef SIMU_H_
#define SIMU_H_
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

#include "Tools.h"
#include "Tirage.h"

class Simu final {
	static Simu *instance;
	const int nbPers;

	Simu(int nb);


public:
	struct PSim {
		Personne *p;
		double elo;
	};
	vector<PSim> allPS;
	void calResult(Match *pm);
	double probGain(double diffElo);

	bool simule(int nbtour, bool fl2);


	static Simu *getInstance(int nb=52);

	void affResult() { Tirage::getInstance()->affResult(); }
	int getNbTentatives() const
	{
		return Tirage::getInstance()->getNbTentatives();
	}
	int getMaxIndice() const
	{
		return Tirage::getInstance()->getMaxIndice();
	}

	~Simu();
};

#endif /* SIMU_H_ */
