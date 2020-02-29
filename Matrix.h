#pragma once

#include <iostream>
#include <string>

class Matrix{
public:
	Matrix();
	virtual ~Matrix();
	//Inicjalizacja macierzy o znanych wymiarach zerami
	virtual void setSize(const int& nI, const int& mI) = 0;
	//Wydruk macierzy
	virtual void printMatrix() = 0;
	//Wypelnienie macierzy losowymi wartosciami z przedzialu <min,max>
	virtual void setRandom(double min=-1.5, double max=1.5) = 0;
	//Przypisuje macierz po transpozycji do przekazanego wskaznika
	virtual void transpose(Matrix* result) = 0;
	//Przypisuje macierz po mnozeniu A*B macierzy A.(B,result) do przekazanego wskaznika "result"
	virtual void dotProduct(Matrix* B, Matrix* result) = 0;
	//Przypisuje macierz po dodawaniu A+B macierzy A.(B,result) do przekazanego wskaznika "result"
	virtual void addMatrix(Matrix* B, Matrix* result) = 0;
	//Przypisuje macierz po odejmowaniu A-B macierzy A.(B,result) do przekazanego wskaznika "result"
	virtual void subtractMatrix(Matrix* B, Matrix* result) = 0;
	//Przypisuje macierz po mnozeniu A*.B (element-wise) macierzy A.(B,result) do przekazanego wskaznika "result"
	virtual void multiplyElementWise(Matrix* B, Matrix* result) = 0;
	//Dla kazdego elementu macierzy przyklada funkcje przekazana przez wskaznik, wynik zapisuje do przekazanego wskaznika "result"
	virtual void forEach(Matrix *result, double(*function)(const double&)) = 0;
	//Zapisuje zawartosc macierzy do pliku tekstowego
	virtual void saveMatrix(std::string fileName) = 0;
	//Wczytuje zawartosc macierzy z pliku tekstowego
	virtual void loadMatrix(std::string fileName) = 0;
	//Ustawia wartosc wskazanego elementu
	virtual void tweakValue(const double& val, const int& i, const int& j) = 0;
	//Zwraca index (i+j*rowSize) maksymalnego elementu w macierzy
	virtual int getIndexOfMaxElement() = 0;
	//Zeruje wszystkie wartosci w macierzy
	virtual void setToZero() = 0;
};