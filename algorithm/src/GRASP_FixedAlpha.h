#ifndef GRASP_FIXEDALPHA_H
#define GRASP_FIXEDALPHA_H

#include "GRASP_Alpha.h"
#include "SMP2.h"

// Class which always returns a fixed alpha value
class GRASP_FixedAlpha: public GRASP_Alpha
{
private:
	double alpha;
	
public:
	GRASP_FixedAlpha(double _alpha);
	void init();
	void init(SMP2 & _p);
	double operator() (SMP2 & _p);
};

#endif // GRASP_FIXEDALPHA_H
