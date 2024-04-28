#pragma once

#include <cctype>

[[nodiscard]] inline bool is_alpha_or_underscore(char const c)
{
    if (std::isalpha(c)) { return true; }
    if (c == '_') { return true; }
    return false;
}

[[nodiscard]] inline bool is_alphanumeric_or_unterscore(char const c)
{
    if (std::isalnum(c)) { return true; }
    if (c == '_') { return true; }
    return false;
}
