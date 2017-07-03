// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_MESH
	#include "mesh.hpp"
	#define INCLUDE_MESH
#endif
#ifndef INCLUDE_CONDITION
	#include "condition.hpp"
	#define INCLUDE_CONDITION
#endif
#ifndef INCLUDE_UTIL
	#include "util.hpp"
	#define INCLUDE_UTIL
#endif

/**
 * TODO
 * - Parallelize everything we can
 * - No more copies: either pass by reference or by pointer! (same for returns)
 */

int main(int argc, char** argv) {
	if (argc < 1 || argc > 2) {
		throw std::invalid_argument("ERROR: Unexpected number of arguments.");
		return 1;
	}

	// Here will read config file and get all parameters
	std::vector< std::vector<Condition> > conditions = {{Condition(CONVECTION, 9.0, 33.0), Condition(ISOTHERM, 8.0, 0.005)}, {Condition(ISOTHERM, 23.0), Condition(FLOW, 60.0)}};

	std::vector<Material> materials;
	materials.push_back(Material({{0.0, 0.0}, {0.5, 0.4}}, 1500.0, 750.0, 170.0, 0.0));
	materials.push_back(Material({{0.5, 0.0}, {1.1, 0.7}}, 1600.0, 770.0, 140.0, 0.0));
	materials.push_back(Material({{0.0, 0.4}, {0.5, 0.8}}, 1900.0, 810.0, 200.0, 0.0));
	materials.push_back(Material({{0.5, 0.7}, {1.1, 0.8}}, 2500.0, 930.0, 140.0, 0.0));

	std::vector<unsigned int> N = {10, 20};
	Mesh mesh(10.0, N, materials, conditions);
	std::vector< std::vector<Volume> > *volumes = mesh.get_volumes();

	// std::cout << "TEST: " << (*volumes)[3][4].get_x()[0] << std::endl;

	std::vector< std::vector <std::vector<double> > > T; // time x (M+1) x (N+1)
	std::vector< std::vector<double> > Tmap, Tprev;
	double Tini = 8.0; // C

	Tprev.resize(N[0]+2, std::vector<double>(N[1]+2, Tini)); // initial T map
	// printMatrix(Tprev);

	double beta = 0.5; // Crank-Nicolson
	double tOver = 10000; // s
	double tDelta = 1; // s
	double t = 0; // s
	// std::vector<double>::size_type k;
	// while (t < tOver) {
	// 	k++;
	// 	t += tDelta;

	std::cout << "START" << std::endl;

	// std::cout << (*volumes)[0][0].neighbors.size() << " " << (*volumes)[0][0].neighbors[0].size() << std::endl;

	for (std::vector<double>::size_type i = 0; i < (*volumes).size(); i++) {
		for (std::vector<double>::size_type j = 0; j < (*volumes)[i].size(); j++) {
			std::cout << i << " " << j << std::endl;
			(*volumes)[i][j].set_neighbors({i, j}, (*volumes));
		}
	}

		std::cout << "SET UP DONE" << std::endl;
		
		for (std::vector<double>::size_type i = 0; i < (*volumes).size(); i++) {
			for (std::vector<double>::size_type j = 0; j < (*volumes)[i].size(); j++) {
				std::cout << i << " " << j << std::endl;
				(*volumes)[i][j].computeCoefficients(beta, tDelta, t, Tprev[i][j], {{Tprev[i-1][j], Tprev[i+1][j]}, {Tprev[i][j-1], Tprev[i][j+1]}});
			}
		}

		// mesh.evaluateKnownTemperatures();
		// mesh.solve();
		
	// }

	
	return 0;
}
