#include <regex>
#include <string>

#include "gtest/gtest.h"
#include "lib/cregex.h"

using namespace pgx;

using RegexMatchTest = ::testing::TestWithParam<std::tuple<std::string, std::string>>;

TEST_P(RegexMatchTest, RegexMatchTest) {
    std::string pattern = std::get<0>(GetParam());
    std::string text = std::get<1>(GetParam());

    CRegex cregex(pattern.c_str());
    bool result = RegexMatch(std::move(cregex), text);

    std::regex std_pattern(pattern);
    bool std_result = std::regex_match(text, std_pattern);

    ASSERT_EQ(result, std_result);
}

INSTANTIATE_TEST_SUITE_P(
    RegexMatchTest,
    RegexMatchTest,
    ::testing::Values(
        std::make_tuple("(a|b)*", "ab"),
        std::make_tuple("(a|b)*", "aba"),
        std::make_tuple("(a|b)*", "abab"),
        std::make_tuple("(a|b)*", "ababab"),
        std::make_tuple("(a|b)*", ""),
        std::make_tuple("(a|b)*", "c"),
        std::make_tuple("a|(bc)*", "a"),
        std::make_tuple("a|(bc)*", "bcbc"),
        std::make_tuple("a|(bc)*", "ab"),
        std::make_tuple("(a|b)c*", "ac"),
        std::make_tuple("(a|b)c*", "bc"),
        std::make_tuple("(a|b)c*", "abc"),
        std::make_tuple("a|b*", "b"),
        std::make_tuple("a|b*", "bbbb"),
        std::make_tuple("a|b*", "ab"),
        std::make_tuple("(a|b)|(c|d)*", "d"),
        std::make_tuple("(a|b)|(c|d)*", "abcd"),
        std::make_tuple("(a|b)|(c|d)*", "e"),
        std::make_tuple("(a*)|(b*)", "aaaa"),
        std::make_tuple("(a*)|(b*)", "bb"),
        std::make_tuple("(a*)|(b*)", "ab")
    )
);

