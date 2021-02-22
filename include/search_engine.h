// Created by TurovV on 18.02.2021.

#ifndef MY_BASKET_SEARCH_ENGINE_H
#define MY_BASKET_SEARCH_ENGINE_H

#include "json.hpp"
#include <set>
#include <string>

namespace search {
    using nlohmann::json;

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

        friend void from_json(json &j, product &p);
        friend void get_prod_top_by_name(std::string &input_string, uint32_t size, std::vector<product> &ans);
        friend std::ostream &operator<<(std::ostream &os, const product &p);

        ~product() = default;
    };

    void get_prod_top_by_name(std::string &input_string, uint32_t size, std::vector<product> &ans);
    class recipe{
        std::vector<search::product> ingredients;
        std::string name;
        //TODO кухня, регион приготовления, время приготовления, пошаговая инструкция с приготовлением (после MVP)
        bool is_ingredient_in_recipe(std::string &input_string, std::vector<product> &ans);

    };

}  // namespace search

#endif  // MY_BASKET_SEARCH_ENGINE_H
