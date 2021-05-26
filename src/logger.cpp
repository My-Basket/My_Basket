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

void error_logger::log(const err::MyBasketError &er) {
    logger::log(er.what());
}

error_logger::~error_logger() {
    error_logger::flush();
}

void error_logger::log(const nlohmann::json::exception &er) {
    logger::log(er.what());
}

file_logger::file_logger(size_t size) : logger(size) {
}

void file_logger::flush() {
    std::time_t time =
        std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string str_time_format(std::ctime(&time));
    std::replace_if(
        str_time_format.begin(), str_time_format.end(),
        [](char &c1) { return (c1 == ' ' || c1 == ':'); }, '_');
    str_time_format.pop_back();
    std::string file_name = "../Logs/logs_by_" + str_time_format;
    std::ofstream fout(file_name);

    fout << text;
    text.clear();
    fout.close();
}

file_logger::~file_logger() {
    file_logger::flush();
}
void file_logger::log(const std::string &logs) {
    logger::log(logs);
}

void error_file_logger::flush() {
    file_logger::flush();
}

error_file_logger::error_file_logger(size_t size) : file_logger(size) {
}

error_file_logger::~error_file_logger() {
    file_logger::flush();
}

void error_file_logger::log(const err::MyBasketError &er) {
    error_logger::log(er);
}

void error_file_logger::log(const nlohmann::json::exception &er) {
    error_logger::log(er);
}
