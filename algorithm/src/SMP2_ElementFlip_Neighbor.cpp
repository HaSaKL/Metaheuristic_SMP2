#include "SMP2_ElementFlip_Neighbor.h"

void SMP2_ElementFlip_Neighbor::setMove(int _element, int _newModule) {
	ElementToModule.first = _element;
	ElementToModule.second = _newModule;
}


void SMP2_ElementFlip_Neighbor::getMove(int& _element, int& _newModule, SMP2& _solution) {
	_element = ElementToModule.first;
	_newModule = ElementToModule.second;
}


void SMP2_ElementFlip_Neighbor::move(SMP2& _solution) {
	_solution.UpdateNumElm(ElementToModule.first, ElementToModule.second);
	_solution.UpdateModuleSize(ElementToModule.first, ElementToModule.second);
	
	
	// Debug
	/*std::cout << "-----------------------------------------------" << std::endl;
	std::cout << "Move Element " << ElementToModule.first << " from ";
	std::cout << _solution[ElementToModule.first] << " to " << ElementToModule.second << std::endl;
	*/
	
	_solution[ElementToModule.first] = ElementToModule.second;
	// FIXME: OR your could add the difference, which has already been evaluated with the IncrEval-Function
	// However this would force the IncrEval to always produce a valid result (no repair needed) and 
	// it would force an exact representation (no add ons onto eval fuction as penalties and so fort)
	// alos this would require IncrEval to also change the state of currentNumElm and of currentModuleSize
	_solution.invalidate();

}


bool SMP2_ElementFlip_Neighbor::equals(SMP2_ElementFlip_Neighbor& _neighbor) {
	
	std::pair<int,int> otherElementToModule = _neighbor.getElementToModule();
	
	
	bool res;
	// FIXME: Maybe a standard comparision for pair already does the tricK? Look it up!
	res = ( (otherElementToModule.first == ElementToModule.first) && (otherElementToModule.second == ElementToModule.second));
	return res;
}

void SMP2_ElementFlip_Neighbor::print() {
	std::cout << "[" << ElementToModule.first << "->" << ElementToModule.second << "]" << std::endl;
}

std::pair<int, int> SMP2_ElementFlip_Neighbor::getElementToModule() {
	return ElementToModule;
}