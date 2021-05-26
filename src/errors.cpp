#include <errors.h>

MyBasketError::MyBasketError(const std::string &what) : error(what) {  // NOLINT
}

std::string MyBasketError::what() const {
    return error;
}
