/* 
 * This program test the AdjElementFlip Neighborhood
*/

#include <eo>
#include <algo/moSimpleHC.h>

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
		
		
		std::cout << "SINGLE VERBOSE TEST..." << std::endl;
		
		// Print initial Solution and fitness
		std::cout << "Initial Solution (alpha = " << alpha << "): ";
		p.printSolution();
		std::cout << "Initial Fitness: ";
		p.printFitness();
		std::cout << std::endl;
		
		// define HC-Algorithm
		moSimpleHC<SMP2_Flip_Neighbor> SimpleHC(nh_AdjFlip, FullEval, IncrEval);
		
		// Perform HC-Algorithm
		SimpleHC(p);

		// print final solution and fitness
		std::cout << "Final Solution: ";
		p.printSolution(); 
		std::cout << "Final Fitness: ";
		p.printFitness();
		std::cout << std::endl;
		
		// DEBUG
		// print final solution and fitness
		FullEval(p);
		std::cout << "Final Solution eval: ";
		p.printSolution(); 
		std::cout << "Final Fitness eval: ";
		p.printFitness();
		// */
		
		std::cout << std::endl << std::endl;
		std::cout << "RUNNING MORE TESTS" << std::endl;
		
		int MaxIt = 1000000;
		double avgInitSol = 0;
		double avgFinalSol = 0;
		double cInitSol = 0;
		double cFinalSol = 0;
		
		for(int it = 0; it < MaxIt; it++) {
			
			std::cout << std::endl;
			std::cout << "It: " << it + 1 << " of " << MaxIt;
			p.GRASPInit(alpha);
			FullEval(p);
			cInitSol = p.fitness();
			std::cout << "\t Init: " << cInitSol;
			
			SimpleHC(p);
			FullEval(p);
			cFinalSol = p.fitness(); 
			std::cout << "\t Final: " << cFinalSol;
			
			avgInitSol += cInitSol / MaxIt;
			avgFinalSol += cFinalSol / MaxIt;
		}
		
		std::cout << std::endl << "--------------------------------------------" << std::endl;
		std::cout << "Average Initial Solution: " << avgInitSol << std::endl;
		std::cout << "Average Final Solution:   " << avgFinalSol << std::endl;
		std::cout << "Average Improvement:      " << ((avgInitSol - avgFinalSol) / avgInitSol) * 100 << " %" << std::endl;
		
		make_help(parser);
	}
	
	catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}