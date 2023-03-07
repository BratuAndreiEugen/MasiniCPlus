#include <iostream>
#include <string>
#include <vector>
#include "Masina.h"
#include "Repository.h"
#include "Service.h"
#include "Validator.h"
#include "testVector.h"
#include "UI.h"
#include "WashingList.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

void testAll()
{
	testVector();
	testMasina();
	testRepo();
	testService();
	testWashingList();
}

void startUp()
{
	ValidatorMasini val;

	//RepositoryMasini repo;
	FileRepositoryMasini repo("masini.txt");

	//_CrtDumpMemoryLeaks();

	WashingList list;

	ServiceMasini service{ repo, val, list };

	ConsoleUI ui{ service };

	ui.start();
}

/*
int main()
{

	testAll();
	startUp();

	_CrtDumpMemoryLeaks();
	return 0;
}
*/