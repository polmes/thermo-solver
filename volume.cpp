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

Node::Node() {
	// No need to implement anything
}

Node::Node(const std::vector<double> &_x) {
	x = _x;

	// Initialize coefficients
	aP = bP = 0.0;
	a = {{0.0, 0.0}, {0.0, 0.0}};
}

Volume::Volume(const std::vector< std::vector<double> > &X, const double &depth) {
	x = {(X[0][0] + X[0][1]) / 2, (X[1][0] + X[1][1]) / 2};
	d = {x[0] - X[0][0], x[1] - X[1][0]};
	S = {2 * d[1] * depth, 2 * d[0] * depth};
	V = (2 * d[0]) * (2 * d[1]) * depth;

	// Initialize coefficients
	aP = bP = 0.0;
	a = {{0.0, 0.0}, {0.0, 0.0}};
}

Boundary::Boundary(const std::vector<double> &_x, const Condition &_condition) {
	x = _x;
	d = {0, 0}; // will make computeCoefficients so much easier :)

	// Boundary condition
	condition = &_condition;

	// Initialize coefficients
	aP = bP = 0.0;
	a = {{0.0, 0.0}, {0.0, 0.0}};
}

// Volume::~Volume() {
// 	std::vector<const Condition*>::size_type size, sizes;
// 	sizes = conditions.size();
// 	for (std::vector<const Condition*>::size_type i = 0; i < sizes; i++) {
// 		size = conditions[i].size();
// 		for (std::vector<const Condition*>::size_type j = 0; j < size; j++) {
// 			delete conditions[i][j];
// 			delete neighbors[i][j];
// 		}
// 	}
// }

// double Volume::get_depth() const {
// 	return (*depth);
// }

std::vector<double> Node::get_x() const {
	return x;
}

std::vector<double> Node::get_d() const {
	return d;
}

const Material* Node::get_material() const {
	return material;
}

void Node::set_material(const Material *_material) {
	material = _material;
}

double Volume::get_V() const {
	return V;
}

void Node::set_neighbors(const std::vector<std::vector<Node*>::size_type> &ij, const std::vector< std::vector<Node*> > &volumes) {
	// No need to implement anything
}

void Volume::set_neighbors(const std::vector<std::vector<Node*>::size_type> &ij, const std::vector< std::vector<Node*> > &volumes) {
	neighbors = {{volumes[ij[0]-1][ij[1]], volumes[ij[0]+1][ij[1]]}, {volumes[ij[0]][ij[1]-1], volumes[ij[0]][ij[1]+1]}};
	
	// std::cout << "NEIGHBORS" << std::endl;
	// printMatrix(neighbors);
}

void Boundary::set_neighbors(const std::vector<std::vector<Node*>::size_type> &ij, const std::vector< std::vector<Node*> > &volumes) {
	// Since we cannot have ij[0] == ij[1]...
	if (ij[0] == 0) { // left
		neighbor = volumes[1][ij[1]];
		neighbors = {{0, 1}, {0, 0}};
	} else if (ij[0] == volumes.size()-1) { // right
		neighbor = volumes[ij[0]-1][ij[1]];
		neighbors = {{1, 0}, {0, 0}};
	} else if (ij[1] == 0) { // bottom
		neighbor = volumes[ij[0]][1];
		neighbors = {{0, 0}, {0, 1}};
	} else if (ij[1] == volumes[ij[0]].size()-1) { // top
		neighbor = volumes[ij[0]][ij[1]-1];
		neighbors = {{0, 0}, {1, 0}};
	}
}

void Node::computeCoefficients(const double &beta, const double &tDelta, const double &t, const double &Tprev, const std::vector< std::vector<double> > &Tneighbors) {
	// No need to implement anything

	std::cout << "CORNER" << std::endl;
	std::cout << "aP = " << aP << std::endl;
	std::cout << "bP = " << bP << std::endl;
	printMatrix(a);
}

void Volume::computeCoefficients(const double &beta, const double &tDelta, const double &t, const double &Tprev, const std::vector< std::vector<double> > &Tneighbors) {
	// Inner volumes
	std::cout << "INNER" << std::endl;

	aP = this->get_material()->get_rho() * this->get_material()->get_cp() * this->get_V() / tDelta;
	bP = aP * Tprev + beta * this->get_material()->get_qv() * this->get_V();

	for (std::vector<Volume>::size_type i = 0; i < neighbors.size(); i++) {
		for (std::vector<Volume>::size_type j = 0; j < neighbors[i].size(); j++) {
			a[i][j] = this->computeLambda(i, *neighbors[i][j]) * S[i] / (this->get_d()[i] + neighbors[i][j]->get_d()[i]);
			bP += (1 - beta) * a[i][j] * (Tneighbors[i][j] - Tprev);
			a[i][j] = beta * a[i][j];
			aP += a[i][j];
		}
	}

	std::cout << "aP = " << aP << std::endl;
	std::cout << "bP = " << bP << std::endl;
	printMatrix(a);
}

void Boundary::computeCoefficients(const double &beta, const double &tDelta, const double &t, const double &Tprev, const std::vector< std::vector<double> > &Tneighbors) {
	// Boundary volumes
	std::cout << "BOUNDARY" << std::endl;

	// Isotherm
	if (condition->get_conditionType() == ISOTHERM) {
		aP = 1.0;
		bP = condition->get_T(t);
		a = {{0.0, 0.0}, {0.0, 0.0}};
	}

	// Others
	else {
		// Convection
		if (condition->get_conditionType() == CONVECTION) {
			aP = condition->get_alpha();
			bP = aP * condition->get_Tg();
		}
		// Qflow
		else if (condition->get_conditionType() == FLOW) {
			aP = 0;
			bP = condition->get_Qflow(); // > 0 in; < 0 out
		}
		for (std::vector<bool>::size_type i = 0; i < neighbors.size(); i++) {
			for (std::vector<bool>::size_type j = 0; j < neighbors[i].size(); j++) {
				if (neighbors[i][j]) {
					a[i][j] = neighbor->get_material()->get_lambda() / neighbor->get_d()[i];
					aP += a[i][j];
				}
			}
		}
	}

	std::cout << "aP = " << aP << std::endl;
	std::cout << "bP = " << bP << std::endl;
	printMatrix(a);
}

double Volume::computeLambda(const std::vector<Volume>::size_type &i, const Node &neighbor) {
	return (this->get_d()[i] + neighbor.get_d()[i]) / (this->get_d()[i]/this->get_material()->get_lambda() + neighbor.get_d()[i]/neighbor.get_material()->get_lambda());
}

double Node::get_aP() const {
	return aP;
}

double Node::get_aW() const {
	return a[0][0];
}

double Node::get_aE() const {
	return a[0][1];
}

double Node::get_aS() const {
	return a[1][0];
}

double Node::get_aN() const {
	return a[1][1];
}

double Node::get_bP() const {
	return bP;
}
