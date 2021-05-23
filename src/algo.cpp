#include "algo.h"
#include <iostream>
using nlohmann::json, search::product, search::set_unit;
size_t API::ingredients_to_recipe::choose_category_shop(const std::string &s) {
    if (s == "Base") {
        return shop_mode = BASE;
    } else if (s == "Economy") {
        return shop_mode = ECONOMY;
    } else {
        return shop_mode = PREMIUM;
    }
}
void API::get_prod_top_by_name(std::string &input_string,
                               std::vector<product> &vec,
                               uint32_t size) {
    std::vector<uint32_t> first_str_codepoints;
    try {
        from_str_to_codepoint(input_string, first_str_codepoints);
    } catch (const InvalidString &s) {
        std::cerr << s.what();
        return;
    }
    switch (API::ingredients_to_recipe::shop_mode) {
        case API::Shop_Mode::ECONOMY:
            for (const auto &sh : API::Data_files::econom_shops) {
                API::ingredients_to_recipe::checking_prod_or_rec_in_shop<
                    search::product>(first_str_codepoints, sh, vec, size);
            }
            break;
        case API::Shop_Mode::BASE:
            for (const auto &sh : API::Data_files::base_shops) {
                API::ingredients_to_recipe::checking_prod_or_rec_in_shop<
                    search::product>(first_str_codepoints, sh, vec, size);
            }
            break;
        case API::Shop_Mode::PREMIUM:
            for (const auto &sh : API::Data_files::premium_shops) {
                API::ingredients_to_recipe::checking_prod_or_rec_in_shop<
                    search::product>(first_str_codepoints, sh, vec, size);
            }
            break;
    }
}
void API::search_recipe(const string &input_string,
                        uint32_t size,
                        std::vector<Recipe> &vec) {
    std::vector<uint32_t> first_str_codepoints;
    try {
        from_str_to_codepoint(input_string, first_str_codepoints);
    } catch (const InvalidString &s) {
        std::cerr << s.what();
        return;
    }
    API::ingredients_to_recipe::checking_prod_or_rec_in_shop<search::Recipe>(
        first_str_codepoints, "../data/recipes.json", vec, size);
}
void API::ingredients_to_recipe::run_product_search(
    std::string s,
    uint32_t size,
    std::vector<search::product> &top) {
    API::get_prod_top_by_name(s, top, size);
    res_of_request = std::move(top);
}
void API::ingredients_to_recipe::run_recipes_search(
    const std::vector<search::product> &ingredients,
    uint32_t size,
    std::vector<search::Recipe> &vec) {
    search::get_recipes(ingredients, size, vec);
    if (&recommended_recipes != &vec) {
        recommended_recipes = std::move(vec);
    }
}
std::vector<search::Recipe> API::ingredients_to_recipe::show_recipes() {
    return recommended_recipes;  //возвращает топ 10 рекомендуемых рецептов
}
std::vector<search::product> API::ingredients_to_recipe::show_res_of_request() {
    return res_of_request;  //возвращает первые 10 продуктов по введенной строке
}

void search::put_product_in_basket(std::vector<search::product> &basket,
                                   search::product &prod) {
    basket.push_back(prod);
}

void API::ingredients_to_recipe::choose_ingredients(uint32_t num) {
    auto it = res_of_request.begin();
    for (size_t i = 0; i < num; i++) {
        it++;
    }
    chosen_ingredients.push_back(*it);  // chosen_ingredients - корзина
}
void API::ingredients_to_recipe::discard_basket() {
    chosen_ingredients.clear();
}
void API::ingredients_to_recipe::stop_searching_ingredient() {
    res_of_request.clear();
}
void API::recipe_to_ingredients::run_recipe_search(
    const std::string &s,
    uint32_t size,
    std::vector<search::Recipe> &vec) {
    search_recipe(s, size, vec);
    recipes_request = std::move(vec);
}
std::vector<search::Recipe> API::recipe_to_ingredients::show_recipes() {
    return recipes_request;
}
void API::recipe_to_ingredients::cancel_choice() {
    chosen_recipe.clear();
}
void API::recipe_to_ingredients::stop_searching_recipe() {
    recipes_request.clear();
}
void API::recipe_to_ingredients::choose_recipe(uint32_t num) {
    chosen_recipe = recipes_request[num];  // TODO понять, как получать номер
}