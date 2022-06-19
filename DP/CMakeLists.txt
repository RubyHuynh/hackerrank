cmake_minimum_required(VERSION 3.10)

project(dp)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "-Wwrite-strings")

INCLUDE_DIRECTORIES(/usr/include)
LINK_DIRECTORIES(/usr/lib64)

add_executable(bestContruct bestConstruct.cpp)
#TARGET_LINK_LIBRARIES(learning boost_filesystem-mt boost_filesystem boost_system)



