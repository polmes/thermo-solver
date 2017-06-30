Material::Material(std::vector< std::vector<double> > _boundaries, double _rho, double _cp, double _lambda): boundaries(_boundaries), rho(_rho), cp(_cp), lambda(_lambda);

std::vector< std::vector<double> > getBoundaries() {
	return boundaries;
}

double cp() {
	return cp;
}

double rho() {
	return rho;
}

double lambda() {
	return lambda;
}
