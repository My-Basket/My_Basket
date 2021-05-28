#include "search_engine.h"
#include <logger.h>
#include <cassert>
#include <fstream>
#include "work_with_string.h"

error_file_logger &err_in_file() {
    static error_file_logger fl_log;
    return fl_log;
}

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
    std::vector<uint32_t> &first_str,
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
bool compare(const search::product &p1, const search::product &p2) {
    std::vector<uint32_t> codepoint1;
    std::vector<uint32_t> codepoint2;
    try {
        from_str_to_codepoint(p1.get_name(), codepoint1);
        from_str_to_codepoint(p2.get_name(), codepoint2);
    } catch (const err::MyBasketError &er) {
        err_in_file().log(er);
        return false;
    }
    uint32_t min_value = std::min(codepoint1.size(), codepoint2.size());
    return check_in(codepoint1, codepoint2) >
           0.7 * static_cast<double>(min_value);
}
}  // namespace

namespace search {

std::ostream &operator<<(std::ostream &os, const product &p) {
    os << "{\n"
       << "\t"
       << "\"Name\" : \"" << p.name << "\",\n"  // NOLINT
       << "\t"
       << "\"Category\" : \"" << p.category << "\",\n"  // NOLINT
       << "\t"
       << "\"Price\" : " << p.price << "\n"
       << "}";
    return os;
}

bool get_prod_top_by_name(const std::string &input_string,
                          const std::string &file_name,
                          const uint32_t &size,
                          std::multiset<set_unit<product>> &prods) {
    std::ifstream file(file_name);
    json j = json::parse(file);
    file.close();

    std::vector<uint32_t> first_str_codepoints;
    try {
        from_str_to_codepoint(input_string, first_str_codepoints);
    } catch (const err::MyBasketError &er) {
        err_in_file().log(er);
        return false;
    }
    std::multiset<set_unit<product>> top;
    for (auto const &x : j) {
        product cur_prod(x);
        auto temp_name = cur_prod.get_name();

        std::vector<uint32_t> second_str_codepoints;
        try {
            from_str_to_codepoint(cur_prod.get_name(), second_str_codepoints);
        } catch (const err::MyBasketError &er) {
            err_in_file().log(er);
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
    for (const auto &t : top) {
        prods.insert(t);
    }
    return true;
}

std::string product::get_name() const {
    return name;
}

product::product(const json &j) {
    try {
        name = j["Name"];
        category = j["Category"];
        price = j["Price"];
    } catch (const json::exception &er) {
        err_in_file().log(er);
    }
}

product &product::operator=(const json &j) {
    try {
        name = j["Name"];
        category = j["Category"];
        price = j["Price"];
        return *this;
    } catch (const nlohmann::detail::parse_error &er) {
        err_in_file().log(er);
    }
    return *this;
}

bool product::operator==(const product &p) const {
    return p.name == name;
}

std::ostream &operator<<(std::ostream &os, const Recipe &p) {
    os << "{\n";
    os << "\t"
       << "\"Name\" : "
       << "\"" << p.name << "\","
       << "\n";
    os << "\t"
       << "\"Reference\" : "
       << "\"" << p.reference << "\","
       << "\n";
    os << "\t"
       << "\"Picture reference\" : "
       << "\"" << p.pic_reference << "\","
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
        [&ingredient](const product &p) { return compare(p, ingredient); });
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
        vec.push_back(x.product_);
    }
}

std::string Recipe::get_name() const {
    return name;
}

bool search_recipe(const string &input_string,
                   uint32_t size,
                   std::vector<Recipe> &vec) {
    std::ifstream file("../data/recipes.json");
    json j = json::parse(file);
    file.close();

    std::vector<uint32_t> first_str_codepoints;
    try {
        from_str_to_codepoint(input_string, first_str_codepoints);
    } catch (const err::MyBasketError &er) {
        err_in_file().log(er);
        return false;
    }
    std::multiset<set_unit<Recipe>> top;

    for (const json &x : j) {
        Recipe cur_recipe(x);
        std::string temp_name = cur_recipe.get_name();

        std::vector<uint32_t> second_str_codepoints;
        try {
            from_str_to_codepoint(cur_recipe.get_name(), second_str_codepoints);
        } catch (const err::MyBasketError &er) {
            err_in_file().log(er);
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
    vec.resize(size);
    for (int i = 0; i < size && !top.empty(); i++) {
        vec[i] = top.begin()->product_;
        top.erase(top.begin());
    }
    return true;
}

std::pair<long long, std::vector<std::pair<std::string, uint32_t>>>
Recipe::sum_price_of_rec_prod(const std::string &file_name) {
    std::vector<std::pair<std::string, uint32_t>> price_of_prod(
        ingredients.size());
    long long sum = 0;
    for (size_t i = 0; i < ingredients.size(); i++) {
        std::multiset<set_unit<search::product>> ingredient;
        auto cur_prod_name = ingredients[i].get_name();
        std::vector<uint32_t> first_str_codepoints;
        bool flag = search::get_prod_top_by_name(cur_prod_name, file_name, 1,
                                                 ingredient);
        if (!ingredient.empty() && flag) {
            price_of_prod[i] = {(*ingredient.begin()).product_.get_name(),
                                (*ingredient.begin()).product_.get_price()};
        } else {
            price_of_prod[i] = {cur_prod_name, 100000000};
        }
        sum += price_of_prod[i].second;
    }
    return {sum, price_of_prod};
}

void Recipe::add_product(const search::product &prod) {
    ingredients.push_back(prod);
}

Recipe::Recipe(const std::string &name_) : name(name_) {  // NOLINT
}

std::string Recipe::get_reference() const {
    return reference;
}

std::string Recipe::get_pic_reference() const {
    return pic_reference;
}

std::vector<search::product> const &Recipe::get_ingredients() const {
    return ingredients;
}

Recipe::Recipe(const std::string &name_,
               const std::string &ref_,
               const std::string &pref_)
    : name(name_), reference(ref_), pic_reference(pref_) {
}

product::product(const std::string &name_,
                 const std::string &category_,
                 const uint32_t &price_)
    : name(name_), category(category_), price(price_) {
}
}  // namespace search