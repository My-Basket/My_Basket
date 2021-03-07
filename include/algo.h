

#ifndef MY_BASKET_ALGO_H
#define MY_BASKET_ALGO_H

#include <list>
#include <set>
#include <string>
#include <vector>
#include "search_engine.h"
namespace functions {

class ingredients_to_recipe {
private:
    static std::vector<search::product> res_of_request; //топ 10 продуктов по запросу
    static std::vector<search::product> chosen_ingredients; //продукты корзины
    static std::vector<search::Recipe> recommended_recipes; //топ рекомендуемых рецептов, выданных по запросу find
    // TODO static list<product> chosen_bad_ingredients;
    // TODO static multiset<set_unit, comp> bad_ingredients;
    // TODO vector<string> popular_ingredients;
public:
    static void stop_searching_ingredient();

    static void discard_basket();

    static void choose_ingredients(uint32_t num);
    static void run_product_search(std::string s,
                                   uint32_t size,
                                   std::vector<search::product> &top);

    static std::vector<search::product> show_res_of_request();
    static void run_recipes_search(
        const std::vector<search::product> &ingredients,
        uint32_t size,
        std::vector<search::Recipe> &vec);
    static std::vector<search::Recipe> show_recipes();
    friend void search::get_prod_top_by_name(std::string &input_string,
                                             uint32_t size,
                                             std::vector<search::product> &vec);

    friend void search::get_recipes(
        const std::vector<search::product> &ingredients,
        uint32_t size,
        std::vector<search::Recipe> &vec);

    friend void search::put_product_in_basket(std::string const &product_string);
};

class recipe_to_ingredients {
    static std::vector<search::Recipe> recipes_request;
    static search::Recipe chosen_recipe;

public:
    static void run_recipe_search(const std::string& s, uint32_t size, std::vector<search::Recipe> & vec);
    static std::vector<search::Recipe> show_recipes();

    static void choose_recipe(uint32_t num);

    static void stop_searching_recipe();

    static void cancel_choice();

    friend void search::search_recipe(const std::string &input_string,
                                      uint32_t size, std::vector<search::Recipe> & vec);
};

}  // namespace functions

#endif  // MY_BASKET_SEARCH_ALGO_H
