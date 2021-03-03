// Created by TurovV on 18.02.2021.

#ifndef MY_BASKET_SEARCH_ENGINE_H
#define MY_BASKET_SEARCH_ENGINE_H

#include "json.hpp"
#include <set>
#include <string>
#include <list>

namespace search {

    using nlohmann::json, std::vector, std::tuple, std::string, std::pair, std::tuple, std::set, std::list, std::multiset;

    class product {
    private:
        std::string name;
        std::string category;
        uint32_t price{};

    public:
        explicit product(const json &j);

        product &operator=(const json &j);

        explicit product(json &&j);

        product &operator=(json &&j);

        product(const product &d) = default;

        product &operator=(const product &d) = default;

        product(product &&d) = default;

        product &operator=(product &&d) = default;

        friend void from_json(json &j, product &p); //А нужна ли?
        friend void get_prod_top_by_name(std::string &input_string, uint32_t size);

        friend std::ostream &operator<<(std::ostream &os, const product &p);

        ~product() = default;
    };

    struct set_unit {
        search::product product_;
        uint32_t in_amount;
        uint32_t leven_dist;
    };

    struct comp {
        bool operator()(const set_unit &a, const set_unit &b) const {
            if (a.in_amount != b.in_amount) {
                return a.in_amount > b.in_amount;
            } else {
                return a.leven_dist < b.leven_dist;
            }
        }
    };

    class Recipe {
        std::vector<search::product> ingredients;
        std::string name;
        //TODO кухня, регион приготовления, время приготовления, пошаговая инструкция с приготовлением (после MVP)
    public:
//TODO
        explicit Recipe(const json &j);

        Recipe &operator=(const json &j);

        explicit Recipe(json &&j);

        Recipe &operator=(json &&j);

        Recipe() = default;

        Recipe(const Recipe &recipe) = default;

        Recipe &operator=(const Recipe &recipe) = default;

        Recipe(Recipe &&recipe) = default;

        Recipe &operator=(Recipe &&recipe) = default;

        ~Recipe() = default;

        void clear();
//TODO
        bool is_ingredient_in_recipe(const product &ingredient); //проверка на наличие ингредиента в рецепте

        friend void get_recipes(const std::vector<product> &ingredients, uint32_t size);
        //получает на вход продукты, сует в recommended recipes класса ingredients_to_recipes топ 10 лучших рецептов

        friend void search_recipe(const string &input_string, uint32_t size);
        //ищет рецепт по введённой строке, сует в recipes_request класса recipes_to_ingredients топ 10 лучших рецептов
        friend std::ostream &operator<<(std::ostream &os, const Recipe &p);
    };

    class ingredients_to_recipe {
    private:
        static multiset<set_unit, comp> res_of_request;
        static vector<product> chosen_ingredients;
        static vector<Recipe> recommended_recipes;
        // TODO static list<product> chosen_bad_ingredients;
        //TODO static multiset<set_unit, comp> bad_ingredients;
        // TODO vector<string> popular_ingredients;
    public:
        static void stop_searching_ingredient();

        static void discard_basket();

        static void choose_ingredients(uint32_t num);

        static multiset<set_unit, comp> show_res_of_request();

        friend void get_prod_top_by_name(std::string &input_string, uint32_t size);

        friend void get_recipes(const std::vector<product> &ingredients, uint32_t size);
    };

    class recipe_to_ingredients {
        static vector<Recipe> recipes_request;
        static Recipe chosen_recipe;
    public:
        static vector<Recipe> show_recipes();

        static void choose_recipe(uint32_t num);

        static void stop_searching_recipe();

        static void cancel_choice();

        friend void search_recipe(const string &input_string, uint32_t size);

    };

    void get_prod_top_by_name(std::string &input_string, uint32_t size);

    void search_recipe(const string &input_string, uint32_t size);

    void get_recipes(const std::vector<product> &ingredients, uint32_t size);

}  // namespace search

#endif  // MY_BASKET_SEARCH_ENGINE_H
