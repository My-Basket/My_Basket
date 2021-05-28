#ifndef MY_BASKET_ADDITIONAL_WINDOWS_H
#define MY_BASKET_ADDITIONAL_WINDOWS_H

#include "recipe_book.h"

namespace Ui {

class CategoryWindow;

class StartWindow : public QWidget {
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr);

public slots:
    void go_to_category_window();

private:
    //кнопки окна
    QPushButton *start_shopping_button;
    QLabel *my_basket_label;
    QLabel *description_label;
};

class CategoryWindow : public QWidget {
    Q_OBJECT

public:
    CategoryWindow(QWidget *parent = nullptr);

public slots:
    void go_to_recipe_book();
    void choose_economy();
    void choose_base();
    void choose_premium();

private:
    QPushButton *economy_button;
    QPushButton *base_button;
    QPushButton *premium_button;
    QPushButton *go_to_searching_button;
    QLabel *choose_category_label;

    std::string chosen_category;
};

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

void set_font_color_button(QPushButton *button,
                           std::string const &bg_color,
                           int font_size = 20,
                           int enabled = -1,
                           std::string const &font = "");

void set_font_color_label(QLabel *label,
                          std::string const &word_color = "black",
                          int font_size = 130,
                          std::string const &font = "",
                          std::string const &bg_color = "");
}  // namespace Ui

#endif  // MY_BASKET_ADDITIONAL_WINDOWS_H