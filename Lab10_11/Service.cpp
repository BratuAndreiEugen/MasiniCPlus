#include "Service.h"
#include <assert.h>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>

void ServiceMasini::addCar(int nrInmatriculare, std::string producator, std::string model, std::string tip)
{
	Masina m{ nrInmatriculare, producator, model, tip };
	validator.valideaza(m); // aici poate iesi ValidationError
	repo.store(m); // de aici RepositoryError
	UndoStore* newUndo = new UndoStore{repo, m};
	undo.push_back(newUndo);
}

void ServiceMasini::removeCar(int nrInmatriculare)
{
	Masina m{ nrInmatriculare, "valid", "valid", "valid" };
	validator.valideaza(m); // aici poate iesi ValidationError
	UndoRemove* newUndo = new UndoRemove{ repo, repo.find(nrInmatriculare) };
	repo.remove(m); // de aici RepositoryError
	undo.push_back(newUndo);
}

// Functionalitate Lab 8
void ServiceMasini::removeIF(std::string tip)
{
	repo.removeIF(tip);
	
}

void ServiceMasini::modifyCar(int nrInmatriculare, int newNr, string newProducator, string newModel, string newTip)
{
	Masina m{ nrInmatriculare, "valid", "valid" , "valid" };
	Masina newM{ newNr, newProducator, newModel, newTip };
	validator.valideaza(m);
	validator.valideaza(newM);
	UndoModify* newUndo = new UndoModify{ repo, repo.find(nrInmatriculare) };
	repo.modify(m, newM);
	undo.push_back(newUndo);
}

const Masina& ServiceMasini::findCar(int nrInmatriculare)
{
	Masina m{ nrInmatriculare, "valid", "valid" , "valid" };
	validator.valideaza(m);
	return repo.find(nrInmatriculare);
}

void ServiceMasini::filter(string criteriu, string relevantInfo, vector<Masina>& filteredList)
{
	

	if (relevantInfo == "")
		filteredList = getAllCars();

	
	if (criteriu == "producator")
	{
		/*
		IteratorVector<Masina> i(getAllCars());
		for (i = 0; i < getAllCars().size(); ++i)
		{
			if ((*i).getProducator() == relevantInfo)
				filteredList.add(*i);
		}
		*/

		std::copy_if(getAllCars().begin(), getAllCars().end(), back_inserter(filteredList),
			[relevantInfo](const Masina& m) {
				return m.getProducator() == relevantInfo;
			});


	}
	if (criteriu == "tip")
	{
		/*
		IteratorVector<Masina> i(getAllCars());
		for (i = 0; i < getAllCars().size(); ++i)
		{
			if ((*i).getTip() == relevantInfo)
				filteredList.add(*i);
		}
		*/

		std::copy_if(getAllCars().begin(), getAllCars().end(), back_inserter(filteredList),
			[relevantInfo](const Masina& m) {
				return m.getTip() == relevantInfo;
			});
	}
		
}

bool compareNumar(const Masina& m, const Masina& n)
{
	if (m.getNumar() < n.getNumar())
		return true;
	else
		return false;
}

bool compareTip(const Masina& m, const Masina& n)
{
	if (m.getTip() < n.getTip())
		return true;
	else
		return false;
}

bool compareProducatorModel(const Masina& m, const Masina& n)
{
	if (m.getProducator() < n.getProducator())
	{
		return true;
	}
	else if (m.getModel() < n.getModel() && m.getProducator() == n.getProducator())
	{
		return true;
	}
	return false;
}

void ServiceMasini::sort(string criteriu, vector<Masina>& sortedList)
{
	sortedList = getAllCars();

	if (criteriu == "numar inmatriculare")
	{
		/*
		IteratorVector<Masina> i(sortedList);
		IteratorVector<Masina> j(sortedList);

		for (i = 0; i < sortedList.size() - 1; ++i)
		{
			for (j = i; j < sortedList.size(); ++j)
			{
				if ((*i).getNumar() < (*j).getNumar())
				{
					Masina aux;
					aux = *i;
					*i = *j;
					*j = aux;
				}
			}
		}*/
		std::sort(sortedList.begin(), sortedList.end(), compareNumar);

	}
	if (criteriu == "tip")
	{
		/*
		IteratorVector<Masina> i(sortedList);
		IteratorVector<Masina> j(sortedList);

		for (i = 0; i < sortedList.size() - 1; ++i)
		{
			for (j = i; j < sortedList.size(); ++j)
			{
				if ((*i).getTip() > (*j).getTip())
				{
					Masina aux;
					aux = *i;
					*i = *j;
					*j = aux;
				}
			}
		}*/
		std::sort(sortedList.begin(), sortedList.end(), compareTip);

	}
	if (criteriu == "producator+model")
	{
		/*
		IteratorVector<Masina> i(sortedList);
		IteratorVector<Masina> j(sortedList);

		for (i = 0; i < sortedList.size() - 1; ++i)
		{
			for (j = i; j < sortedList.size(); ++j)
			{
				if ((*i).getProducator() > (*j).getProducator())
				{
					Masina aux;
					aux = *i;
					*i = *j;
					*j = aux;
				}
				else if ((*i).getModel() > (*j).getModel() && (*i).getProducator() == (*j).getProducator())
				{
					Masina aux;
					aux = *i;
					*i = *j;
					*j = aux;
				}
			}
		}*/

		std::sort(sortedList.begin(), sortedList.end(), compareProducatorModel);
	}
}

