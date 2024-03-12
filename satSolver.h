#ifndef SAT_H
#define SAT_H

#include <vector>
#include "tokenizer.h"
#include "parser.h"
#include "tseitinTransformer.h"
#include <memory>
#include "DPLLSolver.h"
#include "nnfTransformer.h"

class SATSolver {
private:
    Parser* parser;
    TseitinTransformer* tseitinTransformer;
    DPLLSolver* dpllSolver;
    NnfTransformer* nnfTransformer;


public:
    SATSolver();
    virtual ~SATSolver();
    /**
     * @param line: a string in the form of "formula; assignment"
     * @return a boolean value for the formula based on the assignment.
     */
     bool solve(std::string line);

};

#endif
