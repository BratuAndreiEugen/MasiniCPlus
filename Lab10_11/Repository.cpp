#include "Repository.h"
#include "myVector.h"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <assert.h>

const vector<Masina>& RepositoryMasini::getAllCars() {
	return this->cars;
}

bool RepositoryMasini::exists(const Masina& m) {
	try {
		find(m.getNumar());
		return true;
	}
	catch (RepoException) {
		return false;
	}
}

const Masina& RepositoryMasini::find(int numarInmatriculare) {
	/*
	IteratorVector<Masina> i(this->cars);
	i = this->cars.begin();
	while (i.valid()) {
		if ((* i).getNumar() == numarInmatriculare)
		{
			return *i;
		}
		i.next();
	}*/

	vector<Masina>::iterator f = std::find_if(this->cars.begin(), this->cars.end(),
		[=](const Masina& m) {
			return m.getNumar() == numarInmatriculare;
		});
	
	if (f != this->cars.end())
		return (*f);
	else {
		std::string s = std::to_string(numarInmatriculare);
		throw RepoException("Masina cu numarul de inmatriculare " + s + " nu a fost gasita in depozit\n");
	}
}

void RepositoryMasini::store(const Masina& m) {
	if (exists(m)) {
		throw RepoException("Masina " + m.getProducator() + " " + m.getModel() + " cu numarul de inmatriculare dat este deja in depozit\n");
	}
	this->cars.push_back(m);
}

void RepositoryMasini::remove(Masina& m) {

	if (!exists(m)) {
		throw RepoException("Masina " + m.getProducator() + " " + m.getModel() + " cu numarul de inmatriculare dat nu se afla in depozit\n");
	}

	/*
	IteratorVector<Masina> i(this->cars);
	i = this->cars.begin();
	int poz = 0;
	while (i.valid()) {
		if ((*i).getNumar() == m.getNumar())
		{
			cars.remove(poz);

		}
		poz++;
		i.next();
	}*/

	vector<Masina>::iterator f = std::find_if(this->cars.begin(), this->cars.end(),
		[=](const Masina& ma) {
			return ma.getNumar() == m.getNumar();
		});

	this->cars.erase(f);

}

void RepositoryMasini::removeIF(string tip)
{
	vector<Masina>::iterator pend;
	pend = std::remove_if(cars.begin(), cars.end(),
		[tip](const Masina& m) {
			return m.getTip() == tip;
		});

	
	


	cars.erase(pend, cars.end());
}

void RepositoryMasini::modify(Masina& m, Masina& newM)
{
	if (!exists(m))
	{
		throw RepoException("Masina " + m.getProducator() + " " + m.getModel() + " cu numarul de inmatriculare dat nu se afla in depozit\n");
	}
	/*
	IteratorVector<Masina> i(this->cars);
	for (i = 0; i < this->cars.size(); ++i) {
		if ((*i).getNumar() == m.getNumar())
		{
			(*i).setNumar(newM.getNumar());
			(*i).setModel(newM.getModel());
			(*i).setProducator(newM.getProducator());
			(*i).setTip(newM.getTip());
		}
	}*/

	vector<Masina>::iterator f = std::find_if(this->cars.begin(), this->cars.end(),
		[=](const Masina& ma) {
			return ma.getNumar() == m.getNumar();
		});

	(*f).setNumar(newM.getNumar());
	(*f).setModel(newM.getModel());
	(*f).setProducator(newM.getProducator());
	(*f).setTip(newM.getTip());
}


// REPOSITORY CU FISIERE

void FileRepositoryMasini::loadFromFile()
{
	std::ifstream f(this->filename);

	if (!f.is_open())
	{
		throw RepoException("-- Nu se poate citi din fisierul " + filename + "--");
	}

	string line;
	while (getline(f, line))
	{
		string producator, model, tip;
		int nr = 0;

		std::stringstream linestream(line);
		string curent;
		int i = 0;

		// Se citeste : NumarInmatriculare/Producator/Model/Tip
		while (getline(linestream, curent, '/'))
		{
			switch (i)
			{
				case 0:
					try {
						nr = std::stoi(curent);
					}
					catch (int e)
					{
						e = 0;
						throw RepoException("--Datele din fisier sunt invalide--");
					}
					break;
				case 1:
					producator = curent;
					break;
				case 2:
					model = curent;
					break;
				case 3:
					tip = curent;
					break;
				default:
					break;
			
			}
			i++;
		}

		Masina m{ nr, producator, model, tip };

		RepositoryMasini::store(m);

	}
	f.close();

}

void FileRepositoryMasini::saveToFile() {
	std::ofstream f(this->filename);

	if (!f.is_open())
	{
		throw RepoException("-- Nu se poate scrie in fisierul " + filename + "--");
	}

	for (auto& m : getAllCars())
	{
		f << m.getNumar() << "/" << m.getProducator() << "/" << m.getModel() << "/" << m.getTip() << "\n";
	}

	f.close();
}

