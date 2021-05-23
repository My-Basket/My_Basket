#include "algo.h"
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
    from_str_to_codepoint(input_string, first_str_codepoints);
    if (API::ingredients_to_recipe::shop_mode == API::Shop_Mode::ECONOMY) {
        API::ingredients_to_recipe::checking_prod_in_shop(
            first_str_codepoints, "../data/av.json", vec, size);
    } else if (API::ingredients_to_recipe::shop_mode == API::Shop_Mode::BASE) {
        API::ingredients_to_recipe::checking_prod_in_shop(
            first_str_codepoints, "../data/karusel.json", vec, size);
    } else {
        API::ingredients_to_recipe::checking_prod_in_shop(
            first_str_codepoints, "../data/spar.json", vec, size);
    }
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
void API::ingredients_to_recipe::checking_prod_in_shop(
    const std::vector<uint32_t> &request,
    const std::string &file_name,
    std::vector<search::product> &res,
    uint32_t size) {
    std::ifstream file(file_name);
    json j = json::parse(file);
    file.close();

    std::multiset<set_unit<product>> top;
    for (auto const &x : j) {
        product cur_prod(x);
        auto temp_name = cur_prod.get_name();

        std::vector<uint32_t> second_str_codepoints;
        from_str_to_codepoint(cur_prod.get_name(), second_str_codepoints);

        uint32_t in_amount = check_in(request, second_str_codepoints);
        uint32_t leven_dist = levenshtein_algo(request, second_str_codepoints);
        top.insert({in_amount, leven_dist, cur_prod});

        if (top.size() > size) {
            auto it = top.end();
            it--;
            top.erase(it);
        }
    }

    for (const set_unit<product> &su : top) {
        res.push_back(su.product_);
    }
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
    search::search_recipe(s, size, vec);
    recipes_request = std::move(vec);
}
std::vector<search::Recipe> API::recipe_to_ingredients::show_recipes() {
    return recipes_request;  // топ 10 рецептов
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