// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_MATERIAL
	#include "material.hpp"
	#define INCLUDE_MATERIAL
#endif

class Volume {
	private:
		// static const int M, N; // shared by all Volume instances
		double aE, aW, aN, aS, aP, bP;
		Material material;
		bool isBoundary; // boundary = 'w' 'e' 'n' 's' 0
		std::vector<double> x;

	protected:
		//

	public:
		// Constructor
		Volume(Material _material);
};
