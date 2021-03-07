// You may need to build the project (run Qt uic code generator) to get
// "ui_RecipeBook.h" resolved -- запускается и без этого

#include "recipebook.h"
#include "algo.h"
//#include "ui_RecipeBook.h"

#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>

RecipeBook::RecipeBook(QWidget *parent) : QWidget(parent) {
    QLabel *product_name_label = new QLabel(tr("product or dish:"));
    product_name_line = new QLineEdit;
    product_name_line->setReadOnly(
        true);  //установили поле только для чтения, можем только отображать,
    //но не редактировать детали имеющихся продуктов и рецептов

    QLabel *recipe_label = new QLabel(tr("recipe:"));
    recipe_text = new QTextEdit;
    recipe_text->setReadOnly(true);

    //экземпляры кнопок правой панели
    add_product_button = new QPushButton(tr("&add product"));
    add_product_button->show();

    find_product_button = new QPushButton(tr("&find product"));
    find_product_button->hide();

    put_in_basket_button = new QPushButton(tr("&put in basket"));
    put_in_basket_button->hide();

    find_recipe_button = new QPushButton(tr("&find recipe"));
    find_recipe_button->hide();  //кнопка скрыта. будет отображена только после
    //того, как пользователь
    //нажмет кнопку "add product"

    check_basket_button = new QPushButton(tr("&check basket"));
    check_basket_button->show();

    //экземпляры кнопок нижней панели
    next_recipe_button = new QPushButton(tr("&next recipe"));
    next_recipe_button->hide();

    previous_recipe_button = new QPushButton(tr("&previous recipe"));
    previous_recipe_button->hide();

    // TODO: можно ли избавиться от копипаста и вынести это в функцию с
    // параметрами (название кнопки (1), ф-я(4))
    connect(add_product_button, SIGNAL(clicked()), this,
            SLOT(add_product_func()));
    connect(find_product_button, SIGNAL(clicked()), this,
            SLOT(find_product_func()));
    connect(put_in_basket_button, SIGNAL(clicked()), this,
            SLOT(put_in_basket_func()));
    connect(find_recipe_button, SIGNAL(clicked()), this,
            SLOT(find_recipe_func()));
    connect(check_basket_button, SIGNAL(clicked()), this,
            SLOT(check_basket_func()));
    connect(next_recipe_button, SIGNAL(clicked()), this,
            SLOT(next_recipe_func()));
    connect(previous_recipe_button, SIGNAL(clicked()), this,
            SLOT(previous_recipe_func()));

    //размещение кнопок - правая часть виджета, вертикальный столбец
    QVBoxLayout *button_layout1 = new QVBoxLayout;
    button_layout1->addWidget(add_product_button, Qt::AlignTop);
    button_layout1->addWidget(find_product_button);
    button_layout1->addWidget(put_in_basket_button);
    button_layout1->addWidget(find_recipe_button);
    button_layout1->addWidget(check_basket_button);
    button_layout1
        ->addStretch();  //разместить кнопки ближе к верхней части экрана

    //размещение кнопок - нижняя часть виджета
    QHBoxLayout *button_layout2 = new QHBoxLayout;
    button_layout2->addWidget(previous_recipe_button);
    button_layout2->addWidget(next_recipe_button);

    //основной макет с поисковой строкой, полем вывода, названиями полей
    QGridLayout *main_layout = new QGridLayout;
    main_layout->addWidget(product_name_label, 0, 0);
    main_layout->addWidget(product_name_line, 0, 1);
    main_layout->addWidget(recipe_label, 1, 0, Qt::AlignTop);
    main_layout->addWidget(recipe_text, 1, 1);
    main_layout->addLayout(button_layout1, 1, 2);  //вложенная компоновка:
    //добавили button_layout1 (теперь дочерний) к main_layout
    main_layout->addLayout(button_layout2, 3, 1);

    setLayout(main_layout);
    setWindowTitle(tr("My_Basket"));
}

void RecipeBook::add_product_func() {
    //перед добавлением нового продукта, сохранение информации о старом
    if (product_name_line->text() != "") {
        old_product = product_name_line->text();
        old_recipe = recipe_text->toPlainText();
    }

    //очищение полей ввода и показа рецепта
    product_name_line->clear();
    recipe_text->clear();

    //отключение режима "только для чтения"
    product_name_line->setReadOnly(false);
    product_name_line->setFocus(
        Qt::OtherFocusReason);  //установка фокуса ввода на product_name_line
    recipe_text->setReadOnly(false);

    add_product_button->setEnabled(false);
    find_product_button->show();
    find_product_button->setEnabled(true);
    put_in_basket_button->show();
    find_recipe_button->show();
}

