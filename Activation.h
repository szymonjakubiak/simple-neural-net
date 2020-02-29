#pragma once

#include<iostream>
#include "Matrix.h"

class Activation
{
public:
	Activation();
	virtual ~Activation();

	//Oblicza macierz po przylozeniu funkcji aktywacji do kazdego elementu macierzy wejsciowej
	virtual void evaluateActivation(Matrix* neuronInput, Matrix* output) = 0;
	//Oblicza macierz po przylozeniu pochodnej funkcji aktywacji do kazdego elementu macierzy wejsciowej
	virtual void evaluateActivationDerivative(Matrix* neuronInput, Matrix* output) = 0;
};

