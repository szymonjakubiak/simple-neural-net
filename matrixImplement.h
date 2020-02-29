#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <algorithm>

#include "Matrix.h"


class matrixImplement : public Matrix
{
public:
	matrixImplement();
	~matrixImplement();
	//Inicjalizacja macierzy o znanych wymiarach zerami
	void setSize(const int& nI, const int& mI) override;
	//Wydruk macierzy
	void printMatrix() override;
	//Wypelnienie macierzy losowymi wartosciami z przedzialu <min,max>
	void setRandom(double min = -1.0, double max = 1.0) override;
	//Przypisuje macierz po transpozycji do przekazanego wskaznika
	void transpose(Matrix* result) override;
	//Przypisuje macierz po mnozeniu A*B macierzy A.(B,result) do przekazanego wskaznika "result"
	void dotProduct(Matrix* B, Matrix* result) override;
	//Przypisuje macierz po dodawaniu A+B macierzy A.(B,result) do przekazanego wskaznika "result"
	void addMatrix(Matrix* B, Matrix* result) override;
	//Przypisuje macierz po odejmowaniu A-B macierzy A.(B,result) do przekazanego wskaznika "result"
	void subtractMatrix(Matrix* B, Matrix* result) override;
	//Przypisuje macierz po mnozeniu A*.B (element-wise) macierzy A.(B,result) do przekazanego wskaznika "result"
	void multiplyElementWise(Matrix* B, Matrix* result) override;
	//Dla kazdego elementu macierzy przyklada funkcje przekazana przez wskaznik, wynik zapisuje do przekazanego wskaznika "result"
	void forEach(Matrix* result, double(*function)(const double&)) override;
	//Zapisuje zawartosc macierzy do pliku tekstowego o podanej nazwie
	void saveMatrix(std::string fileName) override;
	//Wczytuje zawartosc macierzy z pliku tekstowego
	void loadMatrix(std::string fileName) override;
	//Ustawia wartosc wskazanego elementu
	void tweakValue(const double& val, const int& i, const int& j) override;
	//Zwraca index (i+j*rowSize) maksymalnego elementu w macierzy
	int getIndexOfMaxElement() override;
	//Zeruje wszystkie wartosci w macierzy
	void setToZero() override;
	
	
private:
	std::vector<double> mat;
	int mColumns, nRows;
	static bool randInit; //flaga dla generatora
};