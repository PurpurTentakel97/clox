cmake_minimum_required(VERSION 3.22.1)
project(cpplox)

set(CMAKE_CXX_STANDARD 23)

add_executable(genlox
               GenerateAST.cpp
)

add_custom_command(
        OUTPUT ${CMAKE_CURRENT_LIST_DIR}/Expression.cpp ${CMAKE_CURRENT_LIST_DIR}/Expression.hpp
        COMMAND genlox ${CMAKE_CURRENT_LIST_DIR}
        DEPENDS genlox
        VERBATIM
)

add_executable(cpplox
               TokenType.hpp
               Token.hpp
               Lexer.hpp
               Expression.hpp
               Helper.hpp
               Error.hpp
               Lox.cpp
               Token.cpp
               Lexer.cpp
               Expression.cpp
)

