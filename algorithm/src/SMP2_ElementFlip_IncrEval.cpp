#include "SMP2_ElementFlip_IncrEval.h"

// Constructor for the Evaluation functions
// it sets a pointer to the original problem which us used to get
// the problem parameters during the evaluation
SMP2_ElementFlip_IncrEval::SMP2_ElementFlip_IncrEval(SMP2 & _probObj) {
	_problem = & _probObj;
}

void SMP2_ElementFlip_IncrEval::operator ()(EOT& _solution, SMP2_Flip_Neighbor& _neighbor) {
	double incrInterModular = 0;
	double incrDirectInterModular = 0;
	double incrIndirectInterModular = 0;
	double incrTotal = 0;
	
	// get changes
	int elm;
	int newModule;
	int oldModule;
	_neighbor.getMove(elm, newModule);
	oldModule = _problem->solution[elm];
	
	// calculate change in intramodular costs
	int currentSizeNew = _problem->GetCurrentModuleSize(newModule);
	int currentSizeOld = _problem->GetCurrentModuleSize(oldModule);
	incrInterModular = _problem->CalculateIntraModularCosts(currentSizeNew+1) -
						 _problem->CalculateIntraModularCosts(currentSizeNew) +
						 _problem->CalculateIntraModularCosts(currentSizeOld - 1) -
						 _problem->CalculateIntraModularCosts(currentSizeOld);
	
	// calculate the change in direct intermodular costs and get the numElm for this module
	int* newNumElm = new int[_problem->GetNumPath()]();
	int* oldNumElm = new int[_problem->GetNumPath()]();
	
	double newDirectInterModularCosts = _problem->CalculateDirectInterModularCosts(elm, newModule, newNumElm);
	double oldDirectInterModularCosts = _problem->CalculateDirectInterModularCosts(elm, oldModule, oldNumElm);
	incrDirectInterModular = newDirectInterModularCosts - oldDirectInterModularCosts;
	
	// calculate the change in indirect intermodular costs on the basis of the change number of elements
	int* oldTotalNumElm = new int[_problem->GetNumPath()];
	for(int p = 0; p < _problem->GetNumPath(); p++) {
		oldTotalNumElm[p] = _problem->GetCurrentNumElm()[p];
	}
	
	int* newTotalNumElm = new int[_problem->GetNumPath()]();
	for(int p = 0; p < _problem->GetNumPath(); p++) {
		newTotalNumElm[p] = oldTotalNumElm[p] + newNumElm - oldNumElm;
	}
	
	double newIndirectInterModularCosts = _problem->CalculateIndirectInterModularCosts(newTotalNumElm);
	double oldIndirectInterModularCosts = _problem->CalculateIndirectInterModularCosts(oldTotalNumElm);
	
	incrIndirectInterModular = newIndirectInterModularCosts - oldIndirectInterModularCosts;
	
	// total increase is sum of all partial increases
	incrTotal = incrInterModular + incrDirectInterModular + incrIndirectInterModular;
	
	_neighbor.fitness(_solution.fitness() + incrTotal);
	
	delete[] newNumElm;
	delete[] oldNumElm;
	delete[] oldTotalNumElm;
	delete[] newTotalNumElm;
}

SMP2_ElementFlip_IncrEval::~SMP2_ElementFlip_IncrEval() {
}
