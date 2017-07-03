// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_MATERIAL
	#include "material.hpp"
	#define INCLUDE_MATERIAL
#endif
#ifndef INCLUDE_CONDITION
	#include "condition.hpp"
	#define INCLUDE_CONDITION
#endif

class Volume {
	private:
		std::vector<double> x; // node coordinates
		std::vector<double> S; // {vertical, horizontal} areas
		std::vector<double> d; // {horizontal, vertical} distance to volume boundary
		std::vector< std::vector<const Condition*> > conditions; // {{W, E}, {S, N}}
		bool isBoundary; // is this a boundary (outer) volume?
		double V; // volume volume
		const Material *material; // material properties: rho, cp, lambda, qv
		double aP, bP; // coefficients
		std::vector< std::vector<double> > a; // more coefficients: {{aW, aE}, {aS, aN}}
		std::vector< std::vector<const Volume*> > neighbors; // surrounding volumes

	public:
		// Constructors
		Volume(const std::vector< std::vector<double> > &X, const double &depth, const std::vector<std::vector<double>::size_type> &ij, const std::vector<unsigned int> &N, const std::vector< std::vector<Condition> > &_conditions);

		// Destructors
		// ~Volume(); // must delete pointers

		// Getters
		std::vector<double> get_x() const;
		std::vector<double> get_d() const;
		double get_V() const;
		const Material* get_material() const;

		// Setters
		void set_material(const Material *_material);
		void set_neighbors(const std::vector<std::vector<double>::size_type> &ij, const std::vector< std::vector<Volume> > &volumes);

		// Methods
		void computeCoefficients(const double &beta, const double &tDelta, const double &t, const double &Tprev, const std::vector< std::vector<double> > &Tneighbors);
		double computeLambda(const std::vector<Volume>::size_type &i, const Volume &neighbor);
};
