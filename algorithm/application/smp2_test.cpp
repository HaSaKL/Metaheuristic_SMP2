//#include <SMP2.h>
// FIXME: FIX Header definition, DO NOT read from cpp files -> seems fishy..
// better check how to organise your code. Noe, the SMP.h hold the prototypes and
// the function definitions are spread over multiple cpp files, grouped by their
// functionality (Helper, Getter-Functions, Constructors, ...)
#include <eo>
#include "SMP2.h"

//checks for help demand and writes the status file and make_help
void make_help(eoParser & _parser);

//Main Program
int main(int argc, char* argv[])
{
	try 
	{
		std::cout << "Metaheuristic for the (SMP)² compiled at " << __DATE__ << " " << __TIME__;
		std::cout << std::endl << std::endl; 
		
		
		// Read and set user parameters
		// Initialize parser
		eoParser parser(argc, argv);
		
		std::cout << "Loading Problem ... " << std::endl;
		
		std::string fileName = "../../problems/Test4-10-5.dat";
		std::cout << fileName << std::endl << std::endl;
		
		// needed, so rng works in other classes ....
		rng.rand();
		
		// create a problem instance
		SMP2 p(fileName);
		
		p.GRASPInit(0.5);
		
		/* Test if file could be read .... */
		// test if matrix could be read
		// FIXME: Write a test for this...
		/*{ 
		int ** DSM = p.GetDSM();
		std::cout << DSM[2][2] << std::endl;
		
		// test if pathDef could be read
		bool ** PathDef = p.GetPathDef();
		std::cout << PathDef[1][0] << PathDef[1][1] << PathDef[1][2] << std::endl;
		
		// test if pathProb could be read
		double * PathProb = p.GetPathProb();
		std::cout << PathProb[0] << " + " << PathProb[1] << " = " << PathProb[0] + PathProb[1] << std::endl;
		
		// test if interCost could be read
		double *  interCost= p.GetInterCosts();
		std::cout << interCost[0] << " + " << interCost[1] << std::endl;
		
		// test if interMax could be read
		int *  interMax= p.GetInterMaxSize();
		std::cout << interMax[0] << " + " << interMax[1] << std::endl;
		
		// test if intraCost could be read
		double *  intraCost= p.GetIntraCosts();
		std::cout << intraCost[0] << " + " << interCost[1] << std::endl;
		
		// test if intraMax could be read
		int *  intraMax= p.GetIntraMaxSize();
		std::cout << intraMax[0] << " + " << intraMax[1] << std::endl;
		}
		//*/

		
		// Test evaluation fuction and caclulate a known optimal solution for Test4-10-5.dat
		// FIXME: Write a test for this...
		/*{
		
		// initialize some solution
		std::cout << "Initialize to optimal solution ... Objective Fuction Value should be 69.71 " << std::endl;
		p.solution[0] = 0; //A
		p.solution[1] = 1; //B
		p.solution[2] = 2; //C
		p.solution[3] = 1; //D
		p.solution[4] = 1; //E
		p.solution[5] = 1; //F
		p.solution[6] = 0; //G
		p.solution[7] = 0; //H
		p.solution[8] = 2; //I
		p.solution[9] = 0; //J
		
		
		// print new solution
		p.printSolution();
		p.fullEvaluation();
		p.printFitness();
		std::cout << std::endl << std::endl;
		
		// randomly initililze and print solution and fitness
		p.RandomInit();
		p.printSolution();
		p.fullEvaluation();
		p.printFitness();
		}
		//*/
		
		make_help(parser);
	}
	
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}