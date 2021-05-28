// You may need to build the project (run Qt uic code generator) to get
#include "recipebook.h"
#include <QBrush>
#include <QGridLayout>
#include <QMessageBox>
#include <QPalette>
#include <QSizePolicy>
#include <sstream>
#include "algo.h"
#include "startwindow.h"
#include "style_settings.h"

namespace Ui {

static void print_product_by_name(QTextEdit *text_field,
                                  search::product const &product) {
    std::string s = /*"product name:\n" + */ product.get_name() + '\n';
    text_field->insertPlainText(QString::fromUtf8(s.c_str()));
}

static void print_product_by_name_price(QTextEdit *text_field,
                                        search::product const &product) {
    print_product_by_name(text_field, product);
    std::string s =
        "----price:----\n" + std::to_string(product.get_price()) + "₽" + '\n';
    text_field->insertPlainText(QString::fromUtf8(s.c_str()));
}

static void print_recipe(QTextEdit *text_field, search::Recipe const &recipe) {
    std::string s = /*"recipe name:\n" + */ recipe.get_name() + '\n' + '\n' +
                    "----ingredients:----\n";
    for (auto const &prod : recipe.get_ingredients()) {
        s += prod.get_name() + '\n';
    }
    text_field->insertPlainText(QString::fromUtf8(s.c_str()));
}

static void print_products_vector(
    QTextEdit *text_field,
    std::vector<search::product> const &products_vec) {
    int vec_sz = products_vec.size();
    for (int i = 0; i < vec_sz; i++) {
        std::string s = std::to_string(i + 1) + ") ";
        text_field->insertPlainText(s.c_str());
        print_product_by_name(text_field, products_vec[i]);
        text_field->insertPlainText("\n");
    }
}

static void print_products_vector_with_costs(
    QTextEdit *text_field,
    std::vector<std::pair<std::string, uint32_t>> const &products_vec) {
    // setReadOnly
    text_field->insertPlainText(
        (StyleSettings::Titles::shop_list_title + "\n\n").c_str());
    int vec_sz = products_vec.size();
    for (int i = 0; i < vec_sz; i++) {
        std::string s = std::to_string(i + 1) + ") ";
        text_field->insertPlainText(s.c_str());

        s = products_vec[i].first + "\n<--> " +
            std::to_string(products_vec[i].second) + "₽\n\n";
        text_field->insertPlainText(s.c_str());
    }
    ///выглядит, как копипаст предыдущей функции, пофиксить
}

RecipeBook::RecipeBook(QWidget *parent) : QWidget(parent) {
    product_name_label =
        new QLabel(StyleSettings::Titles::product_name_label_title.c_str());
    set_font_color_label(product_name_label, "white", 28, "", "#359530");
    product_name_label->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    product_name_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                                      QSizePolicy::Expanding);
    product_name_line = new QLineEdit;
    product_name_line->setMinimumHeight(30);
    product_name_line->setStyleSheet("QLineEdit { font-size: 20px;}");
    product_name_line->setReadOnly(true);

    recipe_label =
        new QLabel(StyleSettings::Titles::recipe_label_product_title.c_str());
    set_font_color_label(recipe_label, "white", 28, "", "#359530");
    recipe_label->setAlignment(Qt::AlignCenter | Qt::AlignRight);
    recipe_label->setSizePolicy(QSizePolicy::MinimumExpanding,
                                QSizePolicy::Expanding);
    recipe_text = new QTextEdit;
    recipe_text->setFontPointSize(18);
    recipe_text->setReadOnly(true);

    //экземпляры кнопок правой панели
    add_product_button = new QPushButton(
        StyleSettings::Titles::add_product_button_title.c_str());
    set_font_color_button(add_product_button, "#0066CC", 18);
    add_product_button->show();

    add_recipe_button =
        new QPushButton(StyleSettings::Titles::add_recipe_button_title.c_str());
    set_font_color_button(add_recipe_button, "#0066CC", 18);
    add_recipe_button->show();

