#ifndef SMP2_GRASP_ALGO_H
#define SMP2_GRASP_ALGO_H


// problem definition
#include "SMP2.h"
#include "SMP2_Eval.h"

// neighborhoor definitions
#include <neighborhood/moOrderNeighborhood.h>
#include <neighborhood/moRndWithoutReplNeighborhood.h>

// possible LS-Algorithms
#include <algo/moSimpleHC.h>
#include <algo/moFirstImprHC.h>

// possible problem-specific incremental evaluation functions
#include "SMP2_ElementFlip_IncrEval.h"

// Command Line Interface
#include "SMP2_CLI.h"

// Abstract GRASP-class
#include "SMP2_GRASP_abstract.h"

// possible continueators
#include <continuator/moTimeContinuator.h>
#include <continuator/moFitContinuator.h>
#include <continuator/moIterContinuator.h>

// possible alpha generators
#include "GRASP_FixedAlpha.h"
#include "GRASP_UniformRandomAlpha.h"
#include "GRASP_ReactiveAlpha.h"

// time measurements
#include <time.h>

template<class Neighbor>
class SMP2_GRASP_Algo: public SMP2_GRASP_abstract 
{
private:
	// a set of algorithm parameters as defined in CLI.h
	parameters param;
	
	// a pointer to the problem definition is kept for easier method-signatures
	SMP2 * p;
	
	// a pointer to an alpha generator
	GRASP_Alpha * alpha;
	
	// holds the neighborhood size for indexed neighborhoods
	int NeighborHoorSize;
	
	// Evaluation function
	SMP2_Eval fullEval;
	
	// pointer to used neighborhood
	moIndexNeighborhood<Neighbor> * nh;
	
	// pointer incremental evaluation function for the neighborhood, defined during initialization
	moEval<Neighbor> * incrEval;
	
	// pointer to the actual local search algorithm, which is defined during initialization
	moLocalSearch<Neighbor> * ls;
	
	// point to contiunator (stopping criterion), which is defined in basis of parameters during initialization
	moContinuator<Neighbor> * cont;
	
	
public:
	// Constructor - Initialize the Neighborhood and IncrEval
	SMP2_GRASP_Algo(SMP2 & _p, parameters _param) {
		
		// Get Pointer to problem into current scope
		p = & _p;
		
		// make a local copy of the parameters for easier method declarations
		param = _param;
		
		// Define the Neighborhood Size Depending on the Neighbor-Template
		SetNeighborhoodSize();
		
		// Load the Incremental Evaluation Function
		// FIXME: Currently only works for ElementFlip_IncrEval; if other incrEvals become avaiable this could be fixed i a common super-class SMP2_IncrEval, which sets the correct IncrEval depending on the Neighbor-Template
		incrEval = new SMP2_ElementFlip_IncrEval<Neighbor>(*p);
		
		// Set-up the local Search Algrithm
		if (param.localSearchAlgo == '1') {
			// for the Best Improvement
			nh = new moOrderNeighborhood<Neighbor>(NeighborHoorSize);
			ls = new moSimpleHC<Neighbor>(*nh, fullEval, *incrEval);
			
		} else if (param.localSearchAlgo == '2') {
			//For the first Improvement
			nh = new moRndWithoutReplNeighborhood<Neighbor>(NeighborHoorSize);
			ls = new moFirstImprHC<Neighbor>(*nh, fullEval, *incrEval);
			
		} else {
			std::cout << "Error: Unknown Local Search Alogorithms: " << param.localSearchAlgo << std::endl;
			throw;
		}
		
		// Set-up continuator
		if (param.stoppingCriterion == 'I') {
			// If Continuator is specified by the Parameters as
			// Number of Iterations as Stopping Criterion
			cont = new moIterContinuator<Neighbor>(param.maxIterations);

		} else if (param.stoppingCriterion == 'T') {
			// If Continuator is specified by the Parameters as
			// Number of Seconds as Stopping Criterion
			cont = new moTimeContinuator<Neighbor>(param.maxRuntime);
			
		} else if (param.stoppingCriterion == 't') {
			// If Continuator is specified by the Parameters as
			// Target Solution as Stopping Criterion
			if (param.targetValue == std::numeric_limits<double>::max()) {
				std::cout << "Error: No target Vaule provided." << std::endl;
				throw;
			}
			cont = new moFitContinuator<Neighbor>(param.targetValue);
		
		} else {
			// If Continuator is not specified explicitly, was it specified implicit?
			
			// has target value been set?
			if(param.targetValue < std::numeric_limits<double>::max()) {
				cont = new moFitContinuator<Neighbor>(param.targetValue);
			}
			
			// has iteration number been set?
			else if(param.maxIterations > 0) {
				cont = new moIterContinuator<Neighbor>(param.maxIterations);
			}
			
			// has maximum time been set?
			else if(param.maxRuntime > 0) {
				cont = new moTimeContinuator<Neighbor>(param.maxRuntime);

			} else {
				std::cout << "Error: Invalid Stopping Criterion provided. Please provide a vaild stopping Cirterion or a Runtime > 0, Max Iterations Number >0, or a target Value." << std::endl;
				throw;
				
			}
		}
	
		// Set-up alpha generator
		if (param.alphaValue.compare(std::string("R")) == 0) {
			// FIXME: Max, Min and Num values could be parameterized
			alpha = new GRASP_ReactiveAlpha(*p,1,0,10,100);

		} else if (param.alphaValue.compare(std::string("E")) == 0) {
			// FIXME: Max, Min and Num values could be parameterized
			alpha = new GRASP_UniformRandomAlpha(1,0,10);
	
			
		} else {
			
			// See if a valid alpha has been provided to the function
			// check for double, this code comes from Stack OVerflow:
			// http://stackoverflow.com/questions/2065392/c-test-if-input-is-an-double-char
			std::istringstream ss(param.alphaValue);
			double d;
			bool isDouble = (ss >> d) && (ss >> std::ws).eof();
			
			if(isDouble && d >= 0 && d <= 1) {
				alpha = new GRASP_FixedAlpha(d);
			} else {
				
				// no double value or anything els known
				std::cout << "Error: No alpha generator provided or incorrect alpha value." << std::endl;
				throw;
			}
		}
	
	}
	
