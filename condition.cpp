// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_CONDITION
	#include "condition.hpp"
	#define INCLUDE_CONDITION
#endif

Condition::Condition(const ConditionType &_conditionType, const double &_a) {
	conditionType = _conditionType;
	a = _a;
	b = 0.0;
}

Condition::Condition(const ConditionType &_conditionType, const double &_a, const double &_b) {
	conditionType = _conditionType;
	a = _a;
	b = _b;
}

double Condition::get_alpha() const {
	if (conditionType == CONVECTION) return a;
	else throw std::logic_error("ERROR: Wrong ConditionType.");
}

double Condition::get_Tg() const {
	if (conditionType == CONVECTION) return b;
	else throw std::logic_error("ERROR: Wrong ConditionType.");
}

double Condition::get_Qflow() const {
	if (conditionType == FLOW) return a;
	else throw std::logic_error("ERROR: Wrong ConditionType.");
}

double Condition::get_T(const double &t) const {
	if (conditionType == ISOTHERM) return a + b*t;
	else throw std::logic_error("ERROR: Wrong ConditionType.");
}
