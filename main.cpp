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

	// Specify here test and train datasets
	IOdataStructure dataStruct;
	dataStruct.loadData("myData.txt");
	IOdataStructure testDataStruct;
	testDataStruct.loadData("myTest.txt");

	// Instantiate layer, activation fun., loss fun. types
	DenseLayer DL = DenseLayer();
	SigmoidActivation SA = SigmoidActivation();
	LeastSquareLossFunction LF = LeastSquareLossFunction();

	DefaultNetworkEngine engine;
	NeuralNet net(&engine);

	// Specify layers
	net.addLayer(&DL, &SA, 784);
	net.addLayer(&DL, &SA, 30);
	net.addLayer(&DL, &SA, 10);
	
	// Specify loss fun. and learn rate
	net.compileNetwork(&LF, 0.1);
	
	// Specify #epochs and batch size
	net.trainNetwork(dataStruct, 31, 30, testDataStruct);

	return 0;
}