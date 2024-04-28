cmake_minimum_required(VERSION 3.22.1)
project(cpplox)

set(CMAKE_CXX_STANDARD 23)

add_executable(cpplox
               TokenType.hpp
               Token.hpp
               Lexer.hpp
               Lox.cpp
               Token.cpp
               Lexer.cpp
               Error.hpp
               Helper.hpp
)
