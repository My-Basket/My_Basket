#include "search_engine.h"
#include <cassert>
#include <fstream>
#include "work_with_string.h"
//namespace {

void relax(uint32_t &a, uint32_t b) {
    if (a > b) {
        a = b;
    }
}

uint32_t levenshtein_algo(const std::vector<uint32_t> &first_str,
                          const std::vector<uint32_t> &second_str,
                          int deletion,
                          int insertion,
                          int substitution,
                          int transposition) {
    std::vector<std::vector<uint32_t>> f(
        first_str.size(), std::vector<uint32_t>(second_str.size(), 0));

    for (int i = 0; i < first_str.size(); i++) {
        for (int j = 0; j < second_str.size(); j++) {
            if (i == 0 || j == 0) {
                f[i][j] = std::max(i, j);
                continue;
            }

            int w = first_str[i] == second_str[j] ? 0 : substitution;

            f[i][j] = f[i - 1][j] + deletion;
            relax(f[i][j], f[i][j - 1] + insertion);
            relax(f[i][j], f[i - 1][j - 1] + w);
            if (i >= 2 && j >= 2 && first_str[i - 1] == second_str[j] &&
                first_str[i] == second_str[j - 1]) {
                relax(f[i][j], f[i - 2][j - 2] + transposition);
            }
        }
    }
    return f[first_str.size() - 1][second_str.size() - 1];
}

uint32_t check_in(const std::vector<uint32_t> &first_str,
                  const std::vector<uint32_t> &second_str) {
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

//}  // namespace

namespace search {

std::string product::get_name() const {
    return name;
}

std::ostream &operator<<(std::ostream &os, const product &p) {
    os<< "Name: " << p.name << '\n'
       << "   "
       << "Price: " << p.price << '\n';
    return os;
}

void get_prod_top_by_name(std::string &input_string,
                          uint32_t size,
                          std::vector<product> &vec) {
    std::ifstream file("../data/spar.json");
    json j = json::parse(file);
    file.close();

    std::vector<uint32_t> first_str_codepoints;
    from_str_to_codepoint(input_string, first_str_codepoints);


product::product(std::string name_, std::string category_, uint32_t price_)
    : name(std::move(name_)), category(std::move(category_)), price(price_) {
}

product::product(std::string name_, std::string category_, uint32_t price_)
    : name(std::move(name_)), category(std::move(category_)), price(price_) {
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

std::string product::get_name() const {
    return name;
}

uint32_t product::get_price() const {
    return price;
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

std::pair<uint32_t, std::vector<std::pair<std::string, uint32_t>>> Recipe::sum_price_of_rec_prod(const std::string &file_name) {

    std::vector<std::pair<std::string, uint32_t>> price_of_prod(ingredients.size(), {"", 10000});
    uint32_t sum = 0;
    for(size_t i =0; i<ingredients.size(); i++){
        std::vector<search::product> ingredient(1);
        auto cur_prod_name = ingredients[i].get_name();
        std::vector<uint32_t> first_str_codepoints;
        try {
            from_str_to_codepoint(cur_prod_name, first_str_codepoints); //TODO понять безопасная ли это операция здесь
        } catch (const InvalidString &s) {
            sum+=price_of_prod[i].second;
            std::cerr << s.what();
            continue;
        }
        search::checking_prod_or_rec_in_shop<search::product>(first_str_codepoints, file_name, ingredient, 1);
        price_of_prod[i] = {ingredient[0].get_name(), ingredient[0].get_price()};
        sum+=price_of_prod[i].second;
    }
    return {sum, price_of_prod};

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

    vec.clear();

    std::multiset<set_unit<Recipe>> top;
    for (const json &x : j) {
        uint32_t max = 0;
        Recipe R(x);
        for (const product &p : ingredients) {
            if (R.is_ingredient_in_recipe(p)) {
                max++;
            }
        }
        top.insert({max,0, R});

        if (top.size() > size) {
            auto it = top.end();
            it--;
            top.erase(it);
        }
    }

    for (const auto &x: top) {
        vec.push_back(x.product_); /// TODO CHANGE SET UNIT PRODUCT_ TO CONTENT_
    }
}

std::string get_recipe_name(search::Recipe &recipe) {
    return recipe.name;
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
        uint32_t max = 0;
        Recipe R(x);
        for (const product &p : ingredients) {
            if (R.is_ingredient_in_recipe(p)) {
                max++;
            }
        }
        top.insert({max, 0, R});

        if (top.size() > size) {
            auto it = top.end();
            it--;
            top.erase(it);
        }
    }

    for (const auto &x : top) {
        vec.push_back(
            x.product_);  /// TODO CHANGE SET UNIT PRODUCT_ TO CONTENT_
    }
}


std::string get_recipe_name(search::Recipe &recipe) {
    return recipe.name;
}


}  // namespace search