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

Mesh::Mesh(const std::vector<unsigned int> &_N, const std::vector<Material> &materials, const double &_depth): N(_N), depth(_depth) {
	// N = _N;
	// depth = _depth;

	// Get list of boundaries
	std::vector< std::vector<double> > boundaries;
	for (const auto &material: materials) {
		for (const auto &boundary: material.get_boundaries()) {
			boundaries.push_back(boundary);
		}
	}

	// Fix it
	transpose(boundaries);
	for (std::vector<double>::size_type i = 0; i < boundaries.size(); i++) {
		std::sort(boundaries[i].begin(), boundaries[i].end());
		boundaries[i].erase(std::unique(boundaries[i].begin(), boundaries[i].end()), boundaries[i].end());
	}

	std::cout << "BOUNDARIES" << std::endl;
	printMatrix(boundaries);

	// Get number of divisions
	std::vector< std::vector<unsigned int> > divs(boundaries.size());
	for (std::vector<double>::size_type i = 0; i < boundaries.size(); i++) {
		for (std::vector<double>::size_type j = 1; j < boundaries[i].size(); j++) {
			divs[i].push_back(round(N[i] * (boundaries[i][j] - boundaries[i][j-1]) / boundaries[i].back()));
		}
	}

	std::cout << "DIVS" << std::endl;
	printMatrix(divs);

	// Get mesh lines
	X.resize(divs.size());
	std::vector<double> range;
	for (std::vector<int>::size_type i = 0; i < divs.size(); i++) {
		for (std::vector<int>::size_type j = 0; j < divs[i].size(); j++) {
			range = getRange(boundaries[i][j], boundaries[i][j+1], divs[i][j]);
			// printVector(range);
			X[i].insert(X[i].end(), range.begin(), range.end()-1);
		}
		X[i].push_back(boundaries[i].back()); // add missing last element
	}

	// Initialize MxN matrix of volumes
	volumes.resize(N[0]); // use reserve if we only wanted to pre-allocate
	for (std::vector<double>::size_type i = 0; i < N[0]; i++) { // M
		// volumes[i].resize(N[1]);
		for (std::vector<double>::size_type j = 0; j < N[1]; j++) { // N
			volumes[i].push_back(Volume({{X[0][i], X[0][i+1]}, {X[1][j], X[1][j+1]}}, depth, {i, j}, N));
			volumes[i][j].set_material(this->findMaterial(volumes[i][j].get_x(), materials));
		}
	}

	std::cout << "SIZE: " << volumes.size() << " " << volumes[0].size() << std::endl;

	std::cout << "3-4" << std::endl;
	std::cout << volumes[3][4].get_x()[0] << std::endl;

	std::cout << "X" << std::endl;
	printMatrix(X);

	std::cout << X[1].size() << std::endl;
}

const Material* Mesh::findMaterial(const std::vector<double> &x, const std::vector<Material> &materials) {
	std::vector< std::vector<double> > boundaries;
	for (const auto& material: materials) {
		boundaries = material.get_boundaries();
		if ((boundaries[0][0] <= x[0] && boundaries[0][1] >= x[0]) && (boundaries[1][0] <= x[1] && boundaries[1][1] >= x[1])) {
			return &material;
		}
	}
	return nullptr;
}

std::vector< std::vector<Volume> >* Mesh::get_volumes() {
	return &volumes;
}
