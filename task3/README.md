_ИЗ КАКИХ ФАЙЛОВ СОСТОИТ ЗАДАЧА_

* "task3.c" - главная программа
* "func.c" - программа с функциями
* "func.h" - модуль с функциями
* "Makefile" - файл для make

_ИСПОЛЬЗУЕМЫЕ БИБЛИОТЕКИ_

* "stdio.h"
* "stdlib.h"
* "signal.h"
* "limits.h"

_ПРОЦЕСС СБОРКИ ПРОЕКТА_

Нужно ввести "make task3" в командной строке и нажать ENTER

_ПРОЦЕСС ЗАПУСКА ПРОЕКТА_

1) компиляция и сборка решения

2) запуск:

из командной строки с помощью ввода "make valtask3" 
и последующего нажатия на ENTER

3) ввод данных в любом виде

4) выполнение программы:
 
создает пустой динамический массив слов (lst) и буфер слова (buf). 

/Одновременно со всей программой идет обработка сигнала SIGINT. Если наступил, все динамические элементы 
освобождаются и программа выводит о своем завершении и останавливается.

считывание по 10 элементов из stdin.

обработка каждого символа

в конце вывод, сортировка пузырьком (сравнивается код символа, также если
символы одинаковые, то меньше тот, у которого меньше длина) и снова вывод.

освобождение памяти: сначала элементы массива, потом сам массив, затем buf

Есть обработка ошибок: если не выполнилось освобождение памяти, введен
неправильный символ, переполнение buf или lst