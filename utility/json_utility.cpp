#include <search_engine.h>
#include <fstream>
#include <iostream>
#include <json.hpp>

int main() {
    std::cout << "Enter the name of the file: ";
    std::string s;
    std::cin >> s;
    std::ofstream outfile;
    outfile.open("../"+s);
    outfile << "[\n";

    bool flag_begin = true;
    for (;;) {
        std::cout << "Enter the command\n";
        std::string command;
        std::cin >> command;
        if (command == "add") {
            if (!flag_begin) {
                outfile << ",\n";
            } else {
                flag_begin = false;
            }
            std::string name;
            std::cout << "Enter the name of recipe" << std::endl;
            std::getline(std::cin, name, '\n');
            search::Recipe R(name);
            std::cout
                << "Enter the ingredients, write \"end\" when you finish:\n";
            std::string next_ingredient;
            std::cout << "Enter the 1 ingredient:\n";
            std::getline(std::cin, next_ingredient, '\n');
            for (int i = 2; next_ingredient != "end"; i++) {
                std::getline(std::cin, next_ingredient, '\n');
                R.add_product({next_ingredient, "RECIPE", 0});
                if (next_ingredient != "end") {
                    std::cout << "Enter the " << i << " ingredient:\n";
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