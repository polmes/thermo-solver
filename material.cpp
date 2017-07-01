// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_MATERIAL
	#include "material.hpp"
	#define INCLUDE_MATERIAL
#endif

Material::Material(std::vector< std::vector<double> > _boundaries, double _rho, double _cp, double _lambda): boundaries(_boundaries), rho(_rho), cp(_cp), lambda(_lambda) {}

std::vector< std::vector<double> > Material::get_boundaries() {
	return boundaries;
}

double Material::get_cp() {
	return cp;
}

double Material::get_rho() {
	return rho;
}

double Material::get_lambda() {
	return lambda;
}
