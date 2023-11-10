/*
 * Ihm.cpp
 *
 *  Created on: 25 oct. 2023
 *      Author: Yves
 */

#include "Ihm.h"
#include "Tirage.h"
#include <algorithm>
#include <iostream>

Ihm *Ihm::instance = nullptr;

Ihm::Ihm() :
		lib_repnum1("["), lib_repnum2("-"), lib_repnum3("]")

{
	// Nothing

}

Ihm::~Ihm() {

}

void Ihm::lancement() {

	vector<string> lib = { "Gestion Personne", "Lancement Tournoi", "Sortie" };

	bool flagcont = true;

	while (flagcont) {
		switch (getChoix(lib)) {
		case 0:
			gesPersonne();
			break;
		case 1:
			tournoi();
			break;
		case 2:
			Tirage::getInstance()->save();
			flagcont = false;
			break;
		}
	}

}

void Ihm::gesPersonne() {
	vector<string> lib = { "Ajout d'une personne", "Modification d'une personne", "Suppression d'une personne",
			"Retour au menu principal" };
	Tirage *pt = Tirage::getInstance();

	bool flagcont = true;

	vector<Personne*> vp;
	while (flagcont) {
		pt->getPersSortNum(vp, Personne::PNameLess);
		lister(vp);
		switch (getChoix(lib)) {
		case 0:
			ajoutPersonne();
			break;
		case 1:
			modifPersonne(vp);
			break;
		case 2:
			suppPersonne(vp);
			break;
		case 3:
			flagcont = false;
			break;
		default:
			cout << "Erreur retour getChoix non prévu" << endl;
			exit(-1);
		}
	}

}
void Ihm::ajoutPersonne() {
	string nom;

	cout << "Ajout d'une personne" << endl;
	getLib("Nom : ", nom);
	if (nom.length() > (Tools::sizeNameMax - 1)) {
		nom = nom.substr(0, (Tools::sizeNameMax - 1));
		cout << "Attention le nom a été racourci" << endl;
	}
	string libconf = "Confirmez vous l'ajout de la personne XXX" + nom + string("XXX");
	if (confirm(libconf)) {
		Tirage *pt = Tirage::getInstance();
		pt->addPersonne(new Personne(nom));
		pt->save();

		cout << "la personne : XXX" << nom << "XXX a bien été ajoutée" << endl;
		retCont();
	}

}
void Ihm::modifPersonne(const vector<Personne*> &vp) {
	string strnum;
	cout << "Modification d'une personne" << endl;
	getLib("Numero de la personne à modifier : ", strnum);
	int num = atoi(strnum.c_str());
	if (num > 0 && num <= (int) vp.size()) {
		Personne *p = vp[num - 1];
		string nouveaunom;
		string nom = p->getName();
		const string libmod = string("Nouveau nom de la personne XXX") + nom + string("XXX : ");
		getLib(libmod, nouveaunom);
		if (nom.length() > (Tools::sizeNameMax - 1)) {
			nom = nom.substr(0, (Tools::sizeNameMax - 1));
			cout << "Attention le nom a été racourci" << endl;
		}
		string libconf = "Confirmez vous la modification de la personne XXX" + nom + string("XXX ---> XXX") + nouveaunom
				+ string("XXX");

		if (confirm(libconf)) {
			Tirage *pt = Tirage::getInstance();
			p->setName(nouveaunom);
			pt->save();
			cout << "la personne : XXX" << nouveaunom << "XXX a bien été moifiée (ancien nom : XXX" << nom << "XXX" << endl;
			retCont();
		}

	}

}
void Ihm::suppPersonne(const vector<Personne*> &vp) {
	string strnum;
	cout << "Suppression d'une personne" << endl;
	getLib("Numero de la personne à supprimer : ", strnum);
	int num = atoi(strnum.c_str());
	if (num > 0 && num <= (int) vp.size()) {
		Personne *p = vp[num - 1];
		const string nom = p->getName();
		string libconf = "Confirmez vous la suppression de la personne XXX" + nom + string("XXX");

		if (confirm(libconf)) {
			Tirage *pt = Tirage::getInstance();
			pt->deletePersonne(p);
			pt->save();

			cout << "la personne : XXX" << nom << "XXX a bien été supprimée" << endl;
			retCont();
		}

	}

}

void Ihm::retCont() {
	string rep;
	cout << "Appuyez sur Entrée pour continuer ...";
	getline(cin, rep);
}

bool Ihm::confirm(const string &lib) {

	string rep;
	cout << lib << " [N]/O : ";
	getline(cin, rep);
	return rep == "O" || rep == "o";

}

string Ihm::nameSize(const Personne *p) const {
	string str = p->getName();
	str += string("                                                                                                         ");
	return str.substr(0, Tools::sizeNameMax - 1);
}

void Ihm::lister(const vector<Personne*> &s) const {
	const int nbColonne = 4;
	int nbLigne = (s.size() + nbColonne - 1) / nbColonne;
	int reste = (s.size() + 3) % nbColonne + 1;

	int ind = 0;

	for (int ligne = 0; ligne < nbLigne; ligne++) {
		ind = ligne;
		for (int col = 0; col < nbColonne && ind < (int) s.size(); col++) {
			const Personne *p = s[ind];
			cout << p->toStr() << ". " << nameSize(p);
			ind += nbLigne;
			if (ligne == nbLigne - 1 && col == reste - 1)
				break;

			if (col >= reste) {
				ind--;
			}
		}
		cout << endl;
	}
}

