// Standard libraries
#include "headers.hpp"

class Condition {
	const enum ConditionType {CONVECTION, ISOTHERM, FLOW};

	private:
		ConditionType conditionType;
		double a, b; // convection: a = alpha, b = Tg; isotherm: T = a + b*t; flow: Qflow = a

	public:
		// Constructors
		Condition(const ConditionType &_conditionType, const double &_a);
		Condition(const ConditionType &_conditionType, const double &_a, const double &_b);

		// Getters
		ConditionType get_conditionType() const;
		double get_alpha() const;
		double get_Tg() const; // could have Tg as f(t)
		double get_Qflow() const; // could have Qflow as f(t)
		double get_T(const double &t) const;
};
