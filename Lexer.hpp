#pragma once

#include <string>
#include <vector>
#include "Token.hpp"





class Lexer final
{
private:
    std::string m_source;
    std::vector<Token> m_tokens{};
    std::size_t m_start = 0;
    std::size_t m_current = 0;
    std::size_t m_line = 1;

    [[nodiscard]] bool is_at_end() const;

    void scan_token();

    char advance();
    [[nodiscard]] bool match(char expected);
    [[nodiscard]] char peek() const;
    [[nodiscard]] char peek_next() const;

    void str();
    void num();
    void identifier();

    void add_token(TokenType token);
    void add_token(TokenType token, Token::literal_ty const& literal);

public:
    explicit Lexer(std::string source);

    [[nodiscard]] std::vector<Token> scan_tokens();
};
