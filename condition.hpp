// Standard libraries
#include "headers.hpp"

class Condition {
	enum ConditionType {CONVECTION, ISOTHERM, FLOW};

	protected:
		ConditionType conditionType;

	public:
		// Getters
		ConditionType get_conditionType() const;
};

// class Conduction: public Condition {
// 	public:
// 		Condition();
// }

class Convection: public Condition {
	private:
		double alpha, Tg;

	public:
		// Constructors
		Convection(const double &_alpha, const double &_Tg);

		// Getters
		double get_alpha() const;
		double get_Tg() const; // could have Tg as f(t)
};

class Flow: public Condition {
	private:
		double Qflow; // W/m

	public:
		// Constructors
		Flow(const double &_Qflow);

		// Getters
		double get_Qflow() const; // could have Qflow as f(t)
};

class Isotherm: public Condition {
	private:
		double a, b; // T = a + b*t

	public:
		// Constructors
		Isotherm(const double &_a);
		Isotherm(const double &_a, const double &_b);

		// Getters
		double get_T(const double &t) const;
};
