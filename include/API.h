#ifndef MY_BASKET_API_H
#define MY_BASKET_API_H
#include <fstream>
#include <functional>
#include <list>
#include <set>
#include <string>
#include <vector>
#include "json.hpp"
#include "search_engine.h"
#include "work_with_string.h"

namespace API {
enum Shop_Mode { ECONOMY, BASE, PREMIUM };
namespace Data_files {
const std::vector<std::string> econom_shops = {"../data/spar.json"};
const std::vector<std::string> base_shops = {"../data/karusel.json",
                                             "../data/spar.json"};
const std::vector<std::string> premium_shops = {
    "../data/av.json", "../data/spar.json", "../data/karusel.json"};
}  // namespace Data_files

using search::product, search::Recipe;
class ingredients_and_recipes {
private:
    static std::vector<search::product> res_of_prod_request;  // NOLINT
    static std::vector<search::product> chosen_ingredients;   // NOLINT
    static std::vector<search::Recipe>

        recommended_recipes;              // NOLINT
    static search::Recipe chosen_recipe;  // NOLINT

    static size_t shop_mode;

public:
    static size_t choose_category_shop(const std::string &s);

    static int get_shop_mode();

    static void discard_all();

    static Recipe choose_recipe(uint32_t num);
    static std::pair<std::vector<product>, bool> run_product_search(
        std::string s,
        uint32_t size,
        std::vector<search::product> &top);

    static std::vector<search::product> show_res_of_request();
    static std::vector<search::Recipe> run_recipes_search(
        const std::vector<search::product> &ingredients,
        uint32_t size,
        std::vector<search::Recipe> &vec);
    static std::vector<search::Recipe> show_recipes();
    static std::pair<std::vector<search::Recipe>, bool>
    run_recipe_search_by_str(const std::string &s,
                             uint32_t size,
                             std::vector<search::Recipe> &vec);
    static std::pair<std::pair<std::string, long long>,
                     std::vector<std::pair<std::string, uint32_t>>>
    compare_prices_of_ingredients();

    friend void put_product_in_basket(std::vector<search::product> &basket,
                                      search::product &prod);
};

bool get_prod_top_by_name(string &input_string,
                          std::vector<product> &vec,
                          uint32_t size);
void put_product_in_basket(std::vector<search::product> &basket,
                           search::product &prod);
}  // namespace API

#endif  // MY_BASKET_SEARCH_ALGO_H