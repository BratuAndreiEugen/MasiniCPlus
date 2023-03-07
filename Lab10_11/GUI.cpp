#include "GUI.h"
#pragma once
#include <vector>
#include <sstream>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "Service.h"
#include <QTableWidget>
#include <QFormLayout>
#include <QHeaderView>
#include <QmessageBox>
#include <iostream>
#include "Model.h"

using std::vector;
using std::string;

void GUI::initialize()
{
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	// Partea din stanga 
	QWidget* left = new QWidget;
	QVBoxLayout* leftLayout = new QVBoxLayout;
	left->setLayout(leftLayout);

	// Adaugare
	QWidget* formAdd = new QWidget;
	QFormLayout* formLayout = new QFormLayout;
	formAdd->setLayout(formLayout);

	editNumar = new QLineEdit;
	editProducator = new QLineEdit;
	editModel = new QLineEdit;
	editTip = new QLineEdit;

	formLayout->addRow(lblNumar, editNumar);
	formLayout->addRow(lblProducator, editProducator);
	formLayout->addRow(lblModel, editModel);
	formLayout->addRow(lblTip, editTip);

	adauga = new QPushButton("Adauga masina");
	formLayout->addWidget(adauga);

	leftLayout->addWidget(formAdd);

	// Stergere
	QWidget* formRemove = new QWidget;
	QFormLayout* rm = new QFormLayout;
	editNumar1 = new QLineEdit;
	rm->addRow(lblNumar1, editNumar1);

	sterge = new QPushButton("Sterge masina");
	rm->addWidget(sterge);

	formRemove->setLayout(rm);
	leftLayout->addWidget(formRemove);

	// Modificare
	QWidget* formModify = new QWidget;
	QFormLayout* md = new QFormLayout;
	editNumar2 = new QLineEdit;
	editProducator2 = new QLineEdit;
	editModel2 = new QLineEdit;
	editTip2 = new QLineEdit;

	md->addRow(lblNumar2, editNumar2);
	md->addRow(lblProducator2, editProducator2);
	md->addRow(lblModel2, editModel2);
	md->addRow(lblTip2, editTip2);

	modifica = new QPushButton("Modifica masina");
	md->addWidget(modifica);

	formModify->setLayout(md);
	leftLayout->addWidget(formModify);

	// Cautare
	QWidget* formSearch = new QWidget;
	QFormLayout* sr = new QFormLayout;
	editNumar3 = new QLineEdit;
	sr->addRow(lblNumar3, editNumar3);

	cauta = new QPushButton("Cauta masina");
	sr->addWidget(cauta);

	formSearch->setLayout(sr);
	leftLayout->addWidget(formSearch);

	// Undo
	undo = new QPushButton("Undo");
	leftLayout->addWidget(undo);
	
	

	// Reload
	reloadData = new QPushButton("Reload Tabel");
	leftLayout->addWidget(reloadData);



	// Partea din dreapta
	QWidget* right = new QWidget;
	QVBoxLayout* rightLayout = new QVBoxLayout;
	right->setLayout(rightLayout);

	int lines = 0;
	int columns = 4;
	this->masini = new QTableView;
	myModel = new Model(this, this->service.getAllCars());
	this->masini->setModel(myModel);

	QStringList tableHeader;
	tableHeader << "Numar de inmatriculare" << "Producator" << "Model" << "Tip";
	//this->masini->setHorizontalHeaderLabels(tableHeader);

	// redimensionarea automata a celulelor
	//this->masini->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	rightLayout->addWidget(this->masini);

	// Filtrare
	filtrare = new QPushButton("        Filtrare ( Aplicata pe tabel )        ");
	rightLayout->addWidget(filtrare);
	filterProducator = new QPushButton("Filtrare dupa producator");
	filterTip = new QPushButton("Filtrare dupa tip");

	editProducatorFilter = new QLineEdit;
	editTipFilter = new QLineEdit;

	// Fereastra de filtrare
	QVBoxLayout* layout = new QVBoxLayout;
	this->filter->setLayout(layout);


	closeFilter = new QPushButton("Inchide");

	QFormLayout* l1 = new QFormLayout;
	QFormLayout* l2 = new QFormLayout;
	QWidget* formProducator = new QWidget;
	formProducator->setLayout(l1);
	QWidget* formTip = new QWidget;
	formTip->setLayout(l2);


	l1->addRow(filterP, editProducatorFilter);
	l2->addRow(filterT, editTipFilter);

	layout->addWidget(formProducator);
	layout->addWidget(filterProducator);

	layout->addWidget(formTip);
	layout->addWidget(filterTip);


	layout->addWidget(closeFilter);


	// Sortare
	sortare = new QPushButton("        Sortare ( Aplicata pe tabel )        ");
	rightLayout->addWidget(sortare);

	// Fereastra de sortare
	sortNumar = new QPushButton("Sortare dupa numarul de inmatriculare");
	sortTip = new QPushButton("Sortare dupa tip");
	sortProducatorModel = new QPushButton("Sortare dupa producator si model");

	QVBoxLayout* sortLayout = new QVBoxLayout;
	this->sort->setLayout(sortLayout);
	closeSort = new QPushButton("Inchide");

	sortLayout->addWidget(sortNumar);
	sortLayout->addWidget(sortTip);
	sortLayout->addWidget(sortProducatorModel);
	sortLayout->addWidget(closeSort);
	

	// Partea cu butoane dinamice
	dynamicBtns = new QWidget;
	btnsLayout = new QHBoxLayout;
	dynamicBtns->setLayout(btnsLayout);
	refreshDynamicButtons();

	rightLayout->addWidget(dynamicBtns);

	// Deschindere washing list
	washingList = new QPushButton("Spalatorie");
	rightLayout->addWidget(washingList);

	rightLayout->addWidget(rdWashingList);

	// Inchidere aplicatie
	closeApp = new QPushButton("Inchide");
	rightLayout->addWidget(closeApp);


	// PARTEA DIN DREAPTA DE TOT :) ( Lab 13 )
	QWidget* hRight = new QWidget;
	QVBoxLayout* hLayout = new QVBoxLayout;
	hRight->setLayout(hLayout);

	// Adaugare
	QWidget* formAddW = new QWidget;
	QFormLayout* formLayoutW = new QFormLayout;
	formAddW->setLayout(formLayoutW);

	editNrW = new QLineEdit;
	QLabel* lblNrW = new QLabel{ "Numarul de inmatriculare : " };
	formLayoutW->addRow(lblNrW, editNrW);

	adaugaW = new QPushButton("Adauga masina");
	formLayoutW->addWidget(adaugaW);

	hLayout->addWidget(formAddW);


	// Generare
	QWidget* formGenW = new QWidget;
	QFormLayout* genLayoutW = new QFormLayout;
	formGenW->setLayout(genLayoutW);

	QLabel* lblCountW = new QLabel{ "Numarul de masini : " };
	editCountW = new QLineEdit;

	genLayoutW->addRow(lblCountW, editCountW);

	genereazaW = new QPushButton("Genereaza lista");
	genLayoutW->addWidget(genereazaW);

	hLayout->addWidget(formGenW);

	// Golire
	golesteW = new QPushButton("Goleste");
	hLayout->addWidget(golesteW);

	// Final set-up
	mainLayout->addWidget(left);
	mainLayout->addWidget(right);
	mainLayout->addWidget(hRight);

	
}

