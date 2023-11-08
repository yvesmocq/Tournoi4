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
	vector<string> lib={"Ajout d'une personne", "Modification d'une personne", "Suppression d'une personne", "Retour au menu principal"};
	Tirage *pt = Tirage::getInstance();

	bool flagcont=true;

	vector<Personne *> vp;
	while( flagcont )
	{
		pt->getPersSortNum(vp , Personne::PNameLess);
		lister(vp);
		switch( getChoix(lib) )
		{
		case 0 : ajoutPersonne(); break;
		case 1 : modifPersonne(); break;
		case 2 : suppPersonne(); break;
		case 3 : flagcont = false; break;
		default :
			cout << "Erreur retour getChoix non prévu" <<endl;
			exit(-1);
		}
	}

}
void Ihm::ajoutPersonne()
{
	string nom;

		cout << "Ajout d'une personne" <<endl;
		getLib("Nom : ", nom);
		string libconf = "Confirmez vous l'ajout de la personne XXX"+nom+string("XXX");
		if ( confirm(libconf) )
		{
			Tirage *pt = Tirage::getInstance();
			pt->addPersonne(new Personne(nom));
			pt->save();

			cout << "la personne : XXX" <<nom<<"XXX a bien été ajoutée" <<endl;
			retCont();
		}

}
void Ihm::modifPersonne()
{

}
void Ihm::suppPersonne()
{

}

void Ihm::retCont()
{
	string rep;
	cout << "Appuyez sur Entrée pour continuer ...";
	getline(cin,rep);
}

bool Ihm::confirm(const string &lib )
{

	string rep;
	cout << lib << " [N]/O : ";
	getline(cin, rep);
	return rep == "O" || rep == "o";

}

void Ihm::lister(const vector<Personne *> & s) const
{
	int n=1;
	for ( Personne *p : s)
	{
		cout << n <<". "<<p->getName() <<endl;
		n++;
	}
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

void Ihm::getLib(const string & out, string &result)
{
	cout << out ;
	getline(cin, result);
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
