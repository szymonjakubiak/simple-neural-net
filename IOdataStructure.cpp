#include "IOdataStructure.h"

IOdataStructure::IOdataStructure(): recordsNumber(0) {
	//std::cout << "IOdataStructure Constructor" << "\n";
}


IOdataStructure::~IOdataStructure() {
	//std::cout << "IOdataStructure Destructor" << "\n";
	for (int i = 0; i < recordsNumber; i++) {
		delete this->dataMatrix[i];
		delete this->labelMatrix[i];
	}
}


//Wczytuje dane i etykiety z pliku tekstowego
void IOdataStructure::loadData(std::string fileName) {

	std::ifstream iFile(fileName, std::ios::in);
	if (!iFile.is_open()) {
		std::cout << "File " << fileName << " could not be opened" << "\n";
		exit(-1);
	}

	iFile >> recordsNumber;
	iFile >> dataRowsNumber >> dataColumnsNumber;
	iFile >> labelRowsNumber >> labelColumnsNumber;


	std::cout << "Loding data initiated. Total records to load: " << recordsNumber << "\n";

	//Ustawienie rozmiaru danych
	this->dataMatrix.reserve(recordsNumber);
	this->labelMatrix.reserve(recordsNumber);

	//Alokacja macierzy z danymi i etykietami, nadanie wymiarow
	for (int i = 0; i < recordsNumber; i++) {
		this->dataMatrix.emplace_back(new matrixImplement());
		this->labelMatrix.emplace_back(new matrixImplement());
		dataMatrix[i]->setSize(dataRowsNumber, dataColumnsNumber);
		labelMatrix[i]->setSize(labelRowsNumber, labelColumnsNumber);
	}

	double temp;
	//Dla kazdego recordu...
	for (int recNr = 0; recNr < recordsNumber; recNr++) { 

		//wczytaj 'dane' do macierzy
		for (int column = 0; column < dataColumnsNumber; column++) {
			for (int row = 0; row < dataRowsNumber; row++) {
				iFile >> temp;
				this->dataMatrix[recNr]->tweakValue(temp, row, column);
			}
		}

		//wczytaj 'etykiety' do macierzy
		for (int column = 0; column < labelColumnsNumber; column++) {
			for (int row = 0; row < labelRowsNumber; row++) {
				iFile >> temp;
				this->labelMatrix[recNr]->tweakValue(temp, row, column);
			}
		}
	}
	std::cout << "Data loaded successfully" << "\n";

	iFile.close();
}


//Zwraca liczbe przechowywanych obiektow
int IOdataStructure::getNumberOfRecords() {
	return this->recordsNumber;
}


//Zwraca 'dane' i=tego rekordu
Matrix* IOdataStructure::getData(const int& index) {
	return dataMatrix[index];
}


//Zwraca 'etykiete" i-tego rekordu
Matrix* IOdataStructure::getLabel(const int& index) {
	return labelMatrix[index];
}
