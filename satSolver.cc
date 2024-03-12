#include <iostream>
#include "satSolver.h"
#include "error.h"
#include "treeNode.h"

SATSolver::SATSolver() {
    parser = new Parser();
    tseitinTransformer = new TseitinTransformer();
    dpllSolver = new DPLLSolver();
    nnfTransformer = new NnfTransformer();
}

bool SATSolver::solve(std::string line) {
    parser->parse(line);
    TreeNode* root = parser->getRoot();
    nnfTransformer->transform(root);
    std::vector<std::vector<int>>* cnf = tseitinTransformer->transform(root);
    return dpllSolver->solve(*cnf);
}

SATSolver::~SATSolver() {

}




