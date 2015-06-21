/* 
 * This program implements a time to target test. If not target is specified, a long run is realized which hopefulle 
 * gurantees to find a good value. This value is then used to do time to target testing
 *
 * */

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
	std::cout << "Time-to-Target for (SMP)²-GRASP " << std::endl;
	std::cout << "Compiled at " << __DATE__ << " " << __TIME__ << std::endl;
	
	// Initialize Parser and load parameters from CLI
	eoParser parser(argc, argv);
	parameters param;
	parseFile(parser, param);
	
	// Initilaize the Random Number Generator with given seed
	rng.reseed(param.seed);
	
	// Check if a number of iterations was provided
	if (param.maxIterations == 0) {
		std::cout << "Please specify the number of Time-To-Target runs using the Parameter -I= (Max Number of Iterations)" << std::endl;
		throw;
	}
	
	// Create a problem instance and load problem data
	SMP2 p(param.problemFile);
	
	
	// Check if a taget value was provided. If not, make a really long run to find one
	if (param.targetValue == std::numeric_limits<double>::max() ) {
		std::cout << "No target value provided. Trying to find one using defined or default algorithm." << std::endl;
		
		// set parameters for long run
		
		// check if a Runtime was defined for long run, if not set to the abritrary value of 5 Minutes, else use value provided
		if (param.maxRuntime == 0) {
			param.maxRuntime = 300;
		}
		param.stoppingCriterion = 'T';
		
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
		
		// run and save result in target parameter for next run
		double Sol;
		double Dummy;
		std::cout << "Running Algorithm for "<< param.maxRuntime <<" seconds ... " << std::endl;
		Algo->Run(Sol, Dummy); 
		
		std::cout.precision( std::numeric_limits<double>::digits10 + 1);
		std::cout << "Done. Best Solution found: " << Sol << std::endl;
		
		// What can be difficult now it that due to the precision of double-value calculation 
		// the values can differ stong from run to run for optimal solutions (e.g. 22.3716793 vs. 22.37167929999999 vs. 22.37167929999992)
		// this can only be solved using some form of rounding up to a number of precision digits
		// c++' rounding functions (floor, round, ceil) do not provide an precission information -> this needs to be done the hard way
		// precision is set to 6 digits afer the point during all initializations of the alogirhm (in the SMP2_GRASP_Alog construtor and in the
		// SMP2_GRASP_Algo::RunTimeToTarget() method.
		
		// save parameter
		param.targetValue = Sol;
		std::cout << "Using:" << param.targetValue << std::endl;
		
		// delete Algorithm --> construct a new, right one with a target value in the next steps
		delete Algo;
	}
	
	
	// set new stopping criterion and initialize new algorithm
	param.stoppingCriterion = 't';
	
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
	
	
	// Run time-to-target coputation
	std::cout << "Running time to target with target value : " << param.targetValue + pow(10,-6) << std::endl;
	Algo->RunTimeToTarget();
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