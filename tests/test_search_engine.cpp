#include <sstream>
#include <string>
#include <type_traits>
#include "doctest.h"
#include "work_with_string.h"

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