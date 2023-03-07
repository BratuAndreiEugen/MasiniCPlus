#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <random>  
#include <chrono>
#include "Repository.h" // Folosesc RepoException si mostenire
#include "Observer.h"
using std::vector;
using std::string;



class WashingList : public RepositoryMasini, public Observable
{

public:
	/// <summary>
	/// Elibereaza lista de masini
	/// </summary>
	void emptyList();


	/// Pentru adaugarea une masini se foloseste metoda mostenita store(); -> In lab 13 am suprascris-o pentru a efectua notify()
	void store(const Masina& m) override;

	/// <summary>
	/// Se populeaza random cu masini din service
	/// </summary>
	void populateList(vector<Masina> repoCars, int numberOfCars);

	void exportList(string filename);
};

void testWashingList();