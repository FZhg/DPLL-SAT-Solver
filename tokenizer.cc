#include "tokenizer.h"
#include <iostream>
#include <utility>
#include "error.h"


void Tokenizer::setLine(const std::string &line) {
    Tokenizer::line = line;
    headToken = nullptr;
    currentToken = nullptr;
    //TODO: clear garbage
    setTokensContents();
    setTokens();
}

Tokenizer::Tokenizer(const std::string& regexPattern) : regexPattern(regexPattern) {
    re = std::regex (regexPattern);
    headToken = nullptr;
    currentToken = nullptr;
    line = "";
}

Token* Tokenizer::setTokenFromContent(std::string content) {
    TokenType tokenType;
    if (isalpha(content[0])){
        checkVariableNameValid(content);
        tokenType = variable;
    } else if (isValidSpecial(content)){
        tokenType = connective;
    } else{
        throw InvalidInput();
    }
    return new Token(content, tokenType);
}



void Tokenizer::setTokensContents() {
    std::sregex_token_iterator it{ line.begin(),
                                   line.end(), re, {-1,0} };
    tokensContents = std::vector<std::string> { it, {} };
}



bool Tokenizer::isValidSpecial(std::string s) {
    std::regex operatorRe = std::regex (R"([-|*|+|(|)])");
    return std::regex_match(s, operatorRe);
}

void Tokenizer::setTokens() {
    std::vector<std::string> temContents  = {};
    for (const std::string& content : tokensContents){
        if ((not content.empty()) and (not isspace(content[0]))){
            temContents.push_back(content);
        }
    }

    tokensContents = temContents;

    if (tokensContents.empty()){
        throw  InvalidInput();
    } else{
        headToken = setTokenFromContent(tokensContents[0]);
        currentToken= headToken;
        for (int i = 1; (unsigned) i< tokensContents.size(); i ++){
            Token* nextToken = setTokenFromContent(tokensContents[i]);
            currentToken->setNextToken(nextToken);
            currentToken = nextToken;
        }
    }

}





void Tokenizer::checkVariableNameValid(const std::string& variableName) {
    if (variableName.size()> 10){
        throw VariableNameTooLong();
    } else if (std::regex_match(variableName, std::regex("[^[:alnum:]]"))){ // have to use double brackets here
        throw VariableNameNotAlphaDigit();
    }
}

void Tokenizer::checkConstantValid(const std::string& constantStr) {
    if(constantStr.size() > 1 and std::regex_match(constantStr, std::regex("[:alpha:]"))){
        throw VariableNameStartWithDigit();
    } else if (constantStr.size() != 1){
        throw InvalidInput();
    } else if (constantStr != "1" and constantStr !="0"){
        throw InvalidInput();
    }
}

Token *Tokenizer::getHeadToken() const {
    return headToken;
}

Tokenizer::~Tokenizer() {
    Token* token = headToken;
    Token* nextToken;
    while (token != nullptr){
        nextToken = token->getNextToken();
        delete token;
        token  = nextToken;
    }
}


