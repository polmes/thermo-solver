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

// Will read config file and get all consts

int main(int argc, char** argv) {
	if (argc < 1 || argc > 2) {
		throw std::invalid_argument("ERROR: Unexpected number of arguments.");
		return 1;
	}

	std::vector<Material> materials;
	// Material material;
	materials.push_back(Material({{0.0, 0.0}, {0.5, 0.4}}, 1500.0, 750.0, 170.0));
	materials.push_back(Material({{0.5, 0.0}, {1.1, 0.7}}, 1600.0, 770.0, 140.0));
	materials.push_back(Material({{0.0, 0.4}, {0.5, 0.8}}, 1900.0, 810.0, 200.0));

	materials.push_back(Material({{0.5, 0.7}, {1.1, 0.8}}, 2500.0, 930.0, 140.0));
	std::cout << "here" << std::endl;

	printMatrix(materials[0].get_boundaries());

	Mesh mesh({10, 20}, materials, 10);
	std::vector< std::vector<Volume> > *volumes = mesh.getVolumes();

	std::cout << (*volumes)[3][4].get_X()[0] << std::endl;
	// mesh.printMatrix();

	std::vector< std::vector <std::vector<double> > > T; // time x (M+1) x (N+1)
	std::vector< std::vector<double> > Tmap, Tprev;

	const double beta = 0.5; // Crank-Nicolson

	std::vector<double>size_type k;
	while (t < tFinish) {
		k++;
		t += tDelta;
		
		for (std::vector<double>::size_type i = 0; i < (*volumes).size(); i++) {
			for (std::vector<double>::size_type j = 0; j < (*volumes)[i].size(); j++) {
				(*volumes)[i][j].computeCoefficients(beta, )
			}
		}

		(*volumes).computeCoefficients(Tprev);

		
	}

	/*
	TODO
	- Parallelize everything we can
	- No more copies: either pass by reference or by pointer! (same for returns)
	*/
	return 0;
}
