// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_VOLUME
	#include "volume.hpp"
	#define INCLUDE_VOLUME
#endif

class Mesh {
	private:
		std::vector<unsigned int> N; // mesh size MxN (2D)
		double depth; // 3rd dimension
		std::vector< std::vector<double> > X; // global coordinates for mesh lines
		std::vector< std::vector<Volume> > volumes; // themselves

	public:
		// Constructor
		Mesh(const std::vector<unsigned int> &_N, const std::vector<Material> &materials, const double &_depth);

		// Getters
		std::vector< std::vector<Volume> >* get_volumes();

		// Methods
		const Material* findMaterial(const std::vector<double> &x, const std::vector<Material> &materials);
};
