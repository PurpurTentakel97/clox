#pragma once

#include "Token.hpp"
#include <memory>

struct Expression {
    using expr_ty = std::unique_ptr<Expression>;
    virtual ~Expression() = default;
};


struct Binary final : public Expression {
    expr_ty m_left;
    Token m_operator_;
    expr_ty m_right;


    explicit Binary(expr_ty left, Token operator_, expr_ty right);
};


struct Grouping final : public Expression {
    expr_ty m_expression;


    explicit Grouping(expr_ty expression);
};


struct Literal final : public Expression {
    Token::literal_ty m_value;


    explicit Literal(Token::literal_ty value);
};


struct Unary final : public Expression {
    Token m_operator_;
    expr_ty m_right;


    explicit Unary(Token operator_, expr_ty right);
};


