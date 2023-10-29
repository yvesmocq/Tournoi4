/*
 * Ihm.cpp
 *
 *  Created on: 25 oct. 2023
 *      Author: Yves
 */

#include "Ihm.h"
#include "Tirage.h"
#include <algorithm>

Ihm * Ihm::instance=nullptr;

Ihm::Ihm():
		lib_repnum1("["),
		lib_repnum2("-"),
		lib_repnum3("]")

 {
	// Nothing

}

Ihm::~Ihm() {

}


void Ihm::lancement()
{
	Tirage *pt=Tirage::getInstance();

	const vector<Personne *> & allp=pt->getAllPersonnes();

	vector<Personne *> liste(allp.begin()+1,allp.end());

	Personne::sortnum(liste, Personne::PNameLess );

	for ( Personne *p:liste )
	{
		cout << p->numName()<<endl;
	}


}


Ihm *Ihm::getInstance()
{
	if ( instance == nullptr )
	{
		instance = new Ihm();
	}
	return instance;
}
int Ihm::getChoixNum(string phrase, int from, int to)
{
	if ( from > to)
	{
		cerr <<"Erreur getChoixNum from="<<from<<" to="<<to<<endl;
		exit(-1);
	}
	int res;
	char str[20];
	do
	{
		cout <<phrase<<lib_repnum1 <<from <<lib_repnum2 << to <<lib_repnum3;
		fflush(stdout);
		fgets(str,10, stdout);
		res= atoi(str);
	}while(isdigit(str[0]) && from <= res && res <= to);


	return res;

}
