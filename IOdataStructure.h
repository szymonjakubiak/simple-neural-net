#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "matrixImplement.h"

class IOdataStructure
{
public:
	IOdataStructure();
	~IOdataStructure();
	//Wczytuje dane i etykiety z pliku tekstowego
	void loadData(std::string fileName);
	//void saveData(std::string fileName);
	//Zwraca liczbe przechowywanych rekordow
	int getNumberOfRecords();
	//Zwraca 'dane' i=tego rekordu
	Matrix* getData(const int& index);
	//Zwraca 'etykiete" i-tego rekordu
	Matrix* getLabel(const int& index);
private:
	std::vector<Matrix*> dataMatrix;
	std::vector<Matrix*> labelMatrix;
	int dataRowsNumber, dataColumnsNumber;
	int labelRowsNumber, labelColumnsNumber;
	int recordsNumber;
};

