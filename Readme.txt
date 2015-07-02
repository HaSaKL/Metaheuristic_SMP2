This project contains all source files and tests for the essay "Untersuchung zur Leistungsfähigkeit optimierender und heuristischer Verfahren der Dienstleistungsmo-dularisierung"
by Hans Corsten and Hagen Salewski

The folder "algorithm" holds all source codes to compile a couple of GRASP-based applications which can solve the Simulaneous Multi-Path Service Modularisation Problem (SMP)²

To compile, you need to have version 2.0.1 of ParadisEO (http://paradiseo.gforge.inria.fr/index.php?n=Doc.Install) and all it requirements installed. Then:
- mkdir algorithm/build
- cd algorithm/build
- cmake ..
- make

After the compilation all applications can be found in "algorithms/build/applications"

There are some test applications and some productive applications. For the tests only the application SMP2_TimeToTarget is used, it takes the following command line arguments:
	test problem instance 	(-p="TakeProblemFromHere.dat")
	random seed		(-s=12345)
	result file 		(-o="PutResultsInHere.csv")
	neighborhood definition	(-n=1 for Adjecent Element Flip, -n=2 for Element Flip)
	local search algorithm  (-l=1 for Best Improvement, -l=2 for First Random Better Improvement)
	alpha value		(-a=0.1 or any other number in [0,1] or -a=R for Reactive GRASP od -a=E for random Alpha)
	target value		(-t=44.52)
	number of T2T-trials	(-I=10000)
	max runtime in seconds	(-T=3600 for running for 1 hour and set best result as target value - only important if no target value is proviede)


The folder "tests" is self contained and holds all tests, compiled SMP2_TimeToTarget, R-Scripts and Bash-Scrips required to run the tests. In each test-subfolder you can run the tests by executing the Bash script "Run.sh":
./Run.sh


For question please contact the author:
Dr. Hagen Salewski
Department of Business Administration and Production Management
University of Kaiserslautern
Gottlieb-Daimler-Str. 42
67663 Kaiserslautern
Germany

Email: salewski@wiwi.uni-kl.de
