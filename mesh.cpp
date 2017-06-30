// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_MESH
	#include "mesh.hpp"
	#define INCLUDE_MESH
#endif
#ifndef INCLUDE_UTIL
	#include "util.hpp"
	#define INCLUDE_UTIL
#endif

Mesh::Mesh(std::vector<unsigned int> _N, std::vector<Material> materials): N(_N) {
	// Initialize MxN matrix
	// volumes.resize(M, std::vector<Volume>(N)); // reserve if we only wanted to pre-allocate

	std::vector< std::vector<double> > boundaries;
	// Region region;
	// divs.reserve(materials.size(), std::vector<unsigned int>(2));
	for (auto material: materials) {

		// regions.push_back(region(material));
		for (auto boundary: material.getBoundaries()) {
			boundaries.push_back(boundary);
		}
		
	}

	transpose(boundaries);

	for (std::vector<double>::size_type i = 0; i < boundaries.size(); i++) {
		std::sort(boundaries[i].begin(), boundaries[i].end());
		boundaries[i].erase(std::unique(boundaries[i].begin(), boundaries[i].end()), boundaries[i].end());
	}

	std::cout << "sorted" << std::endl;
	printMatrix(boundaries);

	std::vector< std::vector<unsigned int> > divs(boundaries.size());
	for (std::vector<double>::size_type i = 0; i < boundaries.size(); i++) {
		for (std::vector<double>::size_type j = 1; j < boundaries[i].size(); j++) {
			divs[i].push_back(round(N[i] * (boundaries[i][j] - boundaries[i][j-1]) / boundaries[i].back()));
		}
	}

	std::cout << "divs" << std::endl;
	printMatrix(divs);

	X.resize(divs.size());
	std::vector<double> range;
	for (std::vector<int>::size_type i = 0; i < divs.size(); i++) {
		for (std::vector<int>::size_type j = 0; j < divs[i].size(); j++) {
			range = getRange(boundaries[i][j], boundaries[i][j+1], divs[i][j]);
			printVector(range);
			X[i].insert(X[i].end(), range.begin(), range.end()-1);
		}
		X[i].push_back(boundaries[i].back());
	}

	std::cout << "X" << std::endl;
	printMatrix(X);

	std::cout << X[1].size() << std::endl;
}