    find_product_button = new QPushButton(
        StyleSettings::Titles::find_product_button_title.c_str());
    set_font_color_button(find_product_button, "#0066CC", 18);
    find_product_button->hide();

    put_in_basket_button = new QPushButton(
        StyleSettings::Titles::put_in_basket_button_title.c_str());
    set_font_color_button(put_in_basket_button, "#0066CC", 18);
    put_in_basket_button->hide();

    find_recipe_button = new QPushButton(
        StyleSettings::Titles::find_recipe_button_title.c_str());
    set_font_color_button(find_recipe_button, "#0066CC", 18);
    find_recipe_button->hide();
    find_recipe_mode = BasketSearchingMode;  //поиск по набранной корзине

    check_basket_button = new QPushButton(
        StyleSettings::Titles::check_basket_button_title.c_str());
    set_font_color_button(check_basket_button, "#0066CC", 18);
    check_basket_button->show();

    choose_recipe_button = new QPushButton(
        StyleSettings::Titles::choose_recipe_button_title.c_str());
    set_font_color_button(choose_recipe_button, "#0066CC", 18);
    choose_recipe_button->hide();

    //экземпляры кнопок нижней панели
    next_button =
        new QPushButton(StyleSettings::Titles::next_button_title.c_str());
    set_font_color_button(next_button, "#00CC66", 18);
    next_button->hide();

    previous_button =
        new QPushButton(StyleSettings::Titles::previous_button_title.c_str());
    set_font_color_button(previous_button, "#00CC66", 18);
    previous_button->hide();

    // TODO: можно ли избавиться от копипаста и вынести это в функцию с
    // параметрами (название кнопки (1), ф-я(4))
    connect(add_product_button, SIGNAL(clicked()), this,
            SLOT(add_product_func()));
    connect(add_recipe_button, SIGNAL(clicked()), this,
            SLOT(add_recipe_func()));
    connect(find_product_button, SIGNAL(clicked()), this,
            SLOT(find_product_func()));
    connect(put_in_basket_button, SIGNAL(clicked()), this,
            SLOT(put_in_basket_func()));
    connect(find_recipe_button, SIGNAL(clicked()), this,
            SLOT(find_recipe_func()));
    connect(check_basket_button, SIGNAL(clicked()), this,
            SLOT(check_basket_func()));
    connect(choose_recipe_button, SIGNAL(clicked()), this,
            SLOT(choose_recipe_func()));
    connect(next_button, SIGNAL(clicked()), this, SLOT(next_func()));
    connect(previous_button, SIGNAL(clicked()), this, SLOT(previous_func()));

    //размещение кнопок - правая часть виджета, вертикальный столбец
    QVBoxLayout *button_layout1 = new QVBoxLayout;
    button_layout1->addWidget(add_product_button, Qt::AlignTop);
    button_layout1->addWidget(add_recipe_button);
    button_layout1->addWidget(find_product_button);
    button_layout1->addWidget(put_in_basket_button);
    button_layout1->addWidget(find_recipe_button);
    button_layout1->addWidget(check_basket_button);
    button_layout1->addWidget(choose_recipe_button);
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
    setWindowTitle(StyleSettings::Titles::windows_title.c_str());

    //QBrush image_basket_background(
      //  QImage(StyleSettings::Titles::path_to_bg_image.c_str()));
   // QPalette plt = this->palette();
    //plt.setBrush(QPalette::Window, image_basket_background);
    //this->setPalette(plt);

    this->setMinimumSize(StyleSettings::WindowSizes::min_width_window,
                         StyleSettings::WindowSizes::min_height_window);
    ///вынести в отдельную функцию -- копипаст в 4 местах -- мб наследование?
}

void RecipeBook::clear_fields() {
    //очищение полей ввода
    product_name_line->clear();
    recipe_text->clear();
}

void RecipeBook::clear_fields_and_requests() {
    clear_fields();
    product_name_line->setReadOnly(true);
    recipe_text->setReadOnly(true);

    res_of_request_products.clear();
    res_of_request_recipes.clear();
}

