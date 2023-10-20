/*
 * Personne_test.cpp
 *
 *  Created on: 7 sept. 2023
 *      Author: Yves
 */

#include "Personne.h"

bool test_personne()
{
	Personne *p = new Personne();
	if ( p->id_pers <1 )
		return false;
	else
		return true;
}

