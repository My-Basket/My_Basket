//
// Created by vladi on 18.02.2021.
//

#include "search_engine.h"
#include <cassert>
#include <fstream>
#include "work_with_string.h"

namespace {

void relax(uint32_t &a, uint32_t b) {
    if (a > b) {
        a = b;
    }
}

uint32_t levenshtein_algo(std::vector<uint32_t> &first_str,
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
            relax(f[i][j], f[i][j - 1] + 1);
            relax(f[i][j], f[i - 1][j - 1] + w);
        }
    }
    return f[first_str.size() - 1][second_str.size() - 1];
}

uint32_t check_in(std::vector<uint32_t> &first_str,
                  std::vector<uint32_t> &second_str) {
    if (first_str.size() > second_str.size()) {
        return 0;
    }

    uint32_t max_amount = 0;
    for (int i = 1; i < second_str.size() - first_str.size(); i++) {
        uint32_t count = 0;
        for (int j = i; j < i + first_str.size() - 1; j++) {
            if (first_str[j - i + 1] == second_str[j]) {
                count++;
            }
        }
        if (count > max_amount) {
            max_amount = count;
        }
    }
    return max_amount;
}
}  // namespace

namespace search {

std::ostream &operator<<(std::ostream &os, const product &p) {
    os << "{\n"
       << "   "
       << "Name: " << p.name << '\n'
       << "   "
       << "Category: " << p.category << '\n'
       << "   "
       << "Price: " << p.price << '\n'
       << "}\n";
    return os;
}

void get_prod_top_by_name(std::string &input_string,
                          uint32_t size,
                          std::vector<product> &vec) {
    std::ifstream file("../data/av.json");
    json j = json::parse(file);
    file.close();

    std::vector<uint32_t> first_str_codepoints;
    from_str_to_codepoint(input_string, first_str_codepoints);

    std::multiset<set_unit<product>> top;
    for (auto const &x : j) {
        product cur_prod(x);
        auto temp_name = cur_prod.name;

        std::vector<uint32_t> second_str_codepoints;
        from_str_to_codepoint(cur_prod.name, second_str_codepoints);

        uint32_t in_amount =
            check_in(first_str_codepoints, second_str_codepoints);
        uint32_t leven_dist =
            levenshtein_algo(first_str_codepoints, second_str_codepoints);
        top.insert({in_amount, leven_dist, cur_prod});

        if (top.size() > size) {
            auto it = top.end();
            it--;
            top.erase(it);
        }
    }

    for (const set_unit<product> &su : top) {
        vec.push_back(su.product_);
    }
}

product::product(const json &j) {
    try {
        name = j["Name"];
        category = j["Category"];
        price = j["Price"];
    } catch (...) {
        assert((false, "Invalid cast from json to product"));
    }
}
product::product(std::string name_, std::string category_, uint32_t price_)
    : name(std::move(name_)), category(std::move(category_)), price(price_) {
}
product &product::operator=(const json &j) {
    try {
        name = j["Name"];
        category = j["Category"];
        price = j["Price"];
        return *this;
    } catch (...) {
        throw;
    }
}
bool product::operator==(const product &p) const {
    return p.name == name;
}

Recipe::Recipe(const json &j) : name(j["Name"]) {
    for (const json &v : j["Ingredients"]) {
        ingredients.emplace_back(v);
    }
}
std::ostream &operator<<(std::ostream &os, const Recipe &p) {
    os << p.name << "\n";
    os << "Ingredients:\n";
    for (const auto &t : p.ingredients) {
        os << t << "\n";
    }
    return os;
}
void Recipe::clear() {
    ingredients.clear();
    name.clear();
}

bool Recipe::is_ingredient_in_recipe(const product &ingredient) {
    return std::any_of(
        ingredients.begin(), ingredients.end(),
        [&ingredient](const product &p) { return (p == ingredient); });
}

void get_recipes(const std::vector<product> &ingredients,
                 uint32_t size,
                 std::vector<Recipe> &vec) {
    std::ifstream file("../data/recipes.json");
    json j = json::parse(file);
    file.close();

    std::set<set_unit<Recipe>> top;
    for (const product &p : ingredients) {
        uint32_t in_amount = 0;
        uint32_t leven_dist = 0;

        std::vector<uint32_t> first_str_codepoints;
        from_str_to_codepoint(p.name, first_str_codepoints);
        set_unit<Recipe> max;

        for (const json &x : j) {
            Recipe cur_recipe(x);

            std::string temp_name = cur_recipe.name;

            std::vector<uint32_t> second_str_codepoints;
            from_str_to_codepoint(cur_recipe.name, second_str_codepoints);

            in_amount += check_in(first_str_codepoints, second_str_codepoints);
            leven_dist +=
                levenshtein_algo(first_str_codepoints, second_str_codepoints);

            if (max < set_unit<Recipe>({in_amount, leven_dist})) {
                max = {in_amount, leven_dist, cur_recipe};
            }

            top.insert(max);

            if (top.size() > size) {
                auto it = top.end();
                it--;
                top.erase(it);
            }
        }
    }
    for (const auto &su : top) {
        vec.push_back(su.product_);
    }
}

void search_recipe(const string &input_string,
                   uint32_t size,
                   std::vector<Recipe> &vec) {
    std::ifstream file("../data/recipes.json");
    json j = json::parse(file);
    file.close();

    std::vector<uint32_t> first_str_codepoints;
    from_str_to_codepoint(input_string, first_str_codepoints);

    std::multiset<set_unit<Recipe>> top;

    for (const json &x : j) {
        Recipe cur_recipe(x);
        std::string temp_name = cur_recipe.name;

        std::vector<uint32_t> second_str_codepoints;
        from_str_to_codepoint(cur_recipe.name, second_str_codepoints);

        uint32_t in_amount =
            check_in(first_str_codepoints, second_str_codepoints);
        uint32_t leven_dist =
            levenshtein_algo(first_str_codepoints, second_str_codepoints);

        top.insert({in_amount, leven_dist, cur_recipe});

        if (top.size() > size) {
            auto it = top.end();
            it--;
            top.erase(it);
        }
    }
    for (const auto &su : top) {
        vec.push_back(su.product_);
    }
}

}  // namespace search
