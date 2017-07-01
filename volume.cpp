// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_VOLUME
	#include "volume.hpp"
	#define INCLUDE_VOLUME
#endif

Volume::Volume(std::vector<double> _x, Material _material, std::vector<double> X, std::vector<std::vector<double>::size_type> ij, std::vector<unsigned int> N) {
	x = _x;
	material = _material;
	S = {X[0] - X[1], X[2] - X[3]}; // E W N S
	V = S[0] * S[1] * depth;
	d = 

	if (ij[0] == 1) 
}

Volume::Volume() {}

std::vector<double> Volume::get_X() const {
	return x;
}

void Volume::computeAllCoefficients(const double &beta, const std::vector< std::vector<double> > &Tprev, const std::vector<Volume> &neighbors) {
	lambda_e = 

	aE = beta * lambda_e * S[0] / 
}

void Volume::computeTransientCoefficients() {

}

double Volume::computeLambda() {

}

Material Volume::get_material() const {
	return material;
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
