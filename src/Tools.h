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
#include <string>
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
	static const size_t clubMax=16; // nombre maximum de club
	static const size_t sizeMax=128; // nombre max de personne +1
	static const size_t matchMax=(sizeMax/4)*20; // nombre maximum de clubs
	static const size_t sizeNameMax=32; // taille max des noms
	static const size_t sizeNCMax=16; // talle max accronyme du club

	static Tools * getInstance();
	virtual ~Tools();
	Tools& operator=(const Tools &other);
	Tools& operator=(Tools &&other);
	static double doubleRand();
	int genElo();
	bool bernoulli(double p);
	template<size_t N>
	static string to_string(array<int,N> t)
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
	static string to_string(vector<int> t)
	{

		stringstream ss("vector<>{");
		for( size_t i = 0 ; i < t.size() ; i ++)
		{
			ss << t[i];
			if ( i == t.size()-1)
				ss << "}";
			else
				ss << ",";
		}
		return ss.str();
	}

	string toSimple( string from) const;
	int cmp( const char *p1, const char *p2, size_t s) const;

	int nbChif(int n) const;


};

#endif /* TOOLS_H_ */
