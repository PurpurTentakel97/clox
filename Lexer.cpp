#include <cctype>
#include "Lexer.hpp"
#include "Error.hpp"
#include "Helper.hpp"
#include <array>

struct Entry final
{
    std::string key;
    TokenType value;
};

static std::array<std::pair<std::string_view,TokenType>,16> constexpr s_keywords
{
    std::pair{"and", TokenType::And},
    std::pair{"class", TokenType::Class},
    std::pair{"else", TokenType::Else},
    std::pair{"false", TokenType::False},
    std::pair{"for", TokenType::For},
    std::pair{"fun", TokenType::Fun},
    std::pair{"if", TokenType::If},
    std::pair{"nil", TokenType::Nil},
    std::pair{"or", TokenType::Or},
    std::pair{"print", TokenType::Print},
    std::pair{"return", TokenType::Return},
    std::pair{"super", TokenType::Super},
    std::pair{"this", TokenType::This},
    std::pair{"true", TokenType::True},
    std::pair{"var", TokenType::Var},
    std::pair{"while", TokenType::While}
};

static constexpr bool contains(std::string_view const& key)
{
    for (auto const& i : s_keywords)
    {
        if (i.first == key){return true;}
    }
    return false;
}

static constexpr TokenType token_from_string(std::string_view const& key)
{
    for (auto const& i : s_keywords)
    {
        if (i.first == key){return i.second;}
    }
    std::unreachable();
}

bool Lexer::is_at_end() const
{
    return m_current >= m_source.size();
}

void Lexer::scan_token()
{
    switch (char const c = advance())
    {
    // single chars
    case '(': add_token(TokenType::LeftParen);
        break;
    case ')': add_token(TokenType::RightParen);
        break;
    case '{': add_token(TokenType::LeftBrace);
        break;
    case '}': add_token(TokenType::RightBrace);
        break;
    case ',': add_token(TokenType::Comma);
        break;
    case '.': add_token(TokenType::Dot);
        break;
    case '-': add_token(TokenType::Minus);
        break;
    case '+': add_token(TokenType::Plus);
        break;
    case ';': add_token(TokenType::Semicolon);
        break;
    case '*': add_token(TokenType::Star);
        break;

    // chars with potentialliy second character
    case '!': add_token(match('=') ? TokenType::BangEqual : TokenType::Bang);
        break;
    case '=': add_token(match('=') ? TokenType::EqualEqual : TokenType::Equal);
        break;
    case '<': add_token(match('=') ? TokenType::LessEqual : TokenType::Less);
        break;
    case '>': add_token(match('=') ? TokenType::GreaterEqual : TokenType::Greater);
        break;

    // comment
    case '/':
        if (match('/'))
        {
            while (peek() != '\n' and not is_at_end()) { advance(); }
        }
        else if (match('*'))
        {
            while (peek() != '*' and peek_next() != '/' and not is_at_end())
            {
                if (peek() == '\n') { ++m_line; }
                advance();
            }
            // for consuming '*/'
            advance();
            advance();
        }
        else
        {
            add_token(TokenType::Slash);
        }
        break;

    // whitespace
    case ' ':
    case '\r':
    case '\t':
        break;
    case '\n':
        ++m_line;
        break;

    // literals
    case '"': str();
        break;

    default:
        if (std::isdigit(c))
        {
            num();
        }
        else if (is_alpha_or_underscore(c))
        {
            identifier();
        }
        else
        {
            error(m_line, std::string("Unexpected character: ") + c);
        }
        break;
    }
}

char Lexer::advance()
{
    ++m_current;
    return m_source[m_current - 1];
}

bool Lexer::match(char const expected)
{
    if (is_at_end()) { return false; }
    if (m_source[m_current] != expected) { return false; }

    ++m_current;
    return true;
}

char Lexer::peek() const
{
    if (is_at_end()) { return '\0'; }
    return m_source[m_current];
}

char Lexer::peek_next() const
{
    if (m_current + 1 >= m_source.length()) { return '\0'; }
    return m_source[m_current + 1];
}

void Lexer::str()
{
    while (peek() != '"' and not is_at_end())
    {
        if (peek() == '\n') ++m_line;
        advance();
    }

    if (is_at_end())
    {
        error(m_line, "unterminated string.");
        return;
    }

    // advance for the last '"'
    advance();

    auto const length = m_current - 1 - m_start + 1;
    add_token(
        TokenType::String,
        m_source.substr(m_start + 1, length)
    );
}

void Lexer::num()
{
    while (std::isdigit(peek())) { advance(); }
    if (peek() == '.' and std::isdigit(peek_next()))
    {
        // consume the '.'
        advance();

        while (std::isdigit(peek())) { advance(); }
    }

    add_token(TokenType::Number, m_source.substr(m_start, m_current - m_start));
}

void Lexer::identifier()
{
    while (is_alphanumeric_or_unterscore(peek())) { advance(); }
    auto const text = m_source.substr(m_start, m_current - m_start);
    auto const type = contains(text) ? token_from_string(text) : TokenType::Identifier;
    add_token(type);
}

void Lexer::add_token(TokenType const token)
{
    add_token(token, std::monostate());
}

void Lexer::add_token(TokenType const token, Token::literal_ty const& literal)
{
    m_tokens.emplace_back(token,
                          m_source.substr(m_start, m_current - m_start),
                          literal,
                          m_line);
}

Lexer::Lexer(std::string source)
    : m_source{std::move(source)}
{
}

std::vector<Token> Lexer::scan_tokens()
{
    while (not is_at_end())
    {
        m_start = m_current;
        scan_token();
    }

    m_tokens.emplace_back(TokenType::Eof, "", std::monostate(), m_line);
    return m_tokens;
}
