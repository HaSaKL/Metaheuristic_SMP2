#ifndef SMP2_ADJELEMENTFLIPINDEX_NEIGHBOR_H
#define SMP2_ADJELEMENTFLIPINDEX_NEIGHBOR_H

#include "SMP2.h"
#include <neighborhood/moIndexNeighbor.h>

#include <stdlib.h> // for efficient integer division (DIV) with remainder

// A neighbor which is used for an AdjecentElementFlip Indexed Neighborhood
// Size should be (2 * NumElements)

class SMP2_AdjElementFlipIndex_Neighbor: public moIndexNeighbor<SMP2, SMP2::Fitness> {
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

#endif // SMP2_ADJELEMENTFLIPINDEX_NEIGHBOR_H
