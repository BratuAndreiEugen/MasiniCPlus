#include "Lab10_11.h"
#include <QtWidgets/QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
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
#include "GUI.h"


void GUIStartUp()
{
    ValidatorMasini val;

    //RepositoryMasini repo;
    FileRepositoryMasini repo("masini.txt");

    //_CrtDumpMemoryLeaks();

    WashingList list;

    ServiceMasini service{ repo, val, list };

    GUI ui{ service };
    ui.show();
}

void testAll1()
{
    testVector();
    testMasina();
    testRepo();
    testService();
    testWashingList();
}

int main(int argc, char *argv[])
{
    testAll1();

    QApplication a(argc, argv);
    ValidatorMasini val;

    //RepositoryMasini repo;
    FileRepositoryMasini repo("masini.txt");

    //_CrtDumpMemoryLeaks();

    WashingList list;

    ServiceMasini service{ repo, val, list };

    GUI ui{ service };
    ui.setGeometry(500, 100, 1000, 600);
    ui.show();
    
    
    //wl.show();


    return a.exec();
}
