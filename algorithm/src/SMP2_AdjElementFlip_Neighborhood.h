#ifndef SMP2_ADJELEMENTFLIP_NEIGHBORHOOD_H
#define SMP2_ADJELEMENTFLIP_NEIGHBORHOOD_H

#include "SMP2.h"
#include "SMP2_ElementFlip_Neighbor.h"

// FIXME: This could also represent a backable or an indexed neighborhood, if this should become important
#include <neighborhood/moNeighborhood.h>

class SMP2_AdjElementFlip_Neighborhood : public moNeighborhood<SMP2_ElementFlip_Neighbor> {
private:
	// The generic representation of a module flip for an element
	std::pair<int, int> ElementToModule;
	
	// indicator if the current movement was a upward or downward movement
	// toogler
	bool current_up;
	
public:
	void init(SMP2 & _solution, SMP2_ElementFlip_Neighbor & _current);
	bool hasNeighbor(SMP2 & _solution);
	void next(SMP2 & _solution, SMP2_ElementFlip_Neighbor & _current);
	bool cont(SMP2 & _solution);
	std::string className() const;
};

#endif // SMP2_ADJELEMENTFLIP_NEIGHBORHOOD_H
