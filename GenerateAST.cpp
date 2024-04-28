#include <iostream>
#include <utility>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>

using config_ty = std::vector<std::pair<std::string_view, std::vector<std::pair<std::string_view, std::string_view>>>>;
static config_ty const s_config{
    {"Binary", {{"expr_ty", "left"}, {"Token", "operator_"}, {"expr_ty", "right"}}},
    {"Grouping", {{"expr_ty", "expression"}}},
    {"Literal", {{"Token::literal_ty", "value"}}},
    {"Unary", {{"Token", "operator_"}, {"expr_ty", "right"}}},
};

static constexpr auto s_header_class = R"(class {0} final : public Expression {{
private:
{1}
public:
    {0}({2});
}};


)";

static constexpr auto s_source_class = R"({0}::{0}({1})
    : {2} {{}}


)";

static constexpr auto s_header_top = R"(#pragma once

#include "Token.hpp"
#include <memory>

class Expression {
public:
    using expr_ty = std::unique_ptr<Expression>;
    virtual ~Expression() = default;
};


)";

static constexpr auto s_source_top = R"(#pragma once

#include "Expression.hpp"

)";

void define_classes(std::stringstream& header, std::stringstream& source)
{
    for (auto const& [name, fields] : s_config)
    {
        auto constexpr field = R"(    {} m_{};)";
        auto field_heder = std::stringstream{};
        auto ctor = std::stringstream{};
        auto ctor_source = std::stringstream{};
        bool first = true;
        for (auto const& [type, identifier] : fields)
        {
            field_heder << std::format(field, type, identifier) << '\n';
            if (first)
            {
                ctor << type << " " << identifier;
                ctor_source << "m_" << identifier << "{ std::move(" << identifier << ") }";
                first = false;
            }
            else
            {
                ctor << ", " << type << " " << identifier;
                ctor_source << ", " << "m_" << identifier << "{ std::move(" << identifier << ") }";
            }
        }
        header << std::format(s_header_class, name, field_heder.str(), ctor.str());
        source << std::format(s_source_class, name, ctor.str(), ctor_source.str());
    }
}


void define_ast(std::filesystem::path const& output_dir, std::string const& file_name_out_extention)
{
    auto path = std::filesystem::path(output_dir / file_name_out_extention);

    auto output_header = std::stringstream{s_header_top};
    auto output_source = std::stringstream{s_source_top};
    output_header << s_header_top;
    output_source << s_source_top;

    define_classes(output_header, output_source);

    auto file = std::ofstream{path.replace_extension(".hpp")};
    if (not file.is_open()) { std::exit(1); }
    file << output_header.str();
    file.close();


    auto file2 = std::ofstream{path.replace_extension(".cpp")};
    if (not file2.is_open()) { std::exit(1); }
    file2 << output_source.str();
    file2.close();
}

int main(int const argc, char const* const* const argv)
{
    if (argc != 2)
    {
        std::cerr << "missing argument 'output directory'\n";
        return 64;
    }
    std::string output_dir = argv[1];
    define_ast(output_dir, "Expression");
}
