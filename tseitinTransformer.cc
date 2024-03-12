#include "tseitinTransformer.h"
#include "error.h"
TseitinTransformer::TseitinTransformer(){
    cnf = new std::vector<std::vector<int>>();
    varIdTable = new std::map<std::string, int>();
}

void TseitinTransformer::addSubformulaEncoding(TreeNode* subRoot, int subRootRep) {
  // your code starts here
  if(subRoot == nullptr){
      return;
  } else{
      switch (subRoot->getType()) {
          case variable:
              return; // base case; reached the leaf
          case connective:
              if (subRoot->getStrRep() == "-"){
                  int childRep = getRep(subRoot->getLeftChild());
                  addNegEq(subRootRep, childRep);
                  addSubformulaEncoding(subRoot->getLeftChild(), childRep);
                  return;
              } else if(subRoot->getStrRep() == "+"){
                  int F1Rep = getRep(subRoot->getLeftChild());
                  int F2Rep = getRep(subRoot->getRightChild());
                  addOrEq(subRootRep, F1Rep, F2Rep);
                  addSubformulaEncoding(subRoot->getLeftChild(), F1Rep);
                  addSubformulaEncoding(subRoot->getRightChild(), F2Rep); // recurse
                  return;
              } else if(subRoot->getStrRep() == "*"){
                  int F1Rep = getRep(subRoot->getLeftChild());
                  int F2Rep = getRep(subRoot->getRightChild());
                  addAndEq(subRootRep, F1Rep, F2Rep);
                  addSubformulaEncoding(subRoot->getLeftChild(), F1Rep);
                  addSubformulaEncoding(subRoot->getRightChild(), F2Rep); // recurse
                  return;
              }
      }
  }
}

void TseitinTransformer::addNegEq(int negRep, int FRep) {
  // your code starts here
    addTwoLiteralsClause(-negRep, -FRep);
    addTwoLiteralsClause(negRep, FRep);
}

void TseitinTransformer::addOrEq(int orRep, int F1Rep, int F2Rep) {
  // your code starts here
    addThreeLiteralsClause(-orRep, F1Rep, F2Rep);
    addTwoLiteralsClause(-F1Rep, orRep);
    addTwoLiteralsClause(-F2Rep, orRep);
}

void TseitinTransformer::addAndEq(int andRep, int F1Rep, int F2Rep) {
  // your code starts here
    addTwoLiteralsClause(-andRep, F1Rep);
    addTwoLiteralsClause(-andRep, F2Rep);
    addThreeLiteralsClause(-F1Rep, -F2Rep, andRep);
}

std::vector<std::vector<int>>* TseitinTransformer::transform(TreeNode* root) {
    // your code starts here
    setFormulaRoot(root);
    int rootRep = getRep(root);
    addOneLiteralClause(rootRep);
    addSubformulaEncoding(root, rootRep);
  return cnf;
}

void printCnf(std::vector<std::vector<int>>* cnf)  {
  std::ostringstream result;
    for (unsigned int i = 0; i < cnf->size(); ++i) {
        std::vector<int> clause = (*cnf)[i];
        result << "[";
        bool first = true;
        for (unsigned int j = 0; j < clause.size(); ++j) {
            if (!first) {
                result << ", ";
            }
            result << clause[j];
            first = false;
        }
        result << "]";
    }
    std::cout << result.str() << std::endl;
}


TreeNode *TseitinTransformer::getFormulaRoot() const {
    return formulaRoot;
}

void TseitinTransformer::setFormulaRoot(TreeNode *formulaRoot) {
    TseitinTransformer::formulaRoot = formulaRoot;
    cnf->clear();
    varIdTable->clear();
    varIdCounter = 1;
}

unsigned int TseitinTransformer::getConnectiveRep() {
    int operatorId = varIdCounter;
    varIdCounter ++;
    return  operatorId;
}

unsigned int TseitinTransformer::getVarRep(std::string variableName) {
    // your code starts here
    auto lookUpResult = varIdTable->find(variableName);
    if (lookUpResult == varIdTable->end()){
        // assign a new  id
        (*varIdTable)[variableName] = varIdCounter;
        varIdCounter ++;
        return (*varIdTable)[variableName];
    } else{
        return lookUpResult->second;
    }
}

unsigned int TseitinTransformer::getRep(TreeNode *node) {
    switch (node->getType()) {
        case variable:
            return getVarRep(node->getStrRep());
        case connective:
            return getConnectiveRep();
    }
}

void TseitinTransformer::addTwoLiteralsClause(int rep1, int rep2) {
    std::vector<int> clause = std::vector<int>{rep1, rep2};
    cnf->push_back(clause);
}

void TseitinTransformer::addThreeLiteralsClause(int rep1, int rep2, int rep3){
    std::vector<int> clause = std::vector<int>{rep1, rep2, rep3};
    cnf->push_back(clause);
}

void TseitinTransformer::addOneLiteralClause(int rep) {
    std::vector<int> clause = std::vector<int>{rep};
    cnf->push_back(clause);
}


