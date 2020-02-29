#pragma once
#include "LossFunction.h"

class LeastSquareLossFunction :
	public LossFunction
{
public:
	LeastSquareLossFunction();
	~LeastSquareLossFunction();

	//Oblicza funkcje straty dla warstwy neuronOutput na podstawie desiredOutput i zapisuje do macierzy lossOutput
	void evaluateLoss(Matrix* neuronOutpu, Matrix* desiredOutput, Matrix* lossOutput) override;
	//Oblicza pochodna funkcji straty dla warstwy neuronOutput na podstawie desiredOutput i zapisuje do macierzy lossOutput
	void evaluateLossDerivative(Matrix* neuronOutput, Matrix* desiredOutput, Matrix* lossDerivativeOutput) override;

};

