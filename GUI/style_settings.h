#ifndef MY_BASKET_STYLE_SETTINGS_H
#define MY_BASKET_STYLE_SETTINGS_H

#include <string>

#define RUSSIAN_LANGUAGE

namespace StyleSettings {

///поставить define на языки -- ифать внутри структур, чему присваивать строки
struct Titles {
    inline static const std::string windows_title = "My_Basket";
    inline static const std::string path_to_bg_image =
        "../data/image_basket2.jpg";

    inline static const std::string category_economy = "economy";
    inline static const std::string category_base = "base";
    inline static const std::string category_premium = "premium";

#ifndef RUSSIAN_LANGUAGE
    // StartWindow
    inline static const std::string start_shopping_button_title =
        "start shopping!";
    inline static const std::string description_label_title =
        "your assistant in the selection of recipes";
    inline static const std::string choose_category_label_title =
        "Choose shops' category:";
    inline static const std::string economy_button_title = "economy";
    inline static const std::string base_button_title = "base";
    inline static const std::string premium_button_title = "premium";
    inline static const std::string go_to_searching_button = "go to searching!";

    // RecipeBook
    inline static const std::string product_name_label_title =
        "product or dish:";
    inline static const std::string recipe_label_product_title =
        "possible to take:";
    inline static const std::string recipe_label_recipe_title =
        "possible recipe:";
    inline static const std::string recipe_label_in_basket_title = "in basket:";
    inline static const std::string add_product_button_title = "add product";
    inline static const std::string add_recipe_button_title = "add recipe";
    inline static const std::string find_product_button_title = "find product";
    inline static const std::string put_in_basket_button_title =
        "put in basket";
    inline static const std::string find_recipe_button_title = "find recipe";
    inline static const std::string check_basket_button_title = "check basket";
    inline static const std::string choose_recipe_button_title =
        "choose recipe";
    inline static const std::string next_button_title = "next";
    inline static const std::string previous_button_title = "previous";

    //окна предупреждений
    inline static const std::string empty_input_window_title = "Empty input";
    inline static const std::string empty_input_window_text =
        "Please enter a product";
    inline static const std::string empty_basket_window_title = "Empty basket";
    inline static const std::string empty_basket_window_text =
        "Please add at least one product in the basket";

    // SummaryWindow
    inline static const std::string start_again_button_title = "start again";
    inline static const std::string show_final_products_button_title =
        "show products";
    inline static const std::string show_check_button_title =
        "show grocery receipt";
    inline static const std::string end_program_button_title = "end program";
    inline static const std::string best_total_cost_label_title =
        "best total cost:";
    inline static const std::string in_shop_label_title = "in shop:";
    inline static const std::string shop_list_title = "Shop list:";
#else
    // StartWindow
    inline static const std::string start_shopping_button_title =
        "начать заполнять корзину!";
    inline static const std::string description_label_title =
        "ваш помощник в выборе рецептов";
    inline static const std::string choose_category_label_title =
        "Категория магазина:";
    inline static const std::string economy_button_title = "эконом";
    inline static const std::string base_button_title = "стандарт";
    inline static const std::string premium_button_title = "премиум";
    inline static const std::string go_to_searching_button =
        "приступить к поиску!";

    // RecipeBook
    inline static const std::string product_name_label_title =
        "продукт или блюдо:";
    inline static const std::string recipe_label_product_title = "можно взять:";
    inline static const std::string recipe_label_recipe_title =
        "предлагаемый рецепт:";
    inline static const std::string recipe_label_in_basket_title = "в корзине:";
    inline static const std::string add_product_button_title =
        "добавить продукт";
    inline static const std::string add_recipe_button_title = "добавить рецепт";
    inline static const std::string find_product_button_title = "найти продукт";
    inline static const std::string put_in_basket_button_title =
        "положить в корзину";
    inline static const std::string find_recipe_button_title = "найти рецепт";
    inline static const std::string check_basket_button_title =
        "просмотр корзины";
    inline static const std::string choose_recipe_button_title =
        "выбрать рецепт";
    inline static const std::string next_button_title = "вперед";
    inline static const std::string previous_button_title = "назад";

    //окна предупреждений
    inline static const std::string empty_input_window_title = "Empty input";
    inline static const std::string empty_input_window_text =
        "Пожалуйста, введите название продукта";
    inline static const std::string empty_basket_window_title = "Empty basket";
    inline static const std::string empty_basket_window_text =
        "Пожалуйста, добавьте хотя бы один товар в корзину";

    // SummaryWindow
    inline static const std::string start_again_button_title =
        "начать с начала";
    inline static const std::string show_final_products_button_title =
        "просмотр товаров";
    inline static const std::string show_check_button_title = "показ чека";
    inline static const std::string end_program_button_title =
        "завершить программу";
    inline static const std::string best_total_cost_label_title = "Лучший чек:";
    inline static const std::string in_shop_label_title = "в магазине:";
    inline static const std::string shop_list_title = "Список покупок:";
#endif
};

struct Colors {
    inline static const std::string pink_light_button = "#FF9899";
    inline static const std::string pink_medium_button = "#FF7699";
    inline static const std::string pink_hard_button = "#FF1099";
    inline static const std::string green_label = "#359530";
    inline static const std::string green_button = "#00CC66";
    inline static const std::string blue_light_button = "#0066CC";
    inline static const std::string blue_hard_button = "#172030";
    inline static const std::string black = "black";
    inline static const std::string white = "white";
};

struct FontSizes {
    inline static const int my_basket_label_fz = 130;
    inline static const int description_label_fz = 27;

    // StartWindow
    inline static const int start_shopping_button_fz = 30;

    // CategoryWindow
    inline static const int category_window_buttons_fz = 20;

    // SummaryWindow
    inline static const int summary_window_products_text_sz = 18;

    // RecipeBook
    inline static const int recipe_text_sz = 18;
    inline static const int top_products_count = 10;
};

struct FontStyles {
    inline static const std::string bold = "bold";
};

struct WindowSizes {
    inline static const int min_width_window = 1000;
    inline static const int min_height_window = 650;

    // StartWindow
    inline static const int start_window_layout_spacing = 5;
    inline static const int my_basket_label_margin = 50;
    inline static const int choose_category_label_margin = 55;

    // CategoryWindow
    inline static const int cw_main_layout_spacing = 10;

    // SummaryWindow
    inline static const int summary_window_margin = 10;
    inline static const int sw_main_layout_spacing = 15;
    inline static const int sw_label_layout_spacing = 10;
    inline static const int product_text_width = 600;
    inline static const int product_text_height = 400;

    // RecipeBook
    inline static const int product_name_line_min_height = 30;
};

struct Enable {
    bool enabled = true;
    bool unenabled = false;
};

struct ButtonSetting {};
struct ButtonsSettings {};
}  // namespace StyleSettings

#endif  // MY_BASKET_STYLE_SETTINGS_H
