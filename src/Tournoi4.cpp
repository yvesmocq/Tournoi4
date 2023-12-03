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

void signal_handler(int sig)
{
	system("rm sem.sem");
	signal(SIGINT, SIG_DFL);
	raise(SIGINT);
}

int main(int ac, const char *av[] ) {
	// bool flag_test=false;
	bool flag_test=false;
	bool flag_save=false;
	string rep_save;



	int indarg=1;
	while( indarg < ac )
	{
		if ( string(av[indarg]) == "test" )
		{
			flag_test = true;
			indarg++;
			break;
		}
		if ( string(av[indarg]) == "matches" )
		{
			Tirage::getInstance("svt4.dt4");
			Ihm::getInstance()->afficheMatches();
			exit(0);

		}
		if ( string(av[indarg]) == "result")
		{
			Tirage::getInstance("svt4.dt4");
			Ihm::getInstance()->affResult();
			exit(0);
		}
		if ( string(av[indarg]) == "--save" )
		{
			if ( ++indarg < ac )
			{
				rep_save = string(av[indarg]);
				flag_save = true;
			}
			else
			{
				cerr << "erreur il manque le repertoire de sauvegarde"<<endl;
				exit(-1);
			}
		}
		indarg++;

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
		Tirage *pt = Tirage::getInstance("svt4.dt4");
		if ( flag_save )
		{
			pt->setNomFichierAdd(rep_save+"/svt4.dt4");
		}

		FILE *fd= fopen("sem.sem","r");
		if ( fd != NULL )
		{
			cout << "Erreur programme deja lancé !!" <<endl;
			exit(0);
		}
		fd = fopen("sem.sem","w+");
		if ( fd == NULL )
		{
			cout <<"Erreur création fichier sem.sem"<<endl;
			exit(-1);
		}
		fclose(fd);

		signal(SIGINT,signal_handler);

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
