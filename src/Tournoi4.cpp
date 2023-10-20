//============================================================================
// Name        : Tournoi4.cpp
// Author      : Yves Mocquard
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


using namespace std;
#include <iostream>
#include "PartitionInt.h"
#include "Personne.h"
#include "Match.h"
#include "Tirage.h"
#include "Simu.h"



bool test_partitionInt(void);
bool test_match(void);
bool test_personne(void);
bool test_tirage(void);
bool test_mask(void);
bool test_tools(void);
bool test_simu(void);


bool test_all()
{
	if( !test_partitionInt() )
	{
		cout <<"Erreur partitionInt"<<endl;
		return false;
	}
	if( !test_mask() )
	{
		cout << "Erreur test_mask"<<endl;
		return false;
	}
	if ( ! test_tools() )
	{
		cout << "Erreur test_tools"<<endl;
		return false;
	}
	if ( !test_match() )
		return false;
	if ( !test_personne() )
		return false;
	if ( !test_tirage() )
		return false;
	if ( !test_simu() )
		return false;

	return true;
}

int main() {
	// bool flag_test=false;
	bool flag_test=true;

	if ( flag_test )
	{
		if ( !test_all())
			cout<<"Non OK!!!"<<endl;
		else
			cout<<"OK!!!"<<endl;
	}
	else
	{
		cout << "trace1" <<endl;
		Simu *simu=Simu::getInstance(16);
		cout << "trace2" <<endl;

		for ( int i = 0 ; i < 4 ; i++)
		{
			simu->simule(1, i >= 3);
			cout << "trace3" <<endl;

			simu->affResult();
			cout << "trace4" <<endl;
		}

	}




	return 0;
}
