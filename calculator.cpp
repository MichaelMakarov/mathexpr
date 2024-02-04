#include "common.hpp"

#include <cctype>
#include <charconv>
#include <cmath>
#include <format>
#include <numbers>
#include <stack>
#include <unordered_map>

namespace math {
namespace {

using numbers_stack_t = std::stack<number_t>;

using calc_func_t = void (*)(numbers_stack_t &);

inline void verify_stack_size(numbers_stack_t &numbers, std::size_t exp_size, char const *func_name) {
  if (numbers.size() < exp_size) {
    throw std::runtime_error(
        std::format("{}: stack of numbers has size={} but is expected to have size={}.", func_name, numbers.size(), exp_size));
  }
}

inline number_t remove_number(numbers_stack_t &numbers) {
  number_t number = numbers.top();
  numbers.pop();
  return number;
}

void calc_sum(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 2, "sum");
  number_t right = remove_number(numbers);
  number_t left  = remove_number(numbers);
  numbers.push(left + right);
}

void calc_sub(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 2, "sub");
  number_t right = remove_number(numbers);
  number_t left  = remove_number(numbers);
  numbers.push(left - right);
}

void calc_mul(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 2, "mul");
  number_t right = remove_number(numbers);
  number_t left  = remove_number(numbers);
  numbers.push(left * right);
}

void calc_div(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 2, "div");
  number_t right = remove_number(numbers);
  number_t left  = remove_number(numbers);
  numbers.push(left / right);
}

void calc_pow(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 2, "pow");
  number_t right = remove_number(numbers);
  number_t left  = remove_number(numbers);
  numbers.push(std::pow(left, right));
}

void calc_factorial(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "factorial");
  number_t number = remove_number(numbers);
  numbers.push(std::tgamma(number + 1));
}

void calc_exp(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "exp");
  number_t number = remove_number(numbers);
  numbers.push(std::exp(number));
}

void calc_ln(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "ln");
  number_t number = remove_number(numbers);
  numbers.push(std::log(number));
}

void calc_lg(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "lg");
  number_t number = remove_number(numbers);
  numbers.push(std::log10(number));
}

void calc_log(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 2, "log");
  number_t right = remove_number(numbers);
  number_t left  = remove_number(numbers);
  numbers.push(std::log(right) / std::log(left));
}

void calc_sqrt(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "sqrt");
  number_t number = remove_number(numbers);
  numbers.push(std::sqrt(number));
}

void calc_sin(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "sin");
  number_t number = remove_number(numbers);
  numbers.push(std::sin(number));
}

void calc_cos(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "cos");
  number_t number = remove_number(numbers);
  numbers.push(std::cos(number));
}

void calc_tan(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "tan");
  number_t number = remove_number(numbers);
  numbers.push(std::tan(number));
}

void calc_cosh(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "cosh");
  number_t number = remove_number(numbers);
  numbers.push(std::cosh(number));
}

void calc_sinh(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "sinh");
  number_t number = remove_number(numbers);
  numbers.push(std::sinh(number));
}

void calc_tanh(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "tanh");
  number_t number = remove_number(numbers);
  numbers.push(std::tanh(number));
}

void calc_asin(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "asin");
  number_t number = remove_number(numbers);
  numbers.push(std::asin(number));
}

void calc_acos(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "acos");
  number_t number = remove_number(numbers);
  numbers.push(std::acos(number));
}

void calc_atan(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "atan");
  number_t number = remove_number(numbers);
  numbers.push(std::atan(number));
}

void calc_neg(numbers_stack_t &numbers) {
  verify_stack_size(numbers, 1, "~");
  numbers.top() = -numbers.top();
}

void push_pi(numbers_stack_t &numbers) {
  numbers.push(std::numbers::pi);
}

class functions_handler {
public:
  static calc_func_t get_function(std::string_view str) {
    auto iter = functions.find(str);
    if (iter == functions.end()) {
      throw std::invalid_argument(std::format("Encountered unsupported function {}. Don't forget to use brackets.", str));
    }
    return iter->second;
  }

private:
  static std::unordered_map<std::string_view, calc_func_t> const functions;
};

std::unordered_map<std::string_view, calc_func_t> const functions_handler::functions{
    {"+", &calc_sum},       {"-", &calc_sub},     {"*", &calc_mul},     {"/", &calc_div},     {"^", &calc_pow},     {"~", &calc_neg},
    {"!", &calc_factorial}, {"exp", &calc_exp},   {"ln", &calc_ln},     {"lg", &calc_lg},     {"log", &calc_log},   {"sqrt", &calc_sqrt},
    {"sin", &calc_sin},     {"cos", &calc_cos},   {"tan", &calc_tan},   {"asin", &calc_asin}, {"acos", &calc_acos}, {"atan", &calc_atan},
    {"sinh", &calc_sinh},   {"cosh", &calc_cosh}, {"tanh", &calc_tanh}, {"pi", &push_pi},
};

number_t str_to_number(std::string_view str) {
  double                 value;
  std::from_chars_result res = std::from_chars(str.data(), str.data() + str.size(), value);
  if (res.ec != std::errc{}) {
    throw std::invalid_argument(std::format("Failed to parse a number from string {} with error code {}.", str, static_cast<int>(res.ec)));
  }
  return value;
}

} // namespace

number_t calculate_mathexpr(strings_list_t const &list) {
  numbers_stack_t numbers;
  for (auto str : list) {
    if (std::isdigit(str[0]) || (str[0] == '-' && str.size() > 1)) {
      number_t number = str_to_number(str);
      numbers.push(number);
    } else {
      calc_func_t calc_func = functions_handler::get_function(str);
      calc_func(numbers);
    }
  }
  return numbers.top();
}

} // namespace math