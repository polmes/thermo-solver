#include "volume.hpp"

class Mesh {
	private:
		const uint8_t M, N;
		std::vector< std::vector<Volume> > volumes; // 2D

	protected:
		// Sth else

	public:
		// Constructor
		Mesh(uint8_t _M, uint8_t _N);

		// Destructor
		// ~Mesh();

		// Methods
		void printMatrix();
};