void FileRepositoryMasini::store(const Masina& m) {
	RepositoryMasini::store(m);
	saveToFile();
}

void FileRepositoryMasini::remove(Masina& m) {
	RepositoryMasini::remove(m);
	saveToFile();
}

void FileRepositoryMasini::modify(Masina& m, Masina& newM) {
	RepositoryMasini::modify(m, newM);
	saveToFile();
}


// TESTE

void testFindRepo()
{
	RepositoryMasini repo;
	Masina m{ 102, "d", "a", "b" };

	assert(repo.getAllCars().size() == 0);
	repo.store(m);

	assert(repo.find(102).getProducator() == "d");
	
	int err = 0;
	try {
		repo.find(100);

	}
	catch (RepoException) {
		err = 1;
	}

	assert(err == 1);
}

void testStoreRepo()
{
	RepositoryMasini repo;
	Masina m{ 102, "d", "a", "b" };

	assert(repo.getAllCars().size() == 0);
	repo.store(m);
	assert(repo.getAllCars().size() == 1);

	int err = 0;
	try {
		repo.store(m);
	}
	catch (RepoException) {
		err = 1;
	}
	assert(repo.getAllCars().size() == 1 && err);
	m.setNumar(890);
	repo.store(m);
	assert(repo.getAllCars().size() == 2 && repo.getAllCars()[1].getNumar() == 890);
}

void testRemoveRepo()
{
	RepositoryMasini repo;
	Masina m{ 102, "d", "a", "b" };

	assert(repo.getAllCars().size() == 0);
	repo.store(m);
	assert(repo.getAllCars().size() == 1);
	repo.remove(m);
	assert(repo.getAllCars().size() == 0);

	m.setNumar(789);
	int err = 0;
	try {
		repo.remove(m);
	}
	catch (RepoException)
	{
		err = 1;
	}

	assert(err == 1);

}

void testModifyRepo()
{
	RepositoryMasini repo;
	Masina m{ 102, "d", "a", "b" };
	Masina newM{ 102, "!d", "!a", "!b" };
	repo.store(m);
	repo.modify(m, newM);

	assert(repo.getAllCars()[0].getProducator() == "!d" && repo.getAllCars()[0].getModel() == "!a");

	int err = 0;
	m.setNumar(123);
	try {
		repo.modify(m, newM);
	}
	catch (RepoException)
	{
		err = 1;
	}
	assert(err == 1);

}

void testRemoveIF()
{

	RepositoryMasini repo;

	assert(repo.getAllCars().size() == 0);

	repo.store({ 101, "Mercedes-Benz", "Clasa G", "SUV" });
	repo.store({102, "Audi", "A7", "Sport"});
	repo.store({103, "Range Rover", "Velar", "SUV"});
	repo.store({104, "BMW", "Seria 3", "Sedan"});
	repo.store({105, "Toyota", "Proace", "Dubita"});
	repo.store({106, "Mercedes-Benz", "EQS", "Limuzina"});
	repo.store({107, "Audi", "TT", "Sport"});
	repo.store({108, "Toyota", "Supra", "Sport"});
	repo.store({109, "Volkswagen", "Polo", "Compact"});
	repo.store({110, "Volkswagen", "Arteon", "Sedan"});

	assert(repo.getAllCars().size() == 10);
	repo.removeIF("SUV");

	assert(repo.getAllCars().size() == 8);
}

void testFileRepo()
{
	std::ofstream ofs;
	ofs.open("masiniTest.txt", std::ofstream::out);
	ofs << "101/Mercedes - Benz/Clasa G/SUV\n";
	ofs << "102/Audi/A7/Sport\n";
	ofs.close();

	FileRepositoryMasini repo("masiniTest.txt");
	assert(repo.getAllCars().size() == 2);
	
	repo.store({ 103, "Range Rover", "Velar", "SUV" });
	repo.store({ 104, "BMW", "Seria 3", "Sedan" });
	repo.store({ 105, "Toyota", "Proace", "Dubita" });
	repo.store({ 106, "Mercedes-Benz", "EQS", "Limuzina" });
	repo.store({ 107, "Audi", "TT", "Sport" });
	repo.store({ 108, "Toyota", "Supra", "Sport" });
	repo.store({ 109, "Volkswagen", "Polo", "Compact" });
	repo.store({ 110, "Volkswagen", "Arteon", "Sedan" });

	assert(repo.getAllCars().size() == 10);
	
	Masina m{ 104, "BMW", "Seria 3", "Sedan" };
	repo.remove(m);
	assert(repo.getAllCars().size() == 9);

	Masina m1{ 107, "Audi", "TT", "Sport" };
	Masina m2{ 107, "newName", "TT", "Sport" };
	repo.modify(m1, m2);
	assert(repo.getAllCars()[5].getProducator() == "newName");


}

void testRepo()
{
	testFindRepo();
	testStoreRepo();
	testRemoveRepo();
	testRemoveIF();
	testModifyRepo();
	testFileRepo();
}