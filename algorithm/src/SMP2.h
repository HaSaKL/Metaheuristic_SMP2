/* The Class QAP_Problem defines the representation of the
 * Simulataneous Multi-Path Service Modularization Problem (SMP2).
 *
 *
 *
 * This is a MINIMIZATION problem.
 * The class also provides basic functions like:
 *
 * - reading the Problem to set Problem Parameters (FIXME: missing)
 * - Evaluation of Problems' fitness value (FIXME: missing)
 * - Random Initialization of solution (FIXME: missing)
 *
 * FIXME: Currently Missing Features are:
 * - Gready Initalization
 * - a better organization for creating and deleting problem parameters
 *
 * The fitness-setter, getter and the printing are inherited from EO-class
 *
 */

#ifndef SMP2_H
#define SMP2_H

// needed for base classes and random numbers
#include <eo>

class SMP2 : public EO<eoMinimizingFitness>
{
public:
    // actual representation of the problems solution using
    // an integer vector representing for each task to what module
    // it is assigned
	// FIXME: Should/Must this be public or would it be better of private?
    int* solution;

    // Constructors
    SMP2();                      // Default Constructor
    SMP2(SMP2& _problem);        // Copy Constructor
    SMP2(std::string& _fileName); // with Problem file

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
    bool** GetPathDef();
    double* GetPathProb();
	
    // Convinience Functions
    void printSolution();
    void printFitness();

    // Problem-specific Fuctions
    void fullEvaluation();
    void RandomInit();
    void GreedyAdaptiveInit();

private:
	// convinience functions for deleting and copying parameters
	void DeleteProblemParameters();
	void CopyProblem(SMP2 & _problem);


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
    double* interCosts;
    int* interMaxSize;

    // Intramodular costs classes, defined by max size and costs
    // each defined as one-dimensional array of size numInter
    // [numInter x 1]
    double* intraCosts;
    int* intraMaxSize;
};

#endif