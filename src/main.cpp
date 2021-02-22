#include <QApplication>
#include <QPushButton>
#include "work_with_string.h"
#include <iostream>
#include <search_engine.h>
#include <QtGui>
#include <recipebook.h>


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    std::string s = "Яблоки";
    std::vector<search::product> vec;
    search::get_prod_top_by_name(s, 10, vec);
    for(auto t: vec){
        std::cout<<t<<"\n";
    }
    RecipeBook recipebook;
    recipebook.show();
    return app.exec();

}