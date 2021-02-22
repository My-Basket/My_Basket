#include <QApplication>
#include <QPushButton>
#include "work_with_string.h"
#include <iostream>
#include <search_engine.h>

int min(int a, int b){
    return (a<b)? a : b;
}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(100, 200);
    button.show();

    std::string s = "Яблоки";
    std::vector<search::product> vec;
    search::get_prod_top_by_name(s,10, vec);

    return QApplication::exec();

}