#include "SMP2_ElementFlipIndex_Neighbor.h"

void SMP2_ElementFlipIndex_Neighbor::move(SMP2& _solution) {
	// map index key to a specific move
	translate(key, _solution);
	
	// execute this move
	_solution.UpdateNumElm(ElementToModule.first, ElementToModule.second);
	_solution.UpdateModuleSize(ElementToModule.first, ElementToModule.second);
	
	_solution[ElementToModule.first] = ElementToModule.second;
	
	_solution.invalidate();
}


void SMP2_ElementFlipIndex_Neighbor::translate(unsigned int _key, SMP2& _solution) {
	// This function translates a given key from the interval [0, NeighborhoodSize)
	// to a corresponing assignment. The result is saved in the pair ElementToModule,
	// just like in the non-indexed version of this function
	// Since there are two possible flips in the AdjecentElementFlip-Neighborhood per task,
	// there are numTask * 2 neighbors
	
	// they are coded as follows
	//	key-value	operation
	//	0			Element 0 -> Module +1
	//	1			Element 0 -> Module +2
	// 	2			Element 0 -> Module +3
	//	3			Element 0 -> Module +4
	//	4			Element 1 -> Module +1
	//	5			Element 1 -> Module +2
	// ...			...
	
	// This can be translated using integer devision with remainder:
	// the integer value gives the Element which is moved and the remainder gives
	// the amount to move, while making sure the wrap around ist considers
	
	// define structure for div result (consists of rem and qout)
	dev_t res;
	int numModule = _solution.GetNumModule();
	res = div(_key, numModule-1); // -1 since there are NumModule-1 other modules to consider
	
	ElementToModule.first = res.quot;
	
	// wrap-around if you add to the current module an the new module would be larger then the maxModule value. In this case
	// just subtract the maxModule value
	res.rem > numModule -1 ? ElementToModule.second = res.rem - 5 : ElementToModule = res.rem;
}


void SMP2_ElementFlipIndex_Neighbor::getMove(int& _element, int& _newModule, SMP2& _solution) {
	// get move is called by the incremental evaluation. before it is called, the current solution must be translated
	translate(key, _solution);
	_element = ElementToModule.first;
	_newModule = ElementToModule.second;
}
