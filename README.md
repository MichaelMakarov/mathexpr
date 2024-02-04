# mathexprproc
Репозиторий содержит cmake проект, в рамках которого собираются библиотека и запускаемый файл.
Библиотека предоставляет функцию, которая принимает строку с математическим выражением и, обрабатывая её, вычисляет результат. Обработка выражения реализована с применением алгоритма shunting yard для перевода в обратную польскую нотацию.
Запускаемый файл - консольное приложение, которое в бесконечном цикле считывает строку через стандартный поток ввода и вызывает обработку строки с выводом результата в стандартный поток.
