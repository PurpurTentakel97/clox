#include "Token.hpp"
#include "Error.hpp"

Token::Token(TokenType const type, std::string lexeme, literal_ty const liertal, std::size_t const line)
    : m_type{type}, m_lexeme{std::move(lexeme)}, m_literal{liertal}, m_line{line}
{
}

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

std::string Token::string_from_literal() const
{
    if (std::holds_alternative<std::monostate>(m_literal)) { return "std::monostate"; }
    if (std::holds_alternative<std::string>(m_literal)) { return std::get<std::string>(m_literal); }
    if (std::holds_alternative<double>(m_literal)) { return std::to_string(std::get<double>(m_literal)); }
    error(m_line, "intermal error while converting a literal into a string");
    std::unreachable();
}
