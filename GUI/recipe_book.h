#ifndef RECIPEBOOK_H
#define RECIPEBOOK_H

#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include "search_engine.h"

namespace Ui {

class RecipeBook : public QWidget {
    Q_OBJECT

public:
    RecipeBook(QWidget *parent = nullptr);

    enum NextPrevMode { FindProduct_mode, FindRecipe_mode };
    enum FindRecipeMode { BasketSearchingMode, NameSearchingMode };

public slots:
    void add_product_func();
    void add_recipe_func();
    void find_product_func();
    void put_in_basket_func();
    void find_recipe_func();
    void check_basket_func();
    void choose_recipe_func();

    void next_func();
    void previous_func();

private:
    QLineEdit *product_name_line;
    QLabel *product_name_label;
    QTextEdit *recipe_text;
    QLabel *recipe_label;

    //кнопки правой панели
    QPushButton *add_product_button;
    QPushButton *add_recipe_button;
    QPushButton *find_product_button;
    QPushButton *put_in_basket_button;
    QPushButton *find_recipe_button;
    QPushButton *choose_recipe_button;
    QPushButton *check_basket_button;

    //кнопки нижней панели
    QPushButton *next_button;
    QPushButton *previous_button;

    //структуры для хранения информации
    std::vector<search::product> basket_of_products;
    std::vector<search::product> res_of_request_products;
    std::vector<search::Recipe> res_of_request_recipes;

    NextPrevMode current_mode;
    FindRecipeMode find_recipe_mode;
    long long num_current_object = 0;

    void clear_fields();
    void clear_fields_and_requests();
    void activate_search_bar();
    void text_field_find_regime(std::string const &s);

    void button_enabled(QPushButton *button, bool is_enabled);

    void update_buttons_enabled(bool add_product_button_enabled = true,
                                bool add_recipe_button_enabled = true,
                                bool find_product_button_enabled = true,
                                bool put_in_basket_button_enabled = true,
                                bool find_recipe_button_enabled = true,
                                bool choose_recipe_button_enabled = true,
                                bool check_basket_button_enabled = true);

    void update_buttons_showed(bool add_product_button_showed = true,
                               bool add_recipe_button_showed = true,
                               bool find_product_button_showed = true,
                               bool put_in_basket_button_showed = true,
                               bool find_recipe_button_showed = true,
                               bool choose_recipe_button_showed = true,
                               bool check_basket_button_showed = true,
                               bool next_button_showed = true,
                               bool previous_button_showed = true);
};
}  // namespace Ui

#endif  // RECIPEBOOK_H