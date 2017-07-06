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

class Node {
	private:
		const Material *material; // material properties: rho, cp, lambda, qv

	protected:
		std::vector<double> x; // node coordinates
		std::vector<double> d; // {horizontal, vertical} distance to "volume" boundary
		double aP, bP; // some coefficients
		std::vector< std::vector<double> > a; // more coefficients: {{aW, aE}, {aS, aN}}

	public:
		// Constructors
		Node();
		Node(const std::vector<double> &_x);

		// Getters
		std::vector<double> get_x() const;
		std::vector<double> get_d() const;
		const Material* get_material() const;
		double get_aP() const;
		double get_aW() const;
		double get_aE() const;
		double get_aS() const;
		double get_aN() const;
		double get_bP() const;

		// Setters
		void set_material(const Material *_material);
		virtual void set_neighbors(const std::vector<std::vector<double>::size_type> &ij, const std::vector< std::vector<Node*> > &volumes);

		// Methods
		virtual void computeCoefficients(const double &beta, const double &tDelta, const double &t, const double &Tprev, const std::vector< std::vector<double> > &Tneighbors);
};

class Volume: public Node {
	private:
		std::vector<double> S; // {vertical, horizontal} areas
		double V; // volume volume
		std::vector< std::vector<Node*> > neighbors; // surrounding volumes

	public:
		// Constructors
		Volume(const std::vector< std::vector<double> > &X, const double &depth);

		// Destructors
		// ~Volume(); // should delete dangling pointers

		// Getters
		double get_V() const;

		// Setters
		void set_neighbors(const std::vector<std::vector<double>::size_type> &ij, const std::vector< std::vector<Node*> > &volumes);

		// Methods
		void computeCoefficients(const double &beta, const double &tDelta, const double &t, const double &Tprev, const std::vector< std::vector<double> > &Tneighbors);
		double computeLambda(const std::vector<Volume>::size_type &i, const Node &neighbor);
};

class Boundary: public Node {
	private:
		const Condition* condition; // boundary condition
		Node* neighbor; // immediate next volume
		std::vector< std::vector<bool> > neighbors; // where is the neighbor?

	public:
		// Constructors
		Boundary(const std::vector<double> &_x, const Condition &_condition);

		// Setters
		void set_neighbors(const std::vector<std::vector<double>::size_type> &ij, const std::vector< std::vector<Node*> > &volumes);

		// Methods
		void computeCoefficients(const double &beta, const double &tDelta, const double &t, const double &Tprev, const std::vector< std::vector<double> > &Tneighbors);
};
