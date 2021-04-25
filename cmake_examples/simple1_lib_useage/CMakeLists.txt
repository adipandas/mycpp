cmake_minimum_required(VERSION 2.8)
add_executable(simple1_lib_useage main.cpp)
target_link_libraries(simple1_lib_useage ../simple1_lib/build/libSimple.so)
