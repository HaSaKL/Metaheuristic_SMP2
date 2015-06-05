#include "GRASP_UniformRandomAlpha.h"

GRASP_UniformRandomAlpha::GRASP_UniformRandomAlpha(double _maxAlpha, double _minAlpha, int _numAlpha) {
	minAlpha = _minAlpha;
	numAlpha = _numAlpha;
	
	if (_maxAlpha > _minAlpha && _numAlpha > 0) {
		stepAlpha = (_maxAlpha - _minAlpha) / _numAlpha;
	} else {
		std::cout << "Error: Calling Uniform Random Alpha Generator with wrong Parameters!" << std::endl;
		throw;
	}
}

void GRASP_UniformRandomAlpha::init(SMP2 & _p) {
}

double GRASP_UniformRandomAlpha::operator ()(SMP2 & _p) {
	return minAlpha + rng.random(numAlpha) * stepAlpha;
}
