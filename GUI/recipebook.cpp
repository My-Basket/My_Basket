// You may need to build the project (run Qt uic code generator) to get
// "ui_RecipeBook.h" resolved -- запускается и без этого

#include "recipebook.h"
#include <QSizePolicy>
#include "algo.h"
//#include "ui_RecipeBook.h"

#include <QGridLayout>
#include <QMessageBox>
#include <sstream>

RecipeBook::RecipeBook(QWidget *parent) : QWidget(parent) {
    product_name_label = new QLabel(tr("product or dish:"));
    product_name_label->setStyleSheet(
        "QLabel { background-color : #359530; color : white; border-width: "
        "2px; border-radius: 10px; padding: 6px;}");
    product_name_label->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    product_name_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                                      QSizePolicy::Expanding);
    product_name_line = new QLineEdit;
    product_name_line->setReadOnly(true);

    recipe_label = new QLabel(tr("possible to take:"));
    recipe_label->setStyleSheet(
        "QLabel { background-color : #359530; color : white; border-width: "
        "2px; border-radius: 10px; padding: 6px;}");
    recipe_label->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    recipe_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                                QSizePolicy::Expanding);
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
    find_recipe_button->hide();

    check_basket_button = new QPushButton(tr("&check basket"));
    check_basket_button->show();

    //экземпляры кнопок нижней панели
    next_button = new QPushButton(tr("&next"));
    next_button->hide();

    previous_button = new QPushButton(tr("&previous"));
    previous_button->hide();

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
    connect(next_button, SIGNAL(clicked()), this, SLOT(next_func()));
    connect(previous_button, SIGNAL(clicked()), this, SLOT(previous_func()));

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
    button_layout2->addWidget(previous_button);
    button_layout2->addWidget(next_button);

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
    //очищение полей ввода
    product_name_line->clear();
    recipe_text->clear();
    res_of_request_products.clear();
    res_of_request_recipes.clear();

    //отключение режима "только для чтения"
    product_name_line->setReadOnly(false);
    product_name_line->setFocus(
        Qt::OtherFocusReason);  //установка фокуса ввода на product_name_line
    recipe_text->setReadOnly(false);

    add_product_button->setEnabled(false);
    find_product_button->show();
    find_product_button->setEnabled(true);
    put_in_basket_button->hide();
    find_recipe_button->show();
    next_button->hide();
    previous_button->hide();
    recipe_label->setText("possible to take:");
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

    put_in_basket_button->show();
    previous_button->show();
    previous_button->setEnabled(true);
    next_button->show();
    previous_button->setEnabled(true);

    current_mode = FindProduct_mode;

    recipe_label->setText("possible to take:");

    recipe_text->clear();

    //запуск поиска
    res_of_request_products.clear();
    functions::ingredients_to_recipe::run_product_search(
        product_name_line->text().toStdString(), 10, res_of_request_products);
    res_of_request_products =
        functions::ingredients_to_recipe::show_res_of_request();

    //    for (auto &prod : res_of_request) {
    //        QString res_product =
    //        QString::fromUtf8(get_product_name(prod).c_str());
    //        recipe_text->insertPlainText(static_cast<const
    //        QString>(res_product)); recipe_text->insertPlainText("\n");
    //    }
    //    QString res_product =
    //    QString::fromUtf8(get_product_name(res_of_request[0]).c_str());
    //    recipe_text->insertPlainText(static_cast<const QString>(res_product));
    //    num_current_object = 0;

    std::stringstream ss;
    ss << res_of_request_products[0];
    std::string s;
    while (ss >> s) {
        recipe_text->insertPlainText(QString::fromUtf8(s.c_str()));
        recipe_text->insertPlainText("\n");
    }
    num_current_object = 0;
    /// TODO: сделать нормальный вывод в текстовое поле
}

