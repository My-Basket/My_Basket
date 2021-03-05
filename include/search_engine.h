// Created by TurovV on 18.02.2021.

#ifndef MY_BASKET_SEARCH_ENGINE_H
#define MY_BASKET_SEARCH_ENGINE_H

#include <list>
#include <set>
#include <string>
#include "json.hpp"

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

class product {
private:
    std::string name;
    std::string category;
    uint32_t price;

public:
    product(const product &d) = default;

    product &operator=(const product &d) = default;

    product(product &&d) = default;

    product &operator=(product &&d) = default;

    product(const json &j);

    product &operator=(const json &j);

    bool operator==(const product &p) const;

    friend void get_prod_top_by_name(std::string &input_string,
                                     uint32_t size,
                                     std::vector<product> &vec);

    friend void get_recipes(const std::vector<product> &ingredients,
                            uint32_t size);

    friend std::ostream &operator<<(std::ostream &os, const product &p);

    ~product() = default;
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

    friend void get_recipes(const std::vector<product> &ingredients,
                            uint32_t size);
    //получает на вход продукты, сует в recommended recipes класса
    // ingredients_to_recipes топ 10 лучших рецептов

    friend void search_recipe(const std::string &input_string, uint32_t size);

    //ищет рецепт по введённой строке, сует в recipes_request класса
    // recipes_to_ingredients топ 10 лучших рецептов
    friend std::ostream &operator<<(std::ostream &os, const Recipe &p);
};

}  // namespace search

#endif  // MY_BASKET_SEARCH_ENGINE_H
