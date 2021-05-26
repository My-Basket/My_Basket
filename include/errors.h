#ifndef MY_BASKET_ERRORS_H
#define MY_BASKET_ERRORS_H
#include <string>

class MyBasketError {
private:
    std::string error;

public:
    MyBasketError(const std::string &what);
    [[nodiscard]] std::string what() const;
};

#endif  // MY_BASKET_ERRORS_H
