/*
 * PartitionInt_test.cpp
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves
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

