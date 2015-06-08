include_directories(${PARADISEO_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(SMP2_TimeToTarget smp2_TimeToTarget.cpp)
target_link_libraries(SMP2_TimeToTarget ${PARADISEO_LIBRARIES})
target_link_libraries(SMP2_TimeToTarget lSMP2)

add_executable(SMP2_grasp_test smp2_grasp_test.cpp)
target_link_libraries(SMP2_grasp_test ${PARADISEO_LIBRARIES})
target_link_libraries(SMP2_grasp_test lSMP2)

add_executable(SMP2_test smp2_test.cpp)
target_link_libraries(SMP2_test ${PARADISEO_LIBRARIES})
target_link_libraries(SMP2_test lSMP2)

add_executable(SMP2_flipnh_test smp2_flipnh_test.cpp)
target_link_libraries(SMP2_flipnh_test ${PARADISEO_LIBRARIES})
target_link_libraries(SMP2_flipnh_test lSMP2)
