#ifndef GRASP_REACTIVEALPHA_H
#define GRASP_REACTIVEALPHA_H

#include "GRASP_Alpha.h"
#include "SMP2.h"			// to get solution value
#include <utils/eoRNG.h>	// for random numbers

//	class which returns a random alpha value and favors alpha-values
//	which have been successful in the past
class GRASP_ReactiveAlpha: public GRASP_Alpha
{
private:
	// number of alpha values
	int numAlpha;
	double minAlpha;
	double stepAlpha;
	
	// holds the current iteration since the last recalculation and 
	// after how many iterations a recalculataion of alpha probabilities
	// should be realized
	int reCalcIteration;
	int currentIteration;
	
	// alpha idx returned from last time
	int lastAlphaIdx;
	
	// currently best known solution for alpha generator
	double currentBest;
	
	// info structure holing infos about alpha
	std::vector<double> AlphaValue;
	std::vector<double> AlphaProbs;
	std::vector<double> AlphaSolVal;
	std::vector<double> AlphaQuality;
	std::vector<int> AlphaNum;
	
	// structure holding the cumulative distributions for successive alpha values
	// this is used in choosing the alpha
	std::vector<double> CumAlphaDist;
	
	// private methods
	void UpdateCumAlphaDist();
	void ReCalcAlphas();
	double DrawAlpha();
	
public:
	GRASP_ReactiveAlpha(SMP2 & _p, double _maxAlpha, double _minAlpha, int _numAlpha, int _reCalc);
	void init(SMP2 & _p);
	double operator() (SMP2 & _p);
};

#endif // GRASP_REACTIVEALPHA_H
