//
// Created by vladi on 18.02.2021.
//

#include "search_engine.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include "work_with_string.h"

namespace {


    void relax(uint32_t &a, uint32_t b) {
        if (a > b) {
            a = b;
        }
    }

    uint32_t levenshtein_algo(std::vector<uint32_t> &first_str, std::vector<uint32_t> &second_str) {
        std::vector<std::vector<uint32_t>> f(
                first_str.size(), std::vector<uint32_t>(second_str.size(), 0));

        for (int i = 0; i < first_str.size(); i++) {
            for (int j = 0; j < second_str.size(); j++) {

                if (i == 0 || j == 0) {
                    f[i][j] = std::max(i, j);
                    continue;
                }

                int w = first_str[i] == second_str[j] ? 0 : 1;

                f[i][j] = f[i - 1][j] + 1;
                relax(f[i][j], f[i][j - 1] + 1);
                relax(f[i][j], f[i - 1][j - 1] + w);
            }
        }
        return f[first_str.size() - 1][second_str.size() - 1];
    }

    uint32_t check_in(std::vector<uint32_t> &first_str, std::vector<uint32_t> &second_str) {

        if (first_str.size() > second_str.size()) {
            return 0;
        }

        uint32_t max_amount = 0;
        for (int i = 1; i < second_str.size() - first_str.size(); i++) {
            uint32_t count = 0;
            for (int j = i; j < i + first_str.size() - 1; j++) {
                if (first_str[j - i + 1] == second_str[j]) {
                    count++;
                }
            }
            if (count > max_amount) {
                max_amount = count;
            }
        }

        return max_amount;
    }

}  // namespace

namespace search {

    void from_json(json &j, product &p) {
        j.at("Name").get_to(p.name);
        j.at("Category").get_to(p.category);
        j.at("Price").get_to(p.price);
    }

    std::ostream &operator<<(std::ostream &os, const product &p) {
        os << "{\n"
           << "   "
           << "Name: " << p.name << '\n'
           << "   "
           << "Category: " << p.category << '\n'
           << "   "
           << "Price: " << p.price << '\n'
           << "}\n";
        return os;
    }


    void get_prod_top_by_name(std::string &input_string, uint32_t size) {
        std::ifstream file("../data/av.json");
        json j = json::parse(file);
        file.close();

        std::vector<uint32_t> first_str_codepoints;
        from_str_to_codepoint(input_string, first_str_codepoints);

        for (auto const &x : j) {
            product cur_prod(x);
            auto temp_name = cur_prod.name;

            std::vector<uint32_t> second_str_codepoints;
            from_str_to_codepoint(cur_prod.name, second_str_codepoints);

            uint32_t in_amount = check_in(first_str_codepoints, second_str_codepoints);
            uint32_t leven_dist = levenshtein_algo(first_str_codepoints, second_str_codepoints);

            ingredients_to_recipe::res_of_request.insert({cur_prod, in_amount, leven_dist});

            if (ingredients_to_recipe::res_of_request.size() > size) {
                auto it = ingredients_to_recipe::res_of_request.end();
                it--;
                ingredients_to_recipe::res_of_request.erase(it);
            }

        }

    }

    product::product(const json &j) {
        *this = j;
    }

    product &product::operator=(const json &j) {
        try {
            name = j["Name"];
            category = j["Category"];
            price = j["Price"];
            return *this;
        } catch (...) {
            assert((false, "Invalid cast from json to product"));
        }
    }

    product::product(json &&j) {
        *this = j;
    }

    product &product::operator=(json &&j) {
        *this = j;
        return *this;
    }
    void Recipe::clear() {
        ingredients.clear();
        name ="";
    }



    multiset<set_unit, comp> ingredients_to_recipe::show_res_of_request(){
        return res_of_request;
    }

    void ingredients_to_recipe::choose_ingredients(uint32_t num) {

        auto it = res_of_request.begin();
        for (size_t i = 0; i < num; i++) {
            it++;
        }
        chosen_ingredients.push_back(it->product_);

    }
    void ingredients_to_recipe::discard_basket() {
        chosen_ingredients.clear();
    }
    void ingredients_to_recipe::stop_searching_ingredient() {
        res_of_request.clear();
    }
    vector<Recipe> recipe_to_ingredients::show_recipes() {
        return recipes_request;
    }
    void recipe_to_ingredients::cancel_choice() {
        chosen_recipe.clear();
    }
    void recipe_to_ingredients::stop_searching_recipe() {
        recipes_request.clear();
    }
    void recipe_to_ingredients::choose_recipe(uint32_t num) {
        chosen_recipe = recipes_request[num];
    }

}  // namespace search
