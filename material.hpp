// Standard libraries
#include "headers.hpp"

class Material {
	private:
		std::vector< std::vector<double> > boundaries;
		double rho, cp, lambda, qv; // properties

	public:
		// Constructors
		Material(const std::vector< std::vector<double> > &_boundaries, const double &_rho, const double &_cp, const double &_lambda, const double &_qv);

		// Getters
		std::vector< std::vector<double> > get_boundaries() const;
		double get_cp() const;
		double get_rho() const;
		double get_lambda() const; // could have lambda as f(T)
		double get_qv() const; // could have qv as f(t) 
};
