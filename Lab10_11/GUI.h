#pragma once
#include <vector>
#include <string>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "Service.h"
#include <QTableWidget>
#include <QListWidget>
#include "Observer.h"
#include <qpainter.h>
#include "Model.h"
#include <qtableview.h>

using std::vector;
using std::string;

class WashingListGUI : public QWidget, public Observer
{
	friend class GUI;
private:
	ServiceMasini& service;


	// Adaugare 
	QLabel* lblNumar = new QLabel{ "Numarul de inmatriculare : " };
	QLineEdit* editNumar;
	QPushButton* adauga;

	// Generare
	QLabel* lblCount = new QLabel{ "Numarul de masini : " };
	QLineEdit* editCount;
	QPushButton* genereaza;

	// Golire
	QPushButton* goleste;

	// Export
	QLabel* lblFile = new QLabel{ "Fisierul de export : " };
	QLineEdit* editFile;
	QPushButton* exp;


	// Reload
	QPushButton* reloadData;


	// Tabel
	//QTableWidget* masini;

	// Acm lista
	QListWidget* masini;

	// Close
	QPushButton* closeApp;

	void initialize();
	void reloadMasini(vector<Masina> cars);
	void connectSignalsToSlots();

	void update() override {
		this->reloadMasini(service.getAllWashingListed());
	};

public:
	WashingListGUI(ServiceMasini& s) : service{ s } {
		setMouseTracking(true);
		initialize();
		connectSignalsToSlots();
		reloadMasini(service.getAllWashingListed());
	}

	void adaugareWL();
	void golireWL();
	void generareWL();
	void exportWL();


};

class GUI : public QWidget
{
	friend class WashingListGUI;
private:
	ServiceMasini& service;

	QLabel* lblNumar = new QLabel{ "Numarul de inmatriculare : " };
	QLabel* lblNumar1 = new QLabel{ "Numarul de inmatriculare : " }; // STERGERE
	QLabel* lblProducator = new QLabel{ "Producatorul : " };
	QLabel* lblModel = new QLabel{ "Modelul : " };
	QLabel* lblTip = new QLabel{ "Tipul : " };

	QLineEdit* editNumar;
	QLineEdit* editProducator;
	QLineEdit* editModel;
	QLineEdit* editTip;
	
	QLineEdit* editNumar1; // STERGERE

	// MODIFICARE
	QLineEdit* editNumar2;
	QLineEdit* editProducator2;
	QLineEdit* editModel2;
	QLineEdit* editTip2;

	QLabel* lblNumar2 = new QLabel{ "Numarul de inmatriculare ( al masinii pe care doriti sa o modificati ) : " };
	QLabel* lblProducator2 = new QLabel{ "Noul producator : " };
	QLabel* lblModel2 = new QLabel{ "Noul model : " };
	QLabel* lblTip2 = new QLabel{ "Noul tip : " };

	// CAUTARE
	QLineEdit* editNumar3;
	QLabel* lblNumar3 = new QLabel{ "Numarul de inmatriculare : " };

	QPushButton* cauta;
	QPushButton* adauga;
	QPushButton* modifica;
	QPushButton* sterge;
	QPushButton* undo;
	QPushButton* filtrare;
	QPushButton* sortare;
	QPushButton* closeApp;
	QPushButton* washingList; // WASHING LIST
	QPushButton* rdWashingList = new QPushButton("Spalatorie ( Read only - > Drawing )");

	// FILTRARE
	QWidget* filter = new QWidget;

	QPushButton* filterProducator;
	QLabel* filterP = new QLabel("I : ");
	QLineEdit* editProducatorFilter;
	string prod;

	QPushButton* filterTip;
	QLabel* filterT = new QLabel("II : ");
	QLineEdit* editTipFilter;
	string tip;

	QPushButton* closeFilter;

	// SORTARE
	QWidget* sort = new QWidget;

	QPushButton* sortNumar;
	QPushButton* sortTip;
	QPushButton* sortProducatorModel;

	QPushButton* closeSort;


	QPushButton* reloadData;
	QTableView* masini; // tabel de masini
	Model* myModel; // modelul pentru tabelul de masini

	// Partea cu butoane dinamice
	QWidget* dynamicBtns;
	QHBoxLayout* btnsLayout;
	vector<QPushButton*> typeBtns;

	void initialize();
	void reloadMasini(vector<Masina> cars);
	void connectSignalsToSlots();

	// WASHING LIST
	WashingListGUI wl{ service };
	//wl.setGeometry(0, 100, 500, 300);

	// Butoane pt. washing llist management
	QLineEdit* editNrW;
	QPushButton* adaugaW;

	QLineEdit* editCountW;
	QPushButton* genereazaW;

	QPushButton* golesteW;





public:
	GUI(ServiceMasini& s) : service{ s } {
		setMouseTracking(true);
		initialize();
		connectSignalsToSlots();
		reloadMasini(service.getAllCars());
	}

	void cautareGUI();
	void adaugareGUI();
	void stergereGUI();
	void modificareGUI();
	void undoGUI();

	void filtrareGUI();
	void sortareGUI();

	void refreshDynamicButtons();

};


class DrawingGUI : public QWidget, public Observer {

private:
	ServiceMasini& service;


	void initialize() {};

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int x = 0, y = 0;
		int lastPoz = 0;
		for (int i = 0; i < this->service.getAllWashingListed().size(); i++)
		{
			x = lastPoz * 200;
			if(x > 600){
				lastPoz = 0;
				y += 50;
				x = 0;
			}
			p.drawEllipse(x, y, 200, 50);
			string s;
			s.append(std::to_string(i + 1));
			s.append(" ");
			s.append(this->service.getAllWashingListed()[i].getProducator());
			s.append(" ");
			s.append(this->service.getAllWashingListed()[i].getModel());
			p.drawText(x + 20, y + 25, QString::fromStdString(s));
			lastPoz++;
		}
	};
	void update() override {
		
	};
	
public:
	DrawingGUI(ServiceMasini& s) : service{ s } {
		setMouseTracking(true);
		initialize();
	}

};