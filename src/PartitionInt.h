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
 * PartitionInt.h
 *
 *  Created on: 13 sept. 2023
 *      Author: Yves Mocquard
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
