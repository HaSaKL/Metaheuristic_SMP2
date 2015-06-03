#ifndef GRASP_FIXEDALPHA_H
#define GRASP_FIXEDALPHA_H

#include "GRASP_Alpha.h"

// Class which always returns a fixed alpha value
class GRASP_FixedAlpha: public GRASP_Alpha
{
private:
	double alpha;
	
public:
	GRASP_FixedAlpha(double _alpha);
	void init(double _alpha);
	void init();
	double operator() ();
};

#endif // GRASP_FIXEDALPHA_H
