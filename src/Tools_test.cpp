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
 * Tools_test.cpp
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves Mocquard
 */

#include "Tools.h"

bool test_tools()
{

	Tools *pt=Tools::getInstance();

	int res= pt->genElo();
	bool result =  0 < res && res < 4000;


	string s1=string("ABC éê ë ä a D ï îüG");
	string s2=string("abc ee e a a d i iug");

//	char str[40];

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

