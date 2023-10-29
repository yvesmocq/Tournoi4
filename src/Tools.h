/*
 * Tools.h
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves
 */

#ifndef TOOLS_H_
#define TOOLS_H_
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <sstream>
#include <random>
#include <array>
using namespace std;


class Tools {
private :
	static Tools *instance;
	default_random_engine generator;
	normal_distribution<double> distribution;

	array<char,256> tabconvacc;
	void inittabconvacc();

	Tools();

public:

	static const size_t sizeMax=256;

	static Tools * getInstance();
	virtual ~Tools();
	Tools& operator=(const Tools &other);
	Tools& operator=(Tools &&other);
	static double doubleRand();
	int genElo();
	bool bernoulli(double p);
	template<size_t N>
	string to_string(array<int,N> t)
	{

		stringstream ss("array<>{");
		for( size_t i = 0 ; i < N ; i ++)
		{
			ss << t[i];
			if ( i == N-1)
				ss << "}";
			else
				ss << ",";
		}
		return ss.str();
	}

	string toSimple( string from) const;


};

#endif /* TOOLS_H_ */
