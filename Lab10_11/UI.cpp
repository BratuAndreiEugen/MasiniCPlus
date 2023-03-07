#include <iostream>
#include "UI.h"
#include <string>
#include "myVector.h"

using std::string;
using std::cout;
using std::cin;

void ConsoleUI::menu()
{
	cout << "1. Afiseaza toate masinile disponibile \n";
	cout << "2. Adaugare \n";
	cout << "3. Stergere \n";
	cout << "4. Modificare \n";
	cout << "5. Cautare dupa numarul de inmatriculare \n";
	cout << "6. Filtrare dupa producator sau tiip \n";
	cout << "7. Sortare dupa numar de inmatriculare / tip / prducator + model \n";
	cout << "8. Deschide management spalatorie \n";
	cout << "9. remove_if cu TIP \n";
	cout << "10. UNDO \n";
	cout << "0. Iesire din aplicatie \n";

}

void ConsoleUI::carWashMenu()
{
	cout << "       1. Adauga masina \n";
	cout << "       2. Goleste lista \n";
	cout << "       3. Adauga masini random \n";
	cout << "       4. Export in fisier CSV \n";
	cout << "       0. Intoarcere la aplicatia principala \n";
}

void ConsoleUI::printAll()
{
	if (service.getAllCars().size() == 0)
		cout << "--Nu sunt masini in depozit--\n\n";
	
	for(const auto& car :  service.getAllCars())
	{
		cout << "Nr : " << car.getNumar() << " / Producator : " << car.getProducator() << " / Model : " << car.getModel() << " / Tip : " << car.getTip() << "\n";
	}
	cout << "\n";
}

void ConsoleUI::adaugare()
{
	string model, tip, producator;
	int nrInmatriculare;
	cout << " Producator : ";
	cin >> producator;
	cout << "\n";

	cout << " Model : ";
	cin >> model;
	cout << "\n";

	cout << " Tip : ";
	cin >> tip;
	cout << "\n";

	cout << " Numar de inmptriculare : ";
	cin >> nrInmatriculare;
	cout << "\n";

	try {
		service.addCar(nrInmatriculare, producator, model, tip);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << "Masina nu este valida!\n";
		cout << ve.getErrorMessages();
	}
	cout << "\n";
}

void ConsoleUI::stergere()
{
	int nrInmatriculare;
	cout << " Numarul de inmatriculare : ";
	cin >> nrInmatriculare;

	try {
		service.removeCar(nrInmatriculare);
	}
	catch (RepoException& re) {
		cout << re.getErrorMessage();
	}
	catch (ValidationException& ve) {
		cout << ve.getErrorMessages();
	}
	cout << "\n";
}

void ConsoleUI::stergereIF()
{
	string tip;
	cout << "Introduceti un tip pentru care se vor sterge toate masinile : ";
	cin >> tip;
	cout << "\n";
	service.removeIF(tip);
	
	printAll();

}

void ConsoleUI::modificare()
{
	int nrInmatriculare;
	cout << " Numarul de inmatriculare : ";
	cin >> nrInmatriculare;
	cout << "\n";

	try {
		Masina m = service.findCar(nrInmatriculare);
		string newP, newM, newT;
		cout << "Pentru urmatoarele campuri introduceti noua valoare sau apasati ENTER pentru a lasa campul nemodificat--\n\n";

		cout << " Noul producator : ";
		cin >> newP;
		cout << "\n";
		if (newP == "")
			newP = m.getProducator();

		cout << " Noul model : ";
		cin >> newM;
		cout << "\n";
		if (newM == "")
			newM = m.getModel();

		cout << " Noul tip : ";
		cin >> newT;
		cout << "\n";
		if (newT == "")
			newT = m.getTip();

		try {
			service.modifyCar(nrInmatriculare, nrInmatriculare, newP, newM, newT);
		}
		catch (ValidationException) {
			cout << "--Noile date sunt invalide.Se renunta la modificare--";
		}

	}
	catch(RepoException) {
		cout << "--Numar de inmatriculare invalid--\n\n";
	}
	catch (ValidationException) {
		cout << "--Numar de inmatriculare invalid--\n\n";
	}

	

	
}

