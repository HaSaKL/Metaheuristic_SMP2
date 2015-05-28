#ifndef SMP2_ELEMENTFLIP_NEIGHBOR_H
#define SMP2_ELEMENTFLIP_NEIGHBOR_H

#include "SMP2.h"
#include <neighborhood/moNeighbor.h>

// A neighbor which can be used for any neighbor hood which is based 
// on a sinlge change of one elements module assignment
// is used by Adjecent Element Flip and Element Flip Neighborhoods

class SMP2_ElementFlip_Neighbor: public moNeighbor<SMP2, typename SMP2::Fitness> {

private:
	// A pair wich represents the desired Flip-Operations
	// It consists of <element index, new module index>
	std::pair<int, int> ElementToModule;
	
public:
	// set a new possible move
	void setMove (int _element, int _newModule);
	
	// get the current move
	void getMove (int & _element, int & _newModule, SMP2 & _solution);
	
	// get the current ElementToModule Change;
	std::pair<int, int> getElementToModule();
	
	// execute the current move
	void move (SMP2 & _solution);
	
	// check if current move euqals another given move
	bool equals(SMP2_ElementFlip_Neighbor & _neighbor);
	
	// print the current move
	void print();
	
};

#endif // SMP2_ADJELEMENTFLIP_NEIGHBOR_H
