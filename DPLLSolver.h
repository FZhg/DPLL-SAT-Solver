//
// Created by Zhang Fan on 2022-12-05.
//

#ifndef BONUS_DPLLSOLVER_H
#define BONUS_DPLLSOLVER_H


#include <vector>
#include <map>
#include <queue>
#include <utility>
#include "QueMap.h"

class DPLLSolver {
private:
     QueMap<int, bool> assignment;
    std::vector<std::vector<int>> bcp(std::vector<std::vector<int>> cnf);
    std::vector<std::vector<int>> plp(std::vector<std::vector<int>> cnf);
    bool dpll(std::vector<std::vector<int>> cnf);

public:
    DPLLSolver();
    bool solve(std::vector<std::vector<int>> cnf);
};


#endif //BONUS_DPLLSOLVER_H
