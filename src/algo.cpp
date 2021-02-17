//
// Created by nikolya on 04.02.2021.
//
#include "algo.h"

using std::vector, std::unordered_set, std::tuple, std::string, std::pair, std::tuple;

///////////////////////////////////////////
Data::Data() = default;

ingredients_to_recipe::ingredients_to_recipe() = default;

void ingredients_to_recipe::search_ingredient(const std::string &name_of_ingredient) &{
    for (const auto &ingredient: all_ingredients) {
        if (name_of_ingredient == ingredient) {
            ingredients_of_request.emplace_back(ingredient);
        }
    }
}

[[nodiscard]]vector<string> ingredients_to_recipe::show_res_of_request() const {
    return ingredients_of_request;
}

void ingredients_to_recipe::choose_ingredient_in_menu(int a) &{
    chosen_ingredients.insert(ingredients_of_request[a]);
}

void ingredients_to_recipe::remove_ingredient_from_menu(int a) &{
    chosen_ingredients.erase(ingredients_of_request[a]);
}

void ingredients_to_recipe::choose_bad_ingredients(int a) &{
    bad_ingredients.emplace(ingredients_of_request[a]);
}

void ingredients_to_recipe::search_recipes() &{
    int num_of_recipe = 0;
    for (const auto &recipe: all_recipes) {
        int counter = 0;
        bool is_bad_recipe = false;
        for (const auto &my_ingredients: chosen_ingredients) {
            bool flag = false;
            // проверяем, сколько ингредиентов содержится в рецепте
            for (const auto &ingredients: recipe.second) {
                if (ingredients.second == my_ingredients && !flag) {
                    counter++;
                    flag = true;
                }
            }
        }
        // проверяем, есть ли плохие ингредиенты
        for (const auto &bad_ingredient: bad_ingredients) {
            for (const auto &ingredients: recipe.second) {
                if (ingredients.second == bad_ingredient && !is_bad_recipe) {
                    is_bad_recipe = true;
                }
            }
        }
        if (counter > 0 && !is_bad_recipe) {
            recommended_recipes.emplace_back(counter, recipe.first, recipe.second);
        }
        num_of_recipe++;
    }
    std::sort(recommended_recipes.begin(), recommended_recipes.end(), [](auto const &t1, auto const &t2) {
        return std::get<0>(t1) > std::get<0>(t2);
    });    // сортируем рецепты в порядке убывания совпавших элементов
}

void ingredients_to_recipe::stop_searching_ingredient() &{
    ingredients_of_request.clear();
}

void ingredients_to_recipe::cancel_choice() &{
    recommended_recipes.clear();
    chosen_ingredients.clear();
    bad_ingredients.clear();
}


/////////////////////////////////////////
recipe_to_ingredients::recipe_to_ingredients() = default;

void recipe_to_ingredients::search_recipe(const string &name_of_recipe) &{
    for (const auto &recipe_: all_recipes) {
        if (name_of_recipe == recipe_.first) {
            recipes.emplace_back(recipe_);
        }
    }
}

[[nodiscard]]vector<pair<string, vector<pair<int, string>>>> recipe_to_ingredients::get_recipes() const {
    return recipes;
}

void recipe_to_ingredients::stop_searching() &{
    recipes.clear();
}

vector<pair<int, string>> recipe_to_ingredients::ingredients_of_recipe(int num) const {
    return recipes[num].second;
}

