#include <recipebook.h>
#include <search_engine.h>
#include <work_with_string.h>
#include <QApplication>
#include <QPushButton>
#include <QtGui>
#include <iostream>

//std::multiset<search::set_unit, search::comp>
//    search::ingredients_to_recipe::res_of_request;
//std::vector<search::product> search::ingredients_to_recipe::chosen_ingredients;
//std::vector<search::Recipe> search::ingredients_to_recipe::recommended_recipes;
//std::vector<search::Recipe> search::recipe_to_ingredients::recipes_request;
//search::Recipe search::recipe_to_ingredients::chosen_recipe;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::string s = "Вода";
    std::vector<search::product> vec;
    get_prod_top_by_name(s, 10, vec);
//    for (auto t : search::ingredients_to_recipe::show_res_of_request()) {
//        std::cout << t.product_;
//    }

    RecipeBook recipebook;
    recipebook.show();
    return app.exec();
}