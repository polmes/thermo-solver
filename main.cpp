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
 */

int main(int argc, char** argv) {
	std::cout << "Welcome!" << std::endl;

	if (argc < 1 || argc > 2) {
		throw std::invalid_argument("ERROR: Unexpected number of arguments.");
		return 1;
	}

	/* Here will read config file (either default or provided by the user) and get all parameters */

	std::cout << "Setting up...";

	// Boundary conditions
	// std::vector< std::vector<Condition> > conditions = {{Condition(ISOTHERM, 300.0), Condition(ISOTHERM, 200.0)}, {Condition(FLOW, 0.0), Condition(FLOW, 0.0)}};
	// std::vector< std::vector<Condition> > conditions = {{Condition(FLOW, 0.0), Condition(FLOW, 0.0)}, {Condition(ISOTHERM, 300.0), Condition(ISOTHERM, 200.0)}};
	// std::vector< std::vector<Condition> > conditions = {{Condition(FLOW, 0.0), Condition(FLOW, 0.0)}, {Condition(ISOTHERM, 300.0), Condition(CONVECTION, 10.0, 350.0)}};
	std::vector< std::vector<Condition> > conditions = {{Condition(CONVECTION, 9.0, 306.15), Condition(ISOTHERM, 281.15, 0.005)}, {Condition(ISOTHERM, 296.15), Condition(FLOW, -60.0)}};

	// Material properties
	std::vector<Material> materials;
	// materials.push_back(Material({{0.0, 0.0}, {1.1, 0.8}}, 1500.0, 750.0, 170.0, 0.0));
	materials.push_back(Material({{0.0, 0.0}, {0.5, 0.4}}, 1500.0, 750.0, 170.0, 0.0));
	materials.push_back(Material({{0.5, 0.0}, {1.1, 0.7}}, 1600.0, 770.0, 140.0, 0.0));
	materials.push_back(Material({{0.0, 0.4}, {0.5, 0.8}}, 1900.0, 810.0, 200.0, 0.0));
	materials.push_back(Material({{0.5, 0.7}, {1.1, 0.8}}, 2500.0, 930.0, 140.0, 0.0));

	// Mesh discretization
	std::vector<unsigned int> N = {110, 80};
	Mesh mesh(1.0, N, materials, conditions);
	std::vector< std::vector<Volume> > *volumes = mesh.get_volumes();

	// Setup missing parameters
	for (std::vector<double>::size_type i = 0; i < (*volumes).size(); i++) {
		for (std::vector<double>::size_type j = 0; j < (*volumes)[i].size(); j++) {
			(*volumes)[i][j].set_neighbors({i, j}, (*volumes));
		}
	}

	std::cout << " and done." << std::endl;

	// Temperature fields
	std::vector< std::vector <std::vector<double> > > T; // time x N[0] x N[1]
	std::vector< std::vector<double> > Tmap, Tprev; // "supposed" T map, T map from previous time

	// Numeric variables
	double beta = 1; // implicit // 0.5; // Crank-Nicolson
	double tDelta = 1.0; // s
	double delta = 0.0000001; // precision: 1e-7
	bool convergence;

	// Time
	double tOver = 100.0; // 5000.0; // s
	double t = 0.0; // s
	T.resize(int(tOver/tDelta)+1);

	// Initial temperature
	double Tini = 281.15; // K
	T[0].resize(N[0]+2, std::vector<double>(N[1]+2, Tini)); // initial T map

	std::vector<double>::size_type k = 1;
	while (t < tOver) {
		t += tDelta;
		// std::cout << "New iteration at t = " << t << "s...";
		
		// Coefficients are only time-dependent (they are temperature-independent for this case)
		Tprev = T[k-1];
		for (std::vector<double>::size_type i = 0; i < (*volumes).size(); i++) {
			for (std::vector<double>::size_type j = 0; j < (*volumes)[i].size(); j++) {
				// std::cout << "{" << i << ", " << j << "}" << std::endl;
				(*volumes)[i][j].computeCoefficients(beta, tDelta, t, Tprev[i+1][j+1], {{Tprev[i][j+1], Tprev[i+2][j+1]}, {Tprev[i+1][j], Tprev[i+1][j+2]}});
			}
		}

		Tmap = Tprev;
		convergence = false;
		while (!convergence) {
			T[k] = Tmap;
			mesh.solve(T[k]); // modifies T map via reference
			convergence = checkConvergence(T[k], Tmap, delta);
			Tmap = T[k];
		}

		// std::cout << " and converged." << std::endl;
		k++;
	}
	std::cout << std::endl;

	// Print some results
	std::cout << "T at t = 5000s" << std::endl;
	printMatrix(T[100]);

	std::cout << "Bye-bye." << std::endl;
	return 0;
}
