#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <type_traits>
#include <regex>

#include "lib/cregex.h"

using namespace pgx;

int main() {
    std::string pattern = "a|(bc)*";
    // "(a|b)*"
    // "c"
    CRegex regex(pattern);

    // std::cout << std::regex_match("aa", std::regex("*")) << std::endl;

    regex.PrintAutomata();

    const std::string test1 = "bcbc", test2 = "aa";
    // const std::string test2 = "kaak";
    std::cout << RegexMatch(std::move(regex), test1, test2) << std::endl; // 
    return 0;
}
