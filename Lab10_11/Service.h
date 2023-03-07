#pragma once
#include "Masina.h"
#include "Repository.h"
#include "Validator.h"
#include "myVector.h"
#include "WashingList.h"
#include "UndoClass.h"

/// <summary>
/// Clasa de exceptii specifice Repository
/// </summary>
class ServiceException {
private:

	string errorMsg;

public:

	ServiceException(string errorMsg) :errorMsg{ errorMsg } {};

	string getErrorMessage() {
		return this->errorMsg;
	}
};



class ServiceMasini
{
private:

	RepositoryMasini& repo;
	ValidatorMasini& validator;
	WashingList& washingList;
	vector<UndoClass*> undo;

public:

	//constructor
	ServiceMasini(RepositoryMasini& mRepo, ValidatorMasini& mVal, WashingList& list) :repo{ mRepo }, validator{ mVal }, washingList{ list } {};

	ServiceMasini(const ServiceMasini& other) = delete;

	/// <summary>
	/// Returneaza vectorul cu toate masinile din depozit
	/// </summary>
	/// <returns></returns> vector of Masina obj
	const vector<Masina>& getAllCars() {
		return this->repo.getAllCars();
	}

	/// <summary>
	/// Incearca adaugarea unei masini in service
	/// </summary>
	/// <param name="nrInmatriculare"></param>
	/// <param name="producator"></param>
	/// <param name="model"></param>
	/// <param name="tip"></param>
	/// @throws RepoException daca masina cu numarul de inmatriculare dat exista deja
	///         ValidationException daca datele oferite ca parametrii nu sunt corecte
	void addCar(int nrInmatriculare, std::string producator, std::string model, std::string tip);

	/// <summary>
	/// Incearca stergerea unei masini din service
	/// </summary>
	/// <param name="nrInmatriculare"></param>
	/// @throws RepoException daca masina pe care incercam sa o eliminam nu exista
	///         ValidationException daca numarul de inmatriculare dat nu este valid
	void removeCar(int nrInmatriculare);

	/// <summary>
	/// Sterge toate masinile din lista care au tipul dat
	/// </summary>
	/// <param name="tip"></param>
	void removeIF(std::string tip);

	/// <summary>
	/// Modifica masina cu numarul de innmatriculare dat daca aceasta exista
	/// </summary>
	/// <param name="nrInmatriculare"></param>
	/// <param name="newNr"></param>
	/// <param name="newProducator"></param>
	/// <param name="newModel"></param>
	/// <param name="newTip"></param>
	/// @throws RepoException daca masina pe care incercam sa o modificam nu exista
	///         ValidationException daca datele noi nu sunt valide
	void modifyCar(int nrInmatriculare, int newNr, string newProducator, string newModel, string newTip);

	/// <summary>
	/// Cauta o masina dupa nuamrul de inmatriculare
	/// </summary>
	/// <param name="nrInmatriculare"></param>
	/// <returns></returns>
	/// @throws RepoException daca masina nu a fost gasita
	///         ValidationException daca numarul de inmatriculare nu este valid
	const Masina& findCar(int nrInmatriculare);


	void filter(string criteriu, string relevantInfo, vector<Masina>& filteredList);

	void sort(string criteriu, vector<Masina>& sortedList);

	/// <summary>
	/// Face operatia de undo folosind polimorfismul claselor din UndoClass.h
	/// </summary>
	void undoService();

	/// <summary>
	/// Elibereaza toata memoria de pe heap utilizata de lista de undo si sterge toate el. din aceasta
	/// </summary>
	void clearUndo();

	/// <summary>
	/// Adauga in lista de spalat
	/// </summary>
	/// <param name="numarInmatriculare"></param>
	void addToWashingList(int numarInmatriculare);

	/// <summary>
	/// Elibereaza lista de spalat
	/// </summary>
	void emptyWashingList();

	/// <summary>
	/// Returneaza o lista cu toate masinile din spalatorie
	/// </summary>
	/// <returns></returns>
	const vector<Masina>& getAllWashingListed();


	/// <summary>
	/// Salveaza masinile din spalatorie intr-un fisier CSV
	/// </summary>
	/// <param name="filename"></param>
	void saveWashesToFile(string filename);

	void populateWashingList(int max);

	vector<string> getAllTypes();

	string countByType(string type);

	void addObserverToWL(Observer* o) { this->washingList.addObserver(o); };

};

void testService();
