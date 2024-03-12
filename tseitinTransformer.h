#ifndef TSEITIN_H
#define TSEITIN_H

#include <vector>
#include <map>
#include <string>
#include "treeNode.h"

class TseitinTransformer
{
  private:
    TreeNode *formulaRoot;
    std::vector<std::vector<int>>* cnf; // represent CNF in vector of vector
    std::map<std::string, int>* varIdTable; // stores the ID associated with the variable
    int varIdCounter=1; // 1 are reserved for \bot and \top
    void addSubformulaEncoding(TreeNode *subRoot, int subRootRep); // recursive function called on each subformula
    void addNegEq(int negRep, int FRep); // add clauses for a negation subformula
    void addOrEq(int orRep, int F1Rep, int F2Rep); // add clauses for an or subformula
    void addAndEq(int andRep, int F1Rep, int F2Rep); // add clauses for an and subformula
    unsigned int getVarRep(std::string variableName);
    void addOneLiteralClause(int rep);
    void addTwoLiteralsClause(int rep1, int rep2);
    void addThreeLiteralsClause(int rep1, int rep2, int rep3);
    unsigned int getConnectiveRep();
    unsigned int getRep(TreeNode* node);

  public:
    TseitinTransformer();
    TreeNode *getFormulaRoot() const;
    void setFormulaRoot(TreeNode *formulaRoot);
    std::vector<std::vector<int>>* transform(TreeNode* root);
};

void printCnf(std::vector<std::vector<int>>* cnf) ; // a debug helper function to check whehter the correctness of transformation

#endif
