#include "SMP2_ElementFlip_IncrEval.h"

// THIS DOES NOT WORK PROPERLY INCR RESULT DIFFERS FROM FULL EVALUATION!

// Constructor for the Evaluation functions
// it sets a pointer to the original problem which us used to get
// the problem parameters during the evaluation
SMP2_ElementFlip_IncrEval::SMP2_ElementFlip_IncrEval(SMP2 & _probObj) {
	_problem = & _probObj;
}

void SMP2_ElementFlip_IncrEval::operator ()(EOT& _solution, SMP2_Flip_Neighbor& _neighbor) {
	double incrIntraModular = 0;
	double incrDirectInterModular = 0;
	double incrIndirectInterModular = 0;
	double incrTotal = 0;
	
	// get changes
	int elm;
	int newModule;
	int oldModule;
	_neighbor.getMove(elm, newModule);
	oldModule = _problem->solution[elm];
	/*//DEBUG 
	std::cout << std::endl << "old Module: " << oldModule << std::endl;
	std::cout << "new Module: " << newModule << std::endl;
	std::cout << "Element: " << elm << std::endl << std::endl;
	// */
	
	// calculate change in intramodular costs
	int currentSizeNew = _problem->GetCurrentModuleSize(newModule);
	int currentSizeOld = _problem->GetCurrentModuleSize(oldModule);
	incrIntraModular = _problem->CalculateIntraModularCosts(currentSizeNew+1) -
						 _problem->CalculateIntraModularCosts(currentSizeNew) +
						 _problem->CalculateIntraModularCosts(currentSizeOld - 1) -
						 _problem->CalculateIntraModularCosts(currentSizeOld);
	
	// calculate the change in direct intermodular costs and get the numElm for this module
	int* newNumElm = new int[_problem->GetNumPath()]();
	int* oldNumElm = new int[_problem->GetNumPath()]();
	
	double newDirectInterModularCosts = _problem->CalculateDirectInterModularCostsElement(elm, newModule, newNumElm);
	double oldDirectInterModularCosts = _problem->CalculateDirectInterModularCostsElement(elm, oldModule, oldNumElm);
	incrDirectInterModular = newDirectInterModularCosts - oldDirectInterModularCosts;
	
	// calculate the change in indirect intermodular costs on the basis of the change number of elements
	int* oldTotalNumElm = new int[_problem->GetNumPath()];
	for(int p = 0; p < _problem->GetNumPath(); p++) {
		oldTotalNumElm[p] = _problem->GetCurrentNumElm()[p];
	}
	
	int* newTotalNumElm = new int[_problem->GetNumPath()]();
	for(int p = 0; p < _problem->GetNumPath(); p++) {
		newTotalNumElm[p] = oldTotalNumElm[p] + newNumElm[p] - oldNumElm[p];
	}
	
	double newIndirectInterModularCosts = _problem->CalculateIndirectInterModularCosts(newTotalNumElm);
	double oldIndirectInterModularCosts = _problem->CalculateIndirectInterModularCosts(oldTotalNumElm);
	incrIndirectInterModular = newIndirectInterModularCosts - oldIndirectInterModularCosts;
	
	// total increase is sum of all partial increases
	incrTotal = incrIntraModular + incrDirectInterModular + incrIndirectInterModular;
	
	_neighbor.fitness(_solution.fitness() + incrTotal);
	
	delete[] newNumElm;
	delete[] oldNumElm;
	delete[] oldTotalNumElm;
	delete[] newTotalNumElm;
	
	/*// DEBUG
	std::cout << std::endl;
	std::cout << "Change in Direct Intermodular Costs: " << incrDirectInterModular << std::endl;
	std::cout << "Change in Indirect Intermodular Costs: " << incrIndirectInterModular << std::endl;
	std::cout << "Change in Intramodular Costs: " << incrIntraModular << std::endl;
	std::cout << "Total Change: " << incrTotal << std::endl;
	std::cout << "Current Fitness: " << _solution.fitness() << std::endl; 
	// */
}

SMP2_ElementFlip_IncrEval::~SMP2_ElementFlip_IncrEval() {
}
