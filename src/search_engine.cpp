//
// Created by vladi on 18.02.2021.
//

#include "search_engine.h"
#include <cassert>
#include <fstream>
#include <iostream>
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

void get_prod_top_by_name(string &input_string,
                          uint32_t size,
                          std::vector<product> &vec) {
    std::ifstream file("../data/av.json");
    json j = json::parse(file);
    file.close();

    std::vector<uint32_t> first_str_codepoints;
    from_str_to_codepoint(input_string, first_str_codepoints);

    struct set_unit {
        uint32_t in_amount;
        uint32_t leven_dist;
        search::product product_;
        bool operator<(const set_unit &a) const {
            if (a.in_amount != in_amount) {
                return a.in_amount < in_amount;
            } else {
                return a.leven_dist > leven_dist;
            }
        }
    };

    std::multiset<set_unit> top;
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

    for (const set_unit &su : top) {
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

product &product::operator=(const json &j) {
    try {
        name = j["Name"];
        category = j["Category"];
        price = j["Price"];
        return *this;
    } catch (...) {
        assert((false, "Invalid cast from json to product"));
    }
}
bool product::operator==(const product &p) const {
    return p.name == name;
}

Recipe::Recipe(const json &j) : name(j["name"]) {
    for (const json &v : j) {
        ingredients.emplace_back(v);
    }
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

void get_recipes(const std::vector<product> &ingredients, uint32_t size) {
    std::ifstream file("../data/recipes.json");
    json j = json::parse(file);
    file.close();

    struct set_unit {
        uint32_t in_amount;
        uint32_t leven_dist;
        search::Recipe recipe_;
        bool operator<(const set_unit &a) const {
            if (a.in_amount != in_amount) {
                return a.in_amount < in_amount;
            } else {
                return a.leven_dist > leven_dist;
            }
        }
    };

    std::function<bool(const set_unit &a, const set_unit &b)> comp =
        [](const set_unit &a, const set_unit &b) {
            if (a.in_amount != b.in_amount) {
                return a.in_amount > b.in_amount;
            } else {
                return a.leven_dist < b.leven_dist;
            }
        };

    std::set<set_unit> top;
    for (const product &p : ingredients) {
        uint32_t in_amount = 0;
        uint32_t leven_dist = 0;

        std::vector<uint32_t> first_str_codepoints;
        from_str_to_codepoint(p.name, first_str_codepoints);
        set_unit max;
        for (const json &x : j) {
            Recipe cur_recipe(x);
            std::string temp_name = cur_recipe.name;

            std::vector<uint32_t> second_str_codepoints;
            from_str_to_codepoint(cur_recipe.name, second_str_codepoints);

            in_amount += check_in(first_str_codepoints, second_str_codepoints);
            leven_dist +=
                levenshtein_algo(first_str_codepoints, second_str_codepoints);

            if (max < set_unit({in_amount, leven_dist})) {
                max = {in_amount, leven_dist, cur_recipe};
            }
        }

        top.insert({in_amount, leven_dist, max.recipe_});

        if (top.size() > size) {
            auto it = top.end();
            it--;
            top.erase(it);
        }
    }
}

void search_recipe(const string &input_string, uint32_t size) {
    std::ifstream file("../data/recipes.json");
    json j = json::parse(file);
    file.close();

    std::vector<uint32_t> first_str_codepoints;
    from_str_to_codepoint(input_string, first_str_codepoints);

    struct set_unit {
        uint32_t in_amount;
        uint32_t leven_dist;
        search::Recipe recipe_;
        bool operator<(const set_unit &a) const {
            if (a.in_amount != in_amount) {
                return a.in_amount < in_amount;
            } else {
                return a.leven_dist > leven_dist;
            }
        }
    };

    std::multiset<set_unit> top;

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
}

}  // namespace search