void RecipeBook::activate_search_bar() {
    product_name_line->setReadOnly(
        false);  //отключение режима "только для чтения"
    product_name_line->setFocus(
        Qt::OtherFocusReason);  //установка фокуса ввода на product_name_line
    recipe_text->setReadOnly(false);
}

void RecipeBook::text_field_find_regime(std::string const &s) {
    product_name_line->setText(s.c_str());
    product_name_line->setReadOnly(true);  //<=> нельзя менять
    recipe_text->setReadOnly(false);       //<=> можно менять
}

void RecipeBook::add_product_func() {
    clear_fields_and_requests();
    activate_search_bar();
    find_recipe_mode = BasketSearchingMode;

    recipe_label->setText(
        StyleSettings::Titles::recipe_label_product_title.c_str());

    ///обновление состояний всех кнопок -- мб функцию?? от параметров всех
    ///кнопок -- enabled/ не enabled -- а это вынести в отдельную настройку
    ///сразу
    set_font_color_button(add_product_button, "#172030", 18, false);
    set_font_color_button(find_product_button, "#0066CC", 18, true);
    set_font_color_button(put_in_basket_button, "#0066CC", 18, true);
    set_font_color_button(find_recipe_button, "#0066CC", 18, true);
    set_font_color_button(choose_recipe_button, "#0066CC", 18, true);
    set_font_color_button(check_basket_button, "#0066CC", 18, true);

    set_font_color_button(next_button, "#00CC66", 18, true);
    set_font_color_button(previous_button, "#00CC66", 18, true);

    add_product_button->show();
    add_recipe_button->hide();
    find_product_button->show();
    put_in_basket_button->hide();
    find_recipe_button->hide();
    choose_recipe_button->hide();
    check_basket_button->show();

    next_button->hide();
    previous_button->hide();
}

void RecipeBook::add_recipe_func() {
    clear_fields_and_requests();
    activate_search_bar();
    find_recipe_mode = NameSearchingMode;  //режим поиска по совпадению названий

    set_font_color_button(add_product_button, "#0066CC", 18, true);
    set_font_color_button(add_recipe_button, "#172030", 18, false);
    set_font_color_button(find_product_button, "#0066CC", 18, true);
    set_font_color_button(put_in_basket_button, "#0066CC", 18, true);
    set_font_color_button(find_recipe_button, "#0066CC", 18, true);
    set_font_color_button(choose_recipe_button, "#0066CC", 18, true);
    set_font_color_button(check_basket_button, "#0066CC", 18, true);

    set_font_color_button(next_button, "#00CC66", 18, true);
    set_font_color_button(previous_button, "#00CC66", 18, true);

    add_product_button->hide();
    add_recipe_button->show();
    find_product_button->hide();
    put_in_basket_button->hide();
    find_recipe_button->show();
    choose_recipe_button->hide();
    check_basket_button->show();

    next_button->hide();
    previous_button->hide();
    //вектор кнопок и вектор их методов?
}

///можно ли ее вызвать по нажатию enter? чтобы было логично, как будто в обычном
///поисковике
void RecipeBook::find_product_func() {
    //пустой ввод
    if (product_name_line->text() == "") {
        QMessageBox::information(
            this, StyleSettings::Titles::empty_input_window_title.c_str(),
            StyleSettings::Titles::empty_input_window_text.c_str());
        return;
    }
    text_field_find_regime(product_name_line->text().toStdString());

    set_font_color_button(add_product_button, "#0066CC", 18, true);
    set_font_color_button(find_product_button, "#172030", 18, false);
    set_font_color_button(put_in_basket_button, "#0066CC", 18, true);
    set_font_color_button(find_recipe_button, "#0066CC", 18, true);
    set_font_color_button(choose_recipe_button, "#0066CC", 18, true);
    set_font_color_button(check_basket_button, "#0066CC", 18, true);

    set_font_color_button(previous_button, "#00CC66", 18, true);
    set_font_color_button(next_button, "#00CC66", 18, true);

    add_product_button->show();
    add_recipe_button->hide();
    find_product_button->show();
    put_in_basket_button->show();
    find_recipe_button->hide();
    choose_recipe_button->hide();
    check_basket_button->show();

    next_button->show();
    previous_button->show();

    current_mode = FindProduct_mode;
    //запуск поиска
    res_of_request_products.clear();
    API::ingredients_to_recipe::run_product_search(
        product_name_line->text().toStdString(), 10, res_of_request_products);
    res_of_request_products = API::ingredients_to_recipe::show_res_of_request();

    //установка полей и вывод первого продукта
    recipe_label->setText(
        StyleSettings::Titles::recipe_label_product_title.c_str());
    recipe_text->clear();
    print_product_by_name_price(recipe_text, res_of_request_products[0]);

    num_current_object = 0;
}