string Ihm::getStrTour(int n) const {
	stringstream ss;
	ss << "Voulez-vous effectuer le tirage du tour n° " << (n + 1);
	return ss.str();
}

void Ihm::tournoi() {
	Tirage *pt = Tirage::getInstance();

	int nt = pt->getNbTours();

	vector<Personne*> vp;
	if (nt == 0) {
		pt->getPersSortNum(vp, Personne::PNameLess);
	} else {
		pt->getPersSortNum(vp, Personne::PersonneMore);
	}

	cout << "Tournoi" << endl;
	lister(vp);
	if (pt->getNbTours() != 0) {
		saisieResultats();
		pt->affResult();
	}
	if (confirm(getStrTour(nt))) {
		bool flag = !confirm("Voulez-vous un tour sans rerencontre si possible ?");
		pt->makeTirage(flag);

		saisieResultats();

		pt->affResult();

	}
}
void Ihm::affMatch(const Match *m) const {
	char str[4] = "A. ";
	int im = 0;

	for (Personne *p : m->getPersonnes()) {
		cout << string(str);
		if (m->isResultInit()) {
			cout << m->getResult()[im++];
		} else {
			cout << " ";
		}
		cout << " " << nameSize(p);
		str[0]++;
	}
	cout << endl;
}

void Ihm::afficheMatches() {
	Tirage *pt = Tirage::getInstance();
	const vector<Match*> &matches = pt->getLastTour();
	int ind = 1;
	for (Match *m : matches) {
		cout << ind++ << ". ";
		affMatch(m);
	}

}
void Ihm::saisieResultats() {

	Tirage *pt = Tirage::getInstance();
	bool flagcont = true;
	const vector<Match*> &matches = pt->getLastTour();
	while (flagcont) {

		string rep;
		afficheMatches();
		if (pt->nbMatchNonSaisie() == 0) {
			string rep;
			getLib("Tous les matchs sont saisis est-ce correct ? (clef) ", rep);
			if (rep == "t4" || rep == "T4") {
				flagcont = false;
				continue;
			}
		}

		getLib("Numero du match à saisir : ", rep);
		int num = atoi(rep.c_str());
		if (num >= 1 && num <= (int) matches.size()) {
			Match *m = matches[num - 1];
			affMatch(m);
			if (!m->isResultInit() || confirm("Confirmez-vous la modification des résultats de ce match ? ")) {
				if (m->istittable()) {
					array<int, 4> result = { };
					array<int, 4> pers = m->getPersId();
					array<Personne*, 4> pp = m->getPersonnes();
					for (int i = 0; i < 4; i++) {
						if (pers[i] != 0) {
							Personne *p = pp[i];
							bool nok = true;

							while (nok) {
								const string lib = string("Nombre de points pour ") + p->getName() + string("(0-3) : ");
								string rep;
								getLib(lib, rep);
								int res = atoi(rep.c_str());
								if (res < 0 || res > 3) {
									cout << "Erreur on attend une valeur entre 0 et 3 !!!" << endl;
									retCont();
								} else {
									result[i] = res;
									nok = false;
								}
							}

						}

					}
					m->setResult(result);
				} else {
					getLib("Donnez le résultat (une lettre suivi d'un 0 ou un 3) :", rep);
					char c = rep.c_str()[0];
					int c2 = rep.length() == 2 ? atoi(rep.c_str() + 1) : -1;
					int nump = -1;
					if (c >= 'A' && c <= 'D')
						nump = c - 'A';
					if (c >= 'a' && c <= 'd')
						nump = c - 'a';
					if (nump != -1 && (c2 == 3 || c2 == 0)) {
						array<int, 4> result;
						for (int i = 0; i < 4; i++) {
							result[i] = i == nump ? c2 : (2 - c2 / 3);
						}
						m->setResult(result);

						pt->save();
					} else {
						cout << "Saisie incorrecte : XXX" << rep << "XXX" << endl;
						retCont();
					}
				}

			}
		}
	}

	retCont();
}

int Ihm::getChoix(vector<string> lib) const {
	stringstream ss;
	char str[4] = "A. ";
	for (int i = 0; i < (int) lib.size(); i++) {
		str[0] = 'A' + i;
		cout << string(str) << lib[i] << endl;
	}
	int res = -1;
	char str2[4] = "A]";
	char c_borne = 'A' + (lib.size() - 1);
	str2[0] = c_borne;
	char cb_min = c_borne + 'a' - 'A';
	string reponse;
	do {
		cout << "Votre choix [A-" << string(str2) << ": ";
		getline(cin, reponse);
		char c = reponse.c_str()[0];
		if (c >= 'A' && c <= c_borne)
			res = c - 'A';
		if (c >= 'a' && c <= cb_min)
			res = c - 'a';
	} while (res < 0);
	return res;
}

void Ihm::getLib(const string &out, string &result) {
	cout << out;
	getline(cin, result);
}

Ihm* Ihm::getInstance() {
	if (instance == nullptr) {
		instance = new Ihm();
	}
	return instance;
}
int Ihm::getChoixNum(string phrase, int from, int to) {
	if (from > to) {
		cerr << "Erreur getChoixNum from=" << from << " to=" << to << endl;
		exit(-1);
	}
	int res;
	char str[20];
	do {
		cout << phrase << lib_repnum1 << from << lib_repnum2 << to << lib_repnum3;
		fflush(stdout);
		fgets(str, 10, stdout);
		res = atoi(str);
	} while (isdigit(str[0]) && from <= res && res <= to);

	return res;

}
