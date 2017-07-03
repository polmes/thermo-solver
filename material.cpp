// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_MATERIAL
	#include "material.hpp"
	#define INCLUDE_MATERIAL
#endif

Material::Material(const std::vector< std::vector<double> > &_boundaries, const double &_rho, const double &_cp, const double &_lambda, const double &_qv) {
	boundaries = _boundaries;
	rho = _rho;
	cp = _cp;
	lambda = _lambda;
	qv = _qv;
} // would need to use initialization list if we used const members

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

double Material::get_qv() const {
	return qv;
}