void RecipeBook::put_in_basket_func() {
    //добавление продукта в корзину по его номеру в массиве
    // res_of_request_products
    if (res_of_request_products.empty()) {
        return;
    }
    API::put_product_in_basket(basket_of_products,
                               res_of_request_products[num_current_object]);

    clear_fields_and_requests();

    set_font_color_button(add_product_button, "#0066CC", 18, true);
    set_font_color_button(find_product_button, "#0066CC", 18, true);
    set_font_color_button(put_in_basket_button, "#172030", 18, false);
    set_font_color_button(find_recipe_button, "#0066CC", 18, true);
    set_font_color_button(choose_recipe_button, "#0066CC", 18, true);
    set_font_color_button(check_basket_button, "#0066CC", 18, true);

    set_font_color_button(previous_button, "#00CC66", 18, true);
    set_font_color_button(next_button, "#00CC66", 18, true);

    add_product_button->show();
    add_recipe_button->hide();  // todo -- show, если сделаем возможность
                                // несколько рецептов добавлять в корзину
    find_product_button->hide();
    put_in_basket_button->hide();
    find_recipe_button->show();
    choose_recipe_button->hide();
    check_basket_button->show();

    next_button->hide();
    previous_button->hide();
}

void RecipeBook::find_recipe_func() {
    if (find_recipe_mode == BasketSearchingMode) {
        //не пуста ли корзина
        if (basket_of_products.empty()) {
            res_of_request_products.clear();
            res_of_request_recipes.clear();
            QMessageBox::warning(
                this, StyleSettings::Titles::empty_basket_window_title.c_str(),
                StyleSettings::Titles::empty_basket_window_text.c_str());
            return;
        }
        text_field_find_regime("было найдено:");
    } else if (find_recipe_mode == NameSearchingMode) {
        product_name_line->setReadOnly(true);
        recipe_text->setReadOnly(false);
    }

    set_font_color_button(add_product_button, "#0066CC", 18, true);
    set_font_color_button(find_product_button, "#0066CC", 18, true);
    set_font_color_button(put_in_basket_button, "#0066CC", 18, true);
    set_font_color_button(find_recipe_button, "#172030", 18, false);
    set_font_color_button(choose_recipe_button, "#0066CC", 18, true);
    set_font_color_button(check_basket_button, "#0066CC", 18, true);

    set_font_color_button(previous_button, "#00CC66", 18, true);
    set_font_color_button(next_button, "#00CC66", 18, true);

    add_product_button->show();
    add_recipe_button->hide();
    find_product_button->hide();
    put_in_basket_button->hide();
    find_recipe_button->hide();
    choose_recipe_button->show();
    check_basket_button->show();

    next_button->show();
    previous_button->show();

    current_mode = FindRecipe_mode;
    recipe_label->setText(
        StyleSettings::Titles::recipe_label_recipe_title.c_str());

    recipe_text->clear();
    res_of_request_recipes.clear();

    std::vector<search::Recipe> vec2;
    if (find_recipe_mode == BasketSearchingMode) {
        API::ingredients_to_recipe::run_recipes_search(basket_of_products, 10,
                                                       vec2);
        res_of_request_recipes = API::ingredients_to_recipe::show_recipes();
    } else if (find_recipe_mode == NameSearchingMode) {
        // std::cout << "\n NameSearchMode -- product-name: " <<
        // product_name_line->text().toStdString() << '\n';
        API::ingredients_to_recipe::run_recipe_search(
            product_name_line->text().toStdString(), 10, vec2);
        res_of_request_recipes = API::ingredients_to_recipe::show_recipes();
    }

    print_recipe(recipe_text, res_of_request_recipes[0]);
    num_current_object = 0;
}

