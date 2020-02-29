#include "SigmoidActivation.h"

SigmoidActivation::SigmoidActivation() {
	//std::cout << "SigmoidActivation Constructor" << "\n";
}
SigmoidActivation::~SigmoidActivation() {
	//std::cout << "SigmoidActivation Destructor" << "\n";
}

//Funkcja aktywacji
double SigmoidActivation::Sigmoid(const double& val) {
	return (1.0 / (1.0 + exp(-val)));
}

//Pochodna funkcji aktywacji
double SigmoidActivation::SigmoidPrime(const double& val) {
	return SigmoidActivation::Sigmoid(val) * (1.0 - SigmoidActivation::Sigmoid(val));
}

//Oblicza macierz po przylozeniu funkcji aktywacji do kazdego elementu macierzy wejsciowej
void SigmoidActivation::evaluateActivation(Matrix* neuronInput, Matrix* output) {
	neuronInput->forEach(output, Sigmoid);
}

//Oblicza macierz po przylozeniu pochodnej funkcji aktywacji do kazdego elementu macierzy wejsciowej
void SigmoidActivation::evaluateActivationDerivative(Matrix* neuronInput, Matrix* output) {
	neuronInput->forEach(output, SigmoidPrime);
}