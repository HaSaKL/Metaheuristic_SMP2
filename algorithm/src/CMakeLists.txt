include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set (SMP2_SOURCES
		SMP2.cpp
		SMP2_Eval.h
		SMP2_GreedyInit.cpp
		
		SMP2_ElementFlip_Neighbor.cpp
		SMP2_ElementFlip_IncrEval.h
		
		SMP2_AdjElementFlipIndex_Neighbor.cpp
		SMP2_AdjElementFlip_Neighborhood.cpp
		
		SMP2_CLI.h
		)
				
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
add_library (lSMP2 ${SMP2_SOURCES})