#include <errors.h>

namespace err {
MyBasketError::MyBasketError(const std::string &what) : error(what) {  // NOLINT
}

std::string MyBasketError::what() const noexcept {
    return error;
}

InvalidString::InvalidString(const std::string &s)
    : MyBasketError("Invalid String \"" + s + "\"\n") {
}

std::string InvalidString::what() const noexcept {
    return MyBasketError::what();
}
}  // namespace err
