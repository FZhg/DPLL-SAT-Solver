//
// Created by Zhang Fan on 2022-12-06.
//
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "DPLLSolver.h"
#include "tseitinTransformer.h"
#include "QueMap.h"



TEST_CASE("Test for quemap"){
    QueMap<int, bool> assignment = QueMap<int, bool>();
    assignment.push(1, true);
    CHECK(assignment.size() == 1);
}