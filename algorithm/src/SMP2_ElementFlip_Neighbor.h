#ifndef SMP2_ELEMENTFLIP_NEIGHBOR_H
#define SMP2_ELEMENTFLIP_NEIGHBOR_H

#include "SMP2.h"
#include <neighborhood/moNeighbor.h>

// A neighbor which can be used for any neighbor hood which is based 
// on a sinlge change of one elements module assignment
// is used by Adjecent Element Flip and Element Flip Neighborhoods

class SMP2_Flip_Neighbor: public moNeighbor<SMP2, typename SMP2::Fitness> {

private:
	// A pair wich represents the desired Flip-Operations
	// It consists of <element index, new module index>
	std::pair<unsigned int, unsigned int> ElementToModule;
	
public:
	// set a new possible move
	void setMove (unsigned int _element, unsigned int _newModule);
	
	// get the current move
	void getMove (unsigned int & _element, unsigned int & _newModuel);
	
	// execute the current move
	void move (SMP2 & _solution);
	
	// check if current move euqals another given move
	bool equals(SMP2_Flip_Neighbor & _neighbor);
	
	// print the current move
	void print();
	
};

#endif // SMP2_ADJELEMENTFLIP_NEIGHBOR_H
