/* 
 * This program implements a first GRASP Implementation, which utilizes the flip neighborhoor
*/

#include <eo>

// problem definition
#include "SMP2.h"
#include "SMP2_Eval.h"

// Command Line Interface
#include "SMP2_CLI.h"

// possible problem-specific neighbor(hoods)
#include "SMP2_ElementFlipIndex_Neighbor.h"
#include "SMP2_AdjElementFlipIndex_Neighbor.h"

// possible problem-specific incremental evaluation functions
#include "SMP2_ElementFlip_IncrEval.h"

// util - functions from C++ Standard Library
#include <time.h>
#include <fstream>
#include <iostream>

#include "SMP2_GRASP_Algo.h"

void main_function(int argc, char* argv[]) {
	std::cout << "GRASP for the (SMP)²" << std::endl;
	std::cout << "Compiled at " << __DATE__ << " " << __TIME__ << std::endl;
	
	// Initialize Parser and load parameters from CLI
	eoParser parser(argc, argv);
	parameters param;
	parseFile(parser, param);
	
	// Initilaize the Random Number Generator with given seed
	rng.reseed(param.seed);
	
	// Create a problem instance and load problem data
	std::cout << "Loading Problem " << param.problemFile << "...";
	SMP2 p(param.problemFile);
	std::cout << "done." << std::endl;
	
	// Define the Algorithm on the basis of the choosen Neighborhood
	// and initialize the GRASP-Algorithm
	SMP2_GRASP_abstract * Algo;
	if (param.neighborhood == '1') {
		Algo = new SMP2_GRASP_Algo<SMP2_AdjElementFlipIndex_Neighbor> (p, param);
	} else if (param.neighborhood == '2') {
		Algo = new SMP2_GRASP_Algo<SMP2_ElementFlipIndex_Neighbor>(p, param);
	} else {
		std::cout << "Unknown Neighborhood Definition: " << param.neighborhood << std::endl;
		throw;
	}
	
	double Sol;
	double Time;
	
	// Run the algorithm
	Algo->Run(Sol, Time);
	
	std::cout << "Time: " << Time << "; Sol: " << Sol << std::endl;
}


// Main-Program
int main(int argc, char* argv[]) {
	try {
		main_function(argc, argv);
	} 
	catch(std::exception & e) {
		std::cout << "Exception cought: " << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}