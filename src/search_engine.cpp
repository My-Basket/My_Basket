//
// Created by vladi on 18.02.2021.
//

#include <search_engine.h>
#include <cassert>
#include <fstream>

namespace {
void relax(uint32_t &a, uint32_t b) {
    if (a > b) {
        a = b;
    }
}

uint32_t levenshtein_algo(const std::string &first, const std::string &second) {
    uint32_t n = first.length();
    uint32_t m = second.size();
    auto first_t = ' ' + first;
    auto second_t = '+' + second;
    std::vector<std::vector<uint32_t>> f(
        n + 1, std::vector<uint32_t>(m + 1, 0));

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {

            if (i == 0 || j == 0) {
                f[i][j] = std::max(i, j);
                continue;
            }

            int w = first_t[i - 1] == second_t[j - 1] ? 0 : 1;

            relax(f[i][j], f[i - 1][j] + 1);
            relax(f[i][j], f[i][j - 1] + 1);
            relax(f[i][j], f[i - 1][j - 1] + w);
        }
    }
    return f[n][m];
}
}  // namespace

namespace search {

void from_json(json &j, product &p) {
    j.at("Name").get_to(p.name);
    j.at("Category").get_to(p.category);
    j.at("Price").get_to(p.price);
}

std::ostream &operator<<(std::ostream &os, const product &p) {
    os << "{\n"
       << "   "
       << "Name: " << p.name << '\n'
       << "   "
       << "Category: " << p.category << '\n'
       << "   "
       << "Price: " << p.price << '\n'
       << "}\n";
    return os;
}
///TODO Doesn't work yet.
void get_prod_top_by_name(std::string &s,
                          uint32_t size,
                          std::vector<product> &ans) {
    std::ifstream file("../data/spar.json");
    json j = json::parse(file);
    file.close();

    struct comp {
        bool operator() (const std::pair<uint32_t, product> &a, const std::pair<uint32_t, product> &b) const {
            return a.first > b.first;
        }
    };

    std::set<std::pair<uint32_t, product>, comp> top;

    for (auto const &x : j) {
        product cur_prod(x);
        std::string name = cur_prod.name;
        uint32_t coincidence_amount = levenshtein_algo(name, s);
        top.insert({coincidence_amount, cur_prod});

        if (top.size() > size) {
            auto it = top.end();
            it--;
            top.erase(it);
        }
    }

    ans.reserve(top.size());

    for (const auto &x : top) {
        ans.emplace_back(x.second);
    }
}

product::product(const json &j) {
    *this = j;
}

product &product::operator=(const json &j) {
    try {
        name = j["Name"];
        category = j["Category"];
        price = j["Price"];
        return *this;
    } catch (...) {
        assert((false, "Invalid cast from json to product"));
    }
}

product::product(json &&j) {
    *this = j;
}

product &product::operator=(json &&j) {
    *this = j;
    return *this;
}

}  // namespace search
