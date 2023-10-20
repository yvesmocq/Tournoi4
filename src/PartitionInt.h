/*
 * PartitionInt.h
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves
 */

#ifndef PARTITIONINT_H_
#define PARTITIONINT_H_
using namespace std;
#include <set>
#include <list>
#include <array>

class PartitionInt {
private:
	list<array<int,3>> dec4;

public:
	PartitionInt();

	virtual ~PartitionInt();

	const list<array<int,3>> &getList() const
		{
		return dec4;
		}

};

#endif /* PARTITIONINT_H_ */
