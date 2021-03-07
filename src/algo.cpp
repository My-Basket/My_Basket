#include "algo.h"
void functions::ingredients_to_recipe::run_product_search(std::string s, uint32_t size, std::vector<search::product> &top){
    search::get_prod_top_by_name(s, size, top);
    res_of_request = std::move(top);
}
void functions::ingredients_to_recipe::run_recipes_search(const std::vector<search::product>
    &ingredients, uint32_t size, std::vector<search::Recipe> & vec) {
    search::get_recipes(ingredients, size, vec);
    recommended_recipes = std::move(vec);
}
std::vector<search::Recipe> functions::ingredients_to_recipe::show_recipes() {
    return recommended_recipes;
}
std::vector<search::product> functions::ingredients_to_recipe::show_res_of_request() {
    return res_of_request; // возвращает первые 10 продуктов по введенной строке
}

void search::put_product_in_basket(std::string const &product_string){
    for (auto &prod : functions::ingredients_to_recipe::show_res_of_request()) {
        if (get_product_name(prod) == product_string) {
            functions::ingredients_to_recipe::chosen_ingredients.push_back(prod);
        }
    }
}

void functions::ingredients_to_recipe::choose_ingredients(uint32_t num) {
    auto it = res_of_request.begin();
    for (size_t i = 0; i < num; i++) {
        it++;
    }
    chosen_ingredients.push_back(*it); //chosen_ingredients - корзина
}
void functions::ingredients_to_recipe::discard_basket() {
    chosen_ingredients.clear();
}
void functions::ingredients_to_recipe::stop_searching_ingredient() {
    res_of_request.clear();
}
void functions::recipe_to_ingredients::run_recipe_search(const std::string& s, uint32_t size, std::vector<search::Recipe> & vec) {
    search::search_recipe( s,  size,  vec);
    recipes_request = std::move(vec);
}
std::vector<search::Recipe> functions::recipe_to_ingredients::show_recipes() {
    return recipes_request;  // топ 10 рецептов
}
void functions::recipe_to_ingredients::cancel_choice() {
    chosen_recipe.clear();
}
void functions::recipe_to_ingredients::stop_searching_recipe() {
    recipes_request.clear();
}
void functions::recipe_to_ingredients::choose_recipe(uint32_t num) {
    chosen_recipe = recipes_request[num]; //TODO понять, как получать номер
}