// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_VOLUME
	#include "volume.hpp"
	#define INCLUDE_VOLUME
#endif
#ifndef INCLUDE_UTIL
	#include "util.hpp"
	#define INCLUDE_UTIL
#endif

Volume::Volume(const std::vector< std::vector<double> > &X, const double &depth, const std::vector<std::vector<double>::size_type> &ij, const std::vector<unsigned int> &N, const std::vector< std::vector<Condition> > &_conditions) {
	x = {(X[0][0] + X[0][1]) / 2, (X[1][0] + X[1][1]) / 2};
	d = {x[0] - X[0][0], x[1] - X[1][0]};
	S = {2 * d[1] * depth, 2 * d[0] * depth};
	V = (2 * d[0]) * (2 * d[1]) * depth;
	
	isBoundary = false;
	conditions.resize(N.size(), std::vector<const Condition*>(N.size(), nullptr)); // {{W, E}, {S, N}}
	for (std::vector<unsigned int>::size_type i = 0; i < N.size(); i++) {
		if (ij[i] == 0) {
			conditions[i][0] = &_conditions[i][0];
			isBoundary = true;
		} else if (ij[i] == N[i]) {
			conditions[i][1] = &_conditions[i][1];
			isBoundary = true;
		}
	}

	// Initialize coefficients
	neighbors.resize(N.size(), std::vector<const Volume*>(N.size(), nullptr));
	std::cout << neighbors.size() << " " << neighbors[0].size() << std::endl;
	std::cout << neighbors[0][0] << " " << neighbors[0][1] << std::endl;

	aP = bP = 0.0;
	a = {{0.0, 0.0}, {0.0, 0.0}};
}

Volume::~Volume() {
	std::vector<const Condition*>::size_type size, sizes;
	sizes = conditions.size();
	for (std::vector<const Condition*>::size_type i = 0; i < sizes; i++) {
		size = conditions[i].size();
		for (std::vector<const Condition*>::size_type j = 0; j < size; j++) {
			delete conditions[i][j];
			delete neighbors[i][j];
		}
	}
}

std::vector<double> Volume::get_x() const {
	return x;
}

std::vector<double> Volume::get_d() const {
	return d;
}

double Volume::get_V() const {
	return V;
}

const Material* Volume::get_material() const {
	return material;
}

void Volume::set_material(const Material *_material) {
	material = _material;
}

void Volume::set_neighbors(const std::vector<std::vector<double>::size_type> &ij, const std::vector< std::vector<Volume> > &volumes) {
	std::cout << "SETTING UP" << std::endl;
	std::cout << conditions.size() << std::endl;
	neighbors.resize(2);
	std::cout << neighbors.size() << std::endl;
	neighbors[0].resize(2);
	std::cout << neighbors[0].size() << std::endl;
	// neighbors.resize(conditions.size());

	// std::cout << "AGAIN" << std::endl;
	// std::cout << &(volumes[0][0]) << std::endl;
	// // neighbors.push_back()
	// std::cout << "0SZ: " << neighbors[0].size() << std::endl;
	// std::vector<const Volume*> test;
	// neighbors.resize(neighbors.size(), std::vector<const Volume*>(neighbors.size(), nullptr));

	// test.push_back(&(volumes[0][0]));
	// std::cout << "test" << std::endl;
	// neighbors.push_back(test);
	// std::cout << "NOPE" << std::endl;

	// for (std::vector<const Volume*>::size_type i = 0; i < neighbors.size(); i++) {
	// 	// neighbors[i].resize(conditions[i].size());
	// 	std::vector<const Volume*> neighbors1D;
	// 	for (std::vector<const Volume*>::size_type j = 0; j < neighbors[i].size(); j++) {
	// 		std::cout << "here" << std::endl;
	// 		if (conditions[i][j] == NULL) {
	// 			std::cout << "there" << std::endl;
	// 			if (i == 0) {
	// 				std::cout << "tthere" << std::endl;
	// 				if (j == 0) neighbors1D.emplace_back(&(volumes[ij[0]-1][ij[1]]));
	// 				else neighbors1D.emplace_back(&(volumes[ij[0]+1][ij[1]])); // j == 1
	// 			} else { // i == 1
	// 				if (j == 0) neighbors1D.emplace_back(&(volumes[ij[0]][ij[1]-1]));
	// 				else neighbors1D.emplace_back(&(volumes[ij[0]][ij[1]+1])); // j == 1
	// 			}
	// 		} else {
	// 			std::cout << "also" << std::endl;
	// 			neighbors1D.push_back(nullptr);
	// 		}
	// 	}
	// 	std::cout << "final push" << std::endl;
	// 	neighbors.push_back(neighbors1D);
	// 	std::cout << "final push" << std::endl;
	// }
}

