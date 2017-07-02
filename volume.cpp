// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_VOLUME
	#include "volume.hpp"
	#define INCLUDE_VOLUME
#endif

Volume::Volume(const std::vector< std::vector<double> > &X, const double &depth, const std::vector<std::vector<double>::size_type> &ij, const std::vector<unsigned int> &N) {
	x = {(X[0][0] + X[0][1]) / 2, (X[1][0] + X[1][1]) / 2};
	d = {x[0] - X[0][0], x[1] - X[1][0]};
	S = {2 * d[1] * depth, 2 * d[0] * depth};
	V = (2 * d[0]) * (2 * d[1]) * depth;
	
	isBoundary = {{false, false}, {false, false}}; // {{W, E}, {S, N}}
	for (std::vector<unsigned int>::size_type i = 0; i < N.size(); i++) {
		if (ij[i] == 0) isBoundary[i][0] = true;
		else if (ij[i] == N[i]) isBoundary[i][1] = true;
	}
}

std::vector<double> Volume::get_x() const {
	return x;
}

const Material* Volume::get_material() const {
	return material;
}

void Volume::set_material(const Material *_material) {
	material = _material;
}

double Volume::get_aE() const {
	return aE;
}

void Volume::set_aE(const double &_aE) {
	aE = _aE;
}

double Volume::get_aW() const {
	return aW;
}

void Volume::set_aW(const double &_aW) {
	aW = _aW;
}

double Volume::get_aN() const {
	return aN;
}

void Volume::set_aN(const double &_aN) {
	aN = _aN;
}

double Volume::get_aS() const {
	return aS;
}

void Volume::set_aS(const double &_aS) {
	aS = _aS;
}

double Volume::get_aP() const {
	return aP;
}

void Volume::set_aP(const double &_aP) {
	aP = _aP;
}

double Volume::get_bP() const {
	return bP;
}

void Volume::set_bP(const double &_bP) {
	bP = _bP;
}

// void Volume::computeAllCoefficients(const std::vector< std::vector<Volume> > &neighbors, const double &beta, const double &tDelta, const double &t, const double &tPrev) {
// 	std::vector< std::vector<double> > lambdas;

// 	for (std::vector<Volume>::size_type i = 0; i < neighbors.size(); i++) {
// 		for (std::vector<Volume>::size_type j = 0; j < neighbors[i].size(); j++) {
// 			lambdas[i][j] = (this->get_d()[i] + neighbors[i][j].get_d()[i]) / (this->get_d()[i]/this->get_material().get_lambda() + neighbors[i][j].get_d()[i]/neighbors[i][j].get_material().get_lambda());
// 		}
// 	}

// 	aW = beta * lambdas[0][0] * S[0] / (this->get_d()[0] + neighbors[0][0].get_d()[0]);
// 	aE = beta * lambdas[0][1] * S[0] / (this->get_d()[0] + neighbors[0][1].get_d()[0]);
// 	aS = beta * lambdas[1][0] * S[1] / (this->get_d()[1] + neighbors[1][0].get_d()[1]);
// 	aN = beta * lambdas[1][1] * S[1] / (this->get_d()[1] + neighbors[1][1].get_d()[1]);

// 	bP = this->get_material().get_rho() * this->get_material().get_cp() * this->get_V() * this->get_Tprev() / tDelta + beta * this->get_material().get_qv(t) * this->get_V() + (1 - beta) * (aE * (neighbors[0][1].get_Tprev() - this->get_Tprev()) - aW * (this->get_Tprev() - neighbors[0][0].get_Tprev()) + aN * (neighbors[1][1].get_Tprev() - this->get_Tprev()) - aS * (this->get_Tprev() - neighbors[1][0].get_Tprev()) + this->get_qv(tPrev) * this->get_V());

// 	aW = beta * aW;
// 	aE = beta * aE;
// 	aS = beta * aS;
// 	aN = beta * aN;

// 	aP = this->get_material().get_rho() * this->get_material().get_cp() * this->get_V() / tDelta + aW + aE + aS + aN;
// }

void Volume::computeTransientCoefficients() {

}

std::vector< std::vector<double> > Volume::computeLambdas() {

}
