Выбраны были N1 и N2 в task1.

N1 и N2 были реализованы в одной программе под названием task1.c в папке
task1 следующим образом:

Сначала провереятся тип char на знаковость (N2, также понадобиться для 
N1) присваиванием переменной этого типа значение ноль и вычитанием из 
нее один. Полученный знак говорит: знаковый тип char или нет. Потом 
для каждого варианта (знаковый или беззнаковый) вычисляем количество 
байт n. Так как тип sizeof может варьироваться в каждой реализации, 
присвоила каждому переменному типа int значение sizeof(<тип>) * n. 
Дальше вывод.  