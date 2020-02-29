#pragma once

#include <iostream>
#include "Matrix.h"

class LossFunction
{
public:
	LossFunction();
	virtual ~LossFunction();

	//Oblicza funkcje straty dla warstwy neuronOutput na podstawie desiredOutput i zapisuje do macierzy lossOutput
	virtual void evaluateLoss(Matrix* neuronOutpu, Matrix* desiredOutput, Matrix* lossOutput) = 0;
	//Oblicza pochodna funkcji straty dla warstwy neuronOutput na podstawie desiredOutput i zapisuje do macierzy lossOutput
	virtual void evaluateLossDerivative(Matrix* neuronOutput, Matrix* desiredOutput, Matrix* lossDerivativeOutput) = 0;
};

