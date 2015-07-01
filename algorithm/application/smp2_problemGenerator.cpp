#include "ProblemGenerator.h"
#include <sstream>
#include <cstdlib>  // for system()

// This programm will generate a set of test instances which can be used to test
// different heurisitce for the SMP2, all it does is call the problemGenerator-fuction
// from the SMP2 library with a specified set of parameters

int main(int argc, char* argv[]) {
	unsigned int seed = 19510210;
	
	std::string Filename;
	std::ostringstream oss;
	
	// varaibels which can be changed to generate problems with example values for hospital problem instance
	int DSM_size = 13;
	double DSM_density = 0.69;
	int DSM_MaxVal = 6;
	int ModuleNum = 10;
	int MaxModuleSize = 5;
	int PathNum = 16;
	int InterClassNum = 10;
	
	// make problems in different sizes - fix rest, only update MaxModule Size to generate valid problems
	// start with 10 modules with size five and increase size, such that the proportion
	// of (ModuleNumber * MaxModuleSize) / DSM_Size is about 3 (like in the original problem) which worked well
	
	rng.reseed(seed);
	std::cout << "Making Problems with different sizes ... " << std::endl;
	system("mkdir size_test");
	
	DSM_MaxVal = 6;
	DSM_density = 0.69;
	ModuleNum = 10;
	PathNum = 16;
	MaxModuleSize = 5;	
	PathNum = 16;
	InterClassNum = 10;
	
	for (DSM_size = 13; DSM_size < 32; DSM_size = DSM_size + 2) {
		
		MaxModuleSize = ceil ( (3 * DSM_size) / 10 );	// this is the formular described above solved for MaxModuleSize
		
		// make more than one random problem per density, to get a better variation of times...
		for (int i = 1; i < 11; i++) {
			
			Filename = std::string("size_test/KH_size");
			
			oss.str("");
			oss << DSM_size << "-" << i;
			
			Filename.append(oss.str());
			Filename.append(".dat");
			
			GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
		}
	}
	
	
	
	// make problems with different densities
	std::cout << "Making Problems with different densities ... " << std::endl;
	rng.reseed(seed);
	
	system("mkdir density_test");
	
	DSM_size = 13;
	DSM_MaxVal = 6;
	ModuleNum = 10;
	PathNum = 16;
	MaxModuleSize = 6;	
	PathNum = 16;
	InterClassNum = 10;
	
	for (DSM_density = 0.1; DSM_density < 1; DSM_density = DSM_density + 0.1) {
		
		// make more than one random problem per density, to get a better variation of times...
		for (int i = 1; i < 11; i++) {
			
			Filename = std::string("density_test/KH_density");
			
			oss.str("");
			oss << "0" << DSM_density*100 << "-" << i;
			
			Filename.append(oss.str());
			Filename.append(".dat");
			
			GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
		}
	}
	
	
	// make problems with different paths - fix rest
	std::cout << "Making Problems with different PathNumbers ... " << std::endl;
	rng.reseed(seed);
	system("mkdir path_test");
	
	DSM_size = 13;
	DSM_MaxVal = 6;
	DSM_density = 0.50;
	ModuleNum = 10;
	MaxModuleSize = 6;	
	PathNum = 16;
	InterClassNum = 10;
	
	for (PathNum = 16; PathNum < 1025; PathNum = PathNum * 2) {
		
		// make more than one random problem per density, to get a better variation of times...
		for (int i = 1; i < 11; i++) {
		
			Filename = std::string("path_test/KH_path");
			
			oss.str("");
			oss << PathNum << "-" << i;
			
			Filename.append(oss.str());
			Filename.append(".dat");
			
			GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
		
		}
	}
	
	
	// make problems with different number intramodular classes - fix rest
	std::cout << "Making Problems with different Number of IntraModular Classes ..." << std::endl;
	rng.reseed(seed);
	
	system("mkdir moduleSize_test");
	
	DSM_size = 13;
	DSM_MaxVal = 6;
	DSM_density = 0.5;
	ModuleNum = 10;
	MaxModuleSize = 6;	
	PathNum = 16;
	InterClassNum = 10;
	
	for (MaxModuleSize = 3; MaxModuleSize < 13; MaxModuleSize = MaxModuleSize + 1) {
		
		// make more than one random problem per density, to get a better variation of times...
		for (int i = 1; i < 11; i++) {
			
			Filename = std::string("moduleSize_test/KH_moduleSize");
			
			oss.str("");
			oss << MaxModuleSize << "-" << i;
			
			Filename.append(oss.str());
			Filename.append(".dat");
			
			GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
		}
	}
	
	
	
	// make problems with different number of intermodular classes -fix rest
	std::cout << "Making Problems with different Number of InterModular Classes ... " << std::endl;
	rng.reseed(seed);
	
	system("mkdir intermodular_test");
	
	DSM_size = 13;
	DSM_MaxVal = 6;
	DSM_density = 0.5;
	ModuleNum = 10;
	MaxModuleSize = 6;	
	PathNum = 16;
	InterClassNum = 10;
	
	for (InterClassNum = 5; InterClassNum < 50 + 1; InterClassNum = InterClassNum + 5) {
		
		// make more than one random problem per density, to get a better variation of times...
		for (int i = 1; i < 11; i++) {
			
			Filename = std::string("intermodular_test/KH_intermodular");
			
			oss.str("");
			oss << InterClassNum << "-" << i;
			
			Filename.append(oss.str());
			Filename.append(".dat");
			
			GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
		}
	}
	

}