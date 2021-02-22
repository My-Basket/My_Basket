//
// Created by nikolya on 04.02.2021.
//

#ifndef BUCKET_PROJECT_ALGO_H
#define BUCKET_PROJECT_ALGO_H

#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <tuple>
#include <map>
#include <algorithm>
#include <utility>
#include "search_engine.h"
#include <set>
#include <list>

using std::vector, std::unordered_set, std::tuple, std::string, std::pair, std::tuple, search::product, std::set, std::list;

///////////////////////////////////////////

class ingredients_to_recipe  {                          // сценарий получения рецептов по продуктам
    vector<pair<string, vector<product>>> all_recipes;  // вектор рецептов из csv
    vector<product> ingredients_of_request;            // ингредиенты, выпадающие на запрос
    list<product> chosen_ingredients;
    list<product> bad_ingredients;                  // нежелательные ингредиенты
    vector<tuple<int, string, vector<product>>> recommended_recipes; /* рецепты, полученные по продуктам
  (количество совпавших продуктов, название рецепта, список продуктов с их количеством */
    vector<string> popular_ingredients;
public:
    ingredients_to_recipe() = default;

    void search_ingredient(string &name_of_ingredient)&;

    [[nodiscard]]vector<product> show_res_of_request() const &;

    void choose_ingredient_in_menu(std::list<product>::const_iterator it) &;

    void remove_ingredient_from_menu(std::list<product>::const_iterator it) &;

    void choose_bad_ingredients(std::list<product>::const_iterator it) &;

   // void search_recipes() &;

    void stop_searching_ingredient() &;

    void cancel_choice() &;
};

/////////////////////////////////////////
class recipe_to_ingredients { // сценарий получения ингредиентов по рецепту
    vector<pair<string, vector<product>>> client_recipes;
    vector<pair<string, vector<product>>> all_recipes;
public:
    recipe_to_ingredients() = default;
    void search_recipe(const string &name_of_recipe) &;

    [[nodiscard]]vector<pair<string, vector<product>>> get_recipes() const;

    void stop_searching() &;

    [[nodiscard]]vector<product> ingredients_of_recipe(int num) const;
};

#endif //BUCKET_PROJECT_ALGO_H
