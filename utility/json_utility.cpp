#include <search_engine.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <sstream>

int main() {
    std::cout << "Enter the name of the file: ";
    std::string s;
    std::getline(std::cin, s);
    std::ofstream outfile;
    outfile.open("../../data/" + s);
    outfile << "[\n";

    for (;;) {
        bool flag_begin = true;
        std::cout << "Enter the command\n";
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss;
        ss << line;
        std::string command;
        ss >> command;
        if (command == "add") {
            if (!flag_begin) {
                outfile << ",\n";
            } else {
                flag_begin = false;
            }
            std::string name;
            std::cout << "Enter the name of recipe\n";
            std::getline(std::cin, name);
            std::string ref;
            std::cout << "Enter the reference\n";
            std::getline(std::cin, ref);
            std::string pic_ref;
            std::cout << "Enter the picture reference\n";
            std::getline(std::cin, pic_ref);
            search::Recipe R(name, ref, pic_ref);
            std::cout
                << "Enter the ingredients, write \"end\" when you finish:\n";
            std::string next_ingredient = "not_end";
            for (int i = 1; next_ingredient != "end"; i++) {
                std::cout << "Enter the " << i << " ingredient:\n";
                std::getline(std::cin, next_ingredient);
                if (next_ingredient != "end") {
                    R.add_product({next_ingredient, "RECIPE", 0});
                }
            }
            outfile << R;
            continue;
        }
        if (command == "transform") {
            std::string in_file;
            ss >> in_file;
            std::string in_file_right_format = "../../data_original/" + in_file;
            std::ifstream fin(in_file_right_format);
            nlohmann::json j;
            try {
                j = nlohmann::json::parse(fin);
            } catch (...) {
                std::cerr << "Can't parse " << in_file_right_format
                          << std::endl;
                continue;
            }
            std::cout << "Enter the path to the \"Name\":\n";
            std::string path_name;
            std::getline(std::cin, path_name);
            std::cout << "Enter the path to the \"Category\":\n";
            std::string path_category;
            std::getline(std::cin, path_category);
            std::cout << "Enter the path to the \"Price\":\n";
            std::string path_price;
            std::getline(std::cin, path_price);

            int price;
            for (const auto &x : j) {
                if (!flag_begin) {
                    outfile << ",\n";
                } else {
                    flag_begin = false;
                }
                try {
                    price = x[path_price];
                } catch (...) {
                    try {
                        price = stoi(std::string(x[path_price]));
                    } catch (...) {
                        std::cerr << "Invalid path " << std::endl;
                    }
                }
                std::string name;
                try {
                    name = x[path_name];
                } catch (...) {
                    std::cerr << "Invalid path " << path_name << std::endl;
                }
                name.erase(std::remove(name.begin(), name.end(), '\"'),
                           name.end());
                name.erase(std::remove(name.begin(), name.end(), '/'),
                           name.end());
                std::string category;
                try {
                    category = x[path_category];
                } catch (...) {
                    std::cerr << "Invalid path " << path_category << std::endl;
                }
                category.erase(
                    std::remove(category.begin(), category.end(), '\"'),
                    category.end());
                category.erase(
                    std::remove(category.begin(), category.end(), '/'),
                    category.end());
                search::product p(name, category, price);
                outfile << p;
            }
            fin.close();
            continue;
        }
        break;
    }
    outfile << "]\n";
    outfile.close();
}