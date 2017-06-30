// C++ libraries
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
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

	std::vector<Material> materials;
	Material material;
	materials.push_back(material({{0.0, 0.0}, {0.5, 0.4}}, 1500.0, 750.0, 170.0));
	materials.push_back(material({{0.5, 0.0}, {1.1, 0.7}}, 1600.0, 770.0, 140.0));

	Mesh mesh(10, 20, materials);
	mesh.printMatrix();

	return 0;
}
