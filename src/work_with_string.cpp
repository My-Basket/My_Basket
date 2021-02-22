#include "work_with_string.h"

pair<int, int> code_point(const string &u) {
    pair<int, int> result;
    result.first = result.second = -1;
    int l = u.length();
    if (l < 1) {
        return result;
    }
    unsigned char u0 = u[0];
    if (u0 >= 0 && u0 <= 127) {
        result.first = u0;
        result.second = 1;
        return result;
    }
    if (l < 2) {
        return result;
    }
    unsigned char u1 = u[1];
    if (u0 >= 192 && u0 <= 223) {

        result.first = (u0 - 192) * 64 + (u1 - 128);
        result.second = 2;
        return result;
    }
    if (u[0] == 0xed && (u[1] & 0xa0) == 0xa0) {
        return result; //code points, 0xd800 to 0xdfff
    }
    if (l < 3) {
        return result;
    }
    unsigned char u2 = u[2];
    if (u0 >= 224 && u0 <= 239) {
        result.first = (u0 - 224) * 4096 + (u1 - 128) * 64 + (u2 - 128);
        result.second = 3;
        return result;
    }
    if (l < 4) {
        return result;
    }
    unsigned char u3 = u[3];
    if (u0 >= 240 && u0 <= 247) {
        result.first = (u0 - 240) * 262144 + (u1 - 128) * 4096 + (u2 - 128) * 64 + (u3 - 128);
        result.second = 4;
        return result;
    }
    return result;
}

std::string utf8_encode(uint32_t symbol) {
    char out[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
    if (symbol <= 0x7F) {
        // ASCII
        out[0] = static_cast<char>( symbol);
        out[1] = 0;
    } else if (symbol <= 0x07FF) {
        // 2-byte unicode
        out[0] = static_cast<char>((((symbol >> 6) & 0x1F) | 0xC0));
        out[1] = static_cast<char>((((symbol >> 0) & 0x3F) | 0x80));
    } else if (symbol <= 0xFFFF) {
        // 3-byte unicode
        out[0] = static_cast<char>((((symbol >> 12) & 0x0F) | 0xE0));
        out[1] = static_cast<char>((((symbol >> 6) & 0x3F) | 0x80));
        out[2] = static_cast<char>((((symbol >> 0) & 0x3F) | 0x80));
    } else if (symbol <= 0x10FFFF) {
        // 4-byte unicode
        out[0] = static_cast<char>((((symbol >> 18) & 0x07) | 0xF0));
        out[1] = static_cast<char>((((symbol >> 12) & 0x3F) | 0x80));
        out[2] = static_cast<char>((((symbol >> 6) & 0x3F) | 0x80));
        out[3] = static_cast<char>((((symbol >> 0) & 0x3F) | 0x80));
    } else {
        // error - use replacement character
        out[0] = static_cast<char>( 0xEF);
        out[1] = static_cast<char>( 0xBF);
        out[2] = static_cast<char>( 0xBD);
    }
    return static_cast<string>(out);
}

void from_str_to_codepoint(string old_s, std::vector<uint32_t> &vec) {
    if (old_s.empty()) {
        return;
    }
    std::string new_s;
    auto[codepoint, symbol_size] = code_point(old_s);
    vec.push_back(0);
    vec.push_back(codepoint);
    new_s.resize(old_s.size() - symbol_size);

    while (!new_s.empty()) {
        for (int i = symbol_size; i < old_s.size(); i++) {
            new_s[i - symbol_size] = old_s[i];
        }

        auto[codepoint, symbol_size] = code_point(new_s);
        vec.push_back(codepoint);
        old_s = new_s;
        new_s.resize(old_s.size() - symbol_size);
    }
}


