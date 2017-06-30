std::vector<double> getRange(double a, double b, int n) {
	std::vector<double> range;
	range.reserve(n);

	double step = (b -a) / n;

	while (a <= b) {
		range.push_back(a);
		a += step;
	}

	return range;
}
