#include "SMP2_AdjElementFlipIndex_Neighbor.h"

void SMP2_AdjElementFlipIndex_Neighbor::move(SMP2& _solution) {
	// map index key to a specific move
	translate(key, _solution);
	
	/*// DEBUG
	std::cout << className();
	std::cout << std::endl;
	std::cout << "Key: " << key;
	std::cout << " translates to " << ElementToModule.first;
	std::cout << " ->" << ElementToModule.second;
	std::cout << std::endl;
	std::cin.get(); // Wait until key is pressed
	// */
	
	// execute this move
	_solution.UpdateNumElm(ElementToModule.first, ElementToModule.second);
	_solution.UpdateModuleSize(ElementToModule.first, ElementToModule.second);
	
	_solution[ElementToModule.first] = ElementToModule.second;
	
	_solution.invalidate();
}

void SMP2_AdjElementFlipIndex_Neighbor::translate(unsigned int _key, SMP2& _solution) {
	// This function translates a given key from the interval [0, NeighborhoodSize)
	// to a corresponing assignment. The result is saved in the pair ElementToModule,
	// just like in the non-indexed version of this function
	// Since there are two possible flips in the AdjecentElementFlip-Neighborhood per task,
	// there are numTask * 2 neighbors
	
	// they are coded as follows
	//	key-value	operation
	//	0			Element 0 -> Module +1
	//	1			Element 0 -> Module -1
	// 	2			Element 1 -> Module +1
	//	3			Element 1 -> Module -1
	//	4			Element 2 -> Module +1
	//	5			Element 2 -> Module -1
	// ...			...
	
	// This can be translated using integer devision with remainder:
	// the integer value gives the Element which is moved and the remainder gives
	// the direction. Remainder 0 -> up and Remainder 1 -> down
	// all that is left to check is if there is a wrap around
	
	// define structure for div result (consists of rem and qout
	div_t res;
	res = div(_key,2);
	
	// quotient is the element number
	ElementToModule.first = res.quot;
	
	// remainder codes wehter the element is moved into a higher or a lower module
	if(res.rem == 0) { // move up
		//if elemt already @ last module, then wrap around
		if(_solution[res.quot] == _solution.GetNumModule()-1) {
			ElementToModule.second = 0;
		} else {
			ElementToModule.second = _solution[res.quot] + 1;
		}
	} else { //remainder == 1 --> move down
		// if element already @ first module, then wrap around
		if(_solution[res.quot] == 0) {
			ElementToModule.second = _solution.GetNumModule()-1;
		} else {
			ElementToModule.second = _solution[res.quot] - 1;
		}
	}
}

void SMP2_AdjElementFlipIndex_Neighbor::getMove(int & _element, int & _newModule, SMP2 & _solution) {
	// get move is called by the incremental evaluation. before it is called, the current solution must be translated
	translate(key, _solution);
	_element = ElementToModule.first;
	_newModule = ElementToModule.second;
}
