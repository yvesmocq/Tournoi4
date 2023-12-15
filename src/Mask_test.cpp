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
 * Mask_test.cpp
 *
 *  Created on: 17 sept. 2023
 *      Author: Yves Mocquard
 */
#include <cstdlib>
#include <iostream>
#include "Mask.h"


bool test_mask()
{

	Mask<1024> m;
	bool tab[1024];
	for( int i=0 ; i < 1024 ; i++)
	{
		tab[i] = rand()%2 == 0;
		if ( m.isBit(i) )
		{
			cout << "erreur 1  i="<<i<<endl;
			return false;
		}
		if ( tab[i] )
		{
			m.setBit(i);
		}
		if ( m.isBit(i) != tab[i])
		{
			cout << "erreur 2  i="<<i<<endl;
			return false;
		}
	}


	for ( int i = 0 ; i < 1024 ; i++ )
	{
		if ( m.isBit(i) != tab[i])
		{
			cout << "erreur 3  i="<<i<<endl;
			return false;
		}
	}
	cout <<"test_mask OK"<<endl;
	return true;
}

