#ifndef MY_BASKET_STYLE_SETTINGS_H
#define MY_BASKET_STYLE_SETTINGS_H

#include <string>

namespace StyleSettings {

///поставить define на языки -- ифать внутри структур, чему присваивать строки
struct Titles {
    inline static const std::string windows_title = "My_Basket";
    inline static const std::string path_to_bg_image =
        "../data/image_basket2.jpg";
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
};

struct Colors {
    inline static const std::string pink_light_button = "";
    inline static const std::string pink_medium_button = "";
    inline static const std::string pink_hard_button = "";
    inline static const std::string green_label = "";
    inline static const std::string green_button = "";
    inline static const std::string blue_light_button = "";
    inline static const std::string blue_hard_button = "";
    inline static const std::string black = "black";
};

struct FontSizes {
    inline static const int my_basket_label_fz = 130;
    inline static const int description_label_fz = 27;
    inline static const int start_shopping_button_fz = 30;
    inline static const int category_window_buttons_fz = 20;
};

struct FontStyles {
    inline static const std::string bold = "bold";
};

struct WindowSizes {
    inline static const int min_width_window = 1000;
    inline static const int min_height_window = 600;
    inline static const int start_window_layout_spacing = 5;
    inline static const int my_basket_label_margin = 50;
};

struct Enable {
    bool enabled = true;
    bool unenabled = false;
};

struct ButtonsSettings {};
} //namespace StyleSettings

#endif  // MY_BASKET_STYLE_SETTINGS_H
