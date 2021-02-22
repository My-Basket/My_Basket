// Created by TurovV on 18.02.2021.

#ifndef MY_BASKET_SEARCH_ENGINE_H
#define MY_BASKET_SEARCH_ENGINE_H

#include <json.hpp>
#include <set>
#include <string>

namespace search {
using nlohmann::json;

class product {
    friend void get_prod_top_by_name(std::string &s, uint32_t size, std::vector<product> &ans);
private:
    std::string name;
    std::string category;
    uint32_t price{};

public:
    product(const json &j);
    product &operator=(const json &j);
    product(json &&j);
    product &operator=(json &&j);

    product(const product &d) = default;
    product &operator=(const product &d) = default;
    product(product &&d) = default;
    product &operator=(product &&d) = default;

    friend void from_json(json &j, product &p);

    friend std::ostream &operator<<(std::ostream &os, const product &p);

    ~product() = default;
};

class recipe {
private:
public:



};

void get_prod_top_by_name(std::string &s, uint32_t size, std::vector<product> &ans); //Searching products by name

//space for functions


}  // namespace search

#endif  // MY_BASKET_SEARCH_ENGINE_H
