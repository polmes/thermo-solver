class Material {
	private:
		const std::vector< std::vector<double> > boundaries(2, std::vector<double>(2));
		const double rho, cp, lambda;

	public:
		// Constructor
		Material(std::vector< std::vector<double> > _boundaries, double _rho, double _cp, double _lambda);

		// Methods
		std::vector< std::vector<double> > getBoundaries();
		double cp(), rho(), lambda(); // future: lambda as f(T)
};
