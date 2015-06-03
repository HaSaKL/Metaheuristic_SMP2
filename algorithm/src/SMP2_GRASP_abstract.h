#ifndef SMP2_GRASP_H
#define SMP2_GRASP_H

#include "SMP2.h"

class SMP2_GRASP_abstract {
public:
	virtual void Run() = 0;
	virtual void Run(double &, double &) = 0;
};

#endif // SMP2_GRASP_H