void RecipeBook::check_basket_func() {
    clear_fields();

    set_font_color_button(add_product_button, "#0066CC", 18, true);
    set_font_color_button(find_product_button, "#0066CC", 18, true);
    set_font_color_button(put_in_basket_button, "#0066CC", 18, true);
    set_font_color_button(find_recipe_button, "#0066CC", 18, true);
    set_font_color_button(choose_recipe_button, "#0066CC", 18, true);
    set_font_color_button(check_basket_button, "#172030", 18, false);

    set_font_color_button(previous_button, "#00CC66", 18, true);
    set_font_color_button(next_button, "#00CC66", 18, true);

    add_product_button->show();
    add_recipe_button->hide();
    find_product_button->hide();
    put_in_basket_button->hide();
    find_recipe_button->show();
    choose_recipe_button->hide();
    check_basket_button->show();

    next_button->hide();
    previous_button->hide();

    recipe_label->setText(
        StyleSettings::Titles::recipe_label_in_basket_title.c_str());

    //вывод корзины на экран
    print_products_vector(recipe_text, basket_of_products);
}

void RecipeBook::previous_func() {
    num_current_object--;
    if (current_mode == FindProduct_mode) {
        //циклический список продуктов
        if (num_current_object < 0) {
            num_current_object = res_of_request_products.size() - 1;
        }
        search::product prod = res_of_request_products[num_current_object];
        recipe_text->clear();
        print_product_by_name_price(recipe_text, prod);
    } else if (current_mode == FindRecipe_mode) {
        //циклический список рецептов
        if (num_current_object < 0) {
            num_current_object = res_of_request_recipes.size() - 1;
        }
        search::Recipe recipe = res_of_request_recipes[num_current_object];
        recipe_text->clear();
        print_recipe(recipe_text, recipe);
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
        recipe_text->clear();
        print_product_by_name_price(recipe_text, prod);
    } else if (current_mode == FindRecipe_mode) {
        //циклический список рецептов
        if (num_current_object == res_of_request_recipes.size()) {
            num_current_object = 0;
        }
        search::Recipe recipe = res_of_request_recipes[num_current_object];
        recipe_text->clear();
        print_recipe(recipe_text, recipe);
    }
}

void RecipeBook::choose_recipe_func() {
    //переход к summary_window

    API::ingredients_to_recipe::choose_recipe(num_current_object);

    summary_window = new SummaryWindow;
    summary_window->show();
    this->close();
}

