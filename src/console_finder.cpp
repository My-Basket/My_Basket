#include <search_engine.h>
#include <work_with_string.h>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <vector>

using nlohmann::json;
using search::set_unit, search::product;

int main() {
    std::ifstream file("../data/karusel2.json");
    json j = json::parse(file);
    file.close();

    std::vector<search::product> products;
    std::vector<search::product> ans;
    for (const auto &x : j) {
        products.emplace_back(x);
    }
    std::string s;
    std::cin >> s;
    std::vector<uint32_t> first_str_codepoints;
    from_str_to_codepoint(s, first_str_codepoints);

    std::multiset<set_unit<product>> top;
    for (auto const &cur_prod : products) {
        std::vector<uint32_t> second_str_codepoints;
        // std::cout << cur_prod.get_name() << '\n';
        from_str_to_codepoint(cur_prod.get_name(), second_str_codepoints);
        uint32_t in_amount =
            check_in(first_str_codepoints, second_str_codepoints);
        uint32_t leven_dist =
            levenshtein_algo(first_str_codepoints, second_str_codepoints);
        top.insert({in_amount, leven_dist, cur_prod});

        if (top.size() > 10) {
            auto it = top.end();
            it--;
            top.erase(it);
        }
    }

    for (const set_unit<product> &su : top) {
        ans.push_back(su.product_);
    }
    for (const auto &su : ans) {
        std::cout << su;
    }

    return 0;
}