void ServiceMasini::undoService()
{
	if (this->undo.size() != 0)
	{
		UndoClass* u;
		u = undo.back();
		u->doUndo();
		delete u;
		undo.pop_back();
	}
	else
		throw ServiceException("--Nu se mai poate face undo--\n\n");
}

void ServiceMasini::clearUndo()
{
	for (UndoClass* u : undo)
	{
		delete u;
	}
	undo.clear();
}

void ServiceMasini::addToWashingList(int numarInmatriculare)
{
	try {
		const auto& car = repo.find(numarInmatriculare);
		washingList.store(car);
	}
	catch (RepoException& ex)
	{
		throw ex;
	}

}

void ServiceMasini::emptyWashingList()
{
	washingList.emptyList();
}

const vector<Masina>& ServiceMasini::getAllWashingListed()
{
	return washingList.getAllCars();
}

void ServiceMasini::saveWashesToFile(string filename)
{
	try {
		washingList.exportList(filename);
	}
	catch (RepoException& ex)
	{
		throw ex;
	}
}

void ServiceMasini::populateWashingList(int max)
{
	emptyWashingList();
	washingList.populateList(getAllCars(), max);
}


// Lab 10
vector<string> ServiceMasini::getAllTypes()
{
	vector<string> types;
	for(auto& car : repo.getAllCars())
	{
		bool ok = 0;
		for (string& type : types)
		{
			if (car.getTip() == type)
			{
				ok = 1;
			}
		}
		if (ok == 0)
		{
			types.push_back(car.getTip());
		}
	}

	return types;
}

string ServiceMasini::countByType(string type)
{
	int nr = 0;
	for (auto& car : repo.getAllCars())
	{
		if (car.getTip() == type)
			nr++;
	}
	string strNr = std::to_string(nr);
	return strNr;

}


void expSort(myVector<Masina>& sortedList, bool (*compareFunction)(const Masina&, const Masina&))
{
	IteratorVector<Masina> i(sortedList);
	IteratorVector<Masina> j(sortedList);

	for (i = 0; i < sortedList.size() - 1; ++i)
	{
		for (j = i; j < sortedList.size(); ++j)
		{
			if ((*compareFunction)(*i, *j)) {
				Masina aux;
				aux = *i;
				*i = *j;
				*j = aux;
			}
		}

	}
}


// TESTE

void testAddService()
{
	ValidatorMasini val;
	RepositoryMasini repo;
	WashingList list;
	ServiceMasini service{ repo, val, list };
	assert(repo.getAllCars().size() == 0);

	service.addCar(123, "aa", "bb", "cc");
	assert(repo.getAllCars().size() == 1);

	int err = 0;
	try
	{
		service.addCar(2, "ds", "dsd", "dsdsd");
	}
	catch (ValidationException)
	{
		err = 1;
	}
	assert(err == 1);

	err = 0;
	try
	{
		service.addCar(123, "ds", "dsd", "dsdsd");
	}
	catch (RepoException)
	{
		err = 1;
	}
	assert(err == 1);
	service.clearUndo();
}

void testRemoveService()
{
	ValidatorMasini val;
	RepositoryMasini repo;
	WashingList list;
	ServiceMasini service{ repo, val, list };
	assert(repo.getAllCars().size() == 0);

	service.addCar(123, "aa", "bb", "cc");
	assert(repo.getAllCars().size() == 1);

	service.addCar(901, "Bentley", "IDK", "Limuzina");
	assert(repo.getAllCars().size() == 2);

	service.removeCar(901);
	assert(repo.getAllCars().size() == 1);


	int err = 0;
	try
	{
		service.removeCar(182);
	}
	catch (RepoException) {
		err = 1;
	}

	assert(err == 1);

	err = 0;
	try
	{
		service.removeCar(1);
	}
	catch (ValidationException) {
		err = 1;
	}

	assert(err == 1);
	
	service.clearUndo();
}

void testRemoveIFService()
{
	ValidatorMasini val;

	RepositoryMasini repo;

	WashingList list;
	ServiceMasini service{ repo, val, list };

	assert(repo.getAllCars().size() == 0);

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

	service.removeIF("Sedan");
	assert(service.getAllCars().size() == 8);
	service.clearUndo();
}

