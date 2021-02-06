#ifndef BUCKET_PROJECT_VIEW_H
#define BUCKET_PROJECT_VIEW_H
#include "algo.h"
class View{
private:
    ingredients_to_recipe scenario_1;
    recipe_to_ingredients scenario_2;
    View(ingredients_to_recipe scenario_1_ , recipe_to_ingredients scenario_2_);
    void show_basket() &;
    void show_recipes() &;
    void show_ingredients_of_recipe(int number) &;
};
#endif