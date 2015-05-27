/* This source file descripes the parameters and default values
 * which make up the command line interface to the GRASP implementation
 * */

struct parameters {
	unsigned seed;
	std::string problemFile;
	std::string outputFile;
};


void parseFile(eoParser & parser, parameters & param) {

	// For each parameter, you can in on single line
	// define the parameter, read it through the parser, and assign it
	param.seed = parser.createParam( 
		unsigned(time(0)),
		"seed",
		"Random number seed",
		's'
		).value();
										
	param.problemFile = parser.createParam( 
		std::string("../../problems/Test4-10-5.dat"),
		"problemFile",
		"Path to problem file",
		'p',
		"Param"
		).value();	
	
	param.outputFile = parser.createParam(
		std::string("output.csv"),
		"resultsFile",
		"Path to the results output file",
		'o',
		"Param"
		).value();
	
	/*
	param.seed = parser.createParam(unsigned(time(0)), "seed", "Random number seed", 'S').value(); // will be in default section General
	param.popSize = parser.createParam(unsigned(15), "popSize", "Population size",'P', "Evolution engine" ).value();
	param.loadName = parser.createParam(string(""), "Load","A save file to restart from",'L', "Persistence" ).value();
	param.inst = parser.createParam(string(""), "inst","A data file to read instances from",'i', "Persistence" ).value();
	param.schema = parser.createParam(string(""), "schema","An xml file mapping processes",'s', "Persistence" ).value();
	param.TSmaxIter = parser.createParam(unsigned(1000), "TSmaxIter", "Maximum number of iterations",'M', "Tabu Search" ).value();
	param.tabuListSize = parser.createParam(unsigned(10), "tabuListSize", "Tabu List Size",'l', "Tabu Search" ).value();
	param.tSize = parser.createParam(unsigned(2), "tSize", "Tournament size",'T', "Evolution Engine" ).value();
	param.minGen = parser.createParam(unsigned(100), "minGen", "Minimum number of iterations",'g', "Stopping criterion" ).value();
	param.maxGen = parser.createParam(unsigned(300), "maxGen", "Maximum number of iterations",'G', "Stopping criterion" ).value();
	param.pCross = parser.createParam(double(0.6), "pCross", "Probability of Crossover", 'C', "Genetic Operators" ).value();
	param.pMut = parser.createParam(double(0.1), "pMut", "Probability of Mutation", 'M', "Genetic Operators" ).value();
	param.nbMigrants = parser.createParam(unsigned(6), "nbMigrants", "Number of migrants",'n', "Migration Policy" ).value();
	param.manGeneration = parser.createParam(unsigned(5), "manGeneration", "Migration at N generations",'N', "Migration Policy" ).value();
	// the name of the "status" file where all actual parameter values will be saved
	string str_status = parser.ProgramName() + ".status"; // default value
	string statusName = parser.createParam(str_status, "status","Status file",'S', "Persistence" ).value();

	// do the following AFTER ALL PARAMETERS HAVE BEEN PROCESSED
	// i.e. in case you need parameters somewhere else, postpone these
	if (parser.userNeedsHelp())
	{
		parser.printHelp(cout);
		exit(1);
	}
	if (statusName != "")
	{
		ofstream os(statusName.c_str());
		os << parser;		// and you can use that file as parameter file
	}*/
}