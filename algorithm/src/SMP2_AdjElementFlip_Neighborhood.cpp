#include "SMP2_AdjElementFlip_Neighborhood.h"


std::string SMP2_AdjElementFlip_Neighborhood::className() const {
	return "SMP2_AdjElementFlip_Neighborhood";
}


bool SMP2_AdjElementFlip_Neighborhood::cont(SMP2& _solution) {
	// continue if another neighbor is possible; Last Neighbor checked is move down in last element
	return !((ElementToModule.first == _solution.GetNumTask()-1) && !current_up);
}


bool SMP2_AdjElementFlip_Neighborhood::hasNeighbor(SMP2& _solution) {
	// a solution has a neighbor, if there are more then two modules and at least one element
	return (_solution.GetNumModule() > 1);
}


void SMP2_AdjElementFlip_Neighborhood::init(SMP2& _solution, SMP2_Flip_Neighbor& _current) {
	// Start out with the first element
	ElementToModule.first = 0;
	
	// see if the next modue needs to be wrapped around or if it is still in range
	int maxModule = _solution.GetNumModule();
	int newModule;
	current_up = true;
	if (_solution[0] == _solution.GetNumModule() -1) {
		newModule = 0; // wrap around
	} else {
		newModule = _solution[0] + 1; // next (higher) module
	}
	
	// set new module number for element
	ElementToModule.second = newModule;
	_current.setMove(0 , newModule);
	
	current_up = true; // since the initial move is up
}


void SMP2_AdjElementFlip_Neighborhood::next(SMP2& _solution, SMP2_Flip_Neighbor& _current) {
	if(current_up) {
	// last movement was up, now it will be down
		if(_solution[ElementToModule.first] == 0) {
			//wrap around at the bottom
			ElementToModule.second = _solution.GetNumModule() - 1;
		} else {
			// next (lower) module
			ElementToModule.second = _solution[ElementToModule.first] - 1;
		}
		// toggle up down for next move
		current_up = false; // current is now down
		
	} else {
	// last movement was down, now the next element needs to go up
		ElementToModule.first++;
		if (_solution[ElementToModule.first] == _solution.GetNumModule() -1) {
			// wrap around
			ElementToModule.second = 0; // wrap around
		} else {
			// next (higher) module
			ElementToModule.second = _solution[ElementToModule.first] + 1; // next (higher) module
		}
		// toggle up down for next move; current is now up
		current_up = true;
	}
	_current.setMove(ElementToModule.first,ElementToModule.second);
}
