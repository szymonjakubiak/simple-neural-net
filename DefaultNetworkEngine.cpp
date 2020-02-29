#include "DefaultNetworkEngine.h"


DefaultNetworkEngine::DefaultNetworkEngine()
{
	//std::cout << "DefaultNetworkEngine Constructor" << "\n";
}


DefaultNetworkEngine::~DefaultNetworkEngine()
{
	//std::cout << "DefaultNetworkEngine Destructor" << "\n";
	delete inputLayerActivationTranspose;
	for (int i = 0; i < layersNumber - 2; i++) {
		delete vWeightsMatrices[i];
		delete vGradientWeights[i];
		delete vDeltaGradientWeights[i];
		delete vBiasesMatrices[i];
		delete vGradientBiases[i];
		delete vDeltaGradientBiases[i];
		delete vActivationTranspose[i];
		delete vWeightsMatricesTranspose[i];
		delete vNeuronIncome[i];
		delete vNeuronActivations[i];
		delete vNeuronActivationsDerivative[i];
	}
}


//Inicjuje alokacje niezbednych macierzy
void DefaultNetworkEngine::setSize(std::vector<int>& sizes, const int& size) {
	this->layersNumber = size;

	//Rezerwacja rozmiaru wektorow
	int reservation = size - 1;
	vWeightsMatrices.reserve(reservation);
	vGradientWeights.reserve(reservation);
	vNeuronIncome.reserve(reservation);
	vDeltaGradientWeights.reserve(reservation);
	vBiasesMatrices.reserve(reservation);
	vGradientBiases.reserve(reservation);
	vDeltaGradientBiases.reserve(reservation);
	vActivationTranspose.reserve(reservation);
	vWeightsMatricesTranspose.reserve(reservation);
	vNeuronActivations.reserve(reservation);
	vNeuronActivationsDerivative.reserve(reservation);


	//Wrzucanie wskaznikow i inicjacja macierzy
	inputLayerActivationTranspose = new matrixImplement();
	for (int i = 0; i < reservation; i++) {
		vWeightsMatrices.emplace_back(new matrixImplement());
		vGradientWeights.emplace_back(new matrixImplement());
		vNeuronIncome.emplace_back(new matrixImplement());
		vDeltaGradientWeights.emplace_back(new matrixImplement());
		vBiasesMatrices.emplace_back(new matrixImplement());
		vGradientBiases.emplace_back(new matrixImplement());
		vDeltaGradientBiases.emplace_back(new matrixImplement());
		vActivationTranspose.emplace_back(new matrixImplement());
		vWeightsMatricesTranspose.emplace_back(new matrixImplement());
		vNeuronActivations.emplace_back(new matrixImplement());
		vNeuronActivationsDerivative.emplace_back(new matrixImplement());
	}

	
	//Przypisanie macierzom odpowiednich wymiarow
	int preSize, postSize;
	inputLayerActivationTranspose->setSize(1, sizes[0]);
	for (int i = 0; i < reservation; i++) {
		preSize = sizes[i];
		postSize = sizes[i + 1];

		vWeightsMatrices[i]->setSize(postSize, preSize);
		vGradientWeights[i]->setSize(postSize, preSize);
		vDeltaGradientWeights[i]->setSize(postSize, preSize);

		vNeuronIncome[i]->setSize(postSize, 1);
		vBiasesMatrices[i]->setSize(postSize, 1);
		vGradientBiases[i]->setSize(postSize, 1);
		vDeltaGradientBiases[i]->setSize(postSize, 1);
		vNeuronActivations[i]->setSize(postSize, 1);
		vNeuronActivationsDerivative[i]->setSize(postSize, 1);

		vActivationTranspose[i]->setSize(1, postSize);
		vWeightsMatricesTranspose[i]->setSize(preSize, postSize);
	}

	//Wypelnienie losowymi wartosciami macierzy wag i biasow
	for (int i = 0; i < reservation; i++) {
		vWeightsMatrices[i]->setRandom();
		vBiasesMatrices[i]->setRandom();
	}
	std::cout << "Engine allocated memory succsessfully" << "\n";
}


