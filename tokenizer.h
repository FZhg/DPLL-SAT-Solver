/**
 *  This file is based on:
 *  1. Mak. (1996). Writing compilers and interpreters: an applied approach. Wiley.
 *  2. https://www.techiedelight.com/tokenize-string-cpp/
 */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <sstream>
#include <vector>
#include <regex>
#include <ostream>
#include "token.h"



/**
 * The Token class behaves like a single-forward list.
 * In each token, there is a nextToken pointers that points to the next token until the end of line.
 */







class Tokenizer
{
    private:
            std::vector<std::string> tokensContents;
            std::string line;
            std::regex re;
            Token* headToken;
            Token* currentToken;

private:
    void setTokensContents();
            void setTokens();
            bool isValidSpecial(std::string s);
            static void  checkVariableNameValid(const std::string& variableName);
            static void  checkConstantValid(const std::string& constantStr);
            Token* setTokenFromContent(std::string content);
            const std::string regexPattern;

    public:
            explicit Tokenizer(const std::string& regexPattern);

            void setLine(const std::string &line);

            Token *getHeadToken() const;

            virtual ~Tokenizer();
};

#endif
