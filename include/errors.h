#ifndef MY_BASKET_ERRORS_H
#define MY_BASKET_ERRORS_H
#include <string>

namespace err {
class MyBasketError {
private:
    std::string error;

public:
    explicit MyBasketError(const std::string &what);
    [[nodiscard]] virtual std::string what() const noexcept;
};

struct InvalidString : MyBasketError {
    explicit InvalidString(const std::string &s);
    [[nodiscard]] std::string what() const noexcept override;
};
}
#endif  // MY_BASKET_ERRORS_H
