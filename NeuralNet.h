#pragma once

#include <iostream>
#include <vector>

#include "Matrix.h"
#include "Activation.h"
#include "LossFunction.h"
#include "NetworkEngine.h"
#include "DenseLayer.h"
#include "IOdataStructure.h"

class NeuralNet
{
public:
	NeuralNet() = delete;
	~NeuralNet();
	NeuralNet(NetworkEngine* engine); //Uzywamy tylko tego konstruktora
	//Dodaj kolejna warstwe do sieci
	void addLayer(Layer* layer, Activation* activation, const int& size);
	//Na podstawie przekazanych warstw przygotowuje silnik do obliczen
	void compileNetwork(LossFunction* _lossFunction, double _learnRate);
	//Trenuje siec zgodnie z przekazanymi parametrami
	void trainNetwork(IOdataStructure& input, const int& epochs, const int& batchSize, IOdataStructure& valid);

private:
	std::vector<Layer*> vLayers;			//Typy warstw
	std::vector<Activation*> vActivations;	//Funkcje aktywacji
	LossFunction* lossFunction;				//Funkcja straty
	NetworkEngine* networkEngine;			//Silnik do wykonywania obliczen

	int layersNumber;				//Liczba warstw
	std::vector<int> vLayersSizes;	//Wymiary kolejnych warstw
	double learnRate;				//Parametr sieci
};

