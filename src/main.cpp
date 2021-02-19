#include <QApplication>
#include <QPushButton>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <vector>
#include "../include/search_engine.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();

    nlohmann::json j;
    std::vector<search::product> vec;
    std::string s = "Коктейль";
    search::get_prod_top_by_name(s, 5, vec);

    return QApplication::exec();
}
