/*
 * Personne.cpp
 *
 *  Created on: 7 sept. 2023
 *      Author: Yves
 */

#include "Personne.h"

// static
int Personne::serie_id_pers=1;

// static
void Personne::resetSerieId(){
	serie_id_pers = 1;
}

Personne::Personne():id_pers(serie_id_pers) {
	serie_id_pers++;
}
Personne::Personne(const string &n):name(n),id_pers(serie_id_pers) {
	serie_id_pers++;
}
Personne::Personne(int id):id_pers(id) {

}


Personne::~Personne()
{}


int Personne::getResult()
{
	if ( this->nbScore != (int)this->matches.size() )
	{
		int res=0;
		int sumdiff=0;
		int diff;

		for( Match *pm : this->matches )
		{
			res += pm->getScore(this, &diff);
			sumdiff += diff;
		}
		this->result = res;
		this->diff = diff;
		this->nbScore = this->matches.size();
	}
	return this->result;
}
double Personne::setNote()
{
	this->getResult();
	if ( id_pers == 0)
		this->note = -1;
	else
		this->note = double(result)+ this->diff*0.01+Tools::doubleRand()*0.0001;
	return this-> note;
}

void Personne::mkMaskMatch()
{
	this->maskMatch1.reset();
	this->maskMatch2.reset();
	for( Match * pm: this->matches )
	{
		if ( pm->istittable() )
		{
			this->maskMatch1.setBit(0);
			this->maskMatch2.setBit(0);
		}
		else
		{
			for( int pid: pm->getPersId() )
			{
				if ( this->maskMatch1.isBit(pid) )
					this->maskMatch2.setBit(pid);
				else
					this->maskMatch1.setBit(pid);
			}
		}
	}
}
const list<Match *> & Personne::getMatches() const
{
	return matches;
}
void Personne::addMatch(Match *m)
{
	this->matches.push_back(m);
}
void Personne::setName(const string & name)
{
	this->name = name;
}
const string & Personne::getName() const
{
	return this->name;
}
string Personne::toStr(){
	char str[10];
	sprintf(str,"%*d",2,id_prov+1);
	return string(str);
}
string Personne::toStrName(){
	char str[100];
	char str2[30];
	strcpy(str,name.c_str());
	str[20] = '\0';
	sprintf(str2,"%*s",10,str);
	return string(str2);
}

string Personne::mkLigne()
{
	stringstream ss;

	ss <<"| " << this->toStr() << " |";
	ss << this->toStrName() << "|";

	for( Match *m:matches)
	{
		ss << m->toStr(this);
		ss << "|";
	}
	ss << " ";
	ss << this->result;
	ss << " |";

	return ss.str();

}


