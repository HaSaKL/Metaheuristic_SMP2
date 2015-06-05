#ifndef GRASP_ALPHA_H
#define GRASP_ALPHA_H

#include "SMP2.h"

// Abstract base class for all alpha-related classes
class GRASP_Alpha
{
public:
	virtual double operator() (SMP2 & _p)= 0;
	virtual void init(SMP2 & _p) = 0;
};

#endif // GRASP_ALPHA_H