SummaryWindow::SummaryWindow(QWidget *parent) : QWidget(parent) {
    //QBrush image_basket_background(
        //QImage(StyleSettings::Titles::path_to_bg_image.c_str()));
    //QPalette plt = this->palette();
    //plt.setBrush(QPalette::Window, image_basket_background);
    //this->setPalette(plt);

    //получение информации о лучшем магазине и лучшей стоимости
    auto calculation_info =
        API::ingredients_to_recipe::compare_prices_of_ingredients();
    shop_name = calculation_info.first.first;
    total_cost = calculation_info.first.second;
    products_vec = calculation_info.second;

    best_total_cost_label =
        new QLabel(StyleSettings::Titles::best_total_cost_label_title.c_str());
    set_font_color_label(best_total_cost_label, "black", 100);
    best_total_cost_label->setAlignment(/*Qt::AlignTop,*/ Qt::AlignCenter);
    best_total_cost_label->setMargin(10);

    total_cost_number_label =
        new QLabel((std::to_string(total_cost) + "₽").c_str());
    set_font_color_label(total_cost_number_label, "black", 100, "bold");
    total_cost_number_label->setAlignment(/*Qt::AlignTop,*/ Qt::AlignCenter);
    total_cost_number_label->setMargin(10);

    shop_name_label = new QLabel(shop_name.c_str());
    set_font_color_label(shop_name_label, "black", 100, "bold");
    shop_name_label->setAlignment(/*Qt::AlignTop,*/ Qt::AlignCenter);
    shop_name_label->setMargin(10);

    in_shop_label =
        new QLabel(StyleSettings::Titles::in_shop_label_title.c_str());
    set_font_color_label(in_shop_label, "black", 100);
    in_shop_label->setAlignment(/*Qt::AlignTop,*/ Qt::AlignCenter);
    in_shop_label->setMargin(10);

    products_text = new QTextEdit;
    products_text->setFontPointSize(18);
    products_text->setFixedSize(
        StyleSettings::WindowSizes::product_text_width,
        StyleSettings::WindowSizes::product_text_height);
    products_text->setReadOnly(true);
    products_text->hide();

    //кнопки
    show_final_products_button = new QPushButton(
        StyleSettings::Titles::show_final_products_button_title.c_str());
    set_font_color_button(show_final_products_button, "#FF7699", 30);
    show_final_products_button->show();

    start_again_button = new QPushButton(
        StyleSettings::Titles::start_again_button_title.c_str());
    set_font_color_button(start_again_button, "#FF7699", 30);
    start_again_button->show();

    show_check_button =
        new QPushButton(StyleSettings::Titles::show_check_button_title.c_str());
    set_font_color_button(show_check_button, "#FF7699", 30);
    show_check_button->hide();

    end_program_button = new QPushButton(
        StyleSettings::Titles::end_program_button_title.c_str());
    set_font_color_button(end_program_button, "#FF7699", 30);
    end_program_button->show();

    QGridLayout *label_layout = new QGridLayout;
    label_layout->addWidget(best_total_cost_label);
    label_layout->addWidget(total_cost_number_label);
    label_layout->addWidget(in_shop_label);
    label_layout->addWidget(shop_name_label);
    label_layout->addWidget(products_text);
    label_layout->setSpacing(10);

    QHBoxLayout *button_layout = new QHBoxLayout;
    button_layout->addWidget(show_final_products_button);
    button_layout->addWidget(show_check_button);
    button_layout->addWidget(start_again_button);
    button_layout->addWidget(end_program_button);

    QGridLayout *main_layout = new QGridLayout;
    main_layout->addLayout(label_layout, 0, 0);
    main_layout->addLayout(button_layout, 1, 0);
    main_layout->setSpacing(15);

    connect(show_final_products_button, SIGNAL(clicked()), this,
            SLOT(show_final_products_func()));
    connect(show_check_button, SIGNAL(clicked()), this,
            SLOT(show_check_func()));
    connect(start_again_button, SIGNAL(clicked()), this,
            SLOT(start_again_func()));
    connect(end_program_button, SIGNAL(clicked()), this,
            SLOT(end_program_func()));

    setLayout(main_layout);
    setWindowTitle(StyleSettings::Titles::windows_title.c_str());

    // this->setFixedSize(1000, 600);
    // this->setMinimumSize(1000, 600);
    this->setMinimumSize(StyleSettings::WindowSizes::min_width_window,
                         StyleSettings::WindowSizes::min_height_window);
}

void SummaryWindow::show_final_products_func() {
    show_final_products_button->hide();
    show_check_button->show();

    best_total_cost_label->hide();
    total_cost_number_label->hide();
    in_shop_label->hide();
    shop_name_label->hide();

    products_text->show();
    print_products_vector_with_costs(products_text, products_vec);
}

void SummaryWindow::show_check_func() {
    show_final_products_button->show();
    show_check_button->hide();

    best_total_cost_label->show();
    total_cost_number_label->show();
    in_shop_label->show();
    shop_name_label->show();

    products_text->hide();
}

void SummaryWindow::start_again_func() {
    set_font_color_button(start_again_button, "#FF1099", 30, false);

    //вызвать колину функцию очистки векторов
    API::ingredients_to_recipe::discard_all();
    CategoryWindow *category_window = new CategoryWindow();
    category_window->show();
    this->close();
}

void SummaryWindow::end_program_func() {
    std::exit(0);
}
}  // namespace Ui