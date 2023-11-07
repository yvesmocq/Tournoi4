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
