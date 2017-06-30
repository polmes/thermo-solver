// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_VOLUME
	#include "volume.hpp"
	#define INCLUDE_VOLUME
#endif

class Mesh {
	private:
		// const unsigned int M, N;
		std::vector<unsigned int> N;
		std::vector< std::vector<Volume> > volumes; // 2D

		// Global coordinates
		std::vector< std::vector<double> > X; // boundaries
		std::vector< std::vector<double> > x; // nodes

	protected:
		// Sth else

	public:
		// Constructor
		Mesh(std::vector<unsigned int> _N, std::vector<Material> materials);

		// Destructor
		// ~Mesh();

		// Methods
		// void printMatrix();

		// regions
};
