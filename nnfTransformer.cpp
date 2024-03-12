//
// Created by Zhang Fan on 2022-12-20.
//

#include "nnfTransformer.h"

void NnfTransformer::transform(TreeNode *root) {
    if (root == nullptr){
        return;
    }

    TreeNode* leftChild = root->getLeftChild();
    TreeNode* rightChild = root->getRightChild();

    if(leftChild == nullptr){
        return; // when the left child is null the right child is null
    }

    if (root->getStrRep() == "-"){
        if(leftChild->getStrRep() == "-"){
            doubleNegation(root);
            transform(root);
            return;
        } else if (leftChild->getStrRep() == "*"){
            negationAnd(root);
            transform(root);
            return;
        } else if (leftChild->getStrRep() == "+"){
            negationOr(root);
            transform(root);
            return;
        } else{
            transform(leftChild);
        }

    } else {
        transform(leftChild);
        transform(rightChild);
    }
}

void NnfTransformer::negationOr(TreeNode *root) {
    TreeNode* orNode = root->getLeftChild();

    orNode->setStrRep("*");
    *root  = *orNode; // the and node becomes the or node

    TreeNode* leftNegationNode = new TreeNode("-", connective);
    TreeNode* F1 = orNode->getLeftChild();
    leftNegationNode->setLeftChild(F1);

    TreeNode* rightNegationNode = new TreeNode("-", connective);
    TreeNode* F2 = orNode->getRightChild();
    rightNegationNode->setLeftChild(F2);

    root->setLeftChild(leftNegationNode);
    root->setRightChild(rightNegationNode);
}

void NnfTransformer::negationAnd(TreeNode *root) {
    TreeNode* andNode = root->getLeftChild();
    
    andNode->setStrRep("+");
    *root  = *andNode; // the and node becomes the or node
    
    TreeNode* leftNegationNode = new TreeNode("-", connective);
    TreeNode* F1 = andNode->getLeftChild();
    leftNegationNode->setLeftChild(F1);
    
    TreeNode* rightNegationNode = new TreeNode("-", connective);
    TreeNode* F2 = andNode->getRightChild();
    rightNegationNode->setLeftChild(F2);
    
    root->setLeftChild(leftNegationNode);
    root->setRightChild(rightNegationNode);
    
}

void NnfTransformer::doubleNegation(TreeNode *root) {
    TreeNode* negationNode = root->getLeftChild();
    TreeNode* F1 = negationNode->getLeftChild();
    *root = *F1;
}

NnfTransformer::NnfTransformer() {}