void RecipeBook::find_product_func() {
    if (product_name_line->text() == "") {
        QMessageBox::information(this, tr("Empty input"),
                                 tr("Please enter a product"));
        return;
    }

    product_name_line->setReadOnly(true);
    find_product_button->setEnabled(false);
    add_product_button->setEnabled(true);

    //    previous_recipe_button->show();
    //    previous_recipe_button->setEnabled(true);
    //    next_recipe_button->show();
    //    previous_recipe_button->setEnabled(true);
    ///либо делать кнопки, и ходить по продуктам по ним
    ///либо вывести в поле recipe_text сразу столбец продуктов и в нем научиться
    ///щелкать по одному продукту

    //вывести на экран список топ 10 найденных продуктов:
    // TODO мб менять название поля recipe_text
    recipe_text->clear();
    ///надо ли здесь запустить какую-то ф-цию для поиска?
    std::vector<search::product> res_of_request =
        functions::ingredients_to_recipe::show_res_of_request();
    for (auto &prod : res_of_request) {
        QString res_product = QString::fromUtf8(get_product_name(prod).c_str());
        recipe_text->insertPlainText(static_cast<const QString>(res_product));
        recipe_text->insertPlainText("\n");
    }
}

void RecipeBook::put_in_basket_func() {
    old_product = product_name_line->text();
    old_recipe = recipe_text->toPlainText();

    search::put_product_in_basket(
        old_product.toStdString());  //добавление продукта в корзину

    product_name_line->clear();
    recipe_text->clear();

    product_name_line->setReadOnly(true);
    recipe_text->setReadOnly(true);
    add_product_button->setEnabled(true);
    find_product_button->hide();
    put_in_basket_button->hide();
}

void RecipeBook::find_recipe_func() {
    // QString basket_grocery_list = извлечь из корзины строку с продуктами
    // if (basket_grocery_list == ""){
    //  QMessageBox::information(this,
    //                  tr("empty grocery list from basket"), tr("please add at
    //                  least one product"));
    //} else
    //  вовина ф-я поиска рецептов по продуктам (product_list);

    // TODO: в полной реализации, если пользователь ничего не добавил в корзину,
    //выводить на экран список топовых рецептов

    product_name_line->setReadOnly(true);
    recipe_text->setReadOnly(true);
    add_product_button->setEnabled(true);  //кнопка нажата
    put_in_basket_button->hide();
    find_recipe_button->hide();

    previous_recipe_button->show();
    next_recipe_button->show();
    find_recipe_button->setEnabled(true);

    //run_recipe_search -- но с какими параметрами? мне хочется просто вызывать поиск, а не передавать ему какие-то аргументы
//    recipe_text->setText(QString::fromUtf8(
//        (search::get_recipe_name(
//             functions::recipe_to_ingredients::show_recipes()[0]))
//            .c_str()));
}

void RecipeBook::check_basket_func() {
    product_name_line->clear();
    put_in_basket_button->hide();
    add_product_button->setEnabled(true);
    //вывести список продуктов корзины на экран -- отдельным окном
}

void RecipeBook::previous_recipe_func() {
    //циклический список рецептов
    QString current_dish = product_name_line->text();
    QMap<QString, QString>::iterator it = map_recipes.find(current_dish);

    if (it == map_recipes.begin()) {
        it = map_recipes.end();
    } else {
        it--;
    }

    product_name_line->setText(it.key());  //название предущего блюда
    recipe_text->setText(it.value());
}

void RecipeBook::next_recipe_func() {
    //циклический список рецептов
    //здесь надо как-то поддерживать указатель на текущий рецепт, чтобы не проходиться по всему массиву заново
    //how to do it
    QString current_dish = product_name_line->text();
    QMap<QString, QString>::iterator it = map_recipes.find(current_dish);

    if (it == map_recipes.end()) {
        it = map_recipes.begin();
    } else {
        it++;
    }

    product_name_line->setText(it.key());  //название следующего блюда
    recipe_text->setText(it.value());
}
