#include "SMP2.h"

/* C O N S T R U C T O R S */
// Default Constructor
SMP2::SMP2() {
		numTask = 0;
		DSM = 0;
		
		numModule = 0;
		numInter = 0;
		interCosts = 0;
		interMaxSize = 0;
		
		numIntra = 0;
		intraCosts = 0;
		intraMaxSize = 0;
		
		numPath = 0;
		pathDef = 0;
		pathProb = 0;
		
		solution = 0;
}

// Copy Constructor
SMP2::SMP2(SMP2 & _problem) {
	CopyProblem(_problem);
}

// Regular Constructor with file pointer
SMP2::SMP2(std::string & _fileName) {
	
	// read the problem data from a given file
	// Note, the following file stucture is expected:
	// line 1: dimension of DSM (int numTask)
	// line 2: empty
	// line 3: number of modules (int numModule)
	// line 4: empty
	// line 5: number of paths (int numPath)
	// line 6: empty
	// line 7: number of intermodular cost classes (int numInter)
	// line 8: empty
	// line 9: number of intramodular cost classes (int numIntra)
	// line 10: empty
	// starting line 11: DSM (int ** DSM)
	// empty line
	// path definition [numPath lines] (bool ** pathDef)
	// empty line
	// path probabilities [one line] (double * pathProb)
	// empty line
	// intermodular cost class costs [one line] (double * interCost)
	// empty line
	// intermodualr cost class size [one line] (double * interMaxSize)
	// empty line
	// intramodular cost class costs [one line] (double * intraCost)
	// empty line
	// intramodular cost class size [one line] (double * intraMaxSize)
	
	//make new object named "file" for reading data, name in fileName, mode: input operations
	std::fstream file(_fileName.c_str(), std::ios::in);
	
	// check if file was opened
	// FIXME: This could be more elaborate...
	if (!file) {
		std::string str ="SMP2-Error: Could not open file [" + _fileName + "]";
		throw std::runtime_error(str);
	}
	
	// read problem dimensions
	file >> numTask;
	file >> numModule;
	file >> numPath;
	file >> numInter;
	file >> numIntra;
	
	// allocate memory for DSM and read it
	DSM = new int *[numTask];
	for (int i=0; i < numTask; i++) {
		DSM[i] = new int [numTask];
		for (int j=0; j < numTask; j++) {
			file >> DSM[i][j];
		}
	}
	
	// allocate memory for path definitions and read them
	pathDef = new bool *[numPath];
	for (int p=0; p < numPath; p++) {
		pathDef[p] = new bool [numTask];
		for (int i=0; i < numTask; i++) {
			file >> pathDef[p][i];
		}
	}
	
	// allocate memory for path probabilitis and read them
	pathProb = new double [numPath];
	for (int p=0; p < numPath; p++) {
		file >> pathProb[p];
	}
	
	// allocate memory for intermodular cost class costs and read them
	interCosts = new double [numInter];
	for (int i=0; i < numInter; i++) {
		file >> interCosts[i];
	}
	
	// allocate memory for intermodular cost class sizes and read them
	interMaxSize = new int [numInter];
	for (int i=0; i < numInter; i++) {
		file >> interMaxSize[i];
	}
	
	// allocate memory for intramodular cost class costs and read them
	intraCosts = new double [numIntra];
	for (int i=0; i < numIntra; i++) {
		file >> intraCosts[i];
	}
	
	// allocate memory for intermodular cost class sizes and read them
	intraMaxSize = new int [numIntra];
	for (int i=0; i < numIntra; i++) {
		file >> intraMaxSize[i];
	}
	
	// create empty solution
	solution = new int [numTask];
	
	file.close();
}

// Destructor
SMP2::~SMP2() {
	DeleteProblemParameters();
}



/* O P E R A T O R S */
// subseting operator
int& SMP2::operator [](int i) {
	return solution[i];
}

// assignment operator
void SMP2::operator =(SMP2 & _problem) {
	// FIXME: Should it be passed as a const? -> Would be better, wouldn't it, LOOK UP SYNTAX AND FIX IT!
	
	DeleteProblemParameters();
	CopyProblem(_problem);
}



/* G E T T E R S */
int** SMP2::GetDSM() {
	return DSM;
}

double* SMP2::GetInterCosts() {
	return interCosts;
}

int* SMP2::GetInterMaxSize() {
	return interMaxSize;
}

double* SMP2::GetIntraCosts() {
	return intraCosts;
}

int* SMP2::GetIntraMaxSize() {
	return intraMaxSize;
}

int SMP2::GetNumInter() {
	return numInter;
}

int SMP2::GetNumIntra() {
	return numIntra;
}

int SMP2::GetNumModule() {
	return numModule;
}

int SMP2::GetNumPath() {
	return numPath;
}

int SMP2::GetNumTask() {
	return numTask;
}

bool** SMP2::GetPathDef() {
	return pathDef;
}

double* SMP2::GetPathProb() {
	return pathProb;
}



/* C O N V I N I E N C E  -   F U N C T I O N S */
// convinience fuctions for constructors and operators
void SMP2::DeleteProblemParameters() {
	// deletes alls problem depentende matrices and arrays
	// this can be used by the destructor and by the copy assignment
	
	// delete problem parameter arrays
	delete[] pathProb;
	delete[] interCosts;
	delete[] interMaxSize;
	delete[] intraCosts;
	delete[] intraMaxSize;
	
	// delete problem parameter matrices
	// DSM
	if (DSM != NULL) {
		for (int i; i < numTask; i++) {
			delete[] DSM[i];
		}
		delete[] DSM;
	}
	
	// path definition
	// FIXME: Is this right? Shouldn't this als delete the matrix, like the DSM above?
		delete[] pathDef;
		
	// delete solution
	delete[] solution;
	
}

