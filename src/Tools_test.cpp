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
	return  0 < res && res < 4000;

}

