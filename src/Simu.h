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
 * Simu.h
 *
 *  Created on: 18 sept. 2023
 *      Author: Yves Mocquard
 */

#ifndef SIMU_H_
#define SIMU_H_
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

#include "Tools.h"
#include "Ihm.h"
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

	void affResult() { Ihm::getInstance()->affResult(); }
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
