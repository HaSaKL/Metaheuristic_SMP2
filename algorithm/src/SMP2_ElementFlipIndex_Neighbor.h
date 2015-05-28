#ifndef SMP2_ELEMENTFLIPINDEX_NEIGHBOR_H
#define SMP2_ELEMENTFLIPINDEX_NEIGHBOR_H

#include "SMP2.h"
#include <neighborhood/moIndexNeighbor.h>

#include <stdlib.h> // for efficient integer division (DIV)

// A neighbor which is used for an ElementFlip Indexed Neighborhood
// Size should be (NumElements * (NumModules - 1))


class SMP2_ElementFlipIndex_Neighbor: public moIndexNeighbor<SMP2, SMP2::Fitness> {
private:
	// A pair wich represents the desired Flip-Operations
	// It consists of <element index, new module index>
	std::pair<int, int> ElementToModule;
	void translate(unsigned int _key, SMP2 & _solution);
	
public:
	using moIndexNeighbor<SMP2, typename SMP2::Fitness>::key;

	void move(SMP2 & _solution);
	void getMove(int & _element, int & _newModule, SMP2 & _solution);
};

#endif // SMP2_ELEMENTFLIPINDEX_NEIGHBOR_H
