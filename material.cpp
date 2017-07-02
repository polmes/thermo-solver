// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_MATERIAL
	#include "material.hpp"
	#define INCLUDE_MATERIAL
#endif

Material::Material(const std::vector< std::vector<double> > &_boundaries, const double &_rho, const double &_cp, const double &_lambda) {
	boundaries = _boundaries;
	rho = _rho;
	cp = _cp;
	lambda = _lambda;
} // would need initialization list if we used const members

std::vector< std::vector<double> > Material::get_boundaries() const {
	return boundaries;
}

double Material::get_cp() const {
	return cp;
}

double Material::get_rho() const {
	return rho;
}

double Material::get_lambda() const {
	return lambda;
}
