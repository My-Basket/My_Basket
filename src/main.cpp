#include <QApplication>
#include <QtGui>
#include <iostream>
#include "algo.h"
#include "for_static.h"
#include "recipebook.h"
#include "search_engine.h"
#include "startwindow.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::string s = "Вода";
    std::vector<search::product> vec;
    functions::ingredients_to_recipe::run_product_search(s, 10, vec);
    auto top_product = functions::ingredients_to_recipe::show_res_of_request();
    for (const auto &t : top_product) {
        std::cout << t;
    }
    std::vector<search::Recipe> vec2;
    functions::ingredients_to_recipe::run_recipes_search(top_product, 10, vec2);
    auto top_recipes = functions::ingredients_to_recipe::show_recipes();
    for (const auto &t : top_recipes) {
        // std::cout <<t;
    }

    // RecipeBook recipebook;
    // recipebook.show();

    StartWindow start_window;
    start_window.show();
    return app.exec();
}