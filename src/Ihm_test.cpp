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
 * Ihm_test.cpp
 *
 *  Created on: 25 oct. 2023
 *      Author: Yves Mocquard
 */

#include "Ihm.h"
#include "Simu.h"
#include "Tirage.h"

bool test_ihm()
{
	// creation des instance ( dont Tirage )*/
	Simu *ps=Simu::getInstance(20);

	Ihm *pihm=Ihm::getInstance();

	pihm->lancement();

}
