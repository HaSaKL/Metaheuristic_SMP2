/* This source file descripes the parameters and default values
 * which make up the command line interface to the GRASP implementation
 * */
#ifndef SMP2_CLI_H
#define SMP2_CLI_H

#include <eo>

// possible problem-specific neighbor(hoods)
#include "SMP2_ElementFlipIndex_Neighbor.h"
#include "SMP2_AdjElementFlipIndex_Neighbor.h"

// neighborhoor definitions
#include <neighborhood/moNeighborhood.h>
#include <eval/moEval.h>

struct parameters {
	// Radnom seed
	unsigned seed;
	
	// Problem description
	std::string problemFile;
	
	// Output File
	std::string outputFile;
	
	// neighborhood selection:
	// 1 - Adjecent Element Flip
	// 2 - Element Flip
	char neighborhood;
	
	// local search Algorithm selection
	// 1 - Best Improvement
	// 2 - First Random  Improvement
	char localSearchAlgo;
	
	// Stopping Criterion, if more than one is provided
	// 'I' - Number of Iterations
	// 't' - Time to Target
	// 'T' - Max Runtime
	char stoppingCriterion;
	
	// Selection of Alpha Value
	// 'R' - Reactive Alpha
	// 'E' - Random Alpha
	// Number - fixed Alpha Value
	std::string alphaValue;
	
	// Maximum number of Iterations
	unsigned int maxIterations;
	
	// Maximum Runtime in seconds
	unsigned int maxRuntime;
	
	// target value to hit
	double targetValue;
};

inline void parseFile(eoParser & parser, parameters & param) {

	// For each parameter, you can in on single line
	// define the parameter, read it through the parser, and assign it
	param.seed = parser.createParam( 
		unsigned(time(0)),
		"seed",
		"Random number seed",
		'S'
		).value();
										
	param.problemFile = parser.createParam( 
		std::string("../../problems/Test4-10-5.dat"),
		"problemFile",
		"Path to problem file",
		'p',
		"Param"
		).value();	
	
	param.outputFile = parser.createParam(
		std::string("output.csv"),
		"resultsFile",
		"Path to the results output file",
		'o',
		"Param"
		).value();
		
	param.neighborhood = parser.createParam(
		'2',
		"neighborhood",
		"Neighborhood Type for local search",
		'n',
		"Param"
		).value();
		
	param.localSearchAlgo = parser.createParam(
		'2',
		"LSAlgo",
		"Local Search Algorithms",
		'l',
		"Param"
		).value();
		
	param.stoppingCriterion = parser.createParam(
		'?',
		"stoppingCriterion",
		"Stopping Criterion", 
		's',
		"Param"
		).value();
		
	param.alphaValue = parser.createParam(
		std::string("R"),
		"alphaValue",
		"Type of Greedy Construction Phase",
		'a',
		"Param"
		).value();
		
	param.maxRuntime = parser.createParam(
		0,
		"maxTime",
		"maximum Runtime in seconds",
		'T',
		"Param"
		).value();
		
	param.maxIterations = parser.createParam(
		0,
		"maxIter",
		"maximum number of iterations",
		'I',
		"Param"
		).value();
		
	param.targetValue = parser.createParam(
		std::numeric_limits<double>::max(), 
		"targetValue",
		"target objective value to stop at",
		't',
		"Param"
		).value();
		
		
} 

#endif	
