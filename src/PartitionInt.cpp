/*
 * PartitionInt.cpp
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves
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


