#include "algo.h"
#include <fstream>
using std::vector, std::unordered_set, std::tuple, std::string, std::pair, std::tuple, std::ifstream;
using nlohmann::json, search::product;
uint32_t size_of_top =10;
///////////////////////////////////////////

void ingredients_to_recipe::search_ingredient(string &name_of_ingredient)&{
    ifstream file_("../data/av.json");
    json j = json::parse(file_);
    file_.close();
    get_prod_top_by_name(name_of_ingredient, size_of_top, ingredients_of_request);
}

[[nodiscard]]vector<product> ingredients_to_recipe::show_res_of_request() const &{
    return ingredients_of_request;
}

void ingredients_to_recipe::choose_ingredient_in_menu(std::list<product>::const_iterator it) &{
    chosen_ingredients.push_back(*it);
}

void ingredients_to_recipe::remove_ingredient_from_menu(std::list<product>::const_iterator it) &{
    chosen_ingredients.erase(it);
}

void ingredients_to_recipe::choose_bad_ingredients(std::list<product>::const_iterator it) &{
    bad_ingredients.push_back(*it);
}
/*
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
*/
void ingredients_to_recipe::stop_searching_ingredient() &{
    ingredients_of_request.clear();
}

void ingredients_to_recipe::cancel_choice() &{
    recommended_recipes.clear();
    chosen_ingredients.clear();
    bad_ingredients.clear();
}


/////////////////////////////////////////

void recipe_to_ingredients::search_recipe(const string &name_of_recipe) &{
    for (const auto &recipe_: all_recipes) {
        if (name_of_recipe == recipe_.first) {
            client_recipes.emplace_back(recipe_);
        }
    }
}

[[nodiscard]]vector<pair<string, vector<product>>> recipe_to_ingredients::get_recipes() const {
    return client_recipes;
}

void recipe_to_ingredients::stop_searching() &{
    client_recipes.clear();
}
vector<product> recipe_to_ingredients::ingredients_of_recipe(int num) const {
    return client_recipes[num].second;
}
