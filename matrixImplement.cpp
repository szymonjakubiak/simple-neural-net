#include "matrixImplement.h"

matrixImplement::matrixImplement(): mColumns(0), nRows(0) {
	//std::cout << "Domyslny Implement" << std::endl;
}
matrixImplement::~matrixImplement() {
	//std::cout << "Destruktor Implement " << nRows << " x " << mColumns << std::endl;
}


//Inicjalizacja macierzy o znanych wymiarach zerami
void matrixImplement::setSize(const int& nI, const int& mI) {
	//std::cout << "Inicjalizacja " << nI << " x " << mI << std::endl;
	mat.resize(nI * mI, 0.0);
	nRows = nI;
	mColumns = mI;
}


//Wydruk macierzy
void matrixImplement::printMatrix() {
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < mColumns; j++) {
			std::cout << mat[i + nRows*j] << " ";
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}


//Wypelnienie macierzy losowymi wartosciami z przedzialu <min,max>
void matrixImplement::setRandom(double min, double max) {
	//Inicjalizacja generatora (tylko za pierwszym razem)
	if (!randInit) {
		srand(unsigned (time(NULL)));
		randInit = true;
	}
	double rnd;
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < mColumns; j++) {
			rnd = (max - min) * rand() / RAND_MAX + min;
			mat[i + nRows * j] = rnd;
		}
	}
}


//Przypisuje macierz po transpozycji do przekazanego wskaznika
void matrixImplement::transpose(Matrix* result) {
	//Indexy i wymiary odniesione do macierzy transponowanej
	int n_rowI, n_colI, n_nRows;

	//Chcemy dostac siê do mat (upcasting)
	matrixImplement* resPointer = dynamic_cast<matrixImplement*>(result);

	//Sprawdzenie czy rzutowanie sie powiodlo
	if (!resPointer) {
		std::cout << "You picked the wrong pointer, fool!" << std::endl;
		exit(-1);
	}

	//Sprawdzenie wymiarow macierzy podanej przez wskaznik 
	if (!(this->nRows == resPointer->mColumns && this->mColumns == resPointer->nRows)) {
		std::cout << "Zle wymiary macierzy - TRANSPOZYCJA" << "\n";
		exit(-1);
	}

	//Przepisanie transpozycji do przekazanej macierzy
	for (int rowI = 0; rowI < nRows; rowI++) {
		for (int colI = 0; colI < mColumns; colI++) {
			//indexy w macierzy transponowanej
			n_rowI = colI;
			n_colI = rowI;
			n_nRows = mColumns;
			resPointer->mat[n_rowI + n_nRows * n_colI] = mat[rowI + nRows * colI];
		}
	}
}


//Przypisuje macierz po mnozeniu macierzy, do przekazanego wskaznika
void matrixImplement::dotProduct(Matrix* B, Matrix* result) {

	//Chcemy dostac siê do atrybutow implementacji Matrix (upcasting)
	matrixImplement* BPointer = dynamic_cast<matrixImplement*>(B);
	matrixImplement* resPointer = dynamic_cast<matrixImplement*>(result);

	//Sprawdzenie czy rzutowanie sie powiodlo
	if (!resPointer || !BPointer) {
		std::cout << "You picked the wrong pointer, fool!" << std::endl;
		exit(-1);
	}

	//Czy mozemy mnozyc macierze
	if (this->mColumns != BPointer->nRows) {
		std::cout << "Zle wymiary macierzy A,B! - DOT_PRODUCT" << "\n";
		std::cout << "A: " << this->nRows << "x" << this->mColumns << "\n" <<
			"B: " << BPointer->nRows << "x" << BPointer->mColumns << "\n" <<
			"Wynikowa " << resPointer->nRows << "x" << resPointer->mColumns << "\n";
		exit(-1);
	}

	//Czy macierz wynikowa ma wlasciwe wymiary
	if (this->nRows != resPointer->nRows || BPointer->mColumns != resPointer->mColumns) {
		std::cout << "Zle wymiary macierzy wynikowej! - DOT_PRODUCT" << std::endl;
		std::cout << "A: " << this->nRows << "x" << this->mColumns << "\n" <<
			"B: " << BPointer->nRows << "x" << BPointer->mColumns << "\n" <<
			"Wynikowa " << resPointer->nRows << "x" << resPointer->mColumns << "\n";
		exit(-1);
	}

	//Obliczenia i przypisanie wartosci
	for (int i = 0; i < this->nRows; i++) {
		for (int k = 0; k < BPointer->mColumns; k++) {

			//Wyczyszczenie smieci z przekazanej macierzy
			resPointer->mat[i + this->nRows * k] = 0;

			for (int j = 0; j < this->mColumns; j++) {
				resPointer->mat[i + this->nRows * k] += this->mat[i + this->nRows * j] * BPointer->mat[j + BPointer->nRows * k];
			}
		}
	}

}


