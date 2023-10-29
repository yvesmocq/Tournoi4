/*
 * Tools_test.cpp
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves
 */

#include "Tools.h"

bool test_tools()
{

	Tools *pt=Tools::getInstance();

	int res= pt->genElo();
	bool result =  0 < res && res < 4000;


	string s1=string("ABC éê ë ä a D ï îüG");
	string s2=string("abc ee e a a d i iug");

	char str[40];

//	int lg=pt->toStr(str,s1,40);
//
//	result = result && lg == 20 && string(str) == s1;
//
//	cout <<"lg="<<lg<<endl;
//	cout << "XXX"<< string(str) <<"XXX" <<endl;
	cout << "XXX"<< s1 <<"XXX" <<endl;
	cout << "XXX"<< pt->toSimple(s1) <<"XXX" <<endl;
	cout << "XXX"<< s2 <<"XXX" <<endl;






	return result && pt->toSimple(s1) == s2;

}

