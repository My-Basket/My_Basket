#include <logger.h>
#include <iostream>

logger::logger(size_t size) : max_size(size) {
}

void logger::log(const std::string &logs) {
    text += logs;
    if (text.size() > max_size) {
        flush();
    }
}

logger::~logger() = default;

error_logger::error_logger(size_t size) : logger(size) {
}

void error_logger::flush() {
    std::cerr << text;
    text.clear();
}

void error_logger::log(const MyBasketError &er) {
    logger::log(er.what());
}

error_logger::~error_logger() {
    error_logger::flush();
}

file_logger::file_logger(size_t size) : logger(size) {
}

void file_logger::flush() {
    auto time = std::chrono::system_clock::now();
    std::fstream fout(
        "../logs/logs_by_" +
        std::to_string(std::chrono::system_clock::to_time_t(time)));
    fout << text;
    text.clear();
    fout.close();
}

file_logger::~file_logger() {
    file_logger::flush();
}
