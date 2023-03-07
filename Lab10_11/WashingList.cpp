#include "WashingList.h"
#include <vector>
#include <string>
#include "Repository.h"
#include <fstream>
#include <assert.h>

using std::shuffle;
using std::ofstream;


void WashingList::emptyList()
{
	this->cars.clear();
	notify();
}


void WashingList::store(const Masina& m)
{
	if (exists(m)) {
		throw RepoException("Masina " + m.getProducator() + " " + m.getModel() + " cu numarul de inmatriculare dat este deja in depozit\n");
	}
	this->cars.push_back(m);
	notify();
}


void WashingList::populateList(vector<Masina> repoCars, int numberOfCars)
{
	shuffle(repoCars.begin(), repoCars.end(), std::default_random_engine(std::random_device{}()));
	while (this->cars.size() < numberOfCars && repoCars.size() > 0)
	{
		this->cars.push_back(repoCars.back());
		repoCars.pop_back();
	}
	notify();
}

void WashingList::exportList(string filename)
{
	string suffix = "csv";
	if (filename.compare(filename.length() - suffix.length(), suffix.length(), suffix) != 0)
	{
		throw RepoException("--Fisierul dat nu este de tip CSV--");
	}

	ofstream out(filename);
	string columns[] = { "Numar de inmatriculare", "Producator", "Model", "Tip" };
	for (auto& column : columns)
	{
		out << column << ",";
	}
	out << "\n";

	for (auto& car : this->cars)
	{
		out << car.getNumar() << "," << car.getProducator() << "," << car.getModel() << "," << car.getTip() << "\n";
	}

	out.close();
}


void testWashingList()
{
	WashingList l;
	Masina m1(106, "Mercedes-Benz", "EQS", "Limuzina");
	Masina m2(102, "Audi", "A7", "Sport");
	Masina m3(103, "Range Rover", "Velar", "SUV");
	Masina m4(101, "Mercedes-Benz", "Clasa G", "SUV");
	assert(l.getAllCars().size() == 0);
	l.store(m1);
	l.store(m2);
	l.store(m3);
	l.store(m4);
	assert(l.getAllCars().size() == 4);

	WashingList l1;
	l1.populateList(l.getAllCars(), 3);

	assert(l1.getAllCars().size() == 3);

	l.exportList("test.csv");


	l.emptyList();
	assert(l.getAllCars().size() == 0);
}