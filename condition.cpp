// Standard libraries
#include "headers.hpp"

// My libraries
#ifndef INCLUDE_CONDITION
	#include "condition.hpp"
	#define INCLUDE_CONDITION
#endif

ConditionType Condition::get_conditionType() const {
	return conditionType;
}

// Conduction::Conduction() {
// 	condition = CONDUCTION;
// }

Convection::Convection(const double &_alpha, const double &_Tg) {
	condition = CONVECTION;
	alpha = _alpha;
	Tg = _Tg;
}

double Convection::get_alpha() const {
	return alpha;
}

double Convection::get_Tg() const {
	return Tg;
}

Flow::Flow(const double &_Qflow) {
	condition = FLOW;
	Qflow = _Qflow;
}

double Flow::get_Qflow() const {
	return Qflow;
}

Isotherm::Isotherm(const double &_a) {
	condition = ISOTHERM;
	a = _a;
	b = 0;
}

Isotherm::Isotherm(const double &_a, const double &_b) {
	condition = ISOTHERM;
	a = _a;
	b = _b;
}

double Isotherm::get_T(const double &t) const {
	return a + b*t;
}
