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

Mesh::Mesh(const double &_depth, const std::vector<unsigned int> &_N, const std::vector<Material> &materials, const std::vector< std::vector<Condition> > &conditions) {
	N = _N;
	depth = _depth;
	// conditions = _conditions;

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

	// std::cout << "BOUNDARIES" << std::endl;
	// printMatrix(boundaries);

	// Get number of divisions
	std::vector< std::vector<unsigned int> > divs(boundaries.size());
	for (std::vector<double>::size_type i = 0; i < boundaries.size(); i++) {
		for (std::vector<double>::size_type j = 1; j < boundaries[i].size(); j++) {
			divs[i].push_back(round(N[i] * (boundaries[i][j] - boundaries[i][j-1]) / boundaries[i].back()));
		}
	}

	// std::cout << "DIVS" << std::endl;
	// printMatrix(divs);

	// Get mesh lines
	X.resize(divs.size());
	std::vector<double> range;
	for (std::vector<int>::size_type i = 0; i < divs.size(); i++) {
		for (std::vector<int>::size_type j = 0; j < divs[i].size(); j++) {
			range = getRange(boundaries[i][j], boundaries[i][j+1], divs[i][j]);
			// std::cout << "RANGE" << std::endl;
			// printVector(range);
			X[i].insert(X[i].end(), range.begin(), range.end());
		}
		X[i].push_back(boundaries[i].back()); // add missing last element
	}

	// std::cout << "X" << std::endl;
	// printMatrix(X);

	// Initialize MxN matrix of "volumes"
	volumes.resize(N[0]+2); // use reserve if we only wanted to pre-allocate
	volumes[0].push_back(new Node({X[0][0], X[1][0]})); // bottom left corner
	for (std::vector<double>::size_type j = 0; j < N[1]; j++) { // N
		volumes[0].push_back(new Boundary({X[0][0], (X[1][j]+X[1][j+1])/2}, conditions[0][0])); // first column
	}
	volumes[0].push_back(new Node({X[0][0], X[1][N[1]]})); // top left corner
	for (std::vector<double>::size_type i = 1; i < N[0]+1; i++) { // M+2
		volumes[i].push_back(new Boundary({(X[0][i-1]+X[0][i])/2, X[1][0]},  conditions[1][0])); // bottom
		for (std::vector<double>::size_type j = 1; j < N[1]+1; j++) { // N+2
			volumes[i].push_back(new Volume({{X[0][i-1], X[0][i]}, {X[1][j-1], X[1][j]}}, depth)); // inner
		}
		volumes[i].push_back(new Boundary({(X[0][i-1]+X[0][i])/2, X[1][N[1]]},  conditions[1][1])); // top
	}
	volumes[N[0]+1].push_back(new Node({X[0][N[0]], X[1][0]})); // bottom right corner
	for (std::vector<double>::size_type j = 0; j < N[1]; j++) { // N
		volumes[N[0]+1].push_back(new Boundary({X[0][N[0]], (X[1][j]+X[1][j+1])/2}, conditions[0][1])); // last column
	}
	volumes[N[0]+1].push_back(new Node({X[0][N[0]], X[1][N[1]]})); // bottom right corner

	// // Initialize MxN matrix of volumes
	// volumes.resize(N[0]); // use reserve if we only wanted to pre-allocate
	// for (std::vector<double>::size_type i = 0; i < N[0]; i++) { // M
	// 	for (std::vector<double>::size_type j = 0; j < N[1]; j++) { // N
	// 		volumes[i].push_back(Volume({{X[0][i], X[0][i+1]}, {X[1][j], X[1][j+1]}}, depth, {i, j}, N, conditions));
	// 		volumes[i][j].set_material(this->findMaterial(volumes[i][j].get_x(), materials));
	// 	}
	// }

	std::cout << typeid(volumes).name() << std::endl;
	// std::cout << typeid(*volumes).name() << std::endl;

	// Setup missing parameters
	for (std::vector<Node*>::size_type i = 0; i < volumes.size(); i++) {
		for (std::vector<Node*>::size_type j = 0; j < volumes[i].size(); j++) {
			// std::cout << i << " " << j << std::endl;
			// std::cout << volumes[i][j]->get_x()[0] << " " << volumes[i][j]->get_x()[1] << std::endl;
			volumes[i][j]->set_material(this->findMaterial(volumes[i][j]->get_x(), materials));
			volumes[i][j]->set_neighbors({i, j}, volumes);
		}
	}
}

const Material* Mesh::findMaterial(const std::vector<double> &x, const std::vector<Material> &materials) {
	std::vector< std::vector<double> > boundaries;
	for (const auto& material: materials) {
		boundaries = material.get_boundaries();
		if ((boundaries[0][0] <= x[0] && boundaries[1][0] >= x[0]) && (boundaries[0][1] <= x[1] && boundaries[1][1] >= x[1])) {
			return &material;
		}
	}
	return nullptr; // error handling
}

std::vector< std::vector<Node*> >* Mesh::get_volumes() {
	return &volumes;
}

void Mesh::solve(std::vector< std::vector<double> > &T) {
	// Standard solver
	for (std::vector< std::vector<double> >::size_type i = 0; i < volumes.size(); i++) {
		for (std::vector< std::vector<double> >::size_type j = 0; j < volumes[i].size(); j++) {
			// aP*T[i][j] = aW*T[i-1][j] + aE*T[i+1][j] + aS*T[i][j-1] + aN*T[i][j+1] + bP
			T[i+1][j+1] = (volumes[i][j]->get_aW() * T[i][j+1] + volumes[i][j]->get_aE() * T[i+2][j+1] + volumes[i][j]->get_aS() * T[i+1][j] + volumes[i][j]->get_aN() * T[i+1][j+2] + volumes[i][j]->get_bP()) / volumes[i][j]->get_aP();
		}
	}

	/* Parallel TDMA solver */
	
	// std::cout << "Starting threads..." << std::endl;

	// // aP*T[i] = aW*T[i-1] + aE*T[i+1] + bP[i]
	// std::thread horizontal(this->tdma, arg);

	// // aP*T[i] = aS*T[i-1] + aN*T[i+1] + bP[i]
	// std::thread vertical(this->tdma, arg);

	// // Wait for threads to finish
	// horizontal.join();
	// vertical.join();

	// std::cout << "... and we're done!" << std::endl;
}

// std::vector<double> T Mesh::tdma() {
// 	// aP*T[i] = aW*T[i-1] + aE*T[i+1] + bP[i]
// 	double aP, aW, aE, bP;
// 	std::vector<double> T, P, R;
// 	T.resize(N+2, 0.0);
// 	P = R = T;
// 	for (std::vector<double>::size_type i = 0; i < N; i++) {
// 		aP = volumes[i][j].get_aP()
// 		aW = volumes[i][j].get_aW();
// 		aE = volumes[i][j].get_aE();
// 		bP = volumes[i][j].get_bP();

// 		P[i+1] = aE / (aP - aW*P[i]);
// 		R[i+1] = (bP + aW*R[i]) / (aP - aW*P[i]);
// 	}
// 	for (std::vector<double>::size_type i = N; i > 0; i--) {
// 		T[i] = P[i]*T[i+1] + R[i];
// 	}
// }
