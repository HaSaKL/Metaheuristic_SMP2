// This function generates problems and writes them to an output file
// it exactly follows the specifications given in SMP2.cpp

#include <utils/eoRNG.h> // for random number generator
#include <fstream>
#include <bitset> 

// Function Prototypes
void SampleWithoutReplacement (int populationSize, int sampleSize, std::vector<int> & samples);

void GenerateProblem(std::string ProblemName, 
						int DSM_size, int DSM_maxValue, double DSM_density, int ModuleNum,
						int PathNum, 
						int InterModularNum, double BaseInterModularCost, double GrowInterModularCost,
						int IntraModularNum, double BaseIntraModularCost, double GrowIntraModularCost) {
	
	// Assert Module Num  --> see that the number of modules is larger then the number of tasks devided by the maximum legal module size
	if (ModuleNum <= DSM_size / (IntraModularNum-1) ) {
		std::cout << "Please choose a larger number of Modules. The minimum number of modules for this problem is: " << 1 + (int)DSM_size / (IntraModularNum-1) << std::endl;
		throw;
	}
							
	/////////
	/* DSM */
	/////////
	
	// allocate memory for DSM and set all elements to zero as default
	std::vector<int> DSM(DSM_size * DSM_size);
	
	// create vector of element indices
	unsigned int NumDSMElm = DSM_size * (DSM_size - 1);
	unsigned int NumActiveDSMElm = floor(NumDSMElm * DSM_density);
	std::vector<int> ElementIdx(NumDSMElm);
	
	// select elements which should be set
	SampleWithoutReplacement(NumDSMElm, NumActiveDSMElm, ElementIdx);
	
	int DSM_total_sum = 0; // this is used for setting max costs
	int DSM_idx;
	// set those elements to a random value, be careful with element index, since it does not consider zeros on diagonal yet
	for (int i = 0; i < NumActiveDSMElm; i++) {
		DSM_idx = 1 + ElementIdx[i] + (int) ElementIdx[i] / DSM_size;
		DSM[DSM_idx] = rng.random(DSM_maxValue) + 1;
		DSM_total_sum += DSM[DSM_idx];
	}
	

	/////////////////////////////
	/* Path Classes Definition */
	/////////////////////////////

	std::vector< std::vector <bool> > PathDef(PathNum, std::vector<bool>(DSM_size));

	// determine power of two which is closed yet bigger number compared to Path_Num -> This will determine the number of elements
	// which vary for each path (2^x > Path_Num, what is x? -> x >= log(Path_Num) / log(2) )
	// this ensures that the number of fixed elements is a big as possible -> more realistic case, also realized like this in the examples
	int numPosPathFlips = (int)ceil( log(PathNum) / log(2) );

	// determine flipable elements
	std::vector<int> FlipElementIdx(numPosPathFlips);
	SampleWithoutReplacement(DSM_size, numPosPathFlips, FlipElementIdx);
	
	// draw permutation index for each path
	std::vector<int> PathPermIdx(PathNum);
	SampleWithoutReplacement(pow(2,numPosPathFlips), PathNum, PathPermIdx);
	
	std::bitset<32> PathPerm; // used for converting the index. Max Number of Paths is now 4 Billion, make sure it is not superpassed
	
	// construct each path based on the permutation index
	for (int path = 0; path < PathNum; path ++) {
		for (int task = 0; task < DSM_size; task ++ ) {
			// set to default, which is task is part of path
			PathDef[path][task] = 1;
		}
		// now set task to path specific value, overwrite default
		PathPerm = PathPermIdx[path];
		for (int i = 0; i < numPosPathFlips; i++) {
			PathDef[path][FlipElementIdx[i]] = PathPerm[i];
		}
	}
	
	
	////////////////////////////////
	/* Path Classes Probabilities */
	////////////////////////////////
	
	// make the path probabilities by drawing a random number for each path and then noramlize the prob by the sum of all drawn numbers
	std::vector<double> PathProb(PathNum);
	double Prob_sum = 0;
	double tmp = 0;
	for (int p = 0; p < PathNum; p++) {
		tmp = rng.uniform();
		PathProb[p] = tmp;
		Prob_sum += tmp;
	}
	for (int p = 0; p < PathNum; p++) {
		PathProb[p] = PathProb[p] / Prob_sum;
	}
	
	
	////////////////////////////////
	/* Intermodular Costs Classes */
	////////////////////////////////
	
	if (InterModularNum < 2 || InterModularNum > ( ((DSM_size-1)*DSM_size)/2 ) ) {
		std::cout << "Number of Inter Modular Coordination Cost Classes is either too small (<1) ot too large (> ((Task-1)*Task) /2).";
		throw;
	}
	
	std::vector<int> InterModularSize(InterModularNum + 1);
	std::vector<double> InterModularCost(InterModularNum + 1);
	
	// evenly devide the number of classes between the maximum and the minimum class size
	// the minimum class size is zero and the maximum class size is the number of elements in the upper triangular matrix
	int minSize = 0;
	int maxSize = ceil( ((DSM_size-1)*DSM_size) / 2 ); // this is the maximum number of elements in upper triangular matrix
	
	InterModularSize[0] = minSize;
	InterModularSize[InterModularNum] = maxSize;
	
	for (int i = 1; i < InterModularNum; i++) {
		InterModularSize[i] = floor( (maxSize / (InterModularNum - 1)) * i ); // "InterModularNum - 1" b/c first size class is taken by zero
	}
	
	
	// calculate the curresponding costs
	// costs for first class (size zero) must be zero; costs for last class (full upper triangular matrix) must be extremely high (sum of all DSM_elements)
	InterModularCost[0] = 0;
	InterModularCost[InterModularNum] = DSM_total_sum;
	
	// calcualte the costs intbetween
	for (int i=1; i < InterModularNum; i++) {
		InterModularCost[i] = BaseInterModularCost * pow ( (InterModularSize[i] / InterModularSize[1]),
																 (log10(1 + GrowInterModularCost) / log10(2) ));
	}
	

	

	////////////////////////////////
	/* Intramodular Costs Classes */
	////////////////////////////////
	
	if (IntraModularNum < 2 || IntraModularNum > DSM_size + 1) {
		std::cout << "Number of Intra Modular Coordination Cost Classes is either too small (<2) ot too large (> DSM_size + 1).";
		throw;
	}
	
	std::vector<int> IntraModularSize(IntraModularNum + 1);
	std::vector<double> IntraModularCost(IntraModularNum + 1);
	
	// evenly devide the number of classes between the maximum and the minimum class size
	// the minimum class size is zero and the maximum class is the number of all elements
	minSize = 0;
	maxSize = DSM_size;
	
	IntraModularSize[0] = minSize;
	IntraModularSize[IntraModularNum] = maxSize;

	// set maximum class sizes of all other classes in steps of one. Class 1 - max 1; class 2 -max 2, and so forth
	for (int i = 1; i < IntraModularNum; i++) {
		IntraModularSize[i] = i;
	}
	
	
	// calculate the curresponding costs
	// costs for first class (size zero) must be zero; costs for last class (full upper triangular matrix) must be extremely high (sum of all DSM_elements)
	IntraModularCost[0] = 0;
	IntraModularCost[IntraModularNum] = DSM_total_sum;
	
	// calcualte the costs intbetween
	for (int i=1; i < IntraModularNum; i++) {
		IntraModularCost[i] = BaseIntraModularCost * pow ( (IntraModularSize[i] / IntraModularSize[1]),
																 (log10(1 + GrowIntraModularCost) / log10(2) ));
	}
	
	
	////////////////////////
	/* WIRTE PROBLEM FILE */
	////////////////////////
	
	// initialize output
	std::ofstream outputFile;
	outputFile.open(ProblemName.c_str());
	
	
	// write DSM_size
	outputFile << DSM_size << std::endl << std::endl;
	
	
	// write Number of Modules
	outputFile << ModuleNum << std::endl << std::endl;
	
	
	// write number of paths
	outputFile << PathNum << std::endl << std::endl;
	
	
	// write number of intermodulare costs classes
	outputFile << InterModularNum+1 << std::endl << std::endl;
	
	
	// write number of intramodulare costs classes
	outputFile << IntraModularNum+1 << std::endl << std::endl;
	
	
	// write DSM
	for (int i=0; i < DSM_size; i++) {
		for (int j=0; j < DSM_size; j++) {
			outputFile << DSM[i * DSM_size + j] << " ";
		}
		outputFile << std::endl;
	}
	outputFile << std::endl;


	// write Path Definition
	for (int p=0; p < PathNum; p++) {
		for (int i = 0; i < DSM_size; i++) {
			outputFile << PathDef[p][i] << " ";
		}
		outputFile << std::endl ;
	}
	outputFile << std::endl;
	
	
	// write Path Probabilities
	for (int p=0; p < PathNum; p++) {
		outputFile << PathProb[p];
	}
	outputFile << std::endl << std::endl;
	
	
	// write intermodular cost class costs
	for (int i = 0; i < InterModularCost.size(); i++) {
		outputFile << InterModularCost[i] << " ";
	}
	outputFile << std::endl << std::endl;
	
	
	// write intermodular cost class size
	for (int i = 0; i < InterModularSize.size(); i++) {
		outputFile << InterModularSize[i] << " ";
	}
	outputFile << std::endl << std::endl;
	
	
	// write intramodular cost class cost
	for (int i = 0; i < IntraModularCost.size(); i++) {
		outputFile << IntraModularCost[i] << " ";
	}
	outputFile << std::endl << std::endl;
	
	// write intramodular cost class size
	for (int i = 0; i < IntraModularSize.size(); i++) {
		outputFile << IntraModularSize[i] << " ";
	}
	outputFile << std::endl << std::endl;

	// close file after writing
	outputFile.close();
}


// Function samples over a range of all possibilities without replacement by shuffeling a vector
//http://stackoverflow.com/questions/311703/algorithm-for-sampling-without-replacement
// this is supposed to be based on 
// Algorithm 3.4.2S of Knuth's book Seminumeric Algorithms.
void SampleWithoutReplacement
(
    int populationSize,    // size of set sampling from
    int sampleSize,        // size of each sample
    std::vector<int> & samples  // output, zero-offset indicies to selected items
)
{
    // Use Knuth's variable names
    int& n = sampleSize;
    int& N = populationSize;

    int t = 0; // total input records dealt with
    int m = 0; // number of items selected so far
    double u;

    while (m < n)
    {
        u = rng.uniform(); // call a uniform(0,1) random number generator

        if ( (N - t)*u >= n - m )
        {
            t++;
        }
        else
        {
            samples[m] = t;
            t++; m++;
        }
    }
}