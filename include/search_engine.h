#ifndef MY_BASKET_SEARCH_ENGINE_H
#define MY_BASKET_SEARCH_ENGINE_H

#include <list>
#include <set>
#include <string>
#include "json.hpp"
#include "iostream"
#include <fstream>
#include "work_with_string.h"
namespace search {

template <typename T>
struct set_unit {
    uint32_t in_amount = 0;
    uint32_t leven_dist = 0;
    T product_;
    bool operator<(const set_unit &a) const {
        if (a.in_amount != in_amount) {
            return a.in_amount < in_amount;
        } else {
            return a.leven_dist > leven_dist;
        }
    }
};

using nlohmann::json;
class Recipe;
class product {
private:
    std::string name;
    std::string category;
    uint32_t price;

public:

    product() = default;
    product(const product &d) = default;

    product &operator=(const product &d) = default;

    product(product &&d) = default;

    product &operator=(product &&d) = default;
    product(std::string name_, std::string category_, uint32_t price_);

    product(const json &j);

    product &operator=(const json &j);
    ~product() = default;

    bool operator==(const product &p) const;
    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] uint32_t get_price() const;

    friend void get_recipes(const std::vector<product> &ingredients,
                            uint32_t size,
                            std::vector<Recipe> &vec);



    friend std::ostream &operator<<(std::ostream &os, const product &p);


};

class Recipe {
    std::vector<search::product> ingredients;
    std::string name;

public:
    Recipe() = default;

    Recipe(const Recipe &recipe) = default;

    Recipe &operator=(const Recipe &recipe) = default;

    Recipe(Recipe &&recipe) = default;

    Recipe &operator=(Recipe &&recipe) = default;

    ~Recipe() = default;

    void clear();

    Recipe(const json &j);

    bool is_ingredient_in_recipe(
        const product &ingredient);  //проверка на наличие ингредиента в рецепте
    std::pair<uint32_t , std::vector<std::pair<std::string, uint32_t>>> sum_price_of_rec_prod(const std::string & file_name);

    friend void get_recipes(const std::vector<product> &ingredients,
                            uint32_t size,
                            std::vector<Recipe> &vec);

    friend std::ostream &operator<<(std::ostream &os, const Recipe &p);

    friend std::string get_recipe_name(Recipe &recipe);

};
template <typename T>
void checking_prod_or_rec_in_shop(
    const std::vector<uint32_t> &request,
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
        uint32_t leven_dist =
            levenshtein_algo(request, second_str_codepoints);
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
void get_recipes(const std::vector<product> &ingredients,
                 uint32_t size,
                 std::vector<Recipe> &vec);


void put_product_in_basket(std::vector<search::product> &basket,
                           search::product &prod);

std::string get_recipe_name(Recipe &recipe);

}  // namespace search
uint32_t levenshtein_algo(const std::vector<uint32_t> &first_str,
                          const std::vector<uint32_t> &second_str,
                          int deletion = 10,
                          int insertion = 10,
                          int substitution = 30,
                          int transposition = 30);
uint32_t check_in(const std::vector<uint32_t> &first_str,
                  const std::vector<uint32_t> &second_str);
#endif  // MY_BASKET_SEARCH_ENGINE_H