#include "Masina.h"
#include <assert.h>

int Masina::getNumar() const
{
	return this->nrInmatriculare;
}

std::string Masina::getProducator() const{
	return this->producator;
}

std::string Masina::getModel() const{
	return this->model;
}

std::string Masina::getTip() const{
	return this->tip;
}

std::string Masina::getData() const {
	std::string s;
	s.append(std::to_string(this->nrInmatriculare));
	s.append(" ");
	s.append(this->producator);
	s.append(" ");
	s.append(this->model);
	s.append(" ");
	s.append(this->tip);
	return s;
}

void Masina::setNumar(int value){
	this->nrInmatriculare = value;
}

void Masina::setProducator(std::string value){
	this->producator = value;
}

void Masina::setModel(std::string value){
	this->model = value;
}

void Masina::setTip(std::string value){
	this->tip = value;
}


void testMasina()
{
	Masina car{ 190, "Mercedes-Benz", "C-Class", "Sedan" };

	assert(car.getModel() == "C-Class");
	assert(car.getNumar() == 190);
	assert(car.getProducator() == "Mercedes-Benz");
	assert(car.getTip() == "Sedan");

	car.setModel("G-Class");
	car.setNumar(501);
	car.setProducator("Mercedes");
	car.setTip("4x4");
	
	assert(car.getModel() == "G-Class");
	assert(car.getNumar() == 501);
	assert(car.getProducator() == "Mercedes");
	assert(car.getTip() == "4x4");
	
	Masina car1 = car;
	assert(car1.getModel() == "G-Class");
	assert(car1 == car);
}