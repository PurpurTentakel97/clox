#include "Token.hpp"

Token::Token(TokenType const type, std::string lexeme, literal_ty const liertal, std::size_t const line)
    : m_type{type}, m_lexeme{std::move(lexeme)}, m_literal{liertal}, m_line{line} { }

TokenType Token::type() const
{
    return m_type;
}

std::string Token::lexeme() const
{
    return m_lexeme;
}

Token::literal_ty Token::literal() const
{
    return m_literal;
}

std::size_t Token::line() const
{
    return m_line;
}


