cmake_minimum_required(VERSION 2.8.12)

project(bonus)

#if (EXISTS "${CMAKE_SOURCE_DIR}/minisat")
#  add_subdirectory(minisat)
#else()
#  message (FATAL_ERROR "MiniSat not found. Use `git clone https://github.com/agurfinkel/minisat` to check it out.")
#endif()

# enable c++11 support
set (CMAKE_CXX_FLAGS "-std=c++11 -Wall ${CMAKE_CXX_FLAGS}")

## expose minisat header files
#include_directories(${CMAKE_SOURCE_DIR}/minisat)

# create the main executable
## change .cpp files if needed
add_executable(${PROJECT_NAME} main.cc tseitinTransformer.cc tseitinTransformer.h satSolver.cc error.cpp parser.cc token.cpp tokenizer.cc treeNode.cc DPLLSolver.cpp DPLLSolver.h nnfTransformer.cpp nnfTransformer.h QueMap.cpp QueMap.h)
## link MiniSAT libraries
#target_link_libraries(${PROJECT_NAME} minisat-lib-static)

# create the executable for tests
add_executable(tests tseitinTransformer.cc tseitinTransformer.h satSolver.cc  satSolver.cc error.cpp parser.cc token.cpp tokenizer.cc treeNode.cc DPLLSolver.cpp DPLLSolver.h testDPPLLSolver.cpp nnfTransformer.cpp nnfTransformer.h QueMap.cpp QueMap.h)
## link MiniSAT libraries
#target_link_libraries(tests minisat-lib-static)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
