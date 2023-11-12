/*
 * Tools.cpp
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves
 */
#include "Tools.h"

//static
Tools * Tools::instance=nullptr;

void Tools::inittabconvacc()
{
#define conv(from,to) tabconvacc[int((unsigned char)from)] = to
	for( int i = 0 ; i < 256 ; i++ )
	{
		tabconvacc[i] = char(i);
	}
	conv('é','e');
	conv('è','e');
	conv('ê','e');
	conv('ë','e');
	conv('â', 'a');
	conv('ä', 'a');
	conv('à', 'a');
	conv('î', 'i');
	conv('ï', 'i');
	conv('ô', 'o');
	conv('ö', 'o');
	conv('ù', 'u');
	conv('û', 'u');
	conv('ü', 'u');
	int diff = int('a')-int('A');
	for ( int i = int('A') ; i <=int('Z') ; i++ )
	{
		conv(i, i+diff);
	}

}
Tools::Tools(): generator(time(nullptr)), distribution(normal_distribution<double>(5.0,2.0))
 {
	inittabconvacc();
	srand(time(nullptr));
}

Tools::~Tools() {
	// TODO Auto-generated destructor stub
}

//static
Tools * Tools::getInstance()
{
	if ( instance == nullptr )
	{
		instance = new Tools();
	}
	return instance;
}

// static function
double Tools::doubleRand()
{
	return ((double)rand())/RAND_MAX;
}

int Tools::genElo()
{
	return 1000+distribution(generator)*200;
}

bool Tools::bernoulli( double p)
{
	bernoulli_distribution d(p);
	return d(generator);
}

string Tools::toSimple( string from ) const
{

	const char *ptrin = from.c_str();

	char ptrout[from.length()+1];

	int i_out = 0;
	for ( size_t i = 0 ; i < from.length() ; i++)
	{
		int v = int( (unsigned char) ptrin[i]);
//		cout <<v<<endl;
		if ( v != 195 )
			ptrout[i_out++]  = tabconvacc[v];
	}

	ptrout[i_out] = '\0';

	return string(ptrout);
}
int Tools::cmp( const char *p1, const char *p2, size_t s) const
{
	for ( size_t i=0 ; i < s ; i++ )
	{
		if( p1[i] != p2[i] )
			return i;
	}
	return s;
}



