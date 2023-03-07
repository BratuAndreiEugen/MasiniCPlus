#pragma once
#include "Service.h"
class ConsoleUI
{
private:

	ServiceMasini& service;

public:
	ConsoleUI(ServiceMasini& serv) : service{ serv } {};

	ConsoleUI(ConsoleUI& other) = delete;

	/// <summary>
	/// Afiseaza meniul
	/// </summary>
	void menu();

	/// <summary>
	/// Afiseaza meniul pentru spalatorie
	/// </summary>
	void carWashMenu();


	/// <summary>
	/// Afiseaza toate masinile salvate
	/// </summary>
	void printAll();

	/// <summary>
	/// Adauga o masina in lista dupa citirea si validarea datelor
	/// </summary>
	void adaugare();

	/// <summary>
	/// Sterge o masina
	/// </summary>
	void stergere();

	/// <summary>
	/// Sterge toate masinile din lista daca o anumita conditie este indeplinita
	/// </summary>
	void stergereIF();

	/// <summary>
	/// Modifica datele unei masini
	/// </summary>
	void modificare();

	/// <summary>
	/// Cauta o masina dupa numar de inmatriculare
	/// </summary>
	void cautare();

	/// <summary>
	/// Filtreaza dupa un criteriu dat de utilizator
	/// </summary>
	void filtrare();
	
	/// <summary>
	/// Sortare dupa un criteriu dat de utilizator
	/// </summary>
	void sortare();

	void uiUndo();

	/// <summary>
	/// Creeaza o lista default de masini
	/// </summary>
	void defaultStart();

	void addCarWash();

	void emptyCarWash();

	void generateCarWash();

	void exportCarWash();


	/// <summary>
	/// Porneste management-ul spalatoriei
	/// </summary>
	void startCarWash();

	/// <summary>
	/// Inceputul aplicatiei
	/// </summary>
	void start();
};

