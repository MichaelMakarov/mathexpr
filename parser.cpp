#include "common.hpp"

#include <format>
#include <unordered_map>

namespace math {

namespace {

class functions_handler {
public:
  static int get_priority(std::string_view str) {
    auto iter = functions.find(str);
    if (iter == functions.end()) {
      throw std::invalid_argument(std::format("Encountered unsupported function {}. Don't forget to use brackets.", str));
    }
    return iter->second;
  }

private:
  static std::unordered_map<std::string_view, int> const functions;
};

std::unordered_map<std::string_view, int> const functions_handler::functions{
    {"+", 2},    {"-", 2},    {"*", 3},    {"/", 3},    {"^", 4},    {"~", 6},  {"!", 7},   {"exp", 5},
    {"ln", 5},   {"lg", 5},   {"log", 5},  {"sqrt", 5}, {"sin", 5},  {"cos", 5}, {"tan", 5}, {"asin", 5},
    {"acos", 5}, {"atan", 5}, {"sinh", 5}, {"cosh", 5}, {"tanh", 5}, {"(", 1},   {")", 8},
};

void add_function_to_list(strings_list_t &strings, strings_list_t &functions, std::string_view func) {
  int  priority = functions_handler::get_priority(func);
  auto end      = functions.begin();
  while (end != functions.end()) {
    if (functions_handler::get_priority(*end) >= priority) {
      ++end;
    } else {
      break;
    }
  }
  strings.splice(strings.end(), functions, functions.begin(), end);
  functions.push_front(func);
}

void process_close_bracket(strings_list_t &strings, strings_list_t &functions) {
  auto end = functions.begin();
  while (end != functions.end()) {
    if (*end != "(") {
      ++end;
    } else {
      break;
    }
  }
  if (end == functions.end()) {
    throw std::invalid_argument("Encountered the close bracket before the open bracket.");
  }
  strings.splice(strings.end(), functions, functions.begin(), end);
  functions.pop_front();
}

std::string_view try_parse_number(char const *begin) {
  std::size_t points_count{};
  char const *end{begin};
  while (true) {
    if (std::isdigit(*end)) {
    } else if (*end == '.' && points_count == 0) {
      ++points_count;
    } else {
      break;
    }
    ++end;
  }
  return std::string_view{begin, static_cast<std::size_t>(end - begin)};
}

std::string_view try_parse_function(char const *begin) {
  char const *end{begin};
  while (true) {
    switch (*end) {
    case 'a':
    case 'c':
    case 'e':
    case 'g':
    case 'h':
    case 'i':
    case 'l':
    case 'n':
    case 'o':
    case 'p':
    case 'r':
    case 's':
    case 't':
    case 'x':
      ++end;
      continue;
    }
    break;
  }
  return std::string_view{begin, static_cast<std::size_t>(end - begin)};
}

std::string_view try_parse_operator(char const *str) {
  switch (*str) {
  case '+':
  case '-':
  case '*':
  case '/':
  case '^':
  case '!':
    return std::string_view{str, 1};
  default:
    return std::string_view{};
  }
}

} // namespace

strings_list_t parse_mathexpr(char const *str) {
  // список строк, в который будем добавлять контент
  strings_list_t strings;
  // список функций
  strings_list_t functions;
  // флаг того, что последним элементом выражения было либо число, либо закрывающая скобка
  bool is_bound{false};
  while (*str != '\0') {
    if (std::isspace(*str)) {
      ++str;
      continue;
    }
    std::string_view number = try_parse_number(str);
    if (!number.empty()) {
      strings.push_back(number);
      str += number.size();
      is_bound = true;
      continue;
    }
    if (*str == '(') {
      functions.push_front("(");
      ++str;
      is_bound = false;
      continue;
    }
    if (*str == ')') {
      process_close_bracket(strings, functions);
      ++str;
      is_bound = true;
      continue;
    }
    std::string_view func;
    // unar minus case
    if (*str == '-' && !is_bound) {
      func = "~";
    } else {
      // operator case
      func = try_parse_operator(str);
      if (func.empty()) {
        // function case
        func = try_parse_function(str);
      }
    }
    if (!func.empty()) {
      if (!is_pi(func)) {
        add_function_to_list(strings, functions, func);
      } else {
        strings.push_back(func);
      }
      str += func.size();
      is_bound = false;
      continue;
    }
    throw std::invalid_argument(std::format("Failed to parse the string {}", str));
  }
  strings.splice(strings.end(), functions);
  return strings;
}

} // namespace math