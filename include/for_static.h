//
// Created by nikolya on 06.03.2021.
//

#ifndef MY_BASKET_FOR_STATIC_H
#define MY_BASKET_FOR_STATIC_H
#include "algo.h"
#include "search_engine.h"
std::vector<search::product> functions::ingredients_to_recipe::res_of_request;
std::vector<search::product>
    functions::ingredients_to_recipe::chosen_ingredients;
std::vector<search::Recipe>
    functions::ingredients_to_recipe::recommended_recipes;
std::vector<search::Recipe> functions::recipe_to_ingredients::recipes_request;
search::Recipe functions::recipe_to_ingredients::chosen_recipe;
#endif  // MY_BASKET_FOR_STATIC_H
