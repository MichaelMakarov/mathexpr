#pragma once 

namespace math {
    /// @brief Тип чисел, сипользуемых в вычислениях
    using number_t = double;

    /**
     * \brief Обработка математического выражения.
     * 
     * Поддерживаются следующие математические операции:
     * 1) + суммирование
     * 2) - вычитание
     * 3) * умножение
     * 4) / деление
     * 5) ^ возведение в степень
     * 6) ! вычисление факториала числа
     * 
     * Поддерживаются следующие математические функции:
     * 1) exp() экспонента
     * 2) ln() натуральный логарифм
     * 3) lg() десятичный логарифм
     * 4) log( , ) логарифм по произвольному основанию
     * 5) sqrt() квадратный корень
     * 6) sin() синус
     * 7) cos() косинус
     * 8) tan() тангенс
     * 9) asin() арксинус
     * 10) acos() арккосинус
     * 11) atan() арктангенс
     * 12) sinh() синус гиперболический
     * 13) cosh() косинус гиперболический
     * 14) tanh() тангенс гиперболический
     * 
     * При возникновении ошибки выбрасывается исключение std::invalid_argument.
     * 
     * \param expr строка с математическим выражением
     * \return результат математического выражения
     */
    number_t process_mathexpr(char const *expr);
}