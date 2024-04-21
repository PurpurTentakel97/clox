#pragma once

#include <format>

#include "TokenType.hpp"
#include <string>
#include <variant>

class Token final
{
public:
    using literal_ty = std::variant<std::monostate>;

private:
    TokenType  m_type;
    std::string  m_lexeme;
    literal_ty m_literal;
    std::size_t m_line;

    public:
    Token(TokenType type, std::string lexeme, literal_ty liertal, std::size_t line);

    [[nodiscard]] TokenType type() const;
    [[nodiscard]] std::string lexeme() const;
    [[nodiscard]] literal_ty literal() const;
    [[nodiscard]] std::size_t line() const;

    [[nodiscard]] friend std::ostream& operator<<(std::ostream& stream, Token const& token)
    {
        std::string buffer;
        std::format_to(std::back_inserter(buffer), "{} {} {}", token.type(), token.lexeme(), token.literal());
        stream << buffer;
        return stream;
    }
};