void GUI::reloadMasini(vector<Masina> cars)
{
	/*
	this->masini->clearContents();
	this->masini->setRowCount(cars.size());

	int line = 0;
	for (auto& car : cars)
	{
		this->masini->setItem(line, 0, new QTableWidgetItem(QString::number(car.getNumar())));
		this->masini->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(car.getProducator())));
		this->masini->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(car.getModel())));
		this->masini->setItem(line, 3, new QTableWidgetItem(QString::fromStdString(car.getTip())));
		line++;
	}
	*/
	this->myModel->setCars(cars);

}

void GUI::connectSignalsToSlots()
{
	QObject::connect(closeApp, &QPushButton::clicked, this, &QWidget::close);

	QObject::connect(adauga, &QPushButton::clicked, this, &GUI::adaugareGUI);

	QObject::connect(reloadData, &QPushButton::clicked, [&]() {this->reloadMasini(service.getAllCars()); });

	QObject::connect(sterge, &QPushButton::clicked, this, &GUI::stergereGUI);

	QObject::connect(modifica, &QPushButton::clicked, this, &GUI::modificareGUI);

	QObject::connect(undo, &QPushButton::clicked, this, &GUI::undoGUI);

	QObject::connect(cauta, &QPushButton::clicked, this, &GUI::cautareGUI);

	QObject::connect(filtrare, &QPushButton::clicked, this, &GUI::filtrareGUI);

	QObject::connect(filterProducator, &QPushButton::clicked, [&]() {
		this->prod = editProducatorFilter->text().toStdString();
		vector<Masina> filteredList;
		this->service.filter("producator", this->prod, filteredList);
		this->reloadMasini(filteredList);
		QMessageBox::information(this, "Info", QString::fromStdString("Filtru aplicat"));
		this->filter->close();
		this->editProducatorFilter->clear();
		});

	QObject::connect(filterTip, &QPushButton::clicked, [&]() {
		this->tip = editTipFilter->text().toStdString();
		vector<Masina> filteredList;
		this->service.filter("tip", this->tip, filteredList);
		this->reloadMasini(filteredList);
		QMessageBox::information(this, "Info", QString::fromStdString("Filtru aplicat"));
		this->filter->close();
		this->editTipFilter->clear();
		});

	QObject::connect(sortare, &QPushButton::clicked, this, &GUI::sortareGUI);

	QObject::connect(sortNumar, &QPushButton::clicked, [&]() {
		vector<Masina> sortedList;
		this->service.sort("numar inmatriculare", sortedList);
		this->reloadMasini(sortedList);
		QMessageBox::information(this, "Info", QString::fromStdString("Sortare aplicata"));
		this->sort->close();
		});

	QObject::connect(sortTip, &QPushButton::clicked, [&]() {
		vector<Masina> sortedList;
		this->service.sort("tip", sortedList);
		this->reloadMasini(sortedList);
		QMessageBox::information(this, "Info", QString::fromStdString("Sortare aplicata"));
		this->sort->close();
		});

	QObject::connect(sortProducatorModel, &QPushButton::clicked, [&]() {
		vector<Masina> sortedList;
		this->service.sort("producator+model", sortedList);
		this->reloadMasini(sortedList);
		QMessageBox::information(this, "Info", QString::fromStdString("Sortare aplicata"));
		this->sort->close();
		});


	// Washing List
	QObject::connect(washingList, &QPushButton::clicked, [&]() {
		//this->wl.show();
		WashingListGUI* w1 = new WashingListGUI(this->service);
		w1->show();
		this->service.addObserverToWL(w1);
		});

	// Read only drawing washing list
	QObject::connect(rdWashingList, &QPushButton::clicked, [&]() {
		//this->wl.show();
		DrawingGUI* w1 = new DrawingGUI(this->service);
		w1->show();
		this->service.addObserverToWL(w1);
		});

	// WASHING LIST MANAGEMENT
	QObject::connect(adaugaW, &QPushButton::clicked, [&]() {
		int nr = editNrW->text().toInt();
		editNrW->clear();
		this->service.addToWashingList(nr);
		});

	QObject::connect(genereazaW, &QPushButton::clicked, [&]() {
		int nr = editCountW->text().toInt();
		editCountW->clear();
		this->service.populateWashingList(nr);
		});

	QObject::connect(golesteW, &QPushButton::clicked, [&]() {
		this->service.emptyWashingList();
		});

}


