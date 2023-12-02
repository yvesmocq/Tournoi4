/*
 * Personne.cpp
 *
 *  Created on: 7 sept. 2023
 *      Author: Yves
 */

#include "Personne.h"
#include "Tools.h"
#include "Tirage.h"
#include <cstring>
#include <cassert>

// static
int Personne::serie_id_pers = 1;

// static
const Personne::P_Less Personne::PersonneLess = P_Less();
const Personne::P_More Personne::PersonneMore = P_More();
const Personne::P_NameLess Personne::PNameLess = P_NameLess();
const Personne::P_MoreDepartage Personne::PMoreDepartage = P_MoreDepartage();


// static
void Personne::resetSerieId() {
	serie_id_pers = 0;
	Personne::nextIdPers();
}

// static public pour test
int Personne::getSerieId() {
	return serie_id_pers;
}

// static function
void Personne::nextIdPers() {
	if (Tirage::isInstance()) {
		const vector<Personne*> &va = Tirage::getInstance()->getAllPersonnes();
		for (int i = serie_id_pers + 1; i < (int) va.size(); i++) {
			if (va[i] == nullptr) {
				serie_id_pers = i;
				break;
			}
		}
	} else {
		serie_id_pers++;
	}

}

// static
int Personne::getIdPersNext() {
	int ret = serie_id_pers;
	Personne::nextIdPers();
	return ret;
}

Personne::Personne() :
		present(true), id_pers(Personne::getIdPersNext()) {
}
Personne::Personne(const string &n) :
		present(true), id_pers(Personne::getIdPersNext()) {
	setName(n);
}
Personne::Personne(int id):
		 present(false), nbScore(0),id_pers(id) {
	assert(id_pers == 0 && "forçage de l'identifiant d'un objet Personne différent de zéro");

}
Personne::Personne(const FlatPers &fp) :
		present(fp.present), id_pers(fp.id) {
	setName(string(fp.name.data()));
	Personne::nextIdPers();
}

Personne::~Personne() {
	if (id_pers < serie_id_pers) {
		serie_id_pers = id_pers;
	}
}
int Personne::getAffLength() const
{
	return nameSimple.length() - name.length();
}
int Personne::getDiffAccent() const
{
	return 2*name.length() - nameSimple.length();
}

int Personne::calculResult() {
	int res = 0;
	int sumdiff = 0;
	int diff;

	for (Match *pm : this->matches) {
		if (pm->isResultInit() )
		{
			res += pm->getScore(this, &diff);
			sumdiff += diff;
		}
	}
	this->result = res;
	this->diff = diff;
	this->nbScore = this->matches.size();
	return this->result;
}
double Personne::calculNote() {
	this->calculResult();
	if (id_pers == 0)
		this->note = -1;
	else
		this->note = double(result) + this->diff * 0.01 + Tools::doubleRand() * 0.0001;
	return this->note;
}

void Personne::calculDepartage()
{
	int res=0;
	for (Match *pm : this->matches) {
		if (pm->isResultInit() )
		{
			for ( const Personne *p:pm->getPersonnes() )
			{
				if ( p != this && p->id_pers != 0)
				{
					res += p->getResult();
				}
			}
		}
	}
	this->departage = res;
}
int Personne::getDepartage() const
{
	return departage;
}

string Personne::club() const
{
	return name.substr(min(name.rfind("("),name.length()));
}
//public
bool Personne::isSameClub( const Personne * p) const
{
	return club() == p->club();
}
void Personne::mkMaskMatch() {
	this->maskMatch1.reset();
	this->maskMatch2.reset();
	for (Match *pm : this->matches) {
		if (pm->istittable()) {
			this->maskMatch1.setBit(0);
			this->maskMatch2.setBit(0);
		} else {
			for (int pid : pm->getPersId()) {
				if (this->maskMatch1.isBit(pid))
					this->maskMatch2.setBit(pid);
				else
					this->maskMatch1.setBit(pid);
			}
		}
	}
}
const list<Match*>& Personne::getMatches() const {
	return matches;
}
int Personne::addMatch(Match *m) {
	this->matches.push_back(m);
	this->calculResult();
	return matches.size();
}
void Personne::setName(const string &name) {
	this->name = name;
	this->nameSimple = Tools::getInstance()->toSimple(name) + name;
}
const string& Personne::getName() const {
	return this->name;
}
const string& Personne::getNameSimple() const {
	return this->nameSimple;
}
double Personne::getNote() const {
	return this->note;
}
const Mask<>& Personne::getMaskMatch1() const {
	return this->maskMatch1;
}
const Mask<>& Personne::getMaskMatch2() const {
	return this->maskMatch2;
}
double Personne::getResult() const {
	return this->result;
}
void Personne::setId_prov(int id_prov) {
	this->id_prov = id_prov;
}
int Personne::getIdProv() const {
	return this->id_prov;
}


// static function
//void sortnum( vector<Personne *> & vec, function<bool(Personne *,Personne *)> fct)
void Personne::sortnum(vector<Personne*> &vec, function<bool(Personne*, Personne*)> fct) {
	sort(vec.begin(), vec.end(), fct);
	for (int i = 0; i < (int) vec.size(); i++) {
		vec[i]->setId_prov(i);
	}
}

void Personne::setPresent(bool flag) {
	present = flag;
}
bool Personne::isPresent() const {
	return present;
}

FlatPers Personne::getFlat() const {
	FlatPers fp = { };
	fp.isValid = true;
	fp.present = this->present;
	fp.id = id_pers;
	strncpy(fp.name.data(), name.c_str(), 39);
	return fp;

}