void SMP2::CopyProblem(SMP2 & _problem){
	// copys problem parameters for problem whos reference is passed
	// this can be used by the copy constructor and the copy assignment
	
	// Copy Problem Parameters
	numTask = _problem.GetNumTask();
	numModule = _problem.GetNumModule();
	numPath = _problem.GetNumPath();
	numInter = _problem.GetNumInter();
	numIntra = _problem.GetNumIntra();
	DSM = _problem.GetDSM();
	pathDef = _problem.GetPathDef();
	pathProb = _problem.GetPathProb();
	interCosts = _problem.GetInterCosts();
	interMaxSize = _problem.GetInterMaxSize();
	intraCosts = _problem.GetIntraCosts();
	intraMaxSize = _problem.GetIntraMaxSize();
	
	// Copy Solution and its fitness value
	solution = new int[numTask];
	for (int i = 0; i < numTask; i++) {
		solution[i] = _problem.solution[i];
	}
	if (!_problem.invalid()) {
		fitness(_problem.fitness());
	}
}


// convinience printing of fitness and solution
void SMP2::printFitness() {
	std::cout << "Fitness: " << fitness() << std::endl;
}

void SMP2::printSolution() {
	std::cout << "Solution: ";
	for (int i = 0; i < numTask -1; i++) {
		std::cout << solution[i] << "-";
	}
	std::cout << solution[numTask-1] << std::endl;
}


/* P R O B L E M  -  S P E C I F I C    F U N C T I O N S */

// fullProblem Evaluation
// result of evaluation fuction is equal to the total costs of the current solution
void SMP2::fullEvaluation() {
	
	double totalCosts = 0;
	double intraModularCosts = 0;
	double directInterModularCosts = 0; 
	double indirectInterModularCosts = 0;
	
	// calculate module sizes
	// FIXME: does the creation of the pointer an so forth need 
	// to be done all the time? If this is also needed in the 
	// Greedy part, make it accessable or put it into an extra 
	// privat fuction for code reuse
	int * moduleSize = new int[numModule]();
	for (int i = 0; i < numTask; i++) {
		moduleSize[solution[i]] += 1;
	}
	
	// calculate intramodular coordination costs
	for (int m = 0; m < numModule; m++) {
		//for each module which contains at least one task
		if (moduleSize[m] > 0) {  
			// if it contains at least on task check which size class fits
			// start with the second largest, if it doesn't fit (moduleSize > intraMaxSize,
			// assign costs of largest class and stop. 
			// If it does fit, do nothing and check next size class
			// this assumes, that the last class is big enough to fit always!
			// FIXME: Also: Class could be invalidated instead
			for (int i = numIntra-1; i>= 0; i--) {
				if (moduleSize[m] > intraMaxSize[i-1]) {
					intraModularCosts += intraCosts[i];
					
					//DEBUG
					//std::cout << "Module " << m << "-->" << moduleSize[m] << " Tasks -->" << intraCosts[i] << std::endl;
					
					break; //stop if size fits
				}
			}
		}
	}
	
	
	
	// calculate direct inter modular costs and the number of elements
	// in the ordered upper triangular matrix (numElm[p]) for each path, 
	// which is needed in the calculation of the indirect intermodular costs
	// FIXME: See remarks for moduleSize
	int* numElm = new int[numPath](); //array for counting element number
	
	// go through all possible element combinations
	// FIXME: Could save a small amount of time, if i = j would be skipped -> maybe take a look at iterators?
	// FIXME: This nested loop looks really ugly and seems to be too large to understand easily
	for (int i = 0; i < numTask; i++) {
		for (int j = 0; j < numTask; j++) {
			// only consider costs if element is in upper triagular matrix, i.e. module for j is greater then module for i
			if (solution[i] < solution[j]) {
				// only do the following if there are any costs at all and do for each path
				if (DSM[i][j] > 0) {
					for (int p = 0; p < numPath; p++) {
						// check if it is relevant on that path
						if (pathDef[p][i] && pathDef[p][j]) {
							//increase number of elements for that path
							numElm[p] += 1;
							
							// add costs to direct intermodular costs, minding path prob
							directInterModularCosts += ( DSM[i][j] * pathProb[p] );
						}
					}
				}
			}	
		}
	}
	
	
	// calculate indirect intermodular coordination costs on basis of numElm
	// uses same procedure as intramodular coordination costs
	// and repeats it for each possible path and considers paths probabilities
	for (int p = 0; p < numPath; p++) {
		// only do if there are any costs to add. CAUTION: this assumes that no elements means no costs!
		if (numElm[p] > 0) {
			// check for each size class if it fits and assign costs accordingly
			for (int i = numInter - 1 ; i >= 0; i--) {
				if (numElm[p] > interMaxSize[i-1]) {
					indirectInterModularCosts += interCosts[i] * pathProb[p];
					break; //stopp if class size fits
				}
			}
		}
	}
	
	// add all costs components
	totalCosts = intraModularCosts + directInterModularCosts + indirectInterModularCosts;
	
	// assign solution value
	fitness(totalCosts);
}

// Random Problem Initialization
void SMP2::RandomInit() {
	// Randomly assign each task to a module
	for (int i = 0; i < numTask; i++) {
		solution[i] = rng.rand() % (numModule);
	}
}
