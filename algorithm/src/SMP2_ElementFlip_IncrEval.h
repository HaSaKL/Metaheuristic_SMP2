#ifndef SMP2_ELEMENTFLIP_INCREVAL_H
#define SMP2_ELEMENTFLIP_INCREVAL_H

#include "SMP2.h"
#include "SMP2_ElementFlip_Neighbor.h"
#include <eval/moEval.h>

class SMP2_ElementFlip_IncrEval: public moEval<SMP2_Flip_Neighbor> {
public:
	typedef typename SMP2_Flip_Neighbor::EOT EOT;
	
	SMP2_ElementFlip_IncrEval(SMP2 & _probObj);
	void operator() (EOT & _solution, SMP2_Flip_Neighbor & _neighbor); 
	
private:
	// a pointer to the original problem to get its data
	SMP2* _problem;
};

#endif // SMP2_ELEMENTFLIP_INCREVAL_H
