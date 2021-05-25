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

uint32_t check_in(
    std::vector<uint32_t> &first_str,  /// TODO change all to const
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
       << "\t"
       << "\"Name\" : \"" << p.name << "\"\n"
       << "\t"
       << "\"Category\" : \"" << p.category << "\"\n"
       << "\t"
       << "\"Price\" : \"" << p.price << "\"\n"
       << "}";
    return os;
}

void get_prod_top_by_name(const std::string &input_string,
                          std::vector<product> &vec,
                          const uint32_t &size) {
    std::ifstream file("../data/karusel1.json");
    json j = json::parse(file);
    file.close();

    std::vector<uint32_t> first_str_codepoints;
    try {
        from_str_to_codepoint(input_string, first_str_codepoints);
    } catch (...) {
        /// TODO log
    }
    std::multiset<set_unit<product>> top;
    for (auto const &x : j) {
        product cur_prod(x);
        auto temp_name = cur_prod.get_name();

        std::vector<uint32_t> second_str_codepoints;
        try {
            from_str_to_codepoint(cur_prod.get_name(), second_str_codepoints);
        } catch (...) {
            /// TODO log
        }
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

std::string product::get_name() const {
    return name;
}

product::product(const json &j) {
    try {
        name = j["Name"];
        category = j["Category"];
        price = j["Price"];
    } catch (...) {
        /// TODO log
    }
}

product &product::operator=(const json &j) {
    try {
        name = j["Name"];
        category = j["Category"];
        price = j["Price"];
        return *this;
    } catch (...) {
        /// TODO log
    }
    return *this;
}

bool product::operator==(const product &p) const {
    return p.name == name;
}

std::ostream &operator<<(std::ostream &os, const Recipe &p) {
    os << "{\n";
    os << "\t"
       << "\"Name\" :"
       << "\"" << p.name << "\""
       << "\n";
    os << "\t"
       << "\"Ingredients\" : [\n";
    for (auto it = p.ingredients.begin(); it < p.ingredients.end(); it++) {
        if (it == p.ingredients.end() - 1) {
            os << *it << "\n";
        } else {
            os << *it << ",\n";
        }
    }
    os << "]\n";
    os << "}";
    return os;
}

uint32_t product::get_price() const {
    return price;
}

//////////// RECIPE \\\\\\\\\\\\\\\

Recipe::Recipe(const json &j) : name(j["Name"]) {
    for (const json &v : j["Ingredients"]) {
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

std::string Recipe::get_name() {
    return name;
}

void search_recipe(const string &input_string,
                   uint32_t size,
                   std::vector<Recipe> &vec) {
    std::ifstream file("../data/recipes.json");
    json j = json::parse(file);
    file.close();

    std::vector<uint32_t> first_str_codepoints;
    try {
        from_str_to_codepoint(input_string, first_str_codepoints);
    } catch (...) {
        /// TODO log
    }
    std::multiset<set_unit<Recipe>> top;

    for (const json &x : j) {
        Recipe cur_recipe(x);
        std::string temp_name = cur_recipe.get_name();

        std::vector<uint32_t> second_str_codepoints;
        try {
            from_str_to_codepoint(cur_recipe.get_name(), second_str_codepoints);
        } catch (...) {
            /// TODO log
        }
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

template <typename T>  /// TODO That's absolutely not normal. Will be deleted.
void checking_prod_or_rec_in_shop(std::vector<uint32_t> &request,
                                  const std::string &file_name,
                                  std::vector<T> &res,
                                  uint32_t size) {
    std::ifstream file(file_name);
    json j = json::parse(file);
    file.close();

    std::multiset<search::set_unit<T>> top;
    for (auto const &x : j) {
        T cur_prod_or_rec(x);
        std::string temp_name = x["Name"];
        std::vector<uint32_t> second_str_codepoints;
        try {
            from_str_to_codepoint(temp_name, second_str_codepoints);
        } catch (const InvalidString &) {
            continue;
        }
        uint32_t in_amount = check_in(request, second_str_codepoints);
        uint32_t leven_dist = levenshtein_algo(request, second_str_codepoints);
        top.insert({in_amount, leven_dist, cur_prod_or_rec});

        if (top.size() > size) {
            auto it = top.end();
            it--;
            top.erase(it);
        }
    }

    for (const auto &su : top) {
        res.push_back(su.product_);
    }
}

std::pair<uint32_t, std::vector<std::pair<std::string, uint32_t>>>
Recipe::sum_price_of_rec_prod(const std::string &file_name) {
    std::vector<std::pair<std::string, uint32_t>> price_of_prod(
        ingredients.size(), {"", 10000});
    uint32_t sum = 0;
    for (size_t i = 0; i < ingredients.size(); i++) {
        std::vector<search::product> ingredient(1);
        auto cur_prod_name = ingredients[i].get_name();
        std::vector<uint32_t> first_str_codepoints;
        try {
            from_str_to_codepoint(cur_prod_name, first_str_codepoints);
        } catch (const InvalidString &s) {
            //            sum += price_of_prod[i].second;
            //            std::cerr << s.what();    /// TODO log
            continue;
        }
        search::checking_prod_or_rec_in_shop<search::product>(
            first_str_codepoints, file_name, ingredient, 1);
        price_of_prod[i] = {ingredient[0].get_name(),
                            ingredient[0].get_price()};
        sum += price_of_prod[i].second;
    }
    return {sum, price_of_prod};
}

void Recipe::add_product(const search::product &prod) {
    ingredients.push_back(prod);
}

Recipe::Recipe(const std::string &name_) : name(name_) {
}

product::product(const string &name_,
                 const string &category_,
                 const uint32_t &price_)
    : name(name_), category(category_), price(price_) {
}
}  // namespace search