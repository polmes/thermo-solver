// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_VOLUME
	#include "volume.hpp"
	#define INCLUDE_VOLUME
#endif

Volume::Volume(std::vector<double> _x, Material _material): x(_x), material(_material) {}

std::vector<double> Volume::getX() {
	return x;
}

void Volume::getCoefficients(double &aE, double &aW, double &aN, double &aS, double &aP, double &bP) {

}
