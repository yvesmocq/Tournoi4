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
#include "Ihm.h"



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

int main(int ac, const char *av[] ) {
	// bool flag_test=false;
	bool flag_test=false;

	if ( ac == 2 )
	{
		if ( string(av[1]) == "test" )
			flag_test = true;
		else
		{
			if ( string(av[1]) == "result")
			{
				Tirage::getInstance("svt4.dt4");
				Ihm::getInstance()->affResult();
				exit(0);
			}
		}
	}

	if ( flag_test )
	{
		cout <<"sizeok(FlatTirage)="<<sizeof(FlatTirage)<<endl;
		if ( !test_all())
			cout<<"Non OK!!!"<<endl;
		else
			cout<<"OK!!!"<<endl;
	}
	else
	{
		Ihm *p_ihm = Ihm::getInstance();
		Tirage::getInstance("svt4.dt4");
		p_ihm->lancement();

//		cout << "trace1" <<endl;
//		Simu *simu=Simu::getInstance(16);
//		cout << "trace2" <<endl;
//
//		for ( int i = 0 ; i < 4 ; i++)
//		{
//			simu->simule(1, i >= 3);
//			cout << "trace3" <<endl;
//
//			simu->affResult();
//			cout << "trace4" <<endl;
//		}

	}




	return 0;
}
