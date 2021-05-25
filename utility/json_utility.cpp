#include <search_engine.h>
#include <chrono>
#include <fstream>
#include <iostream>
#include <json.hpp>

int main() {
    std::cout << "Enter the name of the file: ";
    std::string s;
    std::getline(std::cin, s);
    std::ofstream outfile;
    outfile.open("../../data/" + s);
    outfile << "[\n";

    bool flag_begin = true;
    for (;;) {
        std::cout << "Enter the command\n";
        std::string command;
        std::getline(std::cin, command);
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
        } else {
            break;
        }
    }
    outfile << "]\n";
    outfile.close();
}