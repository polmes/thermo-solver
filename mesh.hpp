// My libraries
#include "volume.hpp"
#include "util.cpp"

class Mesh {
	private:
		const unsigned int M, N;
		std::vector< std::vector<Volume> > volumes; // 2D

		// Global coordinates
		std::vector< std::vector<double> > X; // boundaries
		std::vector< std::vector<double> > x; // nodes

	protected:
		// Sth else

	public:
		// Constructor
		Mesh(unsigned int _M, unsigned int _N, std::vector<Material> materials);

		// Destructor
		// ~Mesh();

		// Methods
		void printMatrix();

		// regions
};