void GUI::cautareGUI()
{
	try {
		// Preluare date din formular
		int numar = editNumar3->text().toInt();
		
		editNumar3->clear();

		Masina found = this->service.findCar(numar);
		this->reloadMasini(service.getAllCars());

		// mesaj
		string msj = "Masina cautata este :  ";
		msj.append(found.getProducator());
		msj.append(" ");
		msj.append(found.getModel());
		msj.append("  / ");
		msj.append(found.getTip());
		QMessageBox::information(this, "Info", QString::fromStdString(msj));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}

void GUI::adaugareGUI()
{
	try {
		// Preluare date din formular
		int numar = editNumar->text().toInt();
		string producator = editProducator->text().toStdString();
		string model = editModel->text().toStdString();
		string tip = editTip->text().toStdString();

		editNumar->clear();
		editProducator->clear();
		editModel->clear();
		editTip->clear();

		this->service.addCar(numar, producator, model, tip);
		this->reloadMasini(service.getAllCars());
	
		// mesaj
		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes."));

		refreshDynamicButtons();
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}

void GUI::stergereGUI()
{
	try {
		// Preluare date din formular
		int numar = editNumar1->text().toInt();
		

		editNumar1->clear();

		this->service.removeCar(numar);
		this->reloadMasini(service.getAllCars());

		// mesaj
		QMessageBox::information(this, "Info", QString::fromStdString("Masina stearsa cu succes."));
		this->wl.reloadMasini(service.getAllWashingListed());
		refreshDynamicButtons();
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}

void GUI::modificareGUI()
{
	try {
		// Preluare date din formular
		int numar = editNumar2->text().toInt();
		string producator = editProducator2->text().toStdString();
		string model = editModel2->text().toStdString();
		string tip = editTip2->text().toStdString();

		editNumar2->clear();
		editProducator2->clear();
		editModel2->clear();
		editTip2->clear();

		this->service.modifyCar(numar, numar, producator, model, tip);
		this->reloadMasini(service.getAllCars());

		// mesaj
		QMessageBox::information(this, "Info", QString::fromStdString("Masina modificata cu succes."));

		refreshDynamicButtons();
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	catch (ValidationException& ve)
	{
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getErrorMessages()));
	}
}

void GUI::undoGUI()
{
	try {
		this->service.undoService();
		this->reloadMasini(service.getAllCars());
		QMessageBox::information(this, "Info", QString::fromStdString("Undo realizat cu succes"));

		this->wl.reloadMasini(service.getAllWashingListed());
		refreshDynamicButtons();
	}
	catch (ServiceException& se) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(se.getErrorMessage()));
	}
}

