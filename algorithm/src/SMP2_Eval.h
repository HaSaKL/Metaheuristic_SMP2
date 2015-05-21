#ifndef SMP2_EVAL_H
#define SMP2_EVAL_H

#include "SMP2.h"
#include <eoEvalFunc.h>

// defines the full evaluation function for the SMP2 in 
// a seperate class to us in build-in heuristics
class SMP2_Eval : public eoEvalFunc <SMP2> {
public:
	void operator() (SMP2 & _problem) {
		_problem.fullEvaluation();
	}
};

#endif // SMP2_EVAL_H
