// Created by TurovV on 18.02.2021.

#ifndef MY_BASKET_ALGO_H
#define MY_BASKET_ALGO_H

#include <list>
#include <set>
#include <string>
#include "search_engine.h"
#include <vector>
namespace functions {

class ingredients_to_recipe {
private:
    static std::multiset<search::set_unit, search::comp> res_of_request;
    static std::vector<search::product> chosen_ingredients;
    static std::vector<search::Recipe> recommended_recipes;
    // TODO static list<product> chosen_bad_ingredients;
    // TODO static multiset<set_unit, comp> bad_ingredients;
    // TODO vector<string> popular_ingredients;
public:
    static void stop_searching_ingredient();

    static void discard_basket();

    static void choose_ingredients(uint32_t num);
    static void run_search(std::string &s, uint32_t size, std::multiset<search::set_unit, search::comp> &top);

    static std::multiset<search::set_unit, search::comp> show_res_of_request();

    friend void get_prod_top_by_name(std::string &input_string, uint32_t size, std::multiset<search::set_unit, search::comp> & top );

    friend void get_recipes(const std::vector<search::product> &ingredients,
                            uint32_t size);
};

class recipe_to_ingredients {
    static std::vector<search::Recipe> recipes_request;
    static search::Recipe chosen_recipe;

public:
    static std::vector<search::Recipe> show_recipes();

    static void choose_recipe(uint32_t num);

    static void stop_searching_recipe();

    static void cancel_choice();

    friend void search_recipe(const std::string &input_string, uint32_t size);
};

}  // namespace functions

#endif  // MY_BASKET_SEARCH_ALGO_H
