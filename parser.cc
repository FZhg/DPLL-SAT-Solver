#include "parser.h"
#include "error.h"
#include <iostream>
#define TOKENIZER_DELIMITER_REGEX_PATTERN R"([\W])"

void Parser::parse(std::string line) {
    tokenizer->setLine(line);
    token = tokenizer->getHeadToken();
    root = parseFormula();


    if (root == nullptr) {
        // No matches
        throw InvalidInput();
    }


    if (token != nullptr){

        throw InvalidInput();
    }

}

TreeNode *Parser::parseFormula() {
    Token* tokenSaved = token;

    TreeNode *parentNode = parseConjTermPlusFormula();
    if ( parentNode != nullptr){
        return parentNode;
    } else {
        token = tokenSaved;  // restore the token pointer
        parentNode = parseConjTerm();
        return parentNode; // return nullptr when things don't match
    }
}


TreeNode *Parser::parseConjTermPlusFormula() {
    TreeNode* parentNode;
    TreeNode* leftChild = parseConjTerm();
    if (leftChild == nullptr){
        return nullptr;
    }
    if (token == nullptr or token->getContent() != "+"){
        return nullptr;
    } else {
        parentNode = new TreeNode(token);
        token = token->getNextToken();
        TreeNode *rightChild = parseFormula();
        if (rightChild == nullptr) {
            return nullptr;
        } else {
            // We have a match
            parentNode->setLeftChild(leftChild);
            parentNode->setRightChild(rightChild);
            return parentNode;
        }
    }
}

TreeNode *Parser::parseConjTerm() {
    Token* tokenSaved = token;

    TreeNode *parentNode = parseTermStarConjTerm();
    if (parentNode != nullptr){
        return parentNode;
    } else {
        token = tokenSaved;
        parentNode = parseTerm();
        return parentNode;
    }
}

TreeNode *Parser::parseTermStarConjTerm() {
    TreeNode * parentNode;
    TreeNode* leftChild = parseTerm();
    if (leftChild == nullptr){
        return nullptr;
    }
    if (token == nullptr or token->getContent() != "*"){
        return nullptr;
    } else{
        parentNode = new TreeNode(token);
        token = token->getNextToken();
        TreeNode* rightChild = parseConjTerm();
        if (rightChild == nullptr){
            return nullptr;
        } else {
            parentNode->setLeftChild(leftChild);
            parentNode->setRightChild(rightChild);
            return parentNode;
        }
    }
}


TreeNode *Parser::parseTerm(){
    if (token == nullptr){
        return nullptr; // reach the end of the line
    }
    TreeNode* parentNode;
    switch (token->getType()) {
        case variable:
            parentNode = new TreeNode(token);
            token = token->getNextToken();
            break;
        case connective:
            if(token->getContent() == "-"){
                parentNode = parseMinusTerm();
            } else if (token->getContent() == "("){
                parentNode = parseBracketsFormula();
                token = token->getNextToken();
            } else{
                parentNode = nullptr;
            }
    }

    return parentNode;
}

TreeNode *Parser::parseMinusTerm() {
    auto * parentNode = new TreeNode(token);
    token = token->getNextToken();
    if (token == nullptr){
        return nullptr;
    }
    TreeNode* child = parseTerm();
    if (child == nullptr){
        return nullptr;
    } else{
        parentNode->setLeftChild(child);
        return parentNode;
    }
}

TreeNode *Parser::parseBracketsFormula() {
    token = token->getNextToken();
    if (token == nullptr){
        return nullptr;
    }
    TreeNode* parentNode = parseFormula();
    if (token == nullptr or token->getContent() != ")"){
        throw UnmatchedParenthesis();
    }
    return parentNode;
}




TreeNode *Parser::getRoot() const {
    return root;
}

Parser::Parser(){
    this->tokenizer = new Tokenizer(TOKENIZER_DELIMITER_REGEX_PATTERN);
    root = nullptr;
}

Parser::~Parser() {

}





