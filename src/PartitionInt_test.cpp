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
 * PartitionInt_test.cpp
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves Mocquard
 */

#include "PartitionInt.h"
#include <iostream>


bool test_partitionInt()
{
	PartitionInt p;
	return p.getList().size() == 20;

//	for ( const auto &res: p.getList())
//	{
//		cout <<"list "<<i++;
//		for (auto c : res )
//			cout<<" "<< c<<" ";
//		cout << endl;
//	}
}

