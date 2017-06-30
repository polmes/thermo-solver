class Volume {
	private:
		// static const int M, N; // shared by all Volume instances
		double aE, aW, aN, aS, aP, bP;
		Material material;
		bool isBoundary; // boundary = 'w' 'e' 'n' 's' 0

	protected:
		//

	public:
		// Constructor
		Volume();
};
