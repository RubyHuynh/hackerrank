
project(GGTest1)
add_compile_options(-std=c++0x)
add_executable (sample sample.cpp )
add_executable (minimumTime ../2187_minimumTime.cpp )
target_link_libraries (sample gtest pthread)
target_link_libraries (minimumTime gtest pthread)

