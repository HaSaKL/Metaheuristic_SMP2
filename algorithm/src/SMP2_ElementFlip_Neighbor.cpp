#include "SMP2_ElementFlip_Neighbor.h"

void SMP2_Flip_Neighbor::setMove(unsigned int _element, unsigned int _newModule) {
	ElementToModule.first = _element;
	ElementToModule.second = _newModule;
}


void SMP2_Flip_Neighbor::getMove(unsigned int& _element, unsigned int& _newModuel) {
	_element = ElementToModule.first;
	_newModuel = ElementToModule.second;
}


void SMP2_Flip_Neighbor::move(SMP2& _solution) {
	_solution[ElementToModule.first] = ElementToModule.second;
	_solution.invalid();
}


bool SMP2_Flip_Neighbor::equals(SMP2_Flip_Neighbor& _neighbor) {
	unsigned element, newModule;
	_neighbor.getMove(element, newModule);
	
	bool res;
	// FIXME: Maybe a standard comparision for pair already does the tricK? Look it up!
	res = ( (element == ElementToModule.first) && (newModule == ElementToModule.second));
	return res;
}

void SMP2_Flip_Neighbor::print() {
	std::cout << "[" << ElementToModule.first << "->" << ElementToModule.second << "]" << std::endl;
}
