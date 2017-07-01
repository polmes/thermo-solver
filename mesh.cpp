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

Mesh::Mesh(std::vector<unsigned int> _N, std::vector<Material> materials, double _depth): N(_N), depth(_depth) {

	std::vector< std::vector<double> > boundaries;
	for (auto material: materials) {
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

	// Initialize MxN matrix
	volumes.resize(N[0]); // reserve if we only wanted to pre-allocate
	std::vector<double> x, S;
	for (std::vector<double>::size_type i = 1; i < X[0].size(); i++) {
		// std::vector<Volume> volumes1D;
		for (std::vector<double>::size_type j = 1; j < X[1].size(); j++) {
			x = {(X[0][i-1] + X[0][i]) / 2, (X[1][j-1] + X[1][j]) / 2};
			S = {X[0][i] - X[0][i-1], X[1][j] - X[1][j-1]};
			volumes[i-1].push_back(Volume(x, findMaterial(x, materials), S, S[0] * S[1] * depth));
		}
		// volumes.push_back(volumes1D);
	}

	std::cout << "SIZE: " << volumes.size() << " " << volumes[0].size() << std::endl;

	std::cout << "3-4" << std::endl;
	std::cout << volumes[3][4].getX()[0] << std::endl;

	std::cout << "X" << std::endl;
	printMatrix(X);

	std::cout << X[1].size() << std::endl;
}

Material Mesh::findMaterial(std::vector<double> x, std::vector<Material> materials) {
	std::vector< std::vector<double> > boundaries;
	for (auto material: materials) {
		boundaries = material.getBoundaries();
		if ((boundaries[0][0] <= x[0] && boundaries[0][1] >= x[0]) && (boundaries[1][0] <= x[1] && boundaries[1][1] >= x[1])) {
			return material;
		}
	}
	// return nullptr;
}

// TODO: Convert as many functions as possible to pass by reference & pointer returns!

std::vector< std::vector<Volume> >* Mesh::getVolumes() {
	return &volumes;
}
