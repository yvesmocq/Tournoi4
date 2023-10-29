/*
 * Ihm_test.cpp
 *
 *  Created on: 25 oct. 2023
 *      Author: Yves
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
