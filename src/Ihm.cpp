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
 * Ihm.cpp
 *
 *  Created on: 25 oct. 2023
 *      Author: Yves Mocquard
 */

#include "Ihm.h"
#include "Tirage.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>

Ihm *Ihm::instance = nullptr;

Ihm::Ihm() :
		lib_repnum1("["), lib_repnum2("-"), lib_repnum3("]")

{
	// Nothing

}

Ihm::~Ihm() {

}

void Ihm::lancement() {

	vector<string> lib = { "Gestion Personne", "Gestion Présence", "Lancement Tournoi", "Sortie" };

	bool flagcont = true;

	while (flagcont) {
		switch (getChoix(lib)) {
		case 0:
			gesPersonne();
			break;
		case 1:
			presence();
			break;
		case 2:
			tournoi();
			break;
		case 3:
			Tirage::getInstance()->save();
			flagcont = false;
			break;
		}
	}

}

void Ihm::presence() {
	cout << endl << endl << "Gestion présence" << endl;
	vector<string> lib = { "Liste globale", "Liste présent", "Liste absent", "Retour au menu précédent" };
	array<function<bool(const Personne*)>, 3> filtre = { Personne::stAll, Personne::stIsPres, Personne::stIsAbs };
	Tirage *pt = Tirage::getInstance();

	bool flagcont = true;
	while (flagcont) {
		vector<Personne*> vp;
		int ret = getChoix(lib);
		if (ret >= 0 && ret < (int) filtre.size()) {
			pt->getPersSortNum(vp, Personne::PNameLess, filtre[ret]);
			presence(vp);
		} else {
			flagcont = false;
		}
	}
}

void Ihm::presence(const vector<Personne*> &vp) {
	cout << endl << endl << "Gestion présence" << endl;

	Tirage *pt = Tirage::getInstance();

	bool flagcont = true;

	string strnum;

	while (flagcont) {
		lister(vp);

		getLib("Numéro de la personne dont on modifie la présence : ", strnum);
		int num = atoi(strnum.c_str());
		if (num > 0 && num <= (int) vp.size()) {
			Personne *p = vp[num - 1];
			bool etat = p->isPresent();
			string lib;
			if (etat)
				lib = "Confirmez-vous l'absence XXX" + p->getName() + "XXX";
			else
				lib = "Confirmez-vous la présence de XXX" + p->getName() + "XXX";
			if (confirm(lib)) {
				p->setPresent(!etat);
				pt->save();

			}

		} else {
			flagcont = false;
		}
	}

}

void Ihm::gesPersonne() {
	vector<string> lib = { "Ajout d'une personne", "Modification d'une personne", "Suppression d'une personne",
			"Gestion présence à l'ajout", "Retour au menu principal" };
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
			gesPresenceAjout();
			break;
		case 4:
			flagcont = false;
			break;
		default:
			cout << "Erreur retour getChoix non prévu" << endl;
			exit(-1);
		}
	}

}

