#pragma once

#include <vector>
#include <string>
#include "Masina.h"

using std::string;
using std::vector;

class ValidationException {

	vector<string> errorMsg;

public:

	ValidationException(vector<string> errorMessages) :errorMsg{ errorMessages } {};

	string getErrorMessages() {
		string fullMsg = "";
		for (const string e : errorMsg) {
			fullMsg += e + "\n";
		}
		return fullMsg;
	}
};

class ValidatorMasini {

public:

	void valideaza(const Masina& m) {
		vector<string> errors;
		if (m.getProducator().length() < 2)
			errors.push_back("--Producatorul trebuie sa aiba cel putin 2 caractere--");
		if (m.getModel().length() < 2)
			errors.push_back("--Modelul trebuie sa aiba cel putin 2 caractere--");
		if (m.getNumar() < 100)
			errors.push_back("--Numarul de inmatriculare trebuie sa fie de 3 cifre--");

		if (errors.size() != 0)
			throw ValidationException(errors);
	}
};