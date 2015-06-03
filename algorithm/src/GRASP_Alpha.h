#ifndef GRASP_ALPHA_H
#define GRASP_ALPHA_H

// Abstract base class for all alpha-related classes
class GRASP_Alpha
{
public:
	virtual double operator() ()= 0;
	virtual void init() = 0;
};

#endif // GRASP_ALPHA_H
