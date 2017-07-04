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

	// Boundary conditions
	std::vector< std::vector<Condition> > conditions = {{Condition(CONVECTION, 9.0, 306.15), Condition(ISOTHERM, 281.15, 0.005)}, {Condition(ISOTHERM, 296.15), Condition(FLOW, 60.0)}};

	// Material properties
	std::vector<Material> materials;
	materials.push_back(Material({{0.0, 0.0}, {0.5, 0.4}}, 1500.0, 750.0, 170.0, 0.0));
	materials.push_back(Material({{0.5, 0.0}, {1.1, 0.7}}, 1600.0, 770.0, 140.0, 0.0));
	materials.push_back(Material({{0.0, 0.4}, {0.5, 0.8}}, 1900.0, 810.0, 200.0, 0.0));
	materials.push_back(Material({{0.5, 0.7}, {1.1, 0.8}}, 2500.0, 930.0, 140.0, 0.0));

	// Mesh discretization
	std::vector<unsigned int> N = {10, 10};
	Mesh mesh(1000.0, N, materials, conditions);
	std::vector< std::vector<Volume> > *volumes = mesh.get_volumes();

	// Setup missing parameters
	for (std::vector<double>::size_type i = 0; i < (*volumes).size(); i++) {
		for (std::vector<double>::size_type j = 0; j < (*volumes)[i].size(); j++) {
			(*volumes)[i][j].set_neighbors({i, j}, (*volumes));
		}
	}

	std::cout << "SET UP DONE" << std::endl;

	// Temperature fields
	std::vector< std::vector <std::vector<double> > > T; // time x N[0] x N[1]
	std::vector< std::vector<double> > Tmap, Tprev; // "invented" T map, T map from previous time

	// Initial temperature
	double Tini = 281.15; // K 8.0; // C
	Tprev.resize(N[0]+2, std::vector<double>(N[1]+2, Tini)); // initial T map
	// printMatrix(Tprev);

	// Numeric variables
	double beta = 1; // 0.5; // Crank-Nicolson
	double tDelta = 1.0; // s
	double delta = 0.0000001; // precision: 1e-7
	bool convergence;

	// Time
	double tOver = 10000.0; // s
	double t = 0.0; // s
	T.resize(int(tOver/tDelta)+1);
	T[0] = Tprev;

	std::vector<double>::size_type k = 1;
	while (t < tOver) {
		t += tDelta;
		std::cout << "New time iteration at t = " << t << "s";

		Tprev = T[k-1];
		
		// Coefficients are only time-dependant (they are temperature-independant)
		for (std::vector<double>::size_type i = 0; i < (*volumes).size(); i++) {
			for (std::vector<double>::size_type j = 0; j < (*volumes)[i].size(); j++) {
				(*volumes)[i][j].computeCoefficients(beta, tDelta, t, Tprev[i+1][j+1], {{Tprev[i][j+1], Tprev[i+2][j+1]}, {Tprev[i+1][j], Tprev[i+1][j+2]}});
			}
		}

		
		Tmap = Tprev;

		convergence = false;
		// c = 0;
		while (!convergence) {
			// c++;
			T[k] = Tmap;
			mesh.solve(T[k]); // modifies T map
			convergence = checkConvergence(T[k], Tmap, delta);
			std::cout << convergence << std::endl;
			Tmap = T[k];
			printMatrix(T[k]);
			// if (c == 1) {
			// 	std::cout << "Tp[0][0] = " << T[1][0][0] << std::endl;
			// 	std::cout << "Tp[0][1] = " << T[1][0][1] << std::endl;
			// 	std::cout << "Tp[1][0] = " << T[1][1][0] << std::endl;
			// 	std::cout << "Tp[1][1] = " << T[1][1][1] << std::endl;
			// }
		}

		// if (c >= 100) std::cout << "No convergence :(" << std::endl;

		// mesh.evaluateKnownTemperatures();
		// mesh.solve();

		k++;


	}

	std::cout << "END" << std::endl;
	
	return 0;
}
