cmake_minimum_required(VERSION 3.13)
project(PhysicalNumber)

set(CMAKE_CXX_STANDARD 17)

add_executable(PhysicalNumber PhysicalNumber.hpp Unit.hpp PhysicalNumberDemo.cpp PhysicalNumber.cpp)