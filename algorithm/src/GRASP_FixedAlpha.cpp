#include "GRASP_FixedAlpha.h"

// Set the alpha value depending on the provided parameter
GRASP_FixedAlpha::GRASP_FixedAlpha(double _alpha) {
	alpha = _alpha;
}

void GRASP_FixedAlpha::init(SMP2 & _p) {
	
}

double GRASP_FixedAlpha::operator() (SMP2 & _p) {
	return alpha;
}