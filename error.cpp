//
// Created by Zhang Fan on 2022-11-02.
//
#include "error.h"

const char *UnmatchedParenthesis::what() const noexcept {
        return "invalid input";
}

const char *VariableNameNotAlphaDigit::what() const noexcept {
    return "invalid input";
}

const char *VariableNameStartWithDigit::what() const noexcept {
    return "invalid input";
}


const char *VariableNameTooLong::what() const noexcept {
    return "invalid input";
}

const char *IncompleteAssignment::what() const noexcept {
    return "incomplete assignment";
}

const char *ContradictingAssignment::what() const noexcept {
    return "contradicting assignment";
}

const char *InvalidInput::what() const noexcept {
    return "invalid input";
}
