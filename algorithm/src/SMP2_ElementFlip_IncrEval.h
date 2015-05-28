#ifndef SMP2_ELEMENTFLIP_INCREVAL_H
#define SMP2_ELEMENTFLIP_INCREVAL_H

#include "SMP2.h"
#include "SMP2_ElementFlip_Neighbor.h"
#include "SMP2_AdjElementFlipIndex_Neighbor.h"
#include <eval/moEval.h>

template <class Neighbor>
class SMP2_ElementFlip_IncrEval: public moEval<Neighbor> {
public:
	// Constructor - declared here b/c Template-dependent
	// (e.g. see http://stackoverflow.com/questions/18186878/invalid-use-of-template-name-without-an-argument-list 
	// and http://stackoverflow.com/questions/495021/why-can-templates-only-be-implemented-in-the-header-file)
	SMP2_ElementFlip_IncrEval(SMP2 & _probObj) {
		_problem = & _probObj;
	}
	
	// interface function - declared here b/c Template-dependent
	typedef typename Neighbor::EOT EOT;
	void operator()(EOT & _solution, Neighbor & _neighbor) {
		// get changes
		int elm;
		int newModule;
		int oldModule;
	
		_neighbor.getMove(elm, newModule, _solution);
		oldModule = _problem->solution[elm];
	
		// Calculate Cost Increase
		double incrTotal = CalculateIncrCosts(elm, newModule, oldModule);
	
		/*// DEBUG
		std::cout << "IncrEval(" << elm << "[" << oldModule << "] ->";
		std::cout << elm << "[" << newModule << "] = ";
		std::cout << incrTotal << std::endl;
		// */
	
	
		// Set new Costs
		_neighbor.fitness(_solution.fitness() + incrTotal);
	}
	
private:
	// a pointer to the original problem to get its data
	SMP2* _problem;
	
	// actual incremental evaluation
	double CalculateIncrCosts(int elm, int newModule, int oldModule) {
		double incrIntraModular = 0;
		double incrDirectInterModular = 0;
		double incrIndirectInterModular = 0;
		double incrTotal = 0;	
	
		/*//DEBUG 
		std::cout << std::endl << "old Module: " << oldModule << std::endl;
		std::cout << "new Module: " << newModule << std::endl;
		std::cout << "Element: " << elm << std::endl << std::endl;
		// */
	
		// calculate change in intramodular costs
		int currentSizeNew = _problem->GetCurrentModuleSize(newModule);
		int currentSizeOld = _problem->GetCurrentModuleSize(oldModule);
		incrIntraModular = _problem->CalculateIntraModularCosts(currentSizeNew + 1) -
							 _problem->CalculateIntraModularCosts(currentSizeNew) +
							 _problem->CalculateIntraModularCosts(currentSizeOld - 1) -
							 _problem->CalculateIntraModularCosts(currentSizeOld);
	
	
		// calculate the change in direct intermodular costs and get the numElm for this module
		int* newNumElm = new int[_problem->GetNumPath()]();
		int* oldNumElm = new int[_problem->GetNumPath()]();
	
		double newDirectInterModularCosts = _problem->CalculateDirectInterModularCostsElement(elm, newModule, newNumElm);
		double oldDirectInterModularCosts = _problem->CalculateDirectInterModularCostsElement(elm, oldModule, oldNumElm);
		incrDirectInterModular = newDirectInterModularCosts - oldDirectInterModularCosts;
	
		// calculate the change in indirect intermodular costs on the basis of the changed number of elements
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
	
		// free memory
		delete[] newNumElm;
		delete[] oldNumElm;
		delete[] oldTotalNumElm;
		delete[] newTotalNumElm;
	
		/*// DEBUG
		std::cout << std::endl;
		std::cout << "Change " << elm << " from " << oldModule << " to " << newModule << std::endl;
		//std::cout << "Total Change: " << incrTotal << std::endl;
		std::cout << "Current fitness is: " << _solution.fitness() << "\t New fitness would be: " << _solution.fitness() + incrTotal << std::endl;
		// 
		
		// DEBUG
		std::cout << "Delta Intramodular: " << incrIntraModular;
		//std::cout << "\t Delta direct Intermodular: " << incrDirectInterModular;
		//std::cout << "\t\t Delta indirect Intermodular: " << incrIndirectInterModular;
		std::cout << std::endl;
		// */
	
		return incrTotal;
	}

};

#endif // SMP2_ELEMENTFLIP_INCREVAL_H
