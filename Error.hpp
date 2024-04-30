#pragma once

#include <iostream>
#include <format>

static bool s_had_error = false;

[[nodiscard]] inline bool had_error()
{
    return s_had_error;
}

inline void set_error()
{
    s_had_error = true;
}

inline void reset_error()
{
    s_had_error = false;
}

inline void report(std::size_t const line, std::string const& where, std::string const& message)
{
    std::cerr << std::format("[line {}] Error{}: {}", line, where, message);
    s_had_error = true;
}

inline void error (std::size_t const line, std::string const& message)
{
    report(line, "", message);
}