void ConsoleUI::cautare()
{
	int nrInmatriculare;
	cout << " Numarul de inmatriculare : ";
	cin >> nrInmatriculare;
	cout << "\n";

	try {
		Masina m = service.findCar(nrInmatriculare);
		cout << "Masina dvs. a fost gasita : \n";
		cout << "Nr : " << m.getNumar() << " / Producator : " << m.getProducator() << " / Model : " << m.getModel() << " / Tip : " << m.getTip() << "\n";
	}
	catch (RepoException& re)
	{
		cout << re.getErrorMessage();
	}
	catch (ValidationException& va)
	{
		cout << va.getErrorMessages();
	}
	cout << "\n";
}


void ConsoleUI::filtrare()
{
	cout << "\n   1. Filtrare dupa producator\n";
	cout << "   2. Filtrare dupa tip\n";


	int option;
	cout << "Introduceti optiunea : ";
	cin >> option;
	cout << "\n";

	if (option == 1)
	{
		cout << "Introduceti un producator : ";
		string producator;
		cin >> producator;
		cout << "\n";
		vector<Masina> v;
		service.filter("producator", producator, v);

		if (v.size() == 0)
			cout << "--Nu sunt masini in filtru--\n\n";

		for (const auto& car : v)
		{
			cout << "Nr : " << car.getNumar() << " / Producator : " << car.getProducator() << " / Model : " << car.getModel() << " / Tip : " << car.getTip() << "\n";
		}
		cout << "\n";
	}
	else if (option == 2)
	{
		cout << "Introduceti un tip : ";
		string tip;
		cin >> tip;
		cout << "\n";
		vector<Masina> v;
		service.filter("tip", tip, v);

		if (v.size() == 0)
			cout << "--Nu sunt masini in filtru--\n\n";

		for(const auto & car : v)
		{
			cout << "Nr : " << car.getNumar() << " / Producator : " << car.getProducator() << " / Model : " << car.getModel() << " / Tip : " << car.getTip() << "\n";
		}
		cout << "\n";
	}
	else
	{
		cout << "--Optiune invalida--\n";
	}
}

void ConsoleUI::sortare()
{
	cout << "\n   1. Sortare dupa numarul de inmatriculare\n";
	cout << "   2. Sortare dupa tip\n";
	cout << "   3. Sortare dupa prodcuator + model\n";


	int option;
	cout << "Introduceti optiunea : ";
	cin >> option;
	cout << "\n";

	vector<Masina> v;
	switch (option)
	{
		case 1:
			
			service.sort("numar inmatriculare", v);

			if (v.size() == 0)
				cout << "--Nu sunt masini in filtru--\n\n";

			for (const auto& car : v)
			{
				cout << "Nr : " << car.getNumar() << " / Producator : " << car.getProducator() << " / Model : " << car.getModel() << " / Tip : " << car.getTip() << "\n";
			}
			cout << "\n";
			break;
		case 2:
			service.sort("tip", v);

			if (v.size() == 0)
				cout << "--Nu sunt masini in filtru--\n\n";

			for (const auto& car : v)
			{
				cout << "Nr : " << car.getNumar() << " / Producator : " << car.getProducator() << " / Model : " << car.getModel() << " / Tip : " << car.getTip() << "\n";
			}
			cout << "\n";
			break;
		case 3:
			service.sort("producator+model", v);

			if (v.size() == 0)
				cout << "--Nu sunt masini in filtru--\n\n";

			for (const auto& car : v)
			{
				cout << "Nr : " << car.getNumar() << " / Producator : " << car.getProducator() << " / Model : " << car.getModel() << " / Tip : " << car.getTip() << "\n";
			}
			cout << "\n";
			break;

		default:
			cout << " Criteriu invalid \n";

	}
}


