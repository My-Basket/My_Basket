#include <recipebook.h>
#include <search_engine.h>
#include <work_with_string.h>
#include <QApplication>
#include <QPushButton>
#include <QtGui>
#include <iostream>
#include "algo.h"
std::multiset<search::set_unit, search::comp>
    functions::ingredients_to_recipe::res_of_request;
std::vector<search::product> functions::ingredients_to_recipe::chosen_ingredients;
std::vector<search::Recipe> functions::ingredients_to_recipe::recommended_recipes;
std::vector<search::Recipe> functions::recipe_to_ingredients::recipes_request;
search::Recipe functions::recipe_to_ingredients::chosen_recipe;
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::string s = "Вода";
    std::multiset<search::set_unit, search::comp> top;
    functions::ingredients_to_recipe::run_search(s, 10, top);
    for (const auto& t : functions::ingredients_to_recipe::show_res_of_request()) {
        std::cout << t.product_;
    }
    RecipeBook recipebook;
    recipebook.show();
    return app.exec();
}