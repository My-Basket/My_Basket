#ifndef MY_BASKET_ALGO_H
#define MY_BASKET_ALGO_H

#include <fstream>
#include <functional>
#include <list>
#include <set>
#include <string>
#include <vector>
#include "search_engine.h"
#include "work_with_string.h"
namespace API {

//enum Request_Mode { RECIPE, PRODUCT};
enum Shop_Mode { ECONOMY, BASE, PREMIUM };
namespace Data_files{
    const std::vector<std::string > econom_shops = {"../data/av.json"};
    const std::vector<std::string > base_shops = {"../data/karusel.json"};
    const std::vector<std::string > premium_shops = {"../data/spar.json"};
}
using search::product, search::Recipe;
class ingredients_to_recipe {
private:
    static std::vector<search::product>
        res_of_request;  //топ 10 продуктов по запросу
    static std::vector<search::product> chosen_ingredients;  //продукты корзины
    static std::vector<search::Recipe>

        recommended_recipes;  //топ рекомендуемых рецептов, выданных по запросу
    // TODO static list<product>
    // chosen_bad_ingredients;
    // TODO static multiset<set_unit, comp> bad_ingredients;
    // TODO vector<string> popular_ingredients;
    static size_t shop_mode;
public:
    static size_t choose_category_shop(const std::string &s);
    template <typename T>
    static void checking_prod_or_rec_in_shop(
        const std::vector<uint32_t> &request,
        const std::string &file_name,
        std::vector<T> &res, uint32_t size){
        std::ifstream file(file_name);
        json j = json::parse(file);
        file.close();

        std::multiset<search::set_unit<T>> top;
        for (auto const &x : j) {
            T cur_prod_or_rec(x);
            std::string temp_name = x["Name"];
            std::vector<uint32_t> second_str_codepoints;
            try {
                from_str_to_codepoint(temp_name, second_str_codepoints);
            } catch (const InvalidString &) {
                continue;
            }
            uint32_t in_amount = check_in(request, second_str_codepoints);
            uint32_t leven_dist = levenshtein_algo(request, second_str_codepoints);
            top.insert({in_amount, leven_dist, cur_prod_or_rec});

            if (top.size() > size) {
                auto it = top.end();
                it--;
                top.erase(it);
            }
        }

        for (const auto &su : top) {
            res.push_back(su.product_);
        }
    }

    static void stop_searching_ingredient();

    static void discard_basket();

    static void choose_ingredients(uint32_t num);
    static void run_product_search(std::string s,
                                   uint32_t size,
                                   std::vector<search::product> &top);

    static std::vector<search::product> show_res_of_request();
    static void run_recipes_search(
        const std::vector<search::product> &ingredients,
        uint32_t size,
        std::vector<search::Recipe> &vec);
    static std::vector<search::Recipe> show_recipes();
    friend void get_prod_top_by_name(std::string &input_string, std::vector<product> &vec,
                                     uint32_t size);

    friend void search::get_recipes(
        const std::vector<search::product> &ingredients,
        uint32_t size,
        std::vector<search::Recipe> &vec);

    friend void search::put_product_in_basket(
        std::vector<search::product> &basket,
        search::product &prod);
    // find

};

class recipe_to_ingredients {
    static std::vector<search::Recipe> recipes_request;
    static search::Recipe chosen_recipe;

public:
    static void run_recipe_search(const std::string &s,
                                  uint32_t size,
                                  std::vector<search::Recipe> &vec);
    static std::vector<search::Recipe> show_recipes();

    static void choose_recipe(uint32_t num);

    static void stop_searching_recipe();

    static void cancel_choice();

    friend void search_recipe(const std::string &input_string,
                                      uint32_t size,
                                      std::vector<search::Recipe> &vec);
};
void get_prod_top_by_name(std::string &input_string,
                          std::vector<product> &vec,
                          uint32_t size);
void search_recipe(const string &input_string,
                   uint32_t size,
                   std::vector<Recipe> &vec);

}  // namespace API

#endif  // MY_BASKET_SEARCH_ALGO_H