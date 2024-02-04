#pragma once

#include "mathexpr.hpp"

#include <cstring>
#include <list>
#include <string_view>
#include <stdexcept>

namespace math {

/// @brief Тип списка строк
using strings_list_t = std::list<std::string_view>;

/**
 * \brief Разюор записанного в строке математического выражения
 * \param expr строка с математическим выражением
 * \return strings_list_t
 */
strings_list_t parse_mathexpr(char const *expr);

/**
 * \brief Вычисление представленного в виде списка строк математического выражения
 * \param list список строк в постфиксной польской нотации
 * \return number_t
 */
number_t calculate_mathexpr(strings_list_t const &list);

/**
 * \brief Проверка строки на содержание числа пи
 * \param str строка
 * \return true строка содержит число пи
 * \return false не содержит
 */
inline bool is_pi(std::string_view str) {
  return str[0] == 'p' && str[1] == 'i';
}

} // namespace math