	// Method dummy which is should be overloaded by neighborhood-specific setter functions
	void SetNeighborhoodSize() {
		throw;
	}
	
	// from abstract base class
	// this realizes to run a set of GRASP Iterations as specified in the parameters
	// This function is silent and return the values to the fuction parameters
	void Run(double & _SolValue, double & _Runtime) {
		// set-up the memory for the best solution value
		double bestVal = std::numeric_limits<double>::max();
		double val = 0;
		
		// set-up timers
		clock_t t;
		double elapsedTime;
		
		// initialize stopping criterion
		cont->init(*p);
		
		// initialize alpha generator
		alpha->init(*p);

		// start timer
		t = clock();
		
		// start calculating until stopping criterion is met
		do
		{
			val = GRASPIteration(alpha->operator ()(*p));
			
			if (val < bestVal) {
				bestVal = val;
			}
		} while(cont->operator()(*p));
		
		// calculate running time
		t = clock() - t;
		elapsedTime = double(t) / (CLOCKS_PER_SEC);
		
		// save results function parameters
		_Runtime = elapsedTime;
		_SolValue= bestVal;
	}
	
	// This calls Run() with parameters and displays them. This is not silent
	void Run() {
		double Runtime;
		double SolValue;
		
		Run(SolValue, Runtime);
		
		// print result
		std::cout << "Solution Value: " << SolValue << ", Time: " << Runtime << std::endl;
	}
	
	// thie realized a specific time-to-target run where the time is measured for each time-to-targe iteraion
	// this implementation uses both the target value and the number of iterations
	// this function has also verbose timing output
	void RunTimeToTarget() {
	
		// initialize result values
		double bestVal = std::numeric_limits<double>::max();
		double val = 0;
		
		// open outputfile for writing
		// initialize output (append to file)
		std::ofstream outputFile;
		outputFile.open(param.outputFile.c_str(),std::ios::app);
		
		// initialize timer
		clock_t t;
		double timeToTarget;
		
		// print output header
		std::cout << "Iteration; Time" << std::endl;
		
		// print file output header if file is empty
		if(outputFile.tellp() == 0)
			outputFile << "Problem; Neighborhood; Algorithm; AlphaValue; Time" << std::endl;
		
		// explicitly delete the current continuator, in case it has been set to something
		// else then a target value; check first if a target value has been defined
		if (param.targetValue < std::numeric_limits<double>::max()) {
			delete cont;
			cont = new moFitContinuator<Neighbor>(param.targetValue);
		} else { 
			std::cout << "Please specify a target value if you want to run time-to-target." << std::endl;
			throw; 
		}
		
		// check if a number of iterations was set as well
		if (param.maxIterations <= 0) {
			std::cout << "Please specify the number of iterations you want to run time-to-target." << std::endl;
			throw;
		}
		
		// repeat for a given number of iterations
		for (int i = 0; i < param.maxIterations; i++) {
			
			// Reset last result, so the current solution value is not optimal
			bestVal = std::numeric_limits<double>::max();
			p->RandomInit();
			
			// intitialize continuator
			cont->init(*p);
			
			// initialize alpha-generator
			alpha->init(*p);
			
			// start clock
			t = clock();
			
			do
			{
				val = GRASPIteration(alpha->operator ()(*p));
				if (val < bestVal) {
					bestVal = val;
				}
			} while(cont->operator()(*p)); // repeat until target value is met
			
			// after target solution was found, calculate elapsed time
			t = clock() - t;
			timeToTarget = double(t) / (CLOCKS_PER_SEC);
			
			// print result
			std::cout << i << "; " << timeToTarget << std::endl;
			
			// write result to file
			outputFile << param.problemFile << "; " << param.neighborhood << "; " << param.localSearchAlgo << "; " << param.alphaValue << "; " << timeToTarget << std::endl;
		}
		
		//close output file
		outputFile.close();
	}
	
	// a single GRASP Iteration consists of GreedyIntialization with alpha and of local search
	// result value ist updated an also returned as function value
	double GRASPIteration(double alpha) {
		// Initializea random solution using greedy construction the solution
		p->GRASPInit(alpha);
		fullEval(*p);
		
		// do the local search
		ls->operator()(*p);
	
		return p->fitness();
	}
	
};

// Overload the generic Neighbor Size Setter depending on neightborhood type

template <> void SMP2_GRASP_Algo<SMP2_AdjElementFlipIndex_Neighbor>::SetNeighborhoodSize() {
		NeighborHoorSize = p->GetNumTask() * 2; 
		};
		
template <> void SMP2_GRASP_Algo<SMP2_ElementFlipIndex_Neighbor>::SetNeighborhoodSize() {
		NeighborHoorSize = p->GetNumTask() * (p->GetNumModule() - 1); 
		};


#endif // SMP2_GRASP_ALGO_H