//Inicjuje dodatkowe parametry sieci
void DefaultNetworkEngine::setUtilities(std::vector<Layer*>& vLayers, std::vector<Activation*>& vActivations, LossFunction* _lossFunction, double _learnRate) {
	this->vLayersPointer = &vLayers;
	this->vActivationsPointer = &vActivations;
	this->lossFunction = _lossFunction;
	this->learnRate = _learnRate;

	std::cout << "Engine assigned utilities successfully" << "\n";
}

void DefaultNetworkEngine::feedForward(Matrix* _inputLayerActivation) {
	this->inputLayerActivation = _inputLayerActivation;
	vWeightsMatrices[0]->dotProduct(inputLayerActivation, vNeuronIncome[0]); // = W[0] * aInput
	vNeuronIncome[0]->addMatrix(vBiasesMatrices[0], vNeuronIncome[0]);// z[0] = (W[0] * aInput]) + b[0]	////////////////
	vActivationsPointer->operator[](0)->evaluateActivation(vNeuronIncome[0], vNeuronActivations[0]);// a[0] = fAktywacji(z[0])
	for (int currentLayer = 1; currentLayer < layersNumber - 1; currentLayer++) {
		// = W[i] * a[i-1]
		vWeightsMatrices[currentLayer]->dotProduct(vNeuronActivations[currentLayer - 1], vNeuronIncome[currentLayer]);

		// z[i] = (W[i] * a[i-1]) + b[i]	////////////////
		vNeuronIncome[currentLayer]->addMatrix(vBiasesMatrices[currentLayer], vNeuronIncome[currentLayer]);

		// a[i] = fAktywacji(z[i])
		vActivationsPointer->operator[](currentLayer)->evaluateActivation(vNeuronIncome[currentLayer], vNeuronActivations[currentLayer]);
	}
}

