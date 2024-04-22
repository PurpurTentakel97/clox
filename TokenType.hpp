#pragma once

enum class TokenType
{
    // single character tonkes
    LeftParen,
    RightParen,
    LeftBrace,
    RightBrace,
    Comma,
    Dot,
    Minus,
    Plus,
    Semicolon,
    Slash,
    Star,

    // one or two character tokens
    Bang,
    BangEqual,
    Equal,
    EqualEqual,
    Greater,
    GreaterEqual,
    Less,
    LessEqual,

    // literals
    Identifier,
    String,
    Number,

    // keywords
    And,
    Class,
    Else,
    False,
    Fun,
    For,
    If,
    Nil,
    Or,
    Print,
    Return,
    Super,
    This,
    True,
    Var,
    While,

    Eof,
};

[[nodiscard]] inline std::string type_to_string(TokenType const type)
{
    switch (type)
    {
    case TokenType::LeftParen:
        return "LeftParen";
    case TokenType::RightParen:
        return "RightParen";
    case TokenType::LeftBrace:
        return "LeftBrace";
    case TokenType::RightBrace:
        return "RightBrace";
    case TokenType::Comma:
        return "Comma";
    case TokenType::Dot:
        return "Dot";
    case TokenType::Minus:
        return "Minus";
    case TokenType::Plus:
        return "Plus";
    case TokenType::Semicolon:
        return "Semicolon";
    case TokenType::Slash:
        return "Slash";
    case TokenType::Star:
        return "Star";
    case TokenType::Bang:
        return "Bang";
    case TokenType::BangEqual:
        return "BangEqual";
    case TokenType::Equal:
        return "Equal";
    case TokenType::EqualEqual:
        return "EqualEqual";
    case TokenType::Greater:
        return "Greater";
    case TokenType::GreaterEqual:
        return "GreaterEqual";
    case TokenType::Less:
        return "Less";
    case TokenType::LessEqual:
        return "LessEqual";
    case TokenType::Identifier:
        return "Identifier";
    case TokenType::String:
        return "String";
    case TokenType::Number:
        return "Number";
    case TokenType::And:
        return "And";
    case TokenType::Class:
        return "Class";
    case TokenType::Else:
        return "Else";
    case TokenType::False:
        return "False";
    case TokenType::Fun:
        return "Fun";
    case TokenType::For:
        return "For";
    case TokenType::If:
        return "If";
    case TokenType::Nil:
        return "Nil";
    case TokenType::Or:
        return "Or";
    case TokenType::Print:
        return "Print";
    case TokenType::Return:
        return "Return";
    case TokenType::Super:
        return "Super";
    case TokenType::This:
        return "This";
    case TokenType::True:
        return "True";
    case TokenType::Var:
        return "Var";
    case TokenType::While:
        return "While";
    case TokenType::Eof:
        return "Eof";
    }
    std::unreachable();
}
