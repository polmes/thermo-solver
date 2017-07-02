// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_MATERIAL
	#include "material.hpp"
	#define INCLUDE_MATERIAL
#endif

class Volume {
	private:
		std::vector<double> x; // node coordinates
		std::vector<double> S; // {vertical, horizontal} areas
		std::vector<double> d; // {horizontal, vertical} distance to volume boundary
		std::vector< std::vector<bool> > isBoundary; // {{W, E}, {S, N}}
		double V; // volume volume
		const Material *material;
		double aE, aW, aN, aS, aP, bP; // coefficients

	public:
		// Constructor
		Volume(const std::vector< std::vector<double> > &X, const double &depth, const std::vector<std::vector<double>::size_type> &ij, const std::vector<unsigned int> &N);

		// Getters
		double get_aE() const;
		double get_aW() const;
		double get_aN() const;
		double get_aS() const;
		double get_aP() const;
		double get_bP() const;
		std::vector<double> get_x() const;
		const Material* get_material() const;

		// Setters
		void set_aE(const double &_aE);
		void set_aW(const double &_aW);
		void set_aN(const double &_aN);
		void set_aS(const double &_aS);
		void set_aP(const double &_aP);
		void set_bP(const double &_bP);
		void set_material(const Material *_material);

		// Methods
		void computeAllCoefficients(const std::vector< std::vector<Volume> > &neighbors, const double &beta, const double &tDelta, const double &t, const double &tPrev);
		void computeTransientCoefficients();
		std::vector< std::vector<double> > computeLambdas();
};
