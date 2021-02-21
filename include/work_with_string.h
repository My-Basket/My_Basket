//
// Created by nikolya on 21.02.2021.
//

#ifndef MY_BASKET_WORK_WITH_STRING_H

#include <string>
#include <sstream>

using std::string, std::stringstream, std::hex, std::showbase, std::pair;

pair<int, int> code_point(const string &u);


string utf8_encode(uint32_t symbol);

#define MY_BASKET_WORK_WITH_STRING_H

#endif //MY_BASKET_WORK_WITH_STRING_H