void testModifyService()
{
	ValidatorMasini val;
	RepositoryMasini repo;
	WashingList list;
	ServiceMasini service{ repo, val, list };
	assert(repo.getAllCars().size() == 0);

	service.addCar(123, "aa", "bb", "cc");
	assert(repo.getAllCars().size() == 1);

	service.addCar(901, "Bentley", "IDK", "Limuzina");
	assert(repo.getAllCars().size() == 2);

	service.modifyCar(901, 899, "Mercedes", "dsds", "Limuzina");
	assert(repo.getAllCars()[1].getNumar() == 899 && repo.getAllCars()[1].getProducator() == "Mercedes");

	service.clearUndo();
}

void testFindService()
{
	ValidatorMasini val;
	
	RepositoryMasini repo;
	
	WashingList list;
	ServiceMasini service{ repo, val, list };
	
	assert(repo.getAllCars().size() == 0);
	
	service.addCar(123, "aa", "bb", "cc");
	assert(repo.getAllCars().size() == 1);
	
	service.addCar(901, "Bentley", "IDK", "Limuzina");
	assert(repo.getAllCars().size() == 2);
	

	Masina m = service.findCar(901);
	assert(m.getModel() == "IDK" && m.getProducator() == "Bentley");

	service.clearUndo();
}


void testFilterService()
{
	ValidatorMasini val;

	RepositoryMasini repo;

	WashingList list;
	ServiceMasini service{ repo, val, list };

	assert(repo.getAllCars().size() == 0);

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

	vector<Masina> v1;
	service.filter("producator", "Volkswagen", v1);
	assert(v1.size() == 2);
	assert(v1[0].getModel() == "Polo");

	vector<Masina> v2;
	service.filter("tip", "SUV", v2);
	assert(v2.size() == 2);
	assert(v2[0].getModel() == "Clasa G");

	vector<Masina> v3;
	service.filter("tip", "", v3);
	assert(v3.size() == 10);

	service.clearUndo();
}

void testCompare()
{
	myVector<Masina> v;
	Masina m1(106, "Mercedes-Benz", "EQS", "Limuzina");
	Masina m2(102, "Audi", "A7", "Sport");
	Masina m3(103, "Range Rover", "Velar", "SUV");
	Masina m4(101, "Mercedes-Benz", "Clasa G", "SUV");
	v.add(m1);
	v.add(m2);
	v.add(m3);
	v.add(m4);

	expSort(v, compareProducatorModel);
	assert(v.get(0).getProducator() == "Range Rover");

	expSort(v, compareNumar);
	assert(v.get(0) == m1 && v.get(1) == m3);

	expSort(v, compareTip);
	assert(v.get(0) == m2 && v.get(3) == m1);
	
}

void testSortService()
{
	ValidatorMasini val;

	RepositoryMasini repo;

	WashingList list;
	ServiceMasini service{ repo, val, list };

	assert(repo.getAllCars().size() == 0);

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

	vector<Masina> v1;
	service.sort("numar inmatriculare", v1);
	assert(v1.size() == 10);
	assert(v1[0].getNumar() == 101);
	assert(v1[3].getNumar() == 104);

	vector<Masina> v2;
	service.sort("tip", v2);
	assert(v2.size() == 10);
	assert(v2[0].getModel() == "Polo");

	vector<Masina> v3;
	service.sort("producator+model", v3);
	assert(v3.size() == 10);
	assert(v3[0].getProducator() == "Audi");
	assert(v3[1].getModel() == "TT");

	service.clearUndo();
}

void testWashingListService()
{
	ValidatorMasini val;

	RepositoryMasini repo;

	WashingList list;
	ServiceMasini service{ repo, val, list };

	assert(repo.getAllCars().size() == 0);

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

	// Adaugare
	service.addToWashingList(101);
	service.addToWashingList(102);
	service.addToWashingList(103);
	service.addToWashingList(104);
	service.addToWashingList(105);

	assert(service.getAllWashingListed().size() == 5 && service.getAllWashingListed()[0].getModel() == "Clasa G");

	// Golire
	service.emptyWashingList();
	assert(service.getAllWashingListed().size() == 0);

	// Generare
	service.populateWashingList(5);
	assert(service.getAllWashingListed().size() == 5);

	service.populateWashingList(11);
	assert(service.getAllWashingListed().size() == 10);

	// Export
	service.saveWashesToFile("test.csv");

	service.clearUndo();
}


void testService()
{
	testAddService();
	testRemoveService();
	testModifyService();
	testFindService();
	testFilterService();

	testCompare();
	testSortService();

	testWashingListService();

	testRemoveIFService();

	
}