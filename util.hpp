// Standard libraries
#include "headers.hpp"

/* Templated code (must be visible to the compiler) */

template <typename T>
std::vector<T> getRange(T a, T b, int n) {
	std::vector<T> range;
	range.reserve(n);

	double step = (b - a) / n;

	while (a < (b - step/2)) {
		range.push_back(a);
		a += step;
	}

	return range;
}

template <typename T>
void printMatrix(std::vector< std::vector<T> > matrix) {
	for (const auto& vector: matrix) {
		for (const auto& element: vector) {
			std::cout << element << '\t';
		}
		std::cout << '\n';
	}
	std::cout << std::flush; // std::endl;
}

template <typename T>
void printVector(std::vector<T> vector) {
	for (const auto& element: vector) {
		std::cout << element << '\t';
	}
	std::cout << std::endl;
}

template <typename T>
void transpose(std::vector< std::vector<T> > &input) {
	std::vector< std::vector<T> > copy = input;
	std::vector< std::vector<T> > matrix(copy[0].size(), std::vector<T>(copy.size()));
	for (typename std::vector<T>::size_type i = 0; i < matrix.size(); i++) {
		for (typename std::vector<T>::size_type j = 0; j < matrix[0].size(); j++) {
			matrix[i][j] = copy[j][i];	
		}
	}
	input = matrix;
}

template <typename T>
bool checkConvergence(std::vector< std::vector<T> > &A, std::vector< std::vector<T> > &B, const double &delta) {
	for (typename std::vector<T>::size_type i = 0; i < A.size(); i++) {
		for (typename std::vector<T>::size_type j = 0; j < A[0].size(); j++) {
			// std::cout << "DELTA: " << delta << std::endl;
			// std::cout << "ABS: " << abs(A[i][j] - B[i][j]) << std::endl;
			// std::cout << "STDABS: " << std::abs(A[i][j] - B[i][j]) << std::endl;
			// std::cout << A[i][j] << " - " << B[i][j] << " = " << (A[i][j] - B[i][j]) << std::endl;
			if (std::abs(A[i][j] - B[i][j]) > delta) return false;
		}
	}
	return true;
}
