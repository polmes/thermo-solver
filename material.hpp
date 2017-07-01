// Standard libraries
#include "headers.hpp"

class Material {
	private:
		std::vector< std::vector<double> > boundaries;
		double rho, cp, lambda;

	public:
		// Constructor
		Material(std::vector< std::vector<double> > _boundaries, double _rho, double _cp, double _lambda);

		// Methods
		std::vector< std::vector<double> > get_boundaries();
		double get_cp(), get_rho(), get_lambda(); // future: lambda as f(T)
};
