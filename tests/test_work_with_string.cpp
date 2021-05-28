#include <type_traits>
#include "doctest.h"
#include "work_with_string.h"
TEST_CASE("codepoint bytes") {
    char k[1];
    SUBCASE("codepoint bytes ASCII special symbols") {
        for (size_t i = 1; i < 32; i++) {
            k[0] = static_cast<char>(i);
            std::string s(k);
            CHECK(code_point(s).second == 1);
        }
    }
    SUBCASE("codepoint bytes ASCII numbers, punctuation marks") {
        for (size_t i = 32; i < 65; i++) {
            k[0] = static_cast<char>(i);
            std::string s(k);
            CHECK(code_point(s).second == 1);
        }
        for (size_t i = 91; i < 97; i++) {
            k[0] = static_cast<char>(i);
            std::string s(k);
            CHECK(code_point(s).second == 1);
        }
        for (size_t i = 123; i < 128; i++) {
            k[0] = static_cast<char>(i);
            std::string s(k);
            CHECK(code_point(s).second == 1);
        }
    }

    SUBCASE("codepoint bytes ASCII latin") {
        for (size_t i = 65; i <= 90; i++) {
            k[0] = static_cast<char>(i);
            std::string s(k);
            CHECK(code_point(s).second == 1);
        }
        for (size_t i = 97; i <= 122; i++) {
            k[0] = static_cast<char>(i);
            std::string s(k);
            CHECK(code_point(s).second == 1);
        }
    }
    SUBCASE("russian symbols") {
        CHECK(code_point("А").second == 2);
        CHECK(code_point("а").second == 2);
        CHECK(code_point("ё").second == 2);
        CHECK(code_point("Ё").second == 2);
    }
    SUBCASE("russian symbols") {
        CHECK(code_point("А").second == 2);
        CHECK(code_point("а").second == 2);
        CHECK(code_point("ё").second == 2);
        CHECK(code_point("Ё").second == 2);
    }
    SUBCASE("Chinese hieroglyphs") {
        CHECK(code_point("丒").second == 3);
        CHECK(code_point("不").second == 3);
        CHECK(code_point("丛").second == 3);
    }
    SUBCASE("emoji") {
        CHECK(code_point("🎧").second == 4);
        CHECK(code_point("🎸").second == 4);
        CHECK(code_point("🥁").second == 4);
    }
}
TEST_CASE("number_of_symbols") {
    CHECK(number_of_symbols("ёжик") == 4);
    CHECK(number_of_symbols("🥁丛A") == 3);
    CHECK(number_of_symbols("!!!") == 3);
    CHECK(number_of_symbols("丛") == 1);
    CHECK(number_of_symbols("!") == 1);
    CHECK(number_of_symbols("а") == 1);
}
TEST_CASE("from_str_to_codepoint, codepoint") {
    std::vector<uint32_t> vec;
    string s1 = "Привет!";
    from_str_to_codepoint(s1, vec);
    CHECK(vec.size() == number_of_symbols(s1) + 1);
    CHECK(vec[1] == 1087);
    CHECK(vec[2] == 1088);
    CHECK(vec[3] == 1080);
    CHECK(vec[4] == 1074);
    CHECK(vec[5] == 1077);
    CHECK(vec[6] == 1090);
    CHECK(vec[7] == 33);
    CHECK(code_point("п").first == 1087);
    CHECK(code_point("р").first == 1088);
    CHECK(code_point("и").first == 1080);
    CHECK(code_point("в").first == 1074);
    CHECK(code_point("е").first == 1077);
    CHECK(code_point("т").first == 1090);
    CHECK(code_point("!").first == 33);
    std::string s2 ="🎧";
    vec.clear();
    from_str_to_codepoint(s2, vec);
    CHECK(vec.size() == number_of_symbols(s2) + 1);
}
