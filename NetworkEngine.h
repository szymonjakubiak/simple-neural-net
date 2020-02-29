#pragma once
#include <iostream>
#include <vector>

#include "Matrix.h"
#include "Layer.h"
#include "Activation.h"
#include "LossFunction.h"

class NetworkEngine
{
public:
	NetworkEngine();
	virtual ~NetworkEngine();

	//Inicjuje alokacje niezbednych macierzy
	virtual void setSize(std::vector<int>& sizes, const int& size) = 0;
	//Inicjuje dodatkowe parametry sieci
	virtual void setUtilities(std::vector<Layer*>& vLayers, std::vector<Activation*>& vActivations, LossFunction* _lossFunction, double _learnRate) = 0;
	//Oblicza stan sieci dla danej macierzy wejscia
	virtual void feedForward(Matrix* inputLayerActivation) = 0;
	//Aktualizuje parametry sieci w oparciu o prawidlowa etykiete dla danego stanu sieci
	virtual void improveNet(Matrix* outputLayerActivation) = 0;
	//Sprawdza czy predykcja sieci jest prawidlowa
	virtual bool checkGuess(Matrix* outputLable) = 0;
	//Zmiania siec na podstawie gradientu wyliczonego z batcha
	virtual void applyImprovements() = 0;
};

