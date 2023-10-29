/*
 * Personne.cpp
 *
 *  Created on: 7 sept. 2023
 *      Author: Yves
 */

#include "Personne.h"
#include "Tools.h"
#include <cstring>

// static
int Personne::serie_id_pers=1;

// static
Personne::P_Less Personne::PersonneLess=P_Less();
Personne::P_More Personne::PersonneMore=P_More();
Personne::P_NameLess Personne::PNameLess=P_NameLess();


// static
void Personne::resetSerieId(){
	serie_id_pers = 1;
}

Personne::Personne():id_pers(serie_id_pers) {
	serie_id_pers++;
}
Personne::Personne(const string &n):name(n),nameSimple(Tools::getInstance()->toSimple(n)+name), id_pers(serie_id_pers) {
	serie_id_pers++;
}
Personne::Personne(int id):id_pers(id) {

}


Personne::~Personne()
{}


int Personne::calculResult()
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
double Personne::calculNote()
{
	this->calculResult();
	if ( id_pers == 0)
		this->note = -1;
	else
		this->note = double(result)+ this->diff*0.01+Tools::doubleRand()*0.0001;
	return this->note;
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
	this->nameSimple = Tools::getInstance()->toSimple(name)+name;
}
const string & Personne::getName() const
{
	return this->name;
}
const string & Personne::getNameSimple() const
{
	return this->nameSimple;
}
double Personne::getNote() const
{
	return this->note;
}
const Mask<> & Personne::getMaskMatch1() const
		{
	return this->maskMatch1;
		}
const Mask<> &  Personne::getMaskMatch2() const
		{
	return this->maskMatch2;
		}
double  Personne::getResult() const
{
	return this->result;
}
void Personne::setId_prov(int id_prov)
{
	this->id_prov = id_prov;
}


string Personne::toStr() const{
	char str[10];
	sprintf(str,"%*d",2,id_prov+1);
	return string(str);
}
string Personne::toStrName() const{
	char str[100];
	char str2[30];
	strcpy(str,name.c_str());
	str[20] = '\0';
	sprintf(str2,"%*s",10,str);
	return string(str2);
}

string Personne::mkLigne() const
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


string Personne::numName() const
{
	stringstream ss;

	ss << (id_prov+1) <<". "<< name;

	return ss.str();


}

// static function
//void sortnum( vector<Personne *> & vec, function<bool(Personne *,Personne *)> fct)
void Personne::sortnum( vector<Personne *> & vec, function<bool(Personne *,Personne *)> fct)
{
	sort(vec.begin(),vec.end(),fct);
	for ( int i = 0 ; i < (int)vec.size() ; i++)
	{
		vec[i]->setId_prov(i);
	}
}

void Personne::setPresent( bool flag)
{
	present = flag;
}
bool Personne::isPresent() const
{
	return present;
}

FlatPers Personne::getFlat() const
{
	FlatPers fp={};
	fp.id = id_pers;
	strncpy(fp.name.data(), name.c_str(), 39);


	return fp;

}
