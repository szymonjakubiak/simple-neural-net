#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>

#include "matrixImplement.h"
#include "SigmoidActivation.h"
#include "LeastSquareLossFunction.h"
#include "DefaultNetworkEngine.h"
#include "NeuralNet.h"
#include "DenseLayer.h"
#include "IOdataStructure.h"


////////////////////////
// MAIN
////////////////////////

bool matrixImplement::randInit = false;


int main(){

	/*
	std::shuffle(outputs.begin(), outputs.end(), std::default_random_engine(unsigned (time(NULL))));
	*/

	IOdataStructure dataStruct;
	dataStruct.loadData("myData.txt");

	IOdataStructure testDataStruct;
	testDataStruct.loadData("myTest.txt");


	DenseLayer* DL = new DenseLayer();
	SigmoidActivation* SA = new SigmoidActivation();
	LeastSquareLossFunction* LF = new LeastSquareLossFunction();

	DefaultNetworkEngine engine;
	NeuralNet net(&engine);

	net.addLayer(DL, SA, 784);
	net.addLayer(DL, SA, 30);
	net.addLayer(DL, SA, 10);
	net.compileNetwork(LF, 0.1);
	net.trainNetwork(dataStruct, 31, 30, testDataStruct);

	delete DL;
	delete SA;
	delete LF;

	return 0;
}