void Ihm::gesPresenceAjout() {
	cout << "Gestion présence à l'ajout" << endl;
	Tirage *pt = Tirage::getInstance();

	bool etat = pt->isPresAjout();

	vector<string> lib = { "Absent", "Présent" };

	cout << "Par défaut à l'ajout un joueur est " << lib[int(etat)] << endl;

	if (confirm("Voulez-vous changer ?")) {
		etat = !etat;
		pt->setPresAjout(etat);
		cout << "Par défaut à l'ajout un joueur est " << lib[etat] << endl;
		retCont();
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
		Personne *p = new Personne(nom);
		p->setPresent(pt->isPresAjout());
		pt->addPersonne(p);
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
			pt->modifPersonne(p);
			pt->save();
			cout << "la personne : XXX" << nouveaunom << "XXX a bien été moifiée (ancien nom : XXX" << nom << "XXX"
					<< endl;
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

void Ihm::retCont() const {
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
	str +=
			string(
					"                                                                                                         ");
	return str.substr(0, Tirage::getInstance()->getLengthAff(p) + 1);
}

string Ihm::strPres(const Personne *p) const {
	stringstream ss;

	if (p->isPresent()) {
		ss << set_colors(VT_GREEN, VT_DEFAULT) << "v";
	} else {
		ss << set_colors(VT_RED, VT_DEFAULT) << "x";
	}
	ss << set_colors(VT_DEFAULT, VT_DEFAULT);

	return ss.str();

}

void Ihm::lister(const vector<Match*> &vm) const {
	vector<Personne*> vp;
	int indm = 1;
	for (Match *m : vm) {
		array<Personne*, 4> pers = m->getPersonnes();
		int i_pm = 0;
		for (Personne *p : pers) {
			if (p->id_pers == 0)
				continue;
			vp.push_back(p);
			p->setId_prov(pers[0]->id_pers == 0 ? -1 : indm);
			p->setId_prov_2(i_pm);
			i_pm++;
		}
		indm++;
	}
	sort(vp.begin(), vp.end(), Personne::PNameLess);

	lister(vp, affPersTable);

}

//static
void Ihm::affPersTable(const Personne *p) {
	Ihm *pihm = Ihm::getInstance();

	string str = pihm->nameSize(p) + " ";

	int pos = str.find_last_not_of(" ");
//	cerr <<"pos="<<pos<<endl;

	str.insert(pos + 2, pihm->strTable(p->getIdProv(), p->getIdProv_2()));

	cout << str << " ";
}

void Ihm::lister(const vector<Personne*> &s, function<void(const Personne*)> fct) const {
	const int nbColonne = 4;
	int nbLigne = (s.size() + nbColonne - 1) / nbColonne;
	int reste = (s.size() + 3) % nbColonne + 1;

	int ind = 0;

	for (int ligne = 0; ligne < nbLigne; ligne++) {
		cout << "    ";
		ind = ligne;
		for (int col = 0; col < nbColonne && ind < (int) s.size(); col++) {
			fct(s[ind]);
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
void Ihm::lister(const vector<Personne*> &s) const {
	lister(s, affPers);
}

//static
void Ihm::affPers(const Personne *p) {
	Ihm *pihm = Ihm::getInstance();
	cout << pihm->toStr(p) << ". " << pihm->strPres(p) << " . " << pihm->nameSize(p);
}

string Ihm::getStrTour(int n) const {
	stringstream ss;
	ss << "Voulez-vous effectuer le tirage du tour n° " << (n + 1);
	return ss.str();
}

vector<int> Ihm::getList(const string &str) const {
	char *ptrall = strdup(str.c_str());
	char *ptr = strtok(ptrall, ",-");
	vector<int> rep;
	if (!isdigit(*ptrall))
		return rep;
	do {
		rep.push_back(atoi(ptr));
	} while ((ptr = strtok(NULL, ",-")) != nullptr);
	free(ptrall);
	return rep;
}
void Ihm::saisieExvol(const vector<Personne*> &vp, vector<Personne*> &exvol) const {
	size_t b_e = vp.size() % 4;
	bool flok = false;
	while (!flok) {
		string lev;
		getLib("Liste des exempts volontaires : ", lev);
//cerr << "sasie XXXXX"<<lev<<"XXX" <<endl;
		vector<int> a = getList(lev);
//cerr <<"Resultat getList XXX" << Tools::to_string(a)<<"XXX"<<endl;
		exvol.clear();
		if (a.size() == 0) {
			flok = true;
		} else {
			if (a.size() > b_e) {
				cout << "Il y en a trop !!!" << endl;
				retCont();
			} else {
				flok = true;
				for (int i : a) {
					if (i > (int) vp.size() || i < 1) {
						cout << "Valeur hors borne !!!" << endl;
						flok = false;
						retCont();
						break;
					}
					exvol.push_back(vp[i - 1]);
				}
			}
		}
	}
}

void Ihm::tournoi() {
	Tirage *pt = Tirage::getInstance();

	int nt = pt->getNbTours();

	vector<Personne*> vp;

	cout << "Tournoi" << endl;
	if (pt->getNbTours() != 0) {
		saisieResultats();
		affResult();
	}
	if (nt == 0) {
		pt->getPersSortNum(vp, Personne::PNameLess, Personne::stIsPres);
	} else {
		pt->getPersSortNum(vp, Personne::PersonneMore, Personne::stIsPres);
	}
	lister(vp);
	vector<Personne*> exvol;
	vector<Personne*> *p_exvol = nullptr;
	if (vp.size() % 4 != 0) {
		bool flok = false;
		while (!flok) {
			saisieExvol(vp, exvol);
			if (exvol.size() != 0) {
				cout << "Liste des exempts pour le tour n° " << (nt + 1) << " :" << endl;
				for (Personne *p : exvol) {
					cout << p->getName() << endl;
				}
				if (confirm("Confirmez-vous cette liste d'exempts volontaire ?")) {
					p_exvol = &exvol;
					flok = true;
				}
			} else {
				flok = true;
			}
		}
	}

	if (confirm(getStrTour(nt))) {
//		bool flag = !confirm("Voulez-vous un tour sans rerencontre si possible ?");
//		if ( pt->makeTirage(false, p_exvol) || pt->makeTirage(true, p_exvol) )
		if (pt->makeTirage(pt->isRerenc(), p_exvol)) {
			pt->save(true);
			saisieResultats();
			affResult();
		} else {
			cout << "Le tirage n'a pas pu se faire !!!";
			retCont();
		}

	}
}

void Ihm::affMatch(const Match *m, string table) const {
	if (m->isResultInit()) {
		cout << set_colors(VT_GREEN, VT_DEFAULT);
	}
	char str[4] = "A. ";
	int im = 0;
	char str_t[8];
	strcpy(str_t, table.data());
	if (str_t[0] != 'E')
		str_t[0] = 'A';
	for (Personne *p : m->getPersonnes()) {
		cout << string(str);
		cout << string(str_t);
		if (m->isResultInit() && p->id_pers != 0) {
			cout << m->getResult()[im];
		} else {
			cout << " ";
		}
		string s = " " + nameSize(p) + " ";
		if (p->getResult() < 0)
			s += "   ";
		else
			s.insert(s.find_last_not_of(" ") + 2, "(" + to_string(int(p->getResult())) + ")");
		if (p->getResult() < 10)
			s += " ";
		cout << s;
		str[0]++;
		if (str_t[0] != 'E')
			str_t[0]++;
		im++;
	}

	cout << set_colors(VT_DEFAULT, VT_DEFAULT);
	cout << endl;
//	cout << endl;
}

string Ihm::strTable(int ind) const {
	return strTable(ind, -1);
}

string Ihm::strTable(int ind, int ind_2) const {
	char str[30];
	if (ind < 0)
		sprintf(str, "Ex  ");
	else {
		char c = (ind_2 == -1) ? 'T' : ('A' + ind_2);
		sprintf(str, "%c%02d ", c, ind);
	}
	return string(str);

}

void Ihm::afficheMatches() {
	Tirage *pt = Tirage::getInstance();
	cout << endl;
	cout << endl << endl;
	cout << endl;
	cout << endl << endl;
	cout << "              Tour N° " << pt->getNbTours() << " :" << endl << endl;
	const vector<Match*> &matches = pt->getLastTour();

	lister(matches);

	int ind = 1;
	cout << endl << endl;
	for (Match *m : matches) {

		cout << "   " << ind << ". ";
		if (m->istittable())
			ind = -1;
		affMatch(m, strTable(ind));
		ind++;
	}

	cout << endl << endl;
	if (!pt->isNoClub()) {
		cout << "nb match 3 meme club = " << pt->nb3SameClub(pt->getLastTour()) << endl;
	}
	cout << endl << endl;

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
			cout << endl << endl << "   ";
			affMatch(m);
			cout << endl << endl;
			if (!m->isResultInit() || confirm("Confirmez-vous la modification des résultats de ce match ? ")) {
				bool flagok = false;
				array<int, 4> result = { };
				if (m->istittable()) {
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
					flagok = true;
				} else {
					cout << endl;
					getLib("Donnez le résultat (une lettre suivi d'un 0 ou un 3) :", rep);
					char c = rep.c_str()[0];
					int c2 = rep.length() == 2 ? atoi(rep.c_str() + 1) : -1;
					int nump = -1;
					if (c >= 'A' && c <= 'D')
						nump = c - 'A';
					if (c >= 'a' && c <= 'd')
						nump = c - 'a';
					if (nump != -1 && (c2 == 3 || c2 == 0)) {
						for (int i = 0; i < 4; i++) {
							result[i] = i == nump ? c2 : (2 - c2 / 3);
						}
						flagok = true;
					} else {
						cout << "Saisie incorrecte : XXX" << rep << "XXX" << endl;
						retCont();
					}
				}
				if (flagok) {
					m->setResult(result);
					pt->save(pt->nbMatchNonSaisie() == 0);
				}

			}
		} else {
			if (rep == "ALEA") {
				for (Match *m : matches) {
					array<int, 4> res = { 0 };
					const array<Personne*, 4> &pers = m->getPersonnes();
					int v1 = rand() % 2 == 0 ? 3 : 0;
					int v2 = v1 == 3 ? 1 : 2;
					int num = rand() % 4;
					if (pers[0]->id_pers == 0) {
						v1 = v2 = 2;
					}
					for (int i = 0; i < 4; i++) {
						if (pers[i] != nullptr && pers[i]->id_pers != 0) {
							res[i] = i == num ? v1 : v2;
						}
					}
					m->setResult(res);
				}
				pt->save(true);

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

void Ihm::getLib(const string &out, string &result) const {
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
string Ihm::toStr(string s, int lg) const {
	char str[100];

	sprintf(str, "%*s", lg, s.c_str());
	return string(str);

}

string Ihm::toStr(int val, int lg) const {
	char str[100];

	sprintf(str, "%*d", lg, val);
	return string(str);

}

string Ihm::toStr(const Personne *p) const {
	return toStr(p->getIdProv() + 1, 2);
}
string Ihm::toStrName(const Personne *p, int lg) const {
	string str = p->getName() + "                            ";
	return str.substr(0, lg + p->getDiffAccent());
}

//string Personne::numName() const {
//	stringstream ss;
//
//	ss << (id_prov + 1) << ". " << name;
//
//	return ss.str();
//
//}

string Ihm::mkLigne(const Personne *p, int nc_result, int nc_dep) const {
	stringstream ss;
//cerr << "t01"<<endl;
	ss << "| " << this->toStr(p) << " | ";
	ss << toStrName(p, Tirage::getInstance()->getMaxNameAffLength()) << " |";
//	cerr << "t02"<<endl;

	int i = 0;
	for (Match *m : p->getMatches()) {
//		cerr << "t020"<<endl;
		while (i < m->getNumTour()) {
			ss << "            |";
			i++;
		}
//		cerr << "t021"<<endl;
		ss << toStr(m, p);
//		cerr << "t022"<<endl;
		ss << "|";
		i++;
	}
//	cerr << "t03"<<endl;
	Tirage *pt = Tirage::getInstance();
	while (i < pt->getNbTours()) {
		ss << "            |";
		i++;
	}
	ss << " ";
//	cerr << "t04"<<endl;

	ss << toStr(p->getResult(), nc_result);
//	cerr << "t05"<<endl;

	ss << " | ";
	ss << toStr(p->getDepartage(), nc_dep);
	ss << " |";
//	cerr << "t06"<<endl;

	return ss.str();

}
string Ihm::toStr(const Match *m, const Personne *p) const {
//	cerr << "t0210"<<endl;

	int n = m->getScore(p);
//	cerr << "t0211"<<endl;

	array<int, 4> pers = m->getPersId();
	array<int, 4> result = m->getResult();
	array<Personne*, 4> personnes = m->getPersonnes();
//	cerr << "t0212"<<endl;

	if (pers[0] == 0) {
		return " " + to_string(n) + " Ex       ";
	}
	array<int, 3> ar = { };

	int ind_ar = (n == 1 && pers[0] != 0) ? 1 : 0;

	int nbadv = 3;
//	cerr << "t0213"<<endl;

	if (pers[0] == 0) {
		if (pers[2] == 0)
			nbadv = 0;
		else if (pers[3] == 0)
			nbadv = 1;
		else
			nbadv = 2;
	} else {
//		cerr<< "tr0213 normal"<<endl;
	}
//	cerr << "t0214"<<endl;

	for (int i = 0; i < 4; i++) {
		if (pers[i] == p->id_pers || pers[i] == 0)
			continue;
		if (result[i] == 0 && pers[0] != 0) {
			ar[2] = i;
		} else if (result[i] == 3 && pers[0] != 0) {
			ar[0] = i;
		} else {
			ar[ind_ar++] = i;
		}
	}
//	cerr << "t0215"<<endl;

	stringstream ss;

	ss << " " << n << " ";
//	cerr << "t0216"<<endl;

	for (int i = 0; i < nbadv; i++) {
//		cerr << "ar[i]="<<ar[i]<<endl;
		ss << toStr(personnes[ar[i]]);
		if (i != nbadv - 1)
			ss << ",";
	}
//	cerr << "t0217"<<endl;
	for (int i = nbadv; i < 3; i++) {
		ss << "   ";
	}
	ss << " ";
//	cerr << "t0218"<<endl;

	return ss.str();

}
void Ihm::affResult() const {
	Tirage *pt = Tirage::getInstance();
	Tools *tools = Tools::getInstance();

	cout << endl << endl << endl;
	cout << "Resultat après tour n° " << pt->getNbTours() << endl;

	int nc_result = 0;
	for (Personne *p : pt->getAllPersonnes()) {
		if (p != nullptr) {
			p->calculNote();
			nc_result = max(nc_result, tools->nbChif((int) p->getResult()));
		}
	}
	int nc_dep = 0;
	vector<Personne*> vp;
	pt->getPersSortNum(vp, Personne::PersonneMore, Personne::stIsMatches);

	pt->setResMedian(vp[vp.size() / 2]->getResult());

	for (Personne *p : vp) {
		if (p != nullptr) {
			p->calculDepartage();
			nc_dep = max(nc_dep, tools->nbChif(p->getDepartage()));
		}
	}

	vp.clear();
	pt->getPersSortNum(vp, Personne::PMoreDepartage, Personne::stIsMatches);

//	sort(vp.begin(), vp.end(), Personne::PersonneMore );
//
//	vp.pop_back();
//
//	for( int i = 0 ; i < (int)vp.size() ; i++ )
//	{
//		vp[i]->setId_prov(i);
//	}

	cout << "|    | Nom" << string(pt->getMaxNameAffLength() - 2, ' ') << "| ";
	for (int i = 0; i < pt->getNbTours(); i++) {
		cout << "Tour N° " << toStr(i + 1, 2) << " | ";
	}
	cout << toStr("Res", nc_result + 1) << "| " << toStr("Dep", nc_dep + 1) << "|" << endl;
	;

	for (const Personne *p : vp) {
//		cerr<< "tr1 id="<<p->getIdProv()<<"name="<<p->getName() <<endl;
		cout << mkLigne(p, nc_result, nc_dep) << endl;
//		cerr<< "tr2 id="<<p->getIdProv()<<endl;
	}
	cout << endl << endl << endl;

}

// private
string Ihm::set_colors(int fg, int bg) const {
	stringstream ss;
	ss << "\33[3" << fg << ";4" << bg << "m";
	return ss.str();
}

