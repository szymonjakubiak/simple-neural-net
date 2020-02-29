#pragma once
#include "Activation.h"
#include <math.h>

class SigmoidActivation :
	public Activation
{
public:
	SigmoidActivation();
	~SigmoidActivation();

	//Oblicza macierz po przylozeniu funkcji aktywacji do kazdego elementu macierzy wejsciowej
	void evaluateActivation(Matrix* neuronInput, Matrix* output) override;
	//Oblicza macierz po przylozeniu pochodnej funkcji aktywacji do kazdego elementu macierzy wejsciowej
	void evaluateActivationDerivative(Matrix* neuronInput, Matrix* output) override;

private:
	//Funkcja aktywacji
	static double Sigmoid(const double& val);
	static double SigmoidPrime(const double& val);
};

