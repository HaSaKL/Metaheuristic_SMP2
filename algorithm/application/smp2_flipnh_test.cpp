/* 
 * This program test the AdjElementFlip Neighborhood
*/

#include <eo>
#include <algo/moSimpleHC.h>
#include <time.h>		// time measurement

// for writing output to file
#include <fstream>
#include <iostream>

#include "SMP2.h"
#include "SMP2_Eval.h"
#include "SMP2_ElementFlip_Neighbor.h"
#include "SMP2_AdjElementFlip_Neighborhood.h"
#include "SMP2_ElementFlip_IncrEval.h"
#include "SMP2_CLI.h"


//checks for help demand and writes the status file and make_help
void make_help(eoParser & _parser);

//Main Program
int main(int argc, char* argv[])
{
	try {
		std::cout << "Metaheuristic for the (SMP)² - FlipNeighborhood Tester compiled at " << __DATE__ << " " << __TIME__;
		std::cout << std::endl << std::endl; 
		
		// Initialize Parser and load parameters (default or from CLI)
		eoParser parser(argc, argv);
		parameters param;
		parseFile(parser, param);
		
		// Initialize RNG
		rng.reseed(param.seed);
		
		// Create a problem instance and load problem data from file
		std::cout << "Loading Problem ...";
		SMP2 p(param.problemFile);
		std::cout << "loaded." << std::endl;
		
		// Define problem functions
		SMP2_Eval FullEval;
				
		
		// Initialize Probem Instance
		double alpha = 0.5;
		p.GRASPInit(alpha);	
		FullEval(p);
		
		// Define Neighborhood and incremental Evaluation
		SMP2_Flip_Neighbor n_flip;
		SMP2_AdjElementFlip_Neighborhood nh_AdjFlip;
		SMP2_ElementFlip_IncrEval IncrEval(p);
		
		
		// define HC-Algorithm
		moSimpleHC<SMP2_Flip_Neighbor> SimpleHC(nh_AdjFlip, FullEval, IncrEval);
		

		// definition of tests to run
		clock_t t;
		
		int MaxIt = 1000000;
		
		double avgInitSol = 0;
		double avgFinalSol = 0;
		double avgSolTime = 0;
		
		double cInitSol = 0;
		double cFinalSol = 0;
		double cSolTime = 0;
		
		// initialize output
		std::ofstream outputFile;

		outputFile.open(param.outputFile.c_str());
		std::cout << "Writing results to " << param.outputFile.c_str() << std::endl;

		outputFile << "TestProblem; alpha; AverageInitialSolution; AverageFinalSolution; AverageSolutionTime \n";
		
		for(double alpha = 0; alpha <= 1 ; alpha += 0.025) {
			
			avgInitSol = 0;
			avgFinalSol = 0;
			avgSolTime = 0;
			
			for(int it = 0; it < MaxIt; it++) {
			
				t = clock();
				
				//std::cout << std::endl;
				//std::cout << "It: " << it + 1 << " of " << MaxIt;
				p.GRASPInit(alpha);
				FullEval(p);
				cInitSol = p.fitness();
				//std::cout << "\t Init: " << cInitSol;
			
				SimpleHC(p);
				FullEval(p);
				cFinalSol = p.fitness(); 
				//std::cout << "\t Final: " << cFinalSol;
				
				t = clock() - t;
				cSolTime = double(t) * 1000 / (CLOCKS_PER_SEC);
				
				avgInitSol += cInitSol / MaxIt;
				avgFinalSol += cFinalSol / MaxIt;
				avgSolTime += cSolTime / MaxIt;
			
			}
			// Output to screen
			std::cout << std::endl << "Alpha = " << alpha << std::endl;
			std::cout << "Average Initial Solution:   " << avgInitSol << std::endl;
			std::cout << "Average Final Solution:     " << avgFinalSol << std::endl;
			std::cout << "Average Solution Time [ms]: " << avgSolTime << std::endl;
			std::cout << "Average Improvement:        " << ((avgInitSol - avgFinalSol) / avgInitSol) * 100 << " %" << std::endl;
			
			// Output to file
			outputFile << param.problemFile << "; " << alpha << "; ";
			outputFile	<< avgInitSol << "; " << avgInitSol << "; ";
			outputFile << avgSolTime << "\n";
		}
		
		// close output file
		outputFile.close();
		
		make_help(parser);
	}
	
	catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}