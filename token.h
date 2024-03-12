//
// Created by Zhang Fan on 2022-11-07.
//

#ifndef PA1_TOKEN_H
#define PA1_TOKEN_H
#include <ostream>

enum TokenType {variable, connective};

class Token
{
private:
    std::string content;
    TokenType type;
    Token* nextToken;


public:
    const std::string &getContent() const;

    TokenType getType() const;

    void setContent(const std::string &content);

    void setType(TokenType type);

    Token(std::string content, TokenType type);

    friend std::ostream &operator<<(std::ostream &os, const Token &token);

    Token *getNextToken() const;

    void setNextToken(Token *nextToken);

};


#endif //PA1_TOKEN_H
