//
// Created by Zhang Fan on 2022-12-20.
//

#ifndef BONUS_NNFTRANSFORMER_H
#define BONUS_NNFTRANSFORMER_H
#include "treeNode.h"

class NnfTransformer {
public:
    NnfTransformer();

    void transform(TreeNode* root);
private:
    void doubleNegation(TreeNode* root);
    void negationAnd(TreeNode* root);
    void negationOr(TreeNode* root);

};


#endif //BONUS_NNFTRANSFORMER_H
