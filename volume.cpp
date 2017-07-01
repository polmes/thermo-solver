// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_VOLUME
	#include "volume.hpp"
	#define INCLUDE_VOLUME
#endif

Volume::Volume(std::vector<double> _x, Material _material, std::vector<double> _S, double _V): x(_x), material(_material), S(_S), V(_V) {}

std::vector<double> Volume::getX() {
	return x;
}

void Volume::computeCoefficients(std::vector< std::vector<double> >* Tprev) {
	aE = 
}

double Volume::get_aE() {
	return aE;
}

void Volume::set_aE(const double& _aE) {
	aE = _aE;
}

double Volume::get_aW() {
	return aW;
}

void Volume::set_aW(const double& _aW) {
	aW = _aW;
}

double Volume::get_aN() {
	return aN;
}

void Volume::set_aN(const double& _aN) {
	aN = _aN;
}

double Volume::get_aS() {
	return aS;
}

void Volume::set_aS(const double& _aS) {
	aS = _aS;
}

double Volume::get_aP() {
	return aP;
}

void Volume::set_aP(const double& _aP) {
	aP = _aP;
}

double Volume::get_bP() {
	return bP;
}

void Volume::set_bP(const double& _bP) {
	bP = _bP;
}
