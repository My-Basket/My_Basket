#include "algo.h"
#include <errors.h>
#include <iostream>
#include "search_engine.h"

using nlohmann::json, search::product, search::set_unit;
std::map<const std::string, const std::string> shop_names = {
    {"../data/av.json", "Азбука вкуса"},
    {"../data/karusel.json", "Карусель"},
    {"../data/spar.json", "SPAR"}};
size_t API::ingredients_to_recipe::choose_category_shop(const std::string &s) {
    if (s == "base") {
        return shop_mode = BASE;
    } else if (s == "economy") {
        return shop_mode = ECONOMY;
    } else {
        return shop_mode = PREMIUM;
    }
}

bool API::get_prod_top_by_name(std::string &input_string,
                               std::vector<product> &vec,
                               uint32_t size) {
    bool flag = false;
    std::multiset<search::set_unit<search::product>> prods;
    switch (API::ingredients_to_recipe::get_shop_mode()) {
        case API::Shop_Mode::ECONOMY:
            for (const auto &sh : API::Data_files::econom_shops) {
                flag =
                    search::get_prod_top_by_name(input_string, sh, size, prods);
            }
            for (const auto &t : prods) {
                vec.push_back(t.product_);
            }
            return flag;
        case API::Shop_Mode::BASE:
            for (const auto &sh : API::Data_files::base_shops) {
                flag =
                    search::get_prod_top_by_name(input_string, sh, size, prods);
            }
            for (const auto &t : prods) {
                vec.push_back(t.product_);
            }
            return flag;
        case API::Shop_Mode::PREMIUM:
            for (const auto &sh : API::Data_files::premium_shops) {
                flag =
                    search::get_prod_top_by_name(input_string, sh, size, prods);
            }
            for (const auto &t : prods) {
                vec.push_back(t.product_);
            }
            return flag;
    }
    return false;
}

std::pair<std::vector<product>, bool>  API::ingredients_to_recipe::run_product_search(
    std::string s,
    uint32_t size,
    std::vector<search::product> &top) {
    bool flag = API::get_prod_top_by_name(s, top, size);
    res_of_request = std::move(top);
    return {res_of_request, flag};
}
std::vector<search::Recipe> API::ingredients_to_recipe::run_recipes_search(
    const std::vector<search::product> &ingredients,
    uint32_t size,
    std::vector<search::Recipe> &vec) {
    search::get_recipes(ingredients, size, vec);
    return recommended_recipes = std::move(vec);
}
std::vector<search::Recipe> API::ingredients_to_recipe::show_recipes() {
    return recommended_recipes;  //возвращает топ 10 рекомендуемых рецептов
}
std::vector<search::product> API::ingredients_to_recipe::show_res_of_request() {
    return res_of_request;  //возвращает первые 10 продуктов по введенной строке
}

void API::put_product_in_basket(std::vector<search::product> &basket,
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

void API::ingredients_to_recipe::discard_all() {
    chosen_recipe.clear();
    recommended_recipes.clear();
    shop_mode = 2;
    res_of_request.clear();
    chosen_ingredients.clear();
}

void API::ingredients_to_recipe::stop_searching_ingredient() {
    res_of_request.clear();
}

std::pair<std::vector<search::Recipe>, bool> API::ingredients_to_recipe::run_recipe_search_by_str(
    const std::string &s,
    uint32_t size,
    std::vector<search::Recipe> &vec) {
    bool is_valid_request = search::search_recipe(s, size, vec);
    recommended_recipes = std::move(vec);
    return {recommended_recipes, is_valid_request};
}

int API::ingredients_to_recipe::get_shop_mode() {
    return shop_mode;
}

search::Recipe API::ingredients_to_recipe::choose_recipe(uint32_t num) {
    return chosen_recipe =
               recommended_recipes[num];
}

std::pair<std::pair<std::string, long long>,
          std::vector<std::pair<std::string, uint32_t>>>
API::ingredients_to_recipe::compare_prices_of_ingredients() {
    long long min_sum = 0;
    bool flag = true;
    size_t min_ind = 0;
    switch (ingredients_to_recipe::get_shop_mode()) {
        case Shop_Mode::ECONOMY:
            for (size_t i = 0; i < Data_files::econom_shops.size(); i++) {
                auto cur_sum =
                    chosen_recipe
                        .sum_price_of_rec_prod(Data_files::econom_shops[i])
                        .first;
                if (cur_sum < min_sum || flag) {
                    flag = false;
                    min_sum = cur_sum;
                    min_ind = i;
                }
            }
            return {
                {shop_names[Data_files::econom_shops[min_ind]], min_sum},
                chosen_recipe
                    .sum_price_of_rec_prod(Data_files::econom_shops[min_ind])
                    .second};
        case Shop_Mode::BASE:
            for (size_t i = 0; i < Data_files::base_shops.size(); i++) {
                auto cur_sum =
                    chosen_recipe
                        .sum_price_of_rec_prod(Data_files::base_shops[i])
                        .first;
                if (cur_sum < min_sum || flag) {
                    flag = false;
                    min_sum = cur_sum;
                    min_ind = i;
                }
            }
            return {{shop_names[Data_files::base_shops[min_ind]], min_sum},
                    chosen_recipe
                        .sum_price_of_rec_prod(Data_files::base_shops[min_ind])
                        .second};
        case Shop_Mode::PREMIUM:
            for (size_t i = 0; i < Data_files::premium_shops.size(); i++) {
                auto cur_sum =
                    chosen_recipe
                        .sum_price_of_rec_prod(Data_files::premium_shops[i])
                        .first;
                if (cur_sum < min_sum || flag) {
                    flag = false;
                    min_sum = cur_sum;
                    min_ind = i;
                }
            }
            return {
                {shop_names[Data_files::premium_shops[min_ind]], min_sum},
                chosen_recipe
                    .sum_price_of_rec_prod(Data_files::premium_shops[min_ind])
                    .second};
    }
    return {{}, {}};
}
