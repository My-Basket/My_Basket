#include <QApplication>
#include <QPushButton>
#include "work_with_string.h"
#include <iostream>
int min(int a, int b){
    return (a<b)? a : b;
}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(2000, 1000);
    button.show();
    ///////////////////////////////////////
    // примерно так будем работать со строками//

    std::string old_s = "Привет😅!b你è";
    std::string new_s;
    std::cout << utf8_encode(code_point(old_s).first); // собственно code_point символа
    int x = code_point(old_s).second;
    std::cout<< " " << x;       // количество байт необходимых для хранения
    new_s.resize(old_s.size()-x);
    while (!new_s.empty()){
        for(int i=x; i<old_s.size(); i++){
            new_s[i-x] = old_s[i];
        }
        std::cout <<"\n"<< utf8_encode(code_point(new_s).first);
        x = code_point(new_s).second;
        std::cout << " " << x;
        old_s  = new_s;
        new_s.resize(old_s.size()-x);
    }

    /////////////////////////////////////
    return QApplication::exec();

}