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
	
	for (DSM_size = 10; DSM_size < 101; DSM_size = DSM_size + 10) {
		
		oss.str("");
		oss << DSM_size;
		
		Filename = std::string("size_test/KH_size");
		Filename.append(oss.str());
		Filename.append(".dat");
		
		MaxModuleSize = ceil ( (3 * DSM_size) / 10 );	// this is the formular described above solved for MaxModuleSize
		
		GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
	}
	
	
	
	// make problems with different densities - fix rest
	std::cout << "Making Problems with different densities ... " << std::endl;
	rng.reseed(seed);
	
	system("mkdir density_test");
	
	DSM_size = 20;
	DSM_MaxVal = 6;
	ModuleNum = 10;
	PathNum = 16;
	MaxModuleSize = 6;	
	PathNum = 16;
	InterClassNum = 10;
	
	for (DSM_density = 0.1; DSM_density < 1.01; DSM_density = DSM_density + 0.1) {
		
		oss.str("");
		oss << "0" << DSM_density*100;
		
		Filename = std::string("density_test/KH_density");
		Filename.append(oss.str());
		Filename.append(".dat");
		
		GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
	}
	
	
	
	// make problems with different paths - fix rest
	std::cout << "Making Problems with different PathNumbers ... " << std::endl;
	rng.reseed(seed);
	system("mkdir path_test");
	
	DSM_size = 20;
	DSM_MaxVal = 6;
	DSM_density = 0.69;
	ModuleNum = 10;
	MaxModuleSize = 6;	
	PathNum = 16;
	InterClassNum = 10;
	
	for (PathNum = 2; PathNum < 1025; PathNum = PathNum * 2) {
		
		oss.str("");
		oss << PathNum;
		
		Filename = std::string("path_test/KH_path");
		Filename.append(oss.str());
		Filename.append(".dat");
		
		GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
	}
	
	
	// make problems with different number intramodular classes - fix rest
	std::cout << "Making Problems with different Number of IntraModular Classes ..." << std::endl;
	rng.reseed(seed);
	
	system("mkdir moduleSize_test");
	
	DSM_size = 20;
	DSM_MaxVal = 6;
	DSM_density = 0.69;
	ModuleNum = 10;
	MaxModuleSize = 6;	
	PathNum = 16;
	InterClassNum = 10;
	
	for (MaxModuleSize = 3; MaxModuleSize < 21; MaxModuleSize = MaxModuleSize + 2) {
		
		oss.str("");
		oss << MaxModuleSize;
		
		Filename = std::string("moduleSize_test/KH_moduleSize");
		Filename.append(oss.str());
		Filename.append(".dat");
		
		GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
	}
	
	
	
	// make problems with different number of intermodular classes -fix rest
	std::cout << "Making Problems with different Number of InterModular Classes ... " << std::endl;
	rng.reseed(seed);
	
	system("mkdir intermodular_test");
	
	DSM_size = 20;
	DSM_MaxVal = 6;
	DSM_density = 0.69;
	ModuleNum = 10;
	MaxModuleSize = 6;	
	PathNum = 16;
	InterClassNum = 10;
	
	for (InterClassNum = 5; InterClassNum < 50 + 1; InterClassNum = InterClassNum + 5) {
		
		oss.str("");
		oss << InterClassNum;
		
		Filename = std::string("intermodular_test/KH_intermodular");
		Filename.append(oss.str());
		Filename.append(".dat");
		
		GenerateProblem(Filename, DSM_size, DSM_MaxVal, DSM_density, ModuleNum, PathNum, InterClassNum, 2, 1.1, MaxModuleSize + 1, 0.75, 2);
	}
	

	// make one with same structure as Test16-13-7.dat
	// rng.reseed(seed);
	// GenerateProblem(std::string("Test.dat"), 13, 6, 0.69, 7, 16, 10, 1, 1.1, 6, 0.75, 2);
}