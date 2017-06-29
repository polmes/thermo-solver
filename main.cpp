// C++ libraries
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <thread>
#include <stdexcept>

// My libraries
#include "mesh.hpp"

// Read config file and get all consts

int main(int argc, char** argv) {
	if (argc < 1 || argc > 2) {
		throw std::invalid_argument("ERROR: Unexpected number of arguments.");
		return 1;
	}

	Mesh mesh(M, N);
	mesh.printMatrix();

	return 0;
}
