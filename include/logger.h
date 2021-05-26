#ifndef MY_BASKET_LOGGER_H
#define MY_BASKET_LOGGER_H

#include <chrono>
#include <fstream>
#include <string>
#include <errors.h>

class logger {
protected:
    std::string text;             // NOLINT
    const size_t max_size = 1e5;  // NOLINT
    virtual void flush() = 0;         // NOLINT

public:
    logger() = default;
    logger(size_t size);
    void log(const std::string &logs);
    virtual ~logger();
};

class error_logger : virtual logger {
private:
    void flush() override;

public:
    error_logger() = default;
    error_logger(size_t size);
    void log(const MyBasketError &er);
    ~error_logger() override;
};

class file_logger : virtual logger {
private:
    void flush() override;

public:
    file_logger() = default;
    file_logger(size_t size);
    ~file_logger() override;
};

#endif  // MY_BASKET_LOGGER_H
