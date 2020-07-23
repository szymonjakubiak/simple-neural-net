#include "NeuralNet.h"

NeuralNet::~NeuralNet()
{
	//std::cout << "NeuralNet Destructor" << "\n";
}


NeuralNet::NeuralNet(NetworkEngine* engine): layersNumber(0)
{
	//std::cout << "NeuralNet Constructor" << "\n";
	this->networkEngine = engine;
}


//Dodaj kolejna warstwe do sieci
void NeuralNet::addLayer(Layer* layer, Activation* activation, const int& size) {
	vLayers.emplace_back(layer);
	vActivations.emplace_back(activation);
	layersNumber++;
	vLayersSizes.emplace_back(size);
}


//Na podstawie przekazanych warstw przygotowuje silnik do obliczen
void NeuralNet::compileNetwork(LossFunction* _lossFunction, double _learnRate) {
	this->lossFunction = _lossFunction;
	this->learnRate = _learnRate;

	networkEngine->setSize(vLayersSizes, layersNumber);
	networkEngine->setUtilities(vLayers, vActivations, lossFunction, learnRate);
}


//Trenuje siec zgodnie z przekazanymi parametrami
void NeuralNet::trainNetwork(IOdataStructure& input, const int& epochs, const int& batchSize, IOdataStructure& valid) {
	
	//Obliczanie liczby i paczek danych
	int numberOfTrainRecords = input.getNumberOfRecords();
	int numberOfBatches = numberOfTrainRecords / batchSize;

	std::cout << "Training initiated" << "\n";

	

	//Dla kazdej 'epoki'
	int successCounter; // Liczba prawidlowo odgadnietych etykiet w zbiorze testowym
	int testDataSize = valid.getNumberOfRecords();
	for (int currenEpoch = 0; currenEpoch < epochs; currenEpoch++) {
		//Dla kazdej paczki danych
		std::cout << "Training in progress... Current epoch: " << currenEpoch+1 << "/" << epochs << "\n";
		for (int currentBatch = 0; currentBatch < numberOfBatches; currentBatch++) {
			//Dla kazdego elementu paczki
			for (int currentPieceInBatch = 0; currentPieceInBatch < batchSize; currentPieceInBatch++) {
				networkEngine->feedForward(input.getData(currentBatch*batchSize + currentPieceInBatch));
				networkEngine->improveNet(input.getLabel(currentBatch*batchSize + currentPieceInBatch));
			}
			networkEngine->applyImprovements();
			
		}

		//W kazdej epoce sprawdzamy postepy w nauce na podstawie danych testowych (jezeli zostaly wprowadzone)
		successCounter = 0;
		if (testDataSize) {
			for (int currentTestCase = 0; currentTestCase < testDataSize; currentTestCase++) {
				networkEngine->feedForward(valid.getData(currentTestCase));
				if (networkEngine->checkGuess(valid.getLabel(currentTestCase))) {
					successCounter++;
				}
			}
			std::cout << "Current network accuracy: " << successCounter << "/" << testDataSize << "\n";
		}
	}
	std::cout << "Training completed" << "\n";
	
}
