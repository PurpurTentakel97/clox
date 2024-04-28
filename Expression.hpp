#pragma once

#include "Token.hpp"
#include <memory>

class Expression {
public:
    using expr_ty = std::unique_ptr<Expression>;
    virtual ~Expression() = default;
};


class Binary final : public Expression {
private:
    expr_ty m_left;
    Token m_operator_;
    expr_ty m_right;

public:
    Binary(expr_ty left, Token operator_, expr_ty right);
};


class Grouping final : public Expression {
private:
    expr_ty m_expression;

public:
    Grouping(expr_ty expression);
};


class Literal final : public Expression {
private:
    Token::literal_ty m_value;

public:
    Literal(Token::literal_ty value);
};


class Unary final : public Expression {
private:
    Token m_operator_;
    expr_ty m_right;

public:
    Unary(Token operator_, expr_ty right);
};


