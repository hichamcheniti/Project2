#include <cstdint>
#include <iostream>
# define M_PI           3.14159265358979323846  /* pi */
using namespace std;
enum Filters { SimpleBoxBlur, GaussianBlur, Sobel, LaplacianOperator, LaplacianGaussian };
void constructSobelMatrix(int8_t** horizontalMatrix, int8_t** verticalMatrix, const int8_t matrixSize) {


	for (int8_t i = 0; i < matrixSize; i++) {
		horizontalMatrix[i] = new int8_t[matrixSize];
		verticalMatrix[i] = new int8_t[matrixSize];

		for (int8_t j = 0; j < matrixSize; j++) {
			if (i == (matrixSize / 2)) {
				verticalMatrix[i][j] = (matrixSize-1)-(j*2);
			}
			else {
				verticalMatrix[i][j] = (matrixSize / 2) - j;
			}
			if (j == (matrixSize / 2)) {
				horizontalMatrix[i][j] = (matrixSize - 1) - (i * 2);
			}
			else {
				horizontalMatrix[i][j] = (matrixSize / 2) - i;
			}
			cout << (int)verticalMatrix[i][j] << ',';
		}
		cout << endl;

	}

}
void constructSimpleBoxBlurMatrix(float** matrix, const int8_t matrixSize) {


	for (int8_t i = 0; i < matrixSize; i++) {
		matrix[i] = new float[matrixSize];
		for (int8_t j = 0; j < matrixSize; j++) {
			matrix[i][j] = (1.0 / 9.0);
			cout << matrix[i][j] << ',';
		}
		cout << endl;

	}

}

void constructLaplacianMatrix(int8_t** matrix, const int8_t matrixSize) {


	for (int8_t i = 0; i < matrixSize; i++) {
		matrix[i] = new int8_t[matrixSize];
		for (int8_t j = 0; j < matrixSize; j++) {
			if (i == matrixSize/2 && j == matrixSize/2) {
				matrix[i][j] = pow(matrixSize,2) - 1;
			}
			else {
				matrix[i][j] = -1;

			}
			cout <<(int) matrix[i][j] << ',';


		}
		cout << endl;

	}

}
void constructGaussianMatrix(double** matrix, int size) {


	double sigma = 1.0;
	double r, s = 2.0 * sigma * sigma;
	int offset = size / 2;
	double sum = 0.0;
	for (int8_t i = 0; i < size; ++i)
			matrix[i] = new double[size];
	for (int8_t x = -offset; x <= offset; x++) {
		for (int8_t y = -offset; y <= offset; y++) {
			r = sqrt(x * x + y * y);
			matrix[x + offset][y + offset] = (exp(-(r * r) / s)) / (M_PI * s);
			sum += matrix[x + offset][y + offset];
		}
	}

	for (int8_t i = 0; i < size; ++i) {
		for (int8_t j = 0; j < size; ++j) {

			matrix[i][j] /= sum;
			cout << matrix[i][j] << ',';


		}
		cout << endl;

	}

}

int main() {
	const size_t size = 7;
	uint8_t filter = Filters::LaplacianOperator;
	switch (filter) {
	case SimpleBoxBlur: {
		float** simpleMatrix = new float* [size];
		constructSimpleBoxBlurMatrix(simpleMatrix, size);
		for (size_t i = 0; i < size; ++i) {
			delete simpleMatrix[i];
		}
		delete[] simpleMatrix; }
					  break;
	case GaussianBlur: {
		double** gaussianMatrix = new double* [size];
		constructGaussianMatrix(gaussianMatrix, size);
		for (size_t i = 0; i < size; ++i) {
			delete gaussianMatrix[i];
		}
		delete[] gaussianMatrix; }
					 break;
	case Sobel: {
		int8_t** horizontalMatrix = new int8_t * [size];
		int8_t** verticalMatrix = new int8_t * [size];
		constructSobelMatrix(horizontalMatrix, verticalMatrix, size);
		for (size_t i = 0; i < size; ++i) {
			delete horizontalMatrix[i];
			delete verticalMatrix[i];

		}

		delete[] horizontalMatrix;
		delete[] verticalMatrix;
		break; }
	case LaplacianOperator: {
		int8_t** laplacianMatrix = new int8_t * [size];
		constructLaplacianMatrix(laplacianMatrix, size);
		for (size_t i = 0; i < size; ++i) {
			delete laplacianMatrix[i];
		}
		delete[] laplacianMatrix;

		break; }
	case LaplacianGaussian: {
		int8_t** laplacianMatrix = new int8_t * [size];
		constructLaplacianMatrix(laplacianMatrix, size);
		double** gaussianMatrix = new double* [size];
		constructGaussianMatrix(gaussianMatrix, size);
		for (size_t i = 0; i < size; ++i) {
			delete laplacianMatrix[i];
		}
		delete[] laplacianMatrix;
		for (size_t i = 0; i < size; ++i) {
			delete gaussianMatrix[i];
		}
		delete[] gaussianMatrix; }
		break;
	}


	return 0;
}