void RecipeBook::put_in_basket_func() {
    //добавление продукта в корзину по его номеру в массиве
    // res_of_request_products
    if (res_of_request_products.empty()) {
        return;
    }
    search::put_product_in_basket(basket_of_products,
                                  res_of_request_products[num_current_object]);

    product_name_line->clear();
    recipe_text->clear();

    product_name_line->setReadOnly(true);
    recipe_text->setReadOnly(true);
    add_product_button->setEnabled(true);
    find_product_button->hide();
    put_in_basket_button->hide();
    next_button->hide();
    previous_button->hide();

    res_of_request_products.clear();
}

void RecipeBook::find_recipe_func() {
    // TODO: в полной реализации: если пользователь ничего не добавил в корзину
    //выводить на экран список топовых рецептов

    if (basket_of_products.empty()) {
        res_of_request_products.clear();
        res_of_request_recipes.clear();
        QMessageBox::warning(
            this, tr("Empty basket"),
            tr("Please add at least one product in the basket"));
        return;
    }

    product_name_line->setReadOnly(true);
    recipe_text->setReadOnly(true);
    add_product_button->setEnabled(true);  //кнопка нажата
    put_in_basket_button->hide();
    find_recipe_button->hide();

    previous_button->show();
    previous_button->setEnabled(true);
    next_button->show();
    next_button->setEnabled(true);
    find_recipe_button->setEnabled(true);

    current_mode = FindRecipe_mode;

    recipe_label->setText("possible recipe:");
    recipe_text->clear();

    res_of_request_recipes.clear();
    std::vector<search::Recipe> vec2;
    functions::ingredients_to_recipe::run_recipes_search(basket_of_products, 10,
                                                         vec2);
    res_of_request_recipes = functions::ingredients_to_recipe::show_recipes();

    std::stringstream ss;
    ss << res_of_request_recipes[0];
    std::string s;
    while (ss >> s) {
        recipe_text->insertPlainText(QString::fromUtf8(s.c_str()));
        recipe_text->insertPlainText("\n");
    }
    num_current_object = 0;
}

void RecipeBook::check_basket_func() {
    product_name_line->clear();
    recipe_text->clear();
    put_in_basket_button->hide();
    add_product_button->setEnabled(true);

    recipe_label->setText("in basket:");

    //вывести список продуктов корзины на экран
    //мб отдельным окном
    for (auto &prod : basket_of_products) {
        QString res_product = QString::fromUtf8(get_product_name(prod).c_str());
        recipe_text->insertPlainText(static_cast<const QString>(res_product));
        recipe_text->insertPlainText("\n");
    }
}

void RecipeBook::previous_func() {
    num_current_object--;
    if (current_mode == FindProduct_mode) {
        //циклический список продуктов
        if (num_current_object < 0) {
            num_current_object = res_of_request_products.size() - 1;
        }
        search::product prod = res_of_request_products[num_current_object];
        recipe_text->setText(QString::fromUtf8(get_product_name(prod).c_str()));
    } else if (current_mode == FindRecipe_mode) {
        //циклический список рецептов
        if (num_current_object < 0) {
            num_current_object = res_of_request_recipes.size() - 1;
        }
        search::Recipe recipe = res_of_request_recipes[num_current_object];
        recipe_text->setText(
            QString::fromUtf8(get_recipe_name(recipe).c_str()));
    }
}

void RecipeBook::next_func() {
    num_current_object++;
    if (current_mode == FindProduct_mode) {
        //циклический список продуктов
        if (num_current_object == res_of_request_products.size()) {
            num_current_object = 0;
        }
        search::product prod = res_of_request_products[num_current_object];
        recipe_text->setText(QString::fromUtf8(get_product_name(prod).c_str()));
    } else if (current_mode == FindRecipe_mode) {
        //циклический список рецептов
        if (num_current_object == res_of_request_recipes.size()) {
            num_current_object = 0;
        }
        search::Recipe recipe = res_of_request_recipes[num_current_object];
        recipe_text->setText(
            QString::fromUtf8(get_recipe_name(recipe).c_str()));
    }
}