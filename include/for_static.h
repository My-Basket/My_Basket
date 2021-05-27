#ifndef MY_BASKET_FOR_STATIC_H
#define MY_BASKET_FOR_STATIC_H
#include "algo.h"
#include "search_engine.h"
size_t API::ingredients_to_recipe::shop_mode = 0;
std::vector<search::product> API::ingredients_to_recipe::res_of_request;
std::vector<search::product>
    API::ingredients_to_recipe::chosen_ingredients;
std::vector<search::Recipe>
    API::ingredients_to_recipe::recommended_recipes;
std::vector<search::Recipe> API::recipe_to_ingredients::recipes_request;
search::Recipe API::recipe_to_ingredients::chosen_recipe;



#endif  // MY_BASKET_FOR_STATIC_H