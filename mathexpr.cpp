#include "common.hpp"


namespace math {
number_t process_mathexpr(char const *expr) {
  strings_list_t list = parse_mathexpr(expr);
  if (list.empty()) {
    throw std::invalid_argument("Input string does not contain a valid mathematical expression.");
  }
  return calculate_mathexpr(list);
}
} // namespace math