void GUI::filtrareGUI()
{
	
	this->filter->show();

	QObject::connect(closeFilter, &QPushButton::clicked, this->filter, &QWidget::close);
	
}

void GUI::sortareGUI()
{
	this->sort->show();

	QObject::connect(closeSort, &QPushButton::clicked, this->sort, &QWidget::close);
}

void GUI::refreshDynamicButtons()
{
	vector<string> types = service.getAllTypes();
	/*if (dynamicBtns->layout() != NULL)
	{
		QLayoutItem* item;
		while ((item = dynamicBtns->layout()->takeAt(0)) != NULL)
		{
			delete item->widget();
			delete item;
		}
		delete dynamicBtns->layout();
	}*/
	for (QPushButton* b : typeBtns)
	{
		delete b;
	}


	typeBtns.clear();
	for (string type : types)
	{
		QPushButton* a = new QPushButton(QString::fromStdString(type));
		typeBtns.push_back(a);
		btnsLayout->addWidget(a);
		//QMessageBox::information(this, "Info", QString::fromStdString(std::to_string(service.countByType(type))));
		string str = this->service.countByType(type);
		QObject::connect(a, &QPushButton::clicked, this, [=]() {QMessageBox::information(this, "Info", QString::fromStdString(str)); });
	}

}



// WASHING LIST


