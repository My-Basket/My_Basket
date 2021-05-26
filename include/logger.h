#ifndef MY_BASKET_LOGGER_H
#define MY_BASKET_LOGGER_H

#include <errors.h>
#include <chrono>
#include <fstream>
#include <json.hpp>
#include <string>

using nlohmann::json;

class logger {
protected:
    std::string text;             // NOLINT
    const size_t max_size = 1e5;  // NOLINT
    virtual void flush() = 0;     // NOLINT

public:
    logger() = default;
    logger(size_t size);
    virtual void log(const std::string &logs);
    virtual ~logger();
};

class error_logger : public virtual logger {
protected:
    void flush() override;

public:
    error_logger() = default;
    error_logger(size_t size);
    virtual void log(const err::MyBasketError &er);
    virtual void log(const json::exception &er);
    ~error_logger() override;
};

class file_logger : public virtual logger {
protected:
    void flush() override;

public:
    file_logger() = default;
    void log(const std::string &logs) override;
    file_logger(size_t size);
    ~file_logger() override;
};

class error_file_logger final : public file_logger, public error_logger {
private:
    void flush() final;

public:
    error_file_logger() = default;
    error_file_logger(size_t size);
    void log(const err::MyBasketError &er) override;
    void log(const json::exception &er) override;
    ~error_file_logger() final;
};

#endif  // MY_BASKET_LOGGER_H
