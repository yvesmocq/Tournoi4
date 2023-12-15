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
 * PartitionInt.cpp
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves Mocquard
 */

#include "PartitionInt.h"


PartitionInt::PartitionInt() {

	set< array<int,3> > sd,sdbis;

	array<int,3> zero={};

	sd.insert(zero);


	this->dec4.push_back(zero);

	for( int sum = 1 ; sum < 4 ; sum++ )
	{
		swap(sd,sdbis);
		sd.clear();
		for( const array<int,3> & a3 : sdbis)
		{
			for ( int i = 0 ; i < 3 ; i++)
			{
				array<int,3> newa3 = a3;
				newa3[i]++;
				sd.insert(newa3);
			}
		}
		// ld.append_range(sd);
		this->dec4.insert(this->dec4.end(),sd.begin(),sd.end());
	}

}


PartitionInt::~PartitionInt() {
	// TODO Auto-generated destructor stub
}


