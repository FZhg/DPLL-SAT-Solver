#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <map>
#include "tokenizer.h"
#include "treeNode.h"




class Parser {
private:
    Tokenizer *tokenizer;
    TreeNode* root;
    Token *token;



    TreeNode* parseFormula();
    TreeNode* parseConjTermPlusFormula();
    TreeNode* parseTermStarConjTerm();
    TreeNode* parseMinusTerm();
    TreeNode* parseBracketsFormula();
    TreeNode* parseConjTerm();
    TreeNode* parseTerm();




public:
    explicit Parser();

    virtual ~Parser();

    void parse(std::string line);
    TreeNode *getRoot() const;
};

#endif
