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

using std::vector, std::unordered_set, std::tuple, std::string, std::pair, std::tuple;

///////////////////////////////////////////
class Data {
protected:
    vector<pair<string, vector<pair<int, string>>>> all_recipes; // вектора, в которые будем погружать рецепты и продукты из CSV файла
    vector<string> all_ingredients;
public:
    Data();
};
///////////////////////////////////////////

class ingredients_to_recipe : Data { // сценарий получения рецептов по продуктам
    vector<string> ingredients_of_request;  // ингредиенты, выпадающие на запрос
    unordered_set<string> chosen_ingredients; // выбранные ингредиенты
    unordered_set<string> bad_ingredients;  // нежелательные ингредиенты
    vector<tuple<int, string, vector<pair<int, string>>>> recommended_recipes; /* рецепты, полученные по продуктам
  (количество совпавших продуктов, название рецепта, список продуктов с их количеством */

public:
    ingredients_to_recipe();

    void search_ingredient(const std::string &name_of_ingredient) &;

    [[nodiscard]]vector<string> show_res_of_request() const;

    void choose_ingredient_in_menu(int a) &;

    void remove_ingredient_from_menu(int a) &;

    void choose_bad_ingredients(int a) &;

    void search_recipes() &;

    void stop_searching_ingredient() &;

    void cancel_choice() &;
};

/////////////////////////////////////////
class recipe_to_ingredients : Data { // сценарий получения ингредиентов по рецепту
    vector<pair<string, vector<pair<int, string>>>> recipes;
public:
    recipe_to_ingredients();

    void search_recipe(const string &name_of_recipe) &;

    [[nodiscard]]vector<pair<string, vector<pair<int, string>>>> get_recipes() const;

    void stop_searching() &;

    [[nodiscard]]vector<pair<int, string>> ingredients_of_recipe(int num) const;
};

#endif //BUCKET_PROJECT_ALGO_H
