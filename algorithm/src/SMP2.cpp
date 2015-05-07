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
	if (pathDef != NULL) {
		for (int p; p < numPath; p++) {
			delete[] pathDef[p];
		}
		delete[] pathDef;
	}
	
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
