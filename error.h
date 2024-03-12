//
// Created by Zhang Fan on 2022-10-21.
//
#ifndef PA1_ERROR_H
#define PA1_ERROR_H
#include <string>
#include <iostream>
#include <exception>

struct InvalidInput : public std::exception{
    const char *what() const noexcept override;
};


struct ContradictingAssignment : public std::exception{
    const char *what() const noexcept override;
};

struct IncompleteAssignment : public std::exception{
    const char *what() const noexcept override;
};

struct VariableNameTooLong : public std::exception{
    const char *what() const noexcept override;
};


struct  VariableNameStartWithDigit : public std::exception{
    const char *what() const noexcept override;
};


struct  VariableNameNotAlphaDigit : public std::exception{
    const char *what() const noexcept override;

};


struct  UnmatchedParenthesis : public std::exception{
    const char *what() const noexcept override;
};
#endif //PA1_ERROR_H
