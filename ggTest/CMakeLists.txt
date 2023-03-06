
project(GGTest1)

add_executable (sample sample.cpp )
target_link_libraries ( sample gtest pthread)