void ConsoleUI::uiUndo() {
	try {
		service.undoService();
	}
	catch (ServiceException e) {
		cout << e.getErrorMessage();
		return;
	}
	cout << "  Undo realizat cu succes \n\n";
}

void ConsoleUI::defaultStart()
{

	try {
		service.addCar(101, "Mercedes-Benz", "Clasa G", "SUV");
		service.addCar(102, "Audi", "A7", "Sport");
		service.addCar(103, "Range Rover", "Velar", "SUV");
		service.addCar(104, "BMW", "Seria 3", "Sedan");
		service.addCar(105, "Toyota", "Proace", "Dubita");
		service.addCar(106, "Mercedes-Benz", "EQS", "Limuzina");
		service.addCar(107, "Audi", "TT", "Sport");
		service.addCar(108, "Toyota", "Supra", "Sport");
		service.addCar(109, "Volkswagen", "Polo", "Compact");
		service.addCar(110, "Volkswagen", "Arteon", "Sedan");
	}
	catch (RepoException)
	{
		cout << "Cel putin una dintre masinile default sunt deja in fisier\n";
	}
}


void ConsoleUI::addCarWash()
{
	int nrInmatriculare;
	cout << "         Numarul de inmatriculare : ";
	cin >> nrInmatriculare;
	cout << '\n';
	try {
		service.addToWashingList(nrInmatriculare);
	}
	catch (RepoException& ex) {
		cout << ex.getErrorMessage();
	}

}

void ConsoleUI::emptyCarWash()
{
	service.emptyWashingList();
}

void ConsoleUI::generateCarWash()
{
	int nr;
	cout << "         Numarul maxim : ";
	cin >> nr;
	cout << '\n';
	service.populateWashingList(nr);
}

void ConsoleUI::exportCarWash()
{
	string filename;
	cout << "         Numele fisierului CSV : ";
	cin >> filename;
	cout << "\n";

	try {
		service.saveWashesToFile(filename);
	}
	catch (RepoException& ex)
	{
		cout << ex.getErrorMessage();
	}
}


void ConsoleUI::startCarWash()
{
	int option;
	while (true) {

		if (service.getAllWashingListed().size() == 0)
			cout << "\n       --Nu sunt masini in depozit--\n\n";
		else
			cout << "\n       --Masinile din spalatorie sunt : \n";

		for (const auto& car : service.getAllWashingListed())
		{
			cout << "       Nr : " << car.getNumar() << " / Producator : " << car.getProducator() << " / Model : " << car.getModel() << " / Tip : " << car.getTip() << "\n";
		}
		cout << "\n";

		carWashMenu();
		cout << "        Optiunea : ";
		cin >> option;
		cout << '\n';

		switch (option)
		{
			case 1:
				addCarWash();
				break;
			case 2:
				emptyCarWash();
				break;
			case 3:
				generateCarWash();
				break;
			case 4:
				exportCarWash();
				break;
			case 0:
				return;
			default:
				cout << "       Mai incearca \n";

		}
	}
}

void ConsoleUI::start()
{
	cout << "  Doriti sa incepeti cuu o lista default ?\n" << "    1. Da     2. Nu  \n";
	
	int option;
	cin >> option;
	if (option == 1)
	{
		defaultStart();
		cout << " Au fost adaugate cateva masini \n";
	}
	cout << "\n";
	
	while (true) {
		menu();
		cout << " Optiunea : ";
		cin >> option;
		cout << '\n';

		switch (option)
		{
			case 1:
				printAll();
				break;
			case 2:
				adaugare();
				break;
			case 3:
				stergere();
				break;
			case 4:
				modificare();
				break;
			case 5:
				cautare();
				break;
			case 6:
				filtrare();
				break;
			case 7:
				sortare();
				break;
			case 8:
				startCarWash();
				break;
			case 9:
				stergereIF();
				break;
			case 10:
				uiUndo();
				break;
			case 0:
				return;
			default:
				cout << "Mai incearca \n";
		
		}	
	}
}