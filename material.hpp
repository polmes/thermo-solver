// Standard libraries
#include "headers.hpp"

class Material {
	private:
		std::vector< std::vector<double> > boundaries;
		double rho, cp, lambda;

	public:
		// Constructor
		Material(const std::vector< std::vector<double> > &_boundaries, const double &_rho, const double &_cp, const double &_lambda);

		// Methods
		std::vector< std::vector<double> > get_boundaries() const;
		double get_cp() const;
		double get_rho() const;
		double get_lambda() const; // future: lambda as f(T)
};
