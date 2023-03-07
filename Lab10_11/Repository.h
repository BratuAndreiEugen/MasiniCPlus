#pragma once
#include <vector>
#include <string>
#include "Masina.h"
#include "myVector.h"

using std::vector;
using std::string;


/// <summary>
/// Clasa de exceptii specifice Repository
/// </summary>
class RepoException {
private:

	string errorMsg;

public:

	RepoException(string errorMsg) :errorMsg{ errorMsg } {};

	string getErrorMessage() {
		return this->errorMsg;
	}
};

class RepositoryMasini
{
protected:

	vector<Masina> cars;

public:

	RepositoryMasini() = default;

	/// <summary>
	/// Constructor de copiere care asigura existenta unui singur obiect repo in program
	/// </summary>
	/// <param name="other"></param>
	RepositoryMasini(const RepositoryMasini& other) = delete;


	/// <summary>
	/// Returneaza o lista cu toate masinile salvate
	/// </summary>
	/// <returns></returns> lista cu masini ( vector de obiecte Masina )
	const vector<Masina>& getAllCars();

	/// <summary>
	/// Confirma daca o masina exista sau nu in lista
	/// </summary>
	/// <param name="m"></param> Masina object
	/// <returns></returns> true daca exista, altfel false
	bool exists(const Masina& m);

	/// <summary>
	/// Cauta o masina dupa numarul acesteia de inmatriculare
	/// </summary>
	/// <param name="numarInmatriculare"></param>
	/// <returns></returns>
	const Masina& find(int numarInmatriculare);

	/// <summary>
	/// Adauga o masina in lista
	/// </summary>
	/// <param name="m"></param>
	/// @throws RepoException daca masina exista deja in lista ( numarul de inmatriculare exista deja in lista )
	virtual void store(const Masina& m);

	/// <summary>
	/// Sterge o masina din lista
	/// </summary>
	/// @throws RepoException daca masina pe care incercam sa o stergem nu se afla in lista
	virtual void remove(Masina& m);

	void removeIF(string tip);

	/// <summary>
	/// Modifica masina m cu datele masinii newM
	/// </summary>
	/// <param name="m"></param>
	/// <param name="newM"></param>
	virtual void modify(Masina& m, Masina& newM);
};

class FileRepositoryMasini : public RepositoryMasini {

private:
	string filename;
	
	void loadFromFile();

	void saveToFile();

public:
	FileRepositoryMasini(string fname) : RepositoryMasini(), filename{ fname } {
		loadFromFile();
	};
	
	void store(const Masina& m) override;

	void remove(Masina& m) override;

	void modify(Masina& m, Masina& newM) override;

};

void testRepo();