void DefaultNetworkEngine::improveNet(Matrix* outputLayerActivation) {
	
	////////////Obliczamy gradienty dla ostatniej warstwy//////////////////
	int lastLayerIndex = layersNumber - 2;
	//lossDerivative = (x-y)
	lossFunction->evaluateLossDerivative(vNeuronActivations[lastLayerIndex], outputLayerActivation, vDeltaGradientBiases[lastLayerIndex]);
	//Activation'[-1] = fAktywacji'(z[-1])
	vActivationsPointer->operator[](lastLayerIndex)->evaluateActivationDerivative(vNeuronIncome[lastLayerIndex], vNeuronActivationsDerivative[lastLayerIndex]);
	//DGradBiases[-1] = lossDerivative .* Activaion[-1]
	vDeltaGradientBiases[lastLayerIndex]->multiplyElementWise(vNeuronActivationsDerivative[lastLayerIndex], vDeltaGradientBiases[lastLayerIndex]);
	//(Activation[-2])Transpozycja
	vNeuronActivations[lastLayerIndex - 1]->transpose(vActivationTranspose[lastLayerIndex - 1]);
	//DGradWeights[-1] = DGradBiases[-1] * (Activation[-2])Transpose
	vDeltaGradientBiases[lastLayerIndex]->dotProduct(vActivationTranspose[lastLayerIndex - 1], vDeltaGradientWeights[lastLayerIndex]);

	////////////Obliczamy gradienty dla warstw ukrytych - idziemy od konca (output) do poczatku (input)///////////////////
	for (int k = layersNumber - 3; k > 0; k--) {
		//Transpozycja Weights[k]
		vWeightsMatrices[k]->transpose(vWeightsMatricesTranspose[k]);
		//Activation'[k] = fAktywacji'(z[k])
		vActivationsPointer->operator[](k)->evaluateActivationDerivative(vNeuronIncome[k], vNeuronActivationsDerivative[k]);
		//DOT[k] = (DGradWeights[k+1])Transpose * DGradBiases[k+1]
		vWeightsMatricesTranspose[k + 1]->dotProduct(vDeltaGradientBiases[k + 1], vDeltaGradientBiases[k]);
		//DGradBiases[k] = DOT[k] .* Activation'[k]
		vDeltaGradientBiases[k]->multiplyElementWise(vNeuronActivationsDerivative[k], vDeltaGradientBiases[k]);
		//(Activation[k-1])Transpozycja
		vNeuronActivations[k-1]->transpose(vActivationTranspose[k-1]);
		//DGradWeights[k] = DGradBiases[k] * (Activation[k-1])Transpose
		vDeltaGradientBiases[k]->dotProduct(vActivationTranspose[k-1], vDeltaGradientWeights[k]);
	}

	
	///////////////Obliczamy gradienty za inputem////////////////////////////
	//Transpozycja Weights[1]
	vWeightsMatrices[1]->transpose(vWeightsMatricesTranspose[1]);
	//Activation'[0] = fAktywacji'(z[0])
	vActivationsPointer->operator[](0)->evaluateActivationDerivative(vNeuronIncome[0], vNeuronActivationsDerivative[0]);
	//DOT[0] = (DWeights[1])Transpose * DGradBiases[1]
	vWeightsMatricesTranspose[1]->dotProduct(vDeltaGradientBiases[1], vDeltaGradientBiases[0]);
	//DGradBiases[0] = DOT[0] .* Activation'[0]
	vDeltaGradientBiases[0]->multiplyElementWise(vNeuronActivationsDerivative[0], vDeltaGradientBiases[0]);
	//(Activation[input])Transpozycja
	inputLayerActivation->transpose(inputLayerActivationTranspose);
	//DGradWeights[0] = DGradBiases[0] * (Activation[input])Transpose
	vDeltaGradientBiases[0]->dotProduct(inputLayerActivationTranspose, vDeltaGradientWeights[0]);


	//Dodajemy DeltaGradient do Gradientu
	for (int i = 0; i < layersNumber - 2; i++) {
		vGradientBiases[i]->addMatrix(vDeltaGradientBiases[i], vGradientBiases[i]);
		vGradientWeights[i]->addMatrix(vDeltaGradientWeights[i], vGradientWeights[i]);
	}
}

//Sprawdza czy predykcja sieci jest prawidlowa
bool DefaultNetworkEngine::checkGuess(Matrix* outputLable) {
	int netIndex, labelIndex;
	netIndex = vNeuronActivations[layersNumber - 2]->getIndexOfMaxElement();
	//vNeuronActivations[layersNumber - 2]->printMatrix();
	labelIndex = outputLable->getIndexOfMaxElement();
	//outputLable->printMatrix();
	//std::cout << "Net guess: " << netIndex << "Correct answer: " << labelIndex << "\n";
	return netIndex == labelIndex;
}

void DefaultNetworkEngine::applyImprovements() {
	//Wprowadzenie poprawki do parametrow sieci
	for (int i = 0; i < layersNumber - 2; i++) {
		//Wprowadzamy Gradient do sieci
		vGradientBiases[i]->forEach(vGradientBiases[i], DefaultNetworkEngine::constForGradient);
		vGradientWeights[i]->forEach(vGradientWeights[i], DefaultNetworkEngine::constForGradient);

		vBiasesMatrices[i]->subtractMatrix(vGradientBiases[i], vBiasesMatrices[i]);
		vWeightsMatrices[i]->subtractMatrix(vGradientWeights[i], vWeightsMatrices[i]);
		//Zerujemy Gradient (znow mozemy dodawac do niego DeltaGradient)
		vGradientBiases[i]->setToZero();
		vGradientWeights[i]->setToZero();
	}
}


//Trzeba bedzie to przerobic (nie uwzglednia batch size)
double DefaultNetworkEngine::constForGradient(const double& val) {
	return 0.3 * val;
}
