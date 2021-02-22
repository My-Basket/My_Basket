//
// Created by nikolya on 21.02.2021.
//

#ifndef MY_BASKET_WORK_WITH_STRING_H

#include <string>
#include <sstream>
#include <vector>

using std::string, std::stringstream, std::hex, std::showbase, std::pair;

pair<int, int> code_point(const string &u);

void from_str_to_codepoint(string &old_s, std::vector<uint32_t> &vec);

uint32_t number_of_symbols(string &s);

string utf8_encode(uint32_t symbol);

#define MY_BASKET_WORK_WITH_STRING_H

#endif //MY_BASKET_WORK_WITH_STRING_H
