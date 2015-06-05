#include "GRASP_ReactiveAlpha.h"


GRASP_ReactiveAlpha::GRASP_ReactiveAlpha(SMP2 & _p, double _maxAlpha, double _minAlpha, int _numAlpha, int _reCalc) {
	
	// for easier calculataion calculate and save numAlpha, minAlpha and stepAlpha
	numAlpha = _numAlpha;
	minAlpha = _minAlpha;
	
	if (_maxAlpha > _minAlpha && _numAlpha > 0) {
		stepAlpha = (_maxAlpha - _minAlpha) / _numAlpha;
	} else {
		std::cout << "Error: Calling Uniform Random Alpha Generator with wrong Parameters!" << std::endl;
		throw;
	}
	
	reCalcIteration = _reCalc;
	
	// set the size of the vectors holding the distriution info
	// and values to helo calculate the distribution
	AlphaNum.resize(numAlpha);
	AlphaProbs.resize(numAlpha);
	AlphaValue.resize(numAlpha);
	AlphaSolVal.resize(numAlpha);
	AlphaQuality.resize(numAlpha);
	CumAlphaDist.resize(numAlpha);
	
	init(_p);
}

void GRASP_ReactiveAlpha::init(SMP2 & _p) {
	
	_p.RandomInit();
	_p.fullEvaluation();
	currentBest = _p.fitness();
	
	currentIteration = 0;
	
	// Reset the starting probabilities
	std::fill(AlphaProbs.begin(), AlphaProbs.end(), 0.1);
	
	// Reset the current quality parameter for each alpha
	std::fill(AlphaQuality.begin(), AlphaQuality.end(), 1);
	
	// Reset the number of times an alpha has been choosen
	std::fill(AlphaNum.begin(), AlphaNum.end(), 0);
	
	// Reset the alpha value
	for (int i = 0; i < numAlpha; i++) {
		AlphaValue[i] = minAlpha + i * stepAlpha;
	}
	
	// Reset the average solution value for a given alpha to the current best know solution
	std::fill(AlphaSolVal.begin(), AlphaSolVal.end(), currentBest);
	
	// Update the Cumulative Alpha Distribution
	UpdateCumAlphaDist();
}

double GRASP_ReactiveAlpha::operator ()(SMP2& _p) {
	// get last solution, observe quality and update probabilities for new alpha
	// return alpha value from the updated distribution
	
	// if this is the first call, just draw alpha an do no book keeping.
	if (currentIteration > 0) {
		
		// do the book keeping of the last solution run
	
		// Recalculate the Average Solution for that alpha value
		double lastAvgVal = AlphaSolVal[lastAlphaIdx];
		double newVal = _p.fitness();
		int currentCount = AlphaNum[lastAlphaIdx] + 1;
	
		AlphaSolVal[lastAlphaIdx] = lastAvgVal + ( (newVal - lastAvgVal) / currentCount );

		// Increase the Alpha Count for the last Alpha used
		AlphaNum[lastAlphaIdx] = currentCount;
		
		// update best known solution if necessary
		if(newVal < currentBest) {
			currentBest = newVal;
		}
	
		// if the current iteration is equal requires recalculation, do so
		if (currentIteration >= reCalcIteration) {
			ReCalcAlphas();
			currentIteration = 0;
		}
	}
	
	currentIteration ++;
		
	return DrawAlpha();
}


void GRASP_ReactiveAlpha::UpdateCumAlphaDist() {
	// saves the cumulative alpha distribution in the vector
	// uses the current alpha probabilities
	
	CumAlphaDist[0] = AlphaProbs[0];
	
	for (int i = 1; i < numAlpha; i++) {
		CumAlphaDist[i] = CumAlphaDist[i-1] + AlphaProbs[i];
	}
}

double GRASP_ReactiveAlpha::DrawAlpha() {
	
		// draw a random number
		double randNum = rng.uniform();
		
		// find out the index of the first alpha which as a cumulative distribution value above this random number
		std::vector<double>::iterator it_idx;
		it_idx = std::upper_bound(CumAlphaDist.begin(), CumAlphaDist.end(), randNum);
		int idx;
		idx = int(it_idx - CumAlphaDist.begin());
		
		// return the corresponding alpha value and set last alpha for later book keeping
		lastAlphaIdx = idx;
		
		return AlphaValue[idx];
}

void GRASP_ReactiveAlpha::ReCalcAlphas() {
	// Based on the currently known best solution an the average solution
	// optained by the different alpha-values, calculate new
	// probabilities for each alpha; if alpha has not been used so far AlphaNum == 0
	// then act like it is the most promising alpha so it will be choosen in the future
	
	// Calculate the Solution Quality
	double SumQualities = 0;
	for(int i=0; i < numAlpha; i++) {
		// if alpha hasn't been drawn so far, act like it is good (do nothing will leave it at 1) 
		// so it will be drawn more likely in the future
		if (AlphaNum[i] > 0) { 
			AlphaQuality[i] = currentBest / AlphaSolVal[i];
		}
		SumQualities += AlphaQuality[i];
	}
	
	// Calcualte the probability based on the solution quality
	for(int i=0; i < numAlpha; i++) {
		AlphaProbs[i] = AlphaQuality[i] / SumQualities;
	}
	
	// Update the Cumulative Distribution based on the new probabilites
	UpdateCumAlphaDist();
}


