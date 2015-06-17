#include "ProblemGenerator.h"

// This programm will generate a set of test instances which can be used to test
// different heurisitce for the SMP2, all it does is call the problemGenerator-fuction
// from the SMP2 library with a specified set of parameters

int main(int argc, char* argv[]) {
	unsigned int seed = 19510210;
	
	//make problems in different sizes - fix rest
	std::cout << "Making Problems with different sizes ... " << std::endl;
	rng.reseed(seed);
	
	
	
	// make problems with different densities - fix rest
	std::cout << "Making Problems with different densities ... " << std::endl;
	rng.reseed(seed);
	
	
	
	// make problems with different paths - fix rest
	std::cout << "Making Problems with different PathNumbers ... " << std::endl;
	rng.reseed(seed);
	
	
	
	// make problems with different number intramodular classes - fix rest
	std::cout << "Making Problems with different Number of IntraModular Classes ..." << std::endl;
	rng.reseed(seed);
	
	
	
	// make problems with different number of intermodular classes -fix rest
	std::cout << "Making Problems with different Number of InterModular Classes ... " << std::endl;
	rng.reseed(seed);
	
	
	
	// make one with same structure as Test16-13-7.dat
	rng.reseed(seed);
	GenerateProblem(std::string("Test.dat"), 13, 6, 0.69, 7, 16, 10, 1, 1.1, 6, 0.75, 2);
}