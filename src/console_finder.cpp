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


    return 0;
}