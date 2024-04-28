#pragma once

#include <format>
#include <string>
#include <variant>
#include <iterator>
#include <ostream>
#include "TokenType.hpp"

class Token final
{
public:
    using literal_ty = std::variant<std::monostate, std::string, double>;

private:
    TokenType m_type;
    std::string m_lexeme;
    literal_ty m_literal;
    std::size_t m_line;


public:
    Token(TokenType type, std::string lexeme, literal_ty liertal, std::size_t line);

    [[nodiscard]] TokenType type() const;
    [[nodiscard]] std::string lexeme() const;
    [[nodiscard]] literal_ty literal() const;
    [[nodiscard]] std::size_t line() const;
    [[nodiscard]] std::string string_from_literal() const;

    [[nodiscard]] friend std::ostream& operator<<(std::ostream& stream, Token const& token)
    {
        std::format_to(std::ostream_iterator<char>(stream),
                       "{} {} {}",
                       type_to_string(token.type()),
                       token.lexeme(),
                       token.string_from_literal());
        return stream;
    }
};
