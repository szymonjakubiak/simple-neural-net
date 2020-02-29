#pragma once

#include <iostream>

#include "NetworkEngine.h"
#include "matrixImplement.h"

class DefaultNetworkEngine :
	public NetworkEngine
{
public:
	DefaultNetworkEngine();
	~DefaultNetworkEngine();

	//Inicjuje alokacje niezbednych macierzy
	void setSize(std::vector<int>& sizes, const int& size) override;
	//Inicjuje dodatkowe parametry sieci
	void setUtilities(std::vector<Layer*>& vLayers, std::vector<Activation*>& vActivations, LossFunction* _lossFunction, double _learnRate) override;
	//Oblicza stan sieci dla danej macierzy wejscia
	void feedForward(Matrix* inputLayerActivation) override;
	//Aktualizuje parametry sieci w oparciu o prawidlowa etykiete dla danego stanu sieci
	void improveNet(Matrix* outputLayerActivation) override;
	//Sprawdza czy predykcja sieci jest prawidlowa
	bool checkGuess(Matrix* outputLable) override;
	//Zmiania siec na podstawie gradientu wyliczonego z batcha
	void applyImprovements() override;

private:
	std::vector<Matrix*> vWeightsMatrices;	//Macierze wag
	std::vector<Matrix*> vBiasesMatrices;	//Macierze biasow
	std::vector<Matrix*> vNeuronActivations;//Macierze poziomu aktywacji neuronow
	Matrix* inputLayerActivation;			//Macierz poziomu aktywacji neuronow na wejsciu
	Matrix* inputLayerActivationTranspose;
	std::vector<Matrix*> vNeuronIncome;		//Wejscie do neuronu
	std::vector<Matrix*> vGradientWeights, vDeltaGradientWeights;	//Macierze z gradientami wag
	std::vector<Matrix*> vGradientBiases, vDeltaGradientBiases;		//Macierze z gradientami biasow
	std::vector<Matrix*> vActivationTranspose;		//Transponowane macierze aktywacji (indexy: od 0 do nLayers-2)
	std::vector<Matrix*> vWeightsMatricesTranspose;	//Transponowane macierze wag (indexy: od 0 do nLayers-2)
	std::vector<Matrix*> vNeuronActivationsDerivative;	//Macierze pochodnych funkcji aktywacji

	std::vector<Layer*>* vLayersPointer;
	std::vector<Activation*>* vActivationsPointer;
	LossFunction* lossFunction;
	double learnRate;
	int layersNumber;
	

	static double constForGradient(const double& val);
};

