#include "LeastSquareLossFunction.h"

LeastSquareLossFunction::LeastSquareLossFunction()
{
	//std::cout << "LeastSquareLossFunction Constructor" << "\n";
}

LeastSquareLossFunction::~LeastSquareLossFunction()
{
	//std::cout << "LeastSquareLossFunction Destructor" << "\n";
}

//Oblicza funkcje straty dla warstwy neuronOutput na podstawie desiredOutput i zapisuje do macierzy lossOutput
void LeastSquareLossFunction::evaluateLoss(Matrix* neuronOutpu, Matrix* desiredOutput, Matrix* lossOutput)
{
	//res = (x-y)
	neuronOutpu->subtractMatrix(desiredOutput, lossOutput);
	//res.^2
	lossOutput->multiplyElementWise(lossOutput, lossOutput);
	//Mozna by dorzucic *0.5, ale nie ma to wiekszego sensu
}

void LeastSquareLossFunction::evaluateLossDerivative(Matrix* neuronOutput, Matrix* desiredOutput, Matrix* lossDerivativeOutput)
{
	//res = (x-y)
	neuronOutput->subtractMatrix(desiredOutput, lossDerivativeOutput);
}
