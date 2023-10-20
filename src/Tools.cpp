/*
 * Tools.cpp
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves
 */
#include "Tools.h"

//static
Tools * Tools::instance=nullptr;

Tools::Tools(): generator(time(nullptr)), distribution(normal_distribution<double>(5.0,2.0))
 {

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



