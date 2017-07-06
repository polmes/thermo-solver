// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_VOLUME
	#include "volume.hpp"
	#define INCLUDE_VOLUME
#endif
#ifndef INCLUDE_CONDITION
	#include "condition.hpp"
	#define INCLUDE_CONDITION
#endif

class Mesh {
	private:
		std::vector<unsigned int> N; // mesh size MxN (2D)
		double depth; // 3rd dimension
		std::vector< std::vector<double> > X; // global coordinates for mesh lines
		std::vector< std::vector<Node*> > volumes; // themselves: N[0]xN[1]
		// std::vector< std::vector<Condition> > conditions; // boundary conditions

	public:
		// Constructors
		Mesh(const double &_depth, const std::vector<unsigned int> &_N, const std::vector<Material> &materials, const std::vector< std::vector<Condition> > &_conditions);

		// Destructors
		// ~Mesh(); // delete dangling pointers

		// Getters
		std::vector< std::vector<Node*> >* get_volumes();

		// Methods
		const Material* findMaterial(const std::vector<double> &x, const std::vector<Material> &materials);
		void solve(std::vector< std::vector<double> > &T);
};
