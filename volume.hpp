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
		std::vector<double> x, S, d;
		double V;
		bool isUsed;

	protected:
		//

	public:
		// Constructor

		Volume(std::vector<double> _x, Material _material, std::vector<double> _S, double _V, bool _isBoundary);
		Volume();

		// Getters
		double get_aE() const;
		double get_aW() const;
		double get_aN() const;
		double get_aS() const;
		double get_aP() const;
		double get_bP() const;

		// Setters
		void set_aE(const double &_aE);
		void set_aW(const double &_aW);
		void set_aN(const double &_aN);
		void set_aS(const double &_aS);
		void set_aP(const double &_aP);
		void set_bP(const double &_bP);

		// Methods
		Material get_material() const;
		std::vector<double> get_X() const;
		// void computeCoefficients(double &aE, double &aW, double &aN, double &aS, double &aP, double &bP);
};
