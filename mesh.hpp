// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_VOLUME
	#include "volume.hpp"
	#define INCLUDE_VOLUME
#endif

class Mesh {
	private:
		const std::vector<unsigned int> N; // MxN (2D)
		std::vector< std::vector<Volume> > volumes;

		// Global coordinates
		std::vector< std::vector<double> > X; // boundaries
		double depth;

	protected:
		// Sth else

	public:
		// Constructor
		Mesh(std::vector<unsigned int> _N, std::vector<Material> materials, double _depth);

		// Destructor
		// ~Mesh();

		// Methods
		Material findMaterial(std::vector<double> x, std::vector<Material> materials);
		std::vector< std::vector<Volume> >* getVolumes();
		// regions
};
