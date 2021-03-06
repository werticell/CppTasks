## Задание 4.Tuple

В этой задаче вам предлагается освоить продвинутое использование шаблонов, в том числе шаблоны с переменным количеством параметров и некоторые compile-time вычисляемые фичи на шаблонах.<br/>
Напишите шаблонный класс с переменным количеством аргументов - ***Tuple*** (кортеж), обобщение класса ***std::pair***, простенький аналог ***std::tuple*** из С++11.
Класс должен обладать следующим набором методов:
- Конструктор по умолчанию, который инициализирует все элементы кортежа значениями по умолчанию;
- Конструктор из набора аргументов, являющихся const lvalue-ссылками;
- Конструктор из набора аргументов, являющихся универсальными ссылками;
- Конструкторы копирования и перемещения, операторы присваивания (copy и move), деструктор;
- Метод **swap**, меняющий местами значения двух кортежей при условии, что у них одинаковые наборы шаблонных аргументов.


Помимо этого, нужно реализовать функции, не являющиеся членами класса:
- Функция **makeTuple**, создающая новый ***Tuple*** с нужными типами по данному набору аргументов-объектов.
- Функция **get** с шаблонным параметром size_t i, которая принимает ***tuple*** и возвращает ссылку на i-й элемент кортежа. Причем ссылка должна быть того же вида, что была и ссылка на принятый ***tuple*** (lvalue, const lvalue или rvalue).
- Функция **get** с шаблонным параметром T, которая принимает ***tuple*** и возвращает ссылку на тот элемент кортежа, который имеет тип T. Причем ссылка должна быть того же вида, что была и ссылка на принятый ***tuple*** (lvalue, const lvalue или rvalue). Если в кортеже несколько элементов типа T, никаких требований на поведение функции не налагается (можно выдавать ошибку компиляции, можно не выдавать и делать что угодно на этапе выполнения).
- Функция **tupleCat**, которая возвращает кортеж, являющийся конкатенацией нескольких кортежей, переданных в качестве аргументов.
- Операторы сравнения для ***Tuple***, сравнивающие кортежи лексикографически.
