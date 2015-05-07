//#include <SMP2.h>
// FIXME: FIX Header definition, DO NOT read from cpp files -> seems fishy..
// better check how to organise your code. Noe, the SMP.h hold the prototypes and
// the function definitions are spread over multiple cpp files, grouped by their
// functionality (Helper, Getter-Functions, Constructors, ...)
#include "SMP2.h"
#include <eo>

//Main Program
int main(int argc, char* argv[])
{
	try 
	{
		std::cout << "Metaheuristic for the (SMP)² compiled at " << __DATE__ << " " << __TIME__;
		std::cout << std::endl << std::endl; 
		
		std::cout << "Loading Problem ... " << std::endl;
		
		std::string fileName = "../../problems/SMP2Test.dat";
		std::cout << fileName << std::endl << std::endl;
		
		// create a problem instance
		SMP2 p(fileName);
		
		
		
		
		/* Test if file could be read .... */
		// test if matrix could be read
		// FIXME: Write a test for this...
		{ 
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

		// test solution output
		p.printSolution();
	}
	
	catch(std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return EXIT_SUCCESS;
}