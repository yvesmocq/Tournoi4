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
 * Tirage_test.cpp
 *
 *  Created on: 8 sept. 2023
 *      Author: Yves Mocquard
 */

#include "Tirage.h"

bool test_tirage()
{
	Tirage *t= Tirage::getInstance();
	int res;
	if ( (res = Personne::getSerieId()) != 1 )
	{
		cout <<"serie_id_pers attendu=1"<< "obtenu ="<<res<<endl;
		return false;
	}

	t->addPersonne(new Personne(string("Nom")));
	if ( (res = Personne::getSerieId()) != 2 )
	{
		cout <<"serie_id_pers attendu=2"<< "obtenu ="<<res<<endl;
		return false;
	}
	t->addPersonne(new Personne(string("Nom1")));
	t->addPersonne(new Personne(string("Nom3")));

	if ( (res = Personne::getSerieId()) != 4 )
	{
		cout <<"serie_id_pers attendu=4"<< "obtenu ="<<res<<endl;
		return false;
	}
	if ( (res = t->getNbPersonnes()) != 3 )
	{
		cout <<"1getNbPersonnes() attendu=3"<< "obtenu ="<<res<<endl;;

	}


	t->deletePersonne(t->getAllPersonnes()[2]);
	if ( (res = Personne::getSerieId()) != 2 )
	{
		cout <<"serie_id_pers attendu=2"<< "obtenu ="<<res<<endl;;
		return false;
	}
	if ( (res = t->getNbPersonnes()) != 2 )
	{
		cout <<"2getNbPersonnes() attendu=2"<< "obtenu ="<<res<<endl;;

	}


	t->addPersonne(new Personne(string("Nom autre")));

	if ( (res = Personne::getSerieId()) != 4 )
	{
		cout <<"2serie_id_pers attendu=4"<< "obtenu ="<<res<<endl;;
		return false;
	}

	const vector<Personne *> &va=t->getAllPersonnes();

	for ( int i = 0 ; i < 4; i++)
	{
		if ( va[i]->id_pers != i)
		{
			cout << "erreur id="<<va[i]->id_pers<<" different de l'indice="<<i<<endl;
			return false;
		}

	}
	if ( (res = t->getNbPersonnes()) != 3 )
	{
		cout <<"3getNbPersonnes() attendu=3"<< "obtenu ="<<res<<endl;;

	}

	delete t;
	return true;
}
