#ifndef MY_BASKET_SEARCH_ENGINE_H
#define MY_BASKET_SEARCH_ENGINE_H

#include <fstream>
#include <list>
#include <set>
#include <string>
#include "iostream"
#include "json.hpp"
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
    product(const std::string &name_,
            const std::string &category_,
            const uint32_t &price_);

    product &operator=(const product &d) = default;

    product(product &&d) = default;

    product &operator=(product &&d) = default;

    product(const json &j);

    product &operator=(const json &j);
    ~product() = default;

    bool operator==(const product &p) const;

    [[nodiscard]] std::string get_name() const;
    [[nodiscard]] uint32_t get_price() const;

    friend product get_the_cheapest(const std::string &file_name, const std::string &s);

    friend void get_recipes(const std::vector<product> &ingredients,
                            uint32_t size,
                            std::vector<Recipe> &vec);

    friend std::ostream &operator<<(std::ostream &os, const product &p);
};

bool get_prod_top_by_name(const std::string &input_string,
                          const std::string &file_name,
                          const uint32_t &size,
                          std::multiset<set_unit<product>> &prods);

class Recipe {
private:
    std::string name;
    std::string reference;
    std::string pic_reference;
    std::vector<search::product> ingredients;

public:
    Recipe() = default;

    Recipe(const Recipe &recipe) = default;

    Recipe &operator=(const Recipe &recipe) = default;

    Recipe(Recipe &&recipe) = default;

    Recipe &operator=(Recipe &&recipe) = default;

    Recipe(const std::string &name_);

    Recipe(const std::string &name_,
           const std::string &ref_,
           const std::string &pref_);

    ~Recipe() = default;

    void clear();

    Recipe(const json &j);

    void add_product(const search::product &prod);

    bool is_ingredient_in_recipe(
        const product &ingredient);  //проверка на наличие ингредиента в рецепте
    std::pair<long long, std::vector<std::pair<std::string, uint32_t>>>
    sum_price_of_rec_prod(const std::string &file_name);

    friend void get_recipes(const std::vector<product> &ingredients,
                            uint32_t size,
                            std::vector<Recipe> &vec);

    friend std::ostream &operator<<(std::ostream &os, const Recipe &p);

    std::string get_name() const;

    std::string get_reference() const;

    std::string get_pic_reference() const;

    std::vector<search::product> const &get_ingredients() const;
};

void search_recipe(const string &input_string,
                   uint32_t size,
                   std::vector<Recipe> &vec);

void get_recipes(const std::vector<product> &ingredients,
                 uint32_t size,
                 std::vector<Recipe> &vec);

void put_product_in_basket(std::vector<search::product> &basket,
                           search::product &prod);

}  // namespace search
#endif  // MY_BASKET_SEARCH_ENGINE_H