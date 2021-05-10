## Задание List + Iterators

В этой задаче вам предлагается реализовать полноценный STL-подобный контейнер (упрощенный относительно настоящего STL, разумеется, но приближенный к нему). Напишите шаблонный класс ***List<T>*** - двусвязный список. Нужно правильно поддержать move-семантику, а также итераторы. (Аллокаторы поддерживать не надо.)
Должно быть реализовано следующее:
- Конструкторы: List() - пустой лист; List(size_t count, const T& value = T()) - лист из count элементов, изначально равных value каждый.
- Конструктор копирования, конструктор перемещения, деструктор, копирующий и перемещающий операторы присваивания;
- Метод **size()**, работающий за O(1);
- Методы **front()** и **back()**, позволяющие получить ссылку на начальный и конечный элемент листа соответственно;
- Метод **сlear()**, который опустошает лист, и метод **empty()**, проверяющий, является ли лист пустым;
- Двунаправленные итераторы, как константные, так и неконстантные, а также reverse-итераторы. При этом нужно не допустить копипасты всего кода итераторов; о том, как этого добиться, см. например [здесь](https://stackoverflow.com/questions/2150192/how-to-avoid-code-duplication-implementing-const-and-non-const-iterators) Reverse-итераторы можно поддержать с помощью *std::reverse_iterator*.
- Методы **begin()**, **end()**, **cbegin()** и **cend()**, реализованные так, чтобы корректно работал код for (const auto& value : lst) для обхода вашего контейнера.
- Методы **insert(const_iterator it, const T&)** и **insert(const_iterator it, T&&)** для вставки элементов в контейнер по итератору, а также **insert(const_iterator it, InputIter frist, InputIter last)** для вставки диапазона.
- Метод **erase** по итератору, а также **erase** от диапазона итераторов.
- Методы **push_back**, **pop_back**, **push_front** и **pop_front**. Разумеется, методы **push_back** и **pop_back** должны корректно обрабатывать как rvalue, так и lvalue.
- Методы **emplace**, **emplace_front** и **emplace_back**, позволяющие сконструировать и вставить по итератору элемент типа T из переданных аргументов, не вызывая для T ни конструктор копирования, ни move-конструктор.
- Метод **reverse**, разворачивающий лист в обратном порядке. Время работы O(n).
- Метод **unique**, который удаляет из контейнера все последовательные дубликаты, то есть все такие элементы x, что x равен предыдущему элементу листа. (См. документацию *std::unique* для лучшего понимания.)
  
  
Вставка в любое место и удаление из любого места одного элемента должны работать за гарантированное O(1) относительно количества элементов. Итераторы на имеющиеся в листе элементы должны не инвалидироваться после любой вставки и после удаления, если это удаление не затрагивает элемент под данным итератором. Для создания листа из элементов типа T тип T не обязан иметь ни конструктор по умолчанию, ни копирующий конструктор. Наличия лишь конструктора перемещения у T должно быть достаточно, чтобы использовать этот тип в контейнере.