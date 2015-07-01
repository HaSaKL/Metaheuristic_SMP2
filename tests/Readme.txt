The folder "non_random" holds all test on non-random problem instances, the folder "random" holds all tests on randomly generated problem instances.
Each test is contained inside a sub-folder and can be reproduced.

Each test folder holds:
- an Executable which runs the actual test (e.g. SMP2_TimeToTarget)
- several problem instances with descriptive names (e.g. KH_density30-5.dat for 5th problem instance for the density test with density of 30%)
- a bash script which calls the executable with the appropriate parameters for each problem
- a results file (*.csv), which in some cases is compressed (*.csv.bz2)
- an R script (*.R) to evaluate the test and produce the plots
- a single or a set of plots (*.png)