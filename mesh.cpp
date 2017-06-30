#include "mesh.hpp"

Mesh::Mesh(unsigned int _M, unsigned int _N, std::vector<Material> materials): M(_M), N(_N) {
	// Initialize MxN matrix
	volumes.resize(M, std::vector<Volume>(N)); // reserve if we only wanted to pre-allocate

	std::vector< std::vector<double> > boundaries;
	Region region;
	divs.reserve(materials.size(), std::vector<unsigned int>(2));
	for (const auto& material: materials) {

		// regions.push_back(region(material));
		boundaries.push_back(material.getBoundaries());
	}

	for (const auto& boundaries1D: boundaries) {
		std::sort( boundaries1D.begin(), boundaries1D.end());
		boundaries1D.erase(std::unique(boundaries1D.begin(), boundaries1D.end()), boundaries1D.end());
	}

	std::vector< std::vector<unsigned int> > divs;
	std::vector<unsigned int> divs1D;
	for (const auto& boundaries1D: boundaries) {
		for (unsigned int i = 1; i < boundaries1D.size(); i++) {
			divs1D.push_back(round(M * (boundaries1D[i] - boundaries1D[i-1]) / boundaries1D.back()));
		}
		divs.push_back(divs1D);
	}

	X.reserve(M+1, std::vector<double>(N+1));
	for (unsigned int i = 0; i < divs.size(); i++) {
		for (unsigned int j = 0; j < divs[i].size(); j++) {
			range = getRange(boundaries[i][j], boundaries[i][j+1], divs[i][j]);
			X.insert(X.end(), range.begin(), range.end());
		}
	}

	for (unsigned int i = 0; i < X.size(); i++) {
		for (unsigned j = 0; j < X[i].size(); j++) {
			std::cout << X[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << std::endl;
}

void Mesh::printMatrix() {
	for (unsigned int i = 0; i < M; ++i) {
		for (unsigned int j = 0; j < N; ++j) {
			std::cout << volumes[i][j] << "\t";
		}
		std::cout << "\n";
	}
	std::cout << std::endl; // flush the stream
}
