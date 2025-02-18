/* The Class QAP_Problem defines the representation of the
 * Simulataneous Multi-Path Service Modularization Problem (SMP2).
 *
 * This is a MINIMIZATION problem.
 * The class also provides basic functions like:
 *
 * The fitness-setter, getter and the printing are inherited from EO-class
 *
 */

#ifndef SMP2_H
#define SMP2_H

// needed for base classes and random numbers
#include <eo>
#include <set>
#include <utility>	// for std::pair-container used in GRASP
#include <vector>		// for the std::vector-container used in GRASP
#include <algorithm>	// for std::alogirhms like sort, for_each in GRASP

class SMP2 : public EO<eoMinimizingFitness>
{
public:
	// actual representation of the problems solution using
	// an integer vector representing for each task to what module
	// it is assigned
	int* solution;

	// Constructors
	SMP2();                      // Default Constructor
	SMP2(SMP2& _problem);        // Copy Constructor
	SMP2(std::string& _fileName);// with Problem file

	// Destructor
	~SMP2();

	// Overloaded Operators
	void operator=(SMP2& _problem); // copy assignment
	int& operator[](int i);         // subsetting operator

	// Getter Methods
	int** GetDSM();
	double* GetInterCosts();
	int* GetInterMaxSize();
	double* GetIntraCosts();
	int* GetIntraMaxSize();
	int GetNumInter();
	int GetNumIntra();
	int GetNumModule();
	int GetNumPath();
	int GetNumTask();
	int GetCurrentModuleSize(int m);
	int* GetCurrentNumElm();
	bool** GetPathDef();
	double* GetPathProb();
	
	// Convinience Functions
	void printSolution();
	void printFitness();

	// Problem-specific Fuctions
	void fullEvaluation();
	double CalculateIntraModularCosts(int moduleSize);
	double CalculateDirectInterModularCostsElement(int i, int m, int numElm[]); //costs for on single task i in module m depending on given assignment of all other tasks
	double CalculateIndirectInterModularCosts(int numElm[]);
	void RandomInit();
	void GRASPInit(double alpha);
	
	// FIXME: This could also be put into the Neighbor-Definition
	void UpdateNumElm(int elm, int newModule);
	void UpdateModuleSize(int elm, int newModule);

	

private:
	// convinience functions for deleting and copying parameters
	void DeleteProblemParameters();
	void CopyProblem(SMP2 & _problem);


	// convinience fuctions for calculating costs and costs increases
	double CalculateDirectInterModularCosts();	//total direct inter modular costs
	double CalculateTotalIntraModularCosts();
	double CalculateIndirectInterModularCosts();

	// FIXME: These could go into SMP2_GreedyInit.h
	// functions and definitions used by the GRASPInit methode
	typedef std::pair<int, int> Assignment;
	typedef std::pair<double, Assignment> RCL_element;
	double GRASPCalculateCostIncrease(Assignment & _assign);
	void GRASPUpdateNumElm(int _task, int _module);
	void GRASPInitCandidateList(std::vector<RCL_element> & _rcl);
	void GRASPAddAssignment(std::vector<RCL_element> & _rcl, double alpha);
	void GRASPUpdateCandidateList(std::vector<RCL_element> & _rcl);
	
	int* CalculateNumElmElement(int elm, int module);
	
    /* PROBLEM-INSTANCE DEPENDENT PARAMETERS */
    // FIXME: Would container types (Vecotr, Array) make my life easier?

    // number of tasks in DSM
    int numTask;

    // number of modules
    // FIXME: Should this be static or dynamically set?
    int numModule;

    // number of possible paths
    int numPath;

    // number of Intermodular Cost Classes
    int numInter;

    // number of Intramodular Cost Classes
    int numIntra;

    // task-task-relationship (Design Structure Matrix)
    // defined as a two dimensional-array
    // [numTasks x numTasks]
    // FIXME: Should this be better float?
    int** DSM;

    // task-path-relationship (What task in on what path)
    // rows correspond to paths and columns to tasks
    // [numPaths x numTasks]
    bool** pathDef;

    // execution probabilities of tasks
    // one-dimensional array of size numPaths
    // [numPaths x 1]
    double* pathProb;

    // Intermodular costs classes, defined by max size and costs
    // each defined as one-dimensional array of size numInter
    // [numInter x 1]
	// CHECKME: Could this be realized with a map or a multimap
    double* interCosts;
    int* interMaxSize;

    // Intramodular costs classes, defined by max size and costs
    // each defined as one-dimensional array of size numInter
    // [numInter x 1]
	// CHECKME: Could this be realized with a map or a multimap
    double* intraCosts;
    int* intraMaxSize;
	
	// Some values to ease calculations for small changes. Work like chaches for calulations
	// Number of Elements which are assigned to each module
	int* currentModuleSize;
	
	// Number of Elements between modules, considering module hierarchy for each path
	int* currentNumElm;
};

#endif