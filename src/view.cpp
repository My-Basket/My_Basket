#include "view.h"

View::View(ingredients_to_recipe scenario_1_, recipe_to_ingredients scenario_2_) :
        scenario_1(std::move(scenario_1_)), scenario_2(std::move(scenario_2_)) {
}


void View::show_basket() &{
    for (const auto &ingredient: scenario_1.show_res_of_request()) {
        std::cout << ingredient << std::endl;
    }
}

void View::show_recipes() &{
    for (const auto &recipe: scenario_2.get_recipes()) {
        std::cout << recipe.first << std::endl;
    }
}

void View::show_ingredients_of_recipe(int number) &{
    for (const auto &ingredients: scenario_2.ingredients_of_recipe(number)) {
        std::cout << ingredients.first << " " << ingredients.second << std::endl;
    }
}

