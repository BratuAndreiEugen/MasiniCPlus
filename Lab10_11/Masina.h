#pragma once
#include <string>

class Masina
{
private:
	int nrInmatriculare;
	std::string producator;
	std::string model;
	std::string tip;

public:

	Masina() = default;

	// Constructor
	Masina(int nrInmatriculare, std::string producator, std::string model, std::string tip) :nrInmatriculare(nrInmatriculare), producator(producator), model(model), tip(tip) {
	};

	// Constructor de copiere
	Masina(const Masina& other) :nrInmatriculare{ other.nrInmatriculare }, producator{ other.producator }, model{ other.model }, tip{ other.tip }{};

	int getNumar() const;

	std::string getProducator() const;

	std::string getModel() const;

	std::string getTip() const;

	std::string getData() const;

	void setNumar(int value);

	void setProducator(std::string value);

	void setModel(std::string value);

	void setTip(std::string value);

	bool operator==(const Masina& other) noexcept { return nrInmatriculare == other.nrInmatriculare && producator == other.producator && model == other.model && tip == other.tip; };

};

void testMasina();
