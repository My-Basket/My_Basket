#include <QApplication>
#include <QPushButton>
#include <work_with_string.h>
#include <iostream>
#include <search_engine.h>
#include <QtGui>
#include <recipebook.h>
std::multiset<search::set_unit, search::comp>search::ingredients_to_recipe::res_of_request;
std::vector<search::product> search::ingredients_to_recipe::chosen_ingredients;
std::vector<search::Recipe> search::ingredients_to_recipe::recommended_recipes;
std::vector<search::Recipe> search::recipe_to_ingredients::recipes_request;
search::Recipe search::recipe_to_ingredients::chosen_recipe;
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::string s = "Вода";
    search::get_prod_top_by_name(s, 10);
    for(auto t:search::ingredients_to_recipe::show_res_of_request()){
        std::cout<< t.product_;
    }
    RecipeBook recipebook;
    recipebook.show();
    return app.exec();

}