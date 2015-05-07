include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(SMP2_test smp2_test.cpp)

target_link_libraries(SMP2_test ${PARADISEO_LIBRARIES})
target_link_libraries(SMP2_test lSMP2)