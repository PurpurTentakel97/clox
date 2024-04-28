#pragma once

#include "Expression.hpp"

Binary::Binary(expr_ty left, Token operator_, expr_ty right)
    : m_left{ std::move(left) }, m_operator_{ std::move(operator_) }, m_right{ std::move(right) } {}


Grouping::Grouping(expr_ty expression)
    : m_expression{ std::move(expression) } {}


Literal::Literal(Token::literal_ty value)
    : m_value{ std::move(value) } {}


Unary::Unary(Token operator_, expr_ty right)
    : m_operator_{ std::move(operator_) }, m_right{ std::move(right) } {}


