#ifndef TNODE_H


#define TNODE_H

#include <string>
#include <ostream>
#include "tokenizer.h"

class TreeNode
{
private:

    std::string strRep;
    TreeNode* leftChild;
    TreeNode* rightChild;
    TokenType type;
public:
    TokenType getType() const;


public:
    TreeNode(Token* token);

    TreeNode(const std::string &strRep, TokenType type);

    TreeNode *getLeftChild() const;

    void setLeftChild(TreeNode *node);

    TreeNode *getRightChild() const;

    void setRightChild(TreeNode *node);

    const std::string &getStrRep() const;

    friend std::ostream &operator<<(std::ostream &os, const TreeNode &node);

    void setStrRep(const std::string &strRep);
};




void printBinaryTree(const std::string& prefix, const TreeNode* node, bool isLeft);

#endif