void Volume::computeCoefficients(const double &beta, const double &tDelta, const double &t, const double &Tprev, const std::vector< std::vector<double> > &Tneighbors) {

	// Inner volumes
	if (!isBoundary) {
		std::cout << "INNER" << std::endl;

		aP = this->get_material()->get_rho() * this->get_material()->get_cp() * this->get_V() / tDelta;
		bP = this->get_material()->get_rho() * this->get_material()->get_cp() * this->get_V() * Tprev / tDelta + beta * this->get_material()->get_qv() * this->get_V();

		for (std::vector<Volume>::size_type i = 0; i < neighbors.size(); i++) {
			for (std::vector<Volume>::size_type j = 0; j < neighbors[i].size(); j++) {
				a[i][j] = this->computeLambda(i, *neighbors[i][j]) * S[i] / (this->get_d()[i] + neighbors[i][j]->get_d()[i]);
				bP += (1 - beta) * a[i][j] * (Tneighbors[i][j] - Tprev);
				a[i][j] = beta * a[i][j];
				aP += a[i][j];
			}
		}
	}

	// Boundary volumes
	else {
		std::cout << "OUTER" << std::endl;
		std::cout << "CONDITIONS SIZE: " << conditions.size() << std::endl;

		// Isotherm
		bP = 0.0;
		unsigned int k = 0;
		for (std::vector<Condition*>::size_type i = 0; i < conditions.size(); i++) {
			for (std::vector<Condition*>::size_type j = 0; j < conditions[i].size(); j++) {
				if (conditions[i][j] != NULL && conditions[i][j]->get_conditionType() == ISOTHERM) {
					std::cout << "made it" << std::endl;
					bP += conditions[i][j]->get_T(t);
					k++;
				}
			}
		}
		if (k > 0) {
			aP = 1.0;
			bP = bP/k; // average if is a corner volume
			a = {{0.0, 0.0}, {0.0, 0.0}};
		}

		// Convection & Qflow
		else { // k == 0
			aP = this->get_material()->get_rho() * this->get_material()->get_cp() * this->get_V() / tDelta;
			bP = this->get_material()->get_rho() * this->get_material()->get_cp() * this->get_V() * Tprev / tDelta + beta * this->get_material()->get_qv() * this->get_V();

			for (std::vector<Volume>::size_type i = 0; i < conditions.size(); i++) { // neighbors.size()
				for (std::vector<Volume>::size_type j = 0; j < conditions[i].size(); j++) { // neighbors[i].size()		// Inner side
					if (conditions[i][j] == NULL) {
						a[i][j] = this->computeLambda(i, *neighbors[i][j]) * S[i] / (this->get_d()[i] + neighbors[i][j]->get_d()[i]);
						bP += (1 - beta) * a[i][j] * (Tneighbors[i][j] - Tprev);
						a[i][j] = beta * a[i][j];
						aP += a[i][j];
					}

					// Boundary side
					else {
						a[i][j] = 0;
						if (conditions[i][j]->get_conditionType() == CONVECTION) {
							aP += beta * conditions[i][j]->get_alpha() * S[i];
							bP += aP * conditions[i][j]->get_Tg() + (1 - beta) * conditions[i][j]->get_alpha() * (conditions[i][j]->get_Tg() - Tprev) * S[i];
						}
						else if (conditions[i][j]->get_conditionType() == FLOW) {
							bP += conditions[i][j]->get_Qflow() * this->get_d()[!i] * 2; // beta * Qflow + (1 - beta) * Qflow
						}
					}
				}
			}
		}
	}

	std::cout << "aP = " << aP << std::endl;
	std::cout << "bP = " << bP << std::endl;
	printMatrix(a);
}

double Volume::computeLambda(const std::vector<Volume>::size_type &i, const Volume &neighbor) {
	return (this->get_d()[i] + neighbor.get_d()[i]) / (this->get_d()[i]/this->get_material()->get_lambda() + neighbor.get_d()[i]/neighbor.get_material()->get_lambda());
}
