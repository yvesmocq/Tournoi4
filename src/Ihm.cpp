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

	vector<string> lib={"Gestion Personne", "Lancement Tournoi", "Sortie"};

	bool flagcont=true;

	while( flagcont )
	{
		switch( getChoix( lib ))
		{
		case 0 : gesPersonne(); break;
		case 1 : tournoi(); break;
		case 2 : Tirage::getInstance()->save();
			flagcont = false; break;
		}
	}


}

void Ihm::gesPersonne()
{
	cout <<"GesPersonne"<<endl;
}
void Ihm::tournoi()
{
	cout <<"tournoi"<<endl;
}

int Ihm::getChoix( vector<string> lib) const
{
	stringstream ss;
	char str[4]="A. ";
	for( int i = 0 ; i < (int)lib.size() ; i++)
	{
		str[0] = 'A' + i;
		cout << string(str) << lib[i] << endl;
	}
	int res = -1;
	char str2[4] = "A]";
	char c_borne = 'A' +(lib.size()-1);
	str2[0] = c_borne;
	char cb_min = c_borne + 'a'-'A';
	string reponse;
	do
	{
		cout << "Votre choix [A-"<<string(str2)<<": ";
		getline(cin, reponse);
		char c=reponse.c_str()[0];
		if ( c >= 'A' && c <= c_borne )
			res = c-'A';
		if ( c >= 'a' && c <= cb_min )
			res = c-'a';
	}while( res < 0);
	return res;
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
