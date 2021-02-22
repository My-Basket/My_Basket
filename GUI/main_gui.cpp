//
// Created by Евгения Федотова
//

#include "recipebook.h"

#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    RecipeBook recipebook;
    recipebook.show();
    return app.exec();
}
