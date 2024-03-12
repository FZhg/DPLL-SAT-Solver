#include <iostream>
#include <utility>
#include "treeNode.h"



TreeNode *TreeNode::getLeftChild() const {
    return leftChild;
}

void TreeNode::setLeftChild(TreeNode *node) {
    TreeNode::leftChild = node;
}

TreeNode *TreeNode::getRightChild() const {
    return rightChild;
}

void TreeNode::setRightChild(TreeNode *node) {
    TreeNode::rightChild = node;
}



const std::string &TreeNode::getStrRep() const {
    return strRep;
}


void TreeNode::setStrRep(const std::string &strRep) {
    TreeNode::strRep = strRep;
}


std::ostream &operator<<(std::ostream &os, const TreeNode &node) {
    os  << node.strRep << "\n";
    return os;
}

TreeNode::TreeNode(const std::string &strRep, TokenType type) : strRep(strRep), type(type) {
    leftChild = nullptr;
    rightChild = nullptr;
}

TreeNode::TreeNode(Token *token) : TreeNode(token->getContent(), token->getType()){}

TokenType TreeNode::getType() const {
    return type;
}


/**
 *  This function is copied from [Stackoverflow](https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c)
 * @param prefix
 * @param node
 * @param isLeft
 */
void printBinaryTree(const std::string& prefix, const TreeNode* node, bool isLeft)
{
    if (node != nullptr)
    {
        std::cout << prefix;
        std::cout << (isLeft ? "|--" : "L--");
        // print the value of the node
        std::cout << node->getStrRep() << std::endl;
        // enter the next tree level - left and right branch
        printBinaryTree(prefix + (isLeft ? "|   " : "    "), node->getRightChild(), true);
        printBinaryTree(prefix + (isLeft ? "|   " : "    "), node->getLeftChild(), false);
    }
}