//
// Created by Zhang Fan on 2022-11-07.
//

#include "token.h"

const std::string &Token::getContent() const {
    return content;
}

TokenType Token::getType() const {
    return type;
}

Token::Token(std::string content, TokenType type) : content(std::move(content)), type(type) {
    nextToken = nullptr; // always initialize pointer to nullptr; Otherwise, it got undefined
}


void Token::setContent(const std::string &content) {
    Token::content = content;
}

void Token::setType(TokenType type) {
    Token::type = type;
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    const static std::string tokenTypesStr[4]  = {"variable", "special", "error"};

    os << "content: " << token.content << " type: " << tokenTypesStr[token.type - variable] << "\n";
    return os;
}

Token *Token::getNextToken() const {
    return nextToken;
}

void Token::setNextToken(Token *nextToken) {
    Token::nextToken = nextToken;
}
