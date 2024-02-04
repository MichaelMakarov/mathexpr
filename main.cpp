#include "mathexpr.hpp"

#include <string>
#include <iostream>

int main() {
    std::string expr_str;
    while (std::getline(std::cin, expr_str)) {
        try {
        auto number = math::process_mathexpr(expr_str.c_str());
        std::cout << "= " << number << std::endl;
        } catch (std::exception const &ex) {
            std::cerr << "error occured: " << ex.what() << std::endl;
        }
    }
    return 0;
}