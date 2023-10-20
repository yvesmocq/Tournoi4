/*
 * Mask_test.cpp
 *
 *  Created on: 17 sept. 2023
 *      Author: Yves
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

