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

class SummaryWindow : public QWidget {
    Q_OBJECT

public:
    SummaryWindow(QWidget *parent = nullptr);

public slots:
    void show_final_products_func();
    void show_check_func();
    void start_again_func();
    static void end_program_func();

private:
    QPushButton *show_final_products_button;
    QPushButton *show_check_button;
    QPushButton *start_again_button;
    QPushButton *end_program_button;

    QLabel *best_total_cost_label;
    QLabel *total_cost_number_label;
    QLabel *in_shop_label;
    QLabel *shop_name_label;

    QTextEdit *products_text;

    int total_cost = 1000;
    std::string shop_name = "EuroSpar";
    std::vector<std::pair<std::string, uint32_t>> products_vec;
};

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

    //завершающее окно
    SummaryWindow *summary_window;  ///мб не надо хранить его в качестве поля??

    NextPrevMode current_mode;
    FindRecipeMode find_recipe_mode;
    long long num_current_object = 0;
    std::string category;

    void clear_fields();
    void clear_fields_and_requests();
    void activate_search_bar();
    void text_field_find_regime(std::string const &s);

    ///что это за функция? она вроде нигде не используется
    friend void search::put_product_in_basket(
        std::vector<search::product> &basket,
        search::product &prod);
};
}  // namespace Ui

#endif  // RECIPEBOOK_H