//Przypisuje macierz po dodawaniu A+B macierzy A.(B,result) do przekazanego wskaznika "result"
void matrixImplement::addMatrix(Matrix* B, Matrix* result) {

	//Chcemy dostac siê do atrybutow implementacji Matrix (upcasting)
	matrixImplement* BPointer = dynamic_cast<matrixImplement*>(B);
	matrixImplement* resPointer = dynamic_cast<matrixImplement*>(result);

	//Sprawdzenie czy rzutowanie sie powiodlo
	if (!resPointer || !BPointer) {
		std::cout << "You picked the wrong pointer, fool!" << std::endl;
		exit(-1);
	}

	//Czy mozemy dodac macierze
	if (this->mColumns != BPointer->mColumns || this->nRows != BPointer->nRows) {
		std::cout << "Zle wymiary macierzy A,B!" << std::endl;
		exit(-1);
	}

	//Czy macierz wynikowa ma wlasciwe wymiary
	if (this->nRows != resPointer->nRows || this->mColumns != resPointer->mColumns) {
		std::cout << "Zle wymiary macierzy wynikowej!" << std::endl;
		exit(-1);
	}

	//Obliczenia i przypisanie wartosci
	for (int i = 0; i < this->nRows; i++) {
		for (int j = 0; j < this->mColumns; j++) {
			resPointer->mat[i + this->nRows * j] = this->mat[i + this->nRows * j] + BPointer->mat[i + BPointer->nRows * j];
		}
	}

}


//Przypisuje macierz po odejmowaniu A-B macierzy A.(B,result) do przekazanego wskaznika "result"
void matrixImplement::subtractMatrix(Matrix* B, Matrix* result) {

	//Chcemy dostac siê do atrybutow implementacji Matrix (upcasting)
	matrixImplement* BPointer = dynamic_cast<matrixImplement*>(B);
	matrixImplement* resPointer = dynamic_cast<matrixImplement*>(result);

	//Sprawdzenie czy rzutowanie sie powiodlo
	if (!resPointer || !BPointer) {
		std::cout << "You picked the wrong pointer, fool!" << std::endl;
		exit(-1);
	}

	//Czy mozemy dodac macierze
	if (this->mColumns != BPointer->mColumns || this->nRows != BPointer->nRows) {
		std::cout << "Zle wymiary macierzy A,B!" << std::endl;
		exit(-1);
	}

	//Czy macierz wynikowa ma wlasciwe wymiary
	if (this->nRows != resPointer->nRows || this->mColumns != resPointer->mColumns) {
		std::cout << "Zle wymiary macierzy wynikowej!" << std::endl;
		exit(-1);
	}

	//Obliczenia i przypisanie wartosci
	for (int i = 0; i < this->nRows; i++) {
		for (int j = 0; j < this->mColumns; j++) {
			resPointer->mat[i + this->nRows * j] = this->mat[i + this->nRows * j] - BPointer->mat[i + BPointer->nRows * j];
		}
	}

}


//Przypisuje macierz po mnozeniu A*.B (element-wise) macierzy A.(B,result) do przekazanego wskaznika "result"
void matrixImplement::multiplyElementWise(Matrix* B, Matrix* result) {

	//Chcemy dostac siê do atrybutow implementacji Matrix (upcasting)
	matrixImplement* BPointer = dynamic_cast<matrixImplement*>(B);
	matrixImplement* resPointer = dynamic_cast<matrixImplement*>(result);

	//Sprawdzenie czy rzutowanie sie powiodlo
	if (!resPointer || !BPointer) {
		std::cout << "You picked the wrong pointer, fool!" << std::endl;
		exit(-1);
	}

	//Czy mozemy dodac macierze
	if (this->mColumns != BPointer->mColumns || this->nRows != BPointer->nRows) {
		std::cout << "Zle wymiary macierzy A,B! - ELEMENT_WISE" << std::endl;
		exit(-1);
	}

	//Czy macierz wynikowa ma wlasciwe wymiary
	if (this->nRows != resPointer->nRows || this->mColumns != resPointer->mColumns) {
		std::cout << "Zle wymiary macierzy wynikowej! - ELEMENT_WISE" << "\n";
		std::cout << "A: " << this->nRows << "x" << this->mColumns << "\n" <<
			"B: " << BPointer->nRows << "x" << BPointer->mColumns << "\n" <<
			"Wynikowa " << resPointer->nRows << "x" << resPointer->mColumns << "\n";
		exit(-1);
	}

	//Obliczenia i przypisanie wartosci
	for (int i = 0; i < this->nRows; i++) {
		for (int j = 0; j < this->mColumns; j++) {
			resPointer->mat[i + this->nRows * j] = this->mat[i + this->nRows * j] * BPointer->mat[i + BPointer->nRows * j];
		}
	}

}


//Dla kazdego elementu macierzy przyklada funkcje przekazana przez wskaznik, wynik zapisuje do przekazanego wskaznika "result"
void matrixImplement::forEach(Matrix* result, double(*function)(const double&)) {

	//Chcemy dostac siê do mat (upcasting)
	matrixImplement* resPointer = dynamic_cast<matrixImplement*>(result);

	//Sprawdzenie czy rzutowanie sie powiodlo
	if (!resPointer) {
		std::cout << "You picked the wrong pointer, fool!" << std::endl;
		exit(-1);
	}

	//Sprawdzenie wymiarow macierzy podanej przez wskaznik 
	if (this->nRows != resPointer->nRows || this->mColumns != resPointer->mColumns) {
		std::cout << "Zle wymiary macierzy wynikowej!" << std::endl;
		exit(-1);
	}

	//Obliczenia i przypisanie wartosci
	for (int i = 0; i < this->nRows; i++) {
		for (int j = 0; j < this->mColumns; j++) {
			resPointer->mat[i + this->nRows * j] = function( this->mat[i + this->nRows * j] );
		}
	}

}


//Zapisuje zawartosc macierzy do pliku tekstowego o podanej nazwie
void matrixImplement::saveMatrix(std::string fileName) {
	std::ofstream oFile;
	oFile.open(fileName, std::ios::out);

	if (!oFile.is_open()) {
		std::cout << "File could not be opened" << "\n";
		exit(-1);
	}

	oFile << this->nRows << ' ' << this->mColumns << "\n";
	for (auto const& value : this->mat) {
		oFile << value << ' ';
	}
	oFile << "\n";

	oFile.close();
}


//Wczytuje zawartosc macierzy z pliku tekstowego
void matrixImplement::loadMatrix(std::string fileName) {
	std::ifstream iFile;
	iFile.open(fileName, std::ios::in);

	if (!iFile.is_open()) {
		std::cout << "File could not be opened" << "\n";
		exit(-1);
	}

	iFile >> this->nRows;
	iFile >> this->mColumns;
	std::cout << this->nRows << " " << this->mColumns << "\n";

	this->setSize(nRows, mColumns);

	for (int i = 0; i < nRows * mColumns; i++) {
		iFile >> this->mat[i];
	}

	iFile.close();
}


//Ustawia wartosc wskazanego elementu
void matrixImplement::tweakValue(const double& val, const int& i, const int& j) {
	this->mat[i + this->nRows * j] = val;
}

int matrixImplement::getIndexOfMaxElement() {
	//std::cout << "mat size = " << mat.size() << "\n";
	int maxIndex = std::max_element(mat.begin(), mat.end()) - mat.begin();
	//std::cout << "max index = " << maxIndex << "\n";
	return maxIndex;
}

//Zeruje wszystkie wartosci w macierzy
void matrixImplement::setToZero() {
	for (auto& vec : mat) {
		vec = 0;
	}
}

