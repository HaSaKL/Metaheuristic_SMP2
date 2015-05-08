include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set (SMP2_SOURCES
		SMP2.cpp
		)
		
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
add_library (lSMP2 ${SMP2_SOURCES})