# String.h

## Оглавление
* [Введение](#Введение)
* [Build](#build)

## Введение

Реализация библиотеки string.h с дополнениями.
- Работа со строками в C.
- Функции с переменным количеством аргументов.
- Создание и связывание статических библиотек, сборка проекта с помощью Makefile.
- Модульное тестирование с использованием платформы Check.
- Оценка тестового покрытия с помощью gcov.

## build
```
cd String_h/src
make s21_string.a
```

## Tests
Unit-тесты реализованы при помощи [Check](https://libcheck.github.io/check/), отчет о покрытии при помощи [LCOV](https://github.com/linux-test-project/lcov)
```
cd String_h/src
make test
```
Отчет о покрытии:
```
cd String_h/src
make gcov_report
```
