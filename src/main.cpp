#include <work_with_string.h>
#include <QApplication>
#include <QtGui>
#include <iostream>
#include "algo.h"
#include "for_static.h"
#include "search_engine.h"
#include "startwindow.h"
uint32_t check_in(
    std::vector<uint32_t> &first_str,  /// TODO change all to const
    std::vector<uint32_t> &second_str);

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::vector<uint32_t> first_str;
    from_str_to_codepoint(
        "Горошек Bonduellе Зеленый с морковкой в кубиках, 400г", first_str);
    std::vector<uint32_t> second_str;
    from_str_to_codepoint(
        "Горошек Stollenwerk зеленый молодой, 330г", second_str);

    std::vector<uint32_t> input_str;
    from_str_to_codepoint(
        "Горошек", input_str);
    auto f_amount = check_in(input_str, first_str);
    auto s_amount = check_in(input_str, second_str);

    auto t = API::recipe_to_ingredients::show_recipes();
    for (auto x : t) {
        std::cout << x.get_name() << "\n";
    }
    Ui::StartWindow start_window;
    start_window.show();

    return app.exec();
}