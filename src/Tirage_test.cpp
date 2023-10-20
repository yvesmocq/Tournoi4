/*
 * Tirage_test.cpp
 *
 *  Created on: 8 sept. 2023
 *      Author: Yves
 */

#include "Tirage.h"

bool test_tirage()
{
	Tirage *t= Tirage::getInstance();
	Personne *p=new Personne(string("Nom"));

	t->addPersonne(p);

	delete t;
	return true;
}