void WashingListGUI::initialize()
{
	QHBoxLayout* mainLayout = new QHBoxLayout;
	this->setLayout(mainLayout);

	// !! Partea din stanga !!
	QWidget* left = new QWidget;
	QVBoxLayout* leftLayout = new QVBoxLayout;
	left->setLayout(leftLayout);

	// Adaugare
	QWidget* formAdd = new QWidget;
	QFormLayout* formLayout = new QFormLayout;
	formAdd->setLayout(formLayout);

	editNumar = new QLineEdit;

	formLayout->addRow(lblNumar, editNumar);

	adauga = new QPushButton("Adauga masina");
	formLayout->addWidget(adauga);

	leftLayout->addWidget(formAdd);

	
	// Generare
	QWidget* formGen = new QWidget;
	QFormLayout* genLayout = new QFormLayout;
	formGen->setLayout(genLayout);

	editCount = new QLineEdit;

	genLayout->addRow(lblCount, editCount);

	genereaza = new QPushButton("Genereaza lista");
	genLayout->addWidget(genereaza);

	leftLayout->addWidget(formGen);

	// Golire
	goleste = new QPushButton("Goleste");
	leftLayout->addWidget(goleste);

	// Export
	QWidget* formExp = new QWidget;
	QFormLayout* expLayout = new QFormLayout;
	formExp->setLayout(expLayout);

	editFile = new QLineEdit;

	expLayout->addRow(lblFile, editFile);


	exp = new QPushButton("Export");
	expLayout->addWidget(exp);

	leftLayout->addWidget(formExp);

	// Reload
	reloadData = new QPushButton("Reload Lista");
	leftLayout->addWidget(reloadData);



	// !! Partea din dreapta !!
	QWidget* right = new QWidget;
	QVBoxLayout* rightLayout = new QVBoxLayout;
	right->setLayout(rightLayout);

	int lines = 0;
	int columns = 4;
	this->masini = new QListWidget;

	//QStringList tableHeader;
	//tableHeader << "Numar de inmatriculare" << "Producator" << "Model" << "Tip";
	//this->masini->setHorizontalHeaderLabels(tableHeader);

	// redimensionarea automata a celulelor
	//this->masini->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	rightLayout->addWidget(masini);

	

	// Inchidere cos
	closeApp = new QPushButton("Inchide");
	rightLayout->addWidget(closeApp);


	// Final set-up
	mainLayout->addWidget(left);
	mainLayout->addWidget(right);


}

void WashingListGUI::connectSignalsToSlots()
{
	QObject::connect(closeApp, &QPushButton::clicked, this, &QWidget::close);
	QObject::connect(adauga, &QPushButton::clicked, this, &WashingListGUI::adaugareWL);
	QObject::connect(goleste, &QPushButton::clicked, this, &WashingListGUI::golireWL);
	QObject::connect(genereaza, &QPushButton::clicked, this, &WashingListGUI::generareWL);
	QObject::connect(exp, &QPushButton::clicked, this, &WashingListGUI::exportWL);

	QObject::connect(reloadData, &QPushButton::clicked, [&]() {this->reloadMasini(service.getAllWashingListed()); });

}

void WashingListGUI::reloadMasini(vector<Masina> cars)
{
	// cu tabel
	//this->masini->clearContents();
	//this->masini->setRowCount(cars.size());

	// cu lista 
	this->masini->clear();

	int line = 0;
	for (auto& car : cars)
	{
		try{
			this->service.findCar(car.getNumar());
			// TABEL
			//this->masini->setItem(line, 0, new QTableWidgetItem(QString::number(car.getNumar())));
			//this->masini->setItem(line, 1, new QTableWidgetItem(QString::fromStdString(car.getProducator())));
			//this->masini->setItem(line, 2, new QTableWidgetItem(QString::fromStdString(car.getModel())));
			//this->masini->setItem(line, 3, new QTableWidgetItem(QString::fromStdString(car.getTip())));
			//line++;

			// LISTA
			this->masini->addItem(QString::fromStdString(car.getData()));
		}
		catch (RepoException& re) {
			continue;
		}
	}

}

void WashingListGUI::adaugareWL()
{
	try {
		// Preluare date din formular
		int numar = editNumar->text().toInt();

		editNumar->clear();

		this->service.addToWashingList(numar);
		this->reloadMasini(service.getAllWashingListed());

		// mesaj
		QMessageBox::information(this, "Info", QString::fromStdString("Masina adaugata cu succes."));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
}

void WashingListGUI::golireWL()
{
	this->service.emptyWashingList();
	this->reloadMasini(service.getAllWashingListed());
	QMessageBox::information(this, "Info", QString::fromStdString("Lista a fost golita."));
}

void WashingListGUI::generareWL()
{
	int nr = editCount->text().toInt();

	editCount->clear();

	this->service.populateWashingList(nr);
	this->reloadMasini(service.getAllWashingListed());

	QMessageBox::information(this, "Info", QString::fromStdString("Au fost generate masini."));
}

void WashingListGUI::exportWL()
{

	try {
		// Preluare date din formular
		string filename = editFile->text().toStdString();

		editFile->clear();

		this->service.saveWashesToFile(filename);

		// mesaj
		QMessageBox::information(this, "Info", QString::fromStdString("Lista a fost salvata in fisier."));
	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getErrorMessage()));
	}
	
}