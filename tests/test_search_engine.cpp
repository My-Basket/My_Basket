#include <sstream>
#include <string>
#include <type_traits>
#include "doctest.h"
#include "work_with_string.h"
void relax2(uint32_t &a, uint32_t b) {
    if (a > b) {
        a = b;
    }
}
uint32_t check_in2(std::vector<uint32_t> &first_str,
                   std::vector<uint32_t> &second_str) {
    if (first_str.size() > second_str.size()) {
        return 0;
    }

    uint32_t max_amount = 0;
    for (int i = 0; i < second_str.size() - first_str.size() + 1; i++) {
        uint32_t count = 0;
        for (int j = 0; j < first_str.size() && j + i < second_str.size();
             j++) {
            if (first_str[j] == second_str[j + i]) {
                count++;
            } else {
                max_amount = std::max(max_amount, count);
                count = 0;
            }
        }
        if (count > max_amount) {
            max_amount = count;
        }
    }
    return max_amount;
}
uint32_t levenshtein_algo2(std::vector<uint32_t> &first_str,
                           std::vector<uint32_t> &second_str) {
    std::vector<std::vector<uint32_t>> f(
        first_str.size(), std::vector<uint32_t>(second_str.size(), 0));

    for (int i = 0; i < first_str.size(); i++) {
        for (int j = 0; j < second_str.size(); j++) {
            if (i == 0 || j == 0) {
                f[i][j] = std::max(i, j);
                continue;
            }

            int w = first_str[i] == second_str[j] ? 0 : 1;

            f[i][j] = f[i - 1][j] + 1;
            relax2(f[i][j], f[i][j - 1] + 1);
            relax2(f[i][j], f[i - 1][j - 1] + w);
        }
    }
    return f[first_str.size() - 1][second_str.size() - 1];
}
TEST_CASE("check_in") {
    std::vector<uint32_t> first_codepoint;
    std::vector<uint32_t> second_codepoint;
    std::string first = "Привет";
    std::string second = "прив";
    from_str_to_codepoint(first, first_codepoint);
    from_str_to_codepoint(second, second_codepoint);
    CHECK(check_in2(second_codepoint, first_codepoint) == 5);
    first = "black";
    second = "ck";
    first_codepoint.clear();
    second_codepoint.clear();
    from_str_to_codepoint(first, first_codepoint);
    from_str_to_codepoint(second, second_codepoint);
    CHECK(check_in2(second_codepoint, first_codepoint) == 2);
}
TEST_CASE("levenstain") {
    std::vector<uint32_t> first_codepoint;
    std::vector<uint32_t> second_codepoint;
    std::string first = "Привет";
    std::string second = "прив";
    from_str_to_codepoint(first, first_codepoint);
    from_str_to_codepoint(second, second_codepoint);
    CHECK(levenshtein_algo2(second_codepoint, first_codepoint) == 2);
    first = "black";
    second = "ck";
    first_codepoint.clear();
    second_codepoint.clear();
    from_str_to_codepoint(first, first_codepoint);
    from_str_to_codepoint(second, second_codepoint);
    CHECK(levenshtein_algo2(second_codepoint, first_codepoint) == 3);
}
