#include "biginteger.h"


BigInteger GCD(BigInteger num1, BigInteger num2) {
    while( num1 != 0 && num2 != 0 )
        (num1 > num2) ? num1 %= num2 : num2 %= num1;
    return num1 + num2;
}


std::istream& operator>>(std::istream& input, BigInteger& num) {
    string s;
    input >> s;
    BigInteger temp(s);
    num = temp;
    return input;
}

std::ostream& operator<<(std::ostream& output, const BigInteger& num) {
    string s;
    s = num.toString();
    output << s;
    return output;
}





BigInteger::BigInteger() : sign(true) {}

BigInteger::BigInteger(string num) {
    for(int i = static_cast<int>(num.size() - 1); i > 0; --i)
        number.push_back(num[i] - '0');

    if(num[0] == '-')
        sign = false;
    else {
        number.push_back(num[0] - '0');
        sign = true;
    }
}

BigInteger::BigInteger(int num) {
    sign = num >= 0;
    if(num == 0)
        number.push_back(0);
    else {
        if(num < 0)
            num *= -1;

        while(num != 0) {
            number.push_back(num % 10);
            num /= 10;
        }
    }

}

BigInteger::BigInteger(const BigInteger& other) {
    sign = other.sign;
    number = other.number;
}


string BigInteger::toString() const {
    string result;
    if(number.empty()){
        result = "";
        return result;
    }
    result = sign ? "" : "-";
    if (number.size() == 1 && number[0] == 0) {
        result = '0';
        return result;
    }
    bool flag = true;

    // необходимо обработать возможные старшие нули появившиеся в результате вычитания
    for (int i = static_cast<int>(number.size() - 1); i >= 0; --i) {
        if (number[i] == 0 && flag)
            continue;
        else {
            flag = false;
            result += number[i] + '0';
        }

    }

    // здесь мы оказались если вдруг нам передали числа вида 00...00 или -00...00
    if (result.empty() || (result[0] == '-' && result.length() == 1))
        result = '0';
    return result;
}






BigInteger& BigInteger::operator+=(const BigInteger& num) {

    if((sign && num.sign) || (!sign && !num.sign)) { // сложение либо двух положительных, либо двух отрицательных чисел
        sum(*this, num);
        return *this;
    }

    if(sign && !num.sign) { // если *this > 0, a num < 0, то это *this - num
        if(modulusCompare(num, *this)) { // если *this больше по модулю
            *this = subtraction(*this, num);
            sign = true;
        }
        else {
            *this = subtraction(num, *this);
            sign = false;
        }
        return *this;
    }

    if(!sign && num.sign) { // если *this < 0,а num > 0, то это num - *this or -(*this - num)
        if(modulusCompare(num, *this)) { // если *this больше по модулю
            *this = subtraction(*this, num);
            sign = false;
        }
        else {
            *this = subtraction(num, *this);
            sign = true;
        }
    }
    return *this;
}

// выполняет сложение двух положительных, либо двух отрицательных чисел и изменяет первое принимаемое значение
void BigInteger::sum(BigInteger& num1, const BigInteger& num2) {
    int num1Size = num1.number.size();
    int num2Size = num2.number.size();
    int remainder = 0;
    for(int i = 0; i <= std::max(num1Size, num2Size) || (remainder > 0); ++i) {
        if(num1Size <= i) //  если первое число окажется меньше не обращаемся к несуществующей памяти
            num1.number.push_back(0);
        num1.number[i] += remainder + ( i < num2Size ? num2.number[i] : 0);
        remainder = num1.number[i] / 10;
        num1.number[i] %= 10;
    }

}

BigInteger operator+(const BigInteger& num1, const BigInteger& num2) {
    BigInteger result = num1;
    return result += num2;
}






// работает корректно только если первое число больше второго
BigInteger BigInteger::subtraction(const BigInteger& num1, const BigInteger& num2) {
    int remainder = 0, num1Size = num1.number.size(), num2Size = num2.number.size();
    BigInteger result;

    for(int i = 0; i < std::max(num1Size, num2Size) || (remainder > 0); ++i) {

        if(i >= num1Size)
            result.number.push_back(0);
        else
            result.number.push_back(num1.number[i]);
        result.number[i] -=  remainder + (i < num2Size ? num2.number[i] : 0) ;
        if(result.number[i] < 0) { // если получили отрицательное число значит необходимо было занять у следующего разряда
            remainder = 1;
            result.number[i] += 10;
        }
        else
            remainder = 0;
    }
    return result;
}

BigInteger& BigInteger::operator-=(const BigInteger& num) {
    if (sign && num.sign) { // если оба числа положительные, то возможно два варианта

        if (*this >= num) { // обычное вычитание
            *this = subtraction(*this, num);
        } else { // вычтем из большего меньшее и поставим отрицательный знак *this
            *this = subtraction(num, *this);
            sign = false;
        }
        return *this;
    }

    if (!sign && !num.sign) { // если оба числа отрицательные, то возможно два варианта (num - *this), где оба положительные

        if (*this >= num) { // в этом случае num >= *this по модулю и результат положительный
            *this = subtraction(num, *this);
            sign = true;
        } else { // в этом случае num <= *this по модулю и результат отрицательный
            *this = subtraction(*this, num);
            sign = false;
        }
        return *this;
    }

    sum(*this, num);
    return *this;
}

BigInteger operator-(const BigInteger& num1, const BigInteger& num2) {
    BigInteger result = num1;
    return result -= num2;
}





bool BigInteger::modulusCompare(const BigInteger& num1 , const BigInteger& num2) const { // <= по модулю
    if(num1.number.size() < num2.number.size())
        return true; // если они положительные, то вернется true, иначе false

    if(num1.number.size() > num2.number.size())
        return false; // если они положительные, то вернется false, иначе true

    for(int i = static_cast<int>(num1.number.size() - 1); i >= 0; --i) {
        if(num1.number[i] < num2.number[i])
            return true;

        if(num1.number[i] > num2.number[i])
            return false;

    }
    return false; // если оказались здесь значит они равны
}

bool BigInteger::compare(const BigInteger& num) const { // если num1 < num2 то возвращает true, иначе false (если num1 == num2 то вернет false)
    // если знаки разные то сравнение очевидно, иначе сравним размеры и поэлементно
    if(sign && !num.sign) // если num1 >= 0 && num2 < 0
        return false;

    if(!sign && num.sign)// если num1 < 0 && num2 >= 0
        return true;

    if((sign && num.sign) || (!sign && !num.sign)) {

        if(number.size() < num.number.size())
            return num.sign; // если они положительные, то вернется true, иначе false

        if(number.size() > num.number.size())
            return !num.sign; // если они положительные, то вернется false, иначе true

        for(int i = static_cast<int>(number.size() - 1); i >= 0; --i) {
            if(number[i] < num.number[i])
                return num.sign;

            if(number[i] > num.number[i])
                return !num.sign;

        }
    }
    return false; // если оказались здесь значит они равны
}

bool operator<(const BigInteger& num1, const BigInteger& num2) {
    return num1.compare(num2);
}

bool operator>(const  BigInteger& num1, const  BigInteger& num2) {
    return num2.compare(num1);
}

bool operator==(const  BigInteger& num1, const  BigInteger& num2) {
    return !(num2 > num1) && !(num1 > num2);
}

bool operator<=(const  BigInteger& num1, const  BigInteger& num2) {
    return !(num1 > num2);
}
bool operator>=(const  BigInteger& num1, const  BigInteger& num2) {
    return !(num1 < num2);
}
bool operator!=(const  BigInteger& num1, const BigInteger&  num2) {
    return (num2 > num1) || (num1 > num2);
}






BigInteger& BigInteger::operator++() {
    return *this += 1;
}

const BigInteger BigInteger::operator++(int) {
    BigInteger tmp = *this;
    ++(*this);
    return tmp;
}

BigInteger& BigInteger::operator--() {
    return *this -= 1;
}

const BigInteger BigInteger::operator--(int) {
     BigInteger tmp = *this;
     --(*this);
     return tmp;
}

BigInteger BigInteger::operator-() const {
    BigInteger copy = *this;
    if (this->number.size() == 1 && this->number[0] == 0)  // если число 0 то у него не должно быть минуса
        copy.sign = true;
    else // иначе нужно поменять знак числа
        copy.sign = !this->sign;
    return copy;
}





BigInteger::operator bool() const {
    return *this != 0;
}

BigInteger::operator long long() const {
    long long result = 0, rank = 1;
    for(const auto& num : number) {
        result += num * rank;
        rank *= 10;
    }
    return result;
}




void BigInteger::normalize() { // убирает ведущие нули и в случае если число имело вид 00...00 делает его просто 0
    int i = static_cast<int>(number.size() - 1);
    while(!number.empty() && number[i] == 0) {
        number.pop_back();
        --i;
    }

    if(number.empty()) {
        number.push_back(0);
        sign = true;
    }
}




BigInteger BigInteger::multiplication(const BigInteger& num1, const BigInteger& num2) {
    BigInteger result;
    size_t length = num1.number.size() + num2.number.size();
    result.sign = (num1.sign == num2.sign);

    result.number.resize(length, 0);

    for(size_t i = 0; i < num1.number.size(); ++i)
        for (size_t j = 0; j < num2.number.size(); ++j)
            result.number[i + j] += num1.number[i] * num2.number[j];

    for(size_t i = 0; i < length; ++i) {
        if (i <= length - 2) // всего возможных разрядов начиная с 0 -> length - 1
            result.number[i + 1] += result.number[i] / 10;
        result.number[i] %= 10;
    }

    result.normalize();
    return result;
}


// число A = A_0 + A_1 * 10^displacement
// число B = B_0 + B_1 * 10^displacement
// тогда формула для их произвдения
// A * B  = A_0 * B_0 + ((A_0 + A_1) * (B_0 + B_1) - A_0 * B_0 - A_1 * B_1) * 10^displacement + A_1 * B_1 * 10 ^(2 * displacement)

BigInteger BigInteger::karatsuba(const BigInteger& num1, const BigInteger& num2) {
    BigInteger result;
    size_t length = num1.number.size() + num2.number.size();
    result.number.resize(length, 0);
    if (num1.number.size() < 32 ||  num2.number.size() < 32) { //если число короче, то выгодно применять обычное умножение

        for(size_t i = 0; i < num1.number.size(); ++i)
            for (size_t j = 0; j < num2.number.size(); ++j)
                result.number[i + j] += num1.number[i] * num2.number[j];
    }
    else {
        size_t displacement = std::max((num1.number.size() + 1) / 2, (num2.number.size() + 1) / 2);

        BigInteger num1Part1; // младшая часть числа num1
        for(size_t i = 0; i < displacement && i < num1.number.size(); ++i)
            num1Part1.number.push_back(num1.number[i] );

        BigInteger num1Part2; // старшая часть числа num1
        if(displacement > num1.number.size()) // если displacement делит число так, что вторая пустая, то присвоим 0
            num1Part2 = 0;
        else
            for(size_t i = displacement; i < num1.number.size(); ++i)
                num1Part2.number.push_back( num1.number[i] );

        BigInteger num2Part1; // младшая часть числа num2
        for(size_t i = 0; i < displacement && i < num2.number.size(); ++i)
            num2Part1.number.push_back( num2.number[i] );

        BigInteger num2Part2; // старшая часть числа num2
        if(displacement > num2.number.size())
            num2Part2 = 0;
        else
            for(size_t i = displacement; i < num2.number.size(); ++i)
                num2Part2.number.push_back( num2.number[i] );

        BigInteger MultiplicationOfSums = karatsuba(num1Part1 + num1Part2, num2Part1 + num2Part2); // произведение сумм частей
        BigInteger FirstConstant = karatsuba(num1Part1, num2Part1); // младший член
        BigInteger ThirdConstant = karatsuba(num1Part2, num2Part2); // старший член

        BigInteger SecondConstant = subtraction(subtraction(MultiplicationOfSums, FirstConstant), ThirdConstant); //разность
        SecondConstant.normalize();

        for(size_t i = 0; i < ThirdConstant.number.size() || i < FirstConstant.number.size() || i < SecondConstant.number.size(); ++i) {
            if(i < FirstConstant.number.size())
                result.number[i] += FirstConstant.number[i];
            if(i < SecondConstant.number.size())
                result.number[i + displacement] += SecondConstant.number[i];
            if(i < ThirdConstant.number.size())
                result.number[i +  displacement * 2] += ThirdConstant.number[i];
        }

    }

    for(size_t i = 0; i < result.number.size(); ++i) {
        if (i <= result.number.size() - 2) // всего возможных разрядов начиная с 0 -> length - 1
            result.number[i + 1] += result.number[i] / 10;
        result.number[i] %= 10;
    }

    result.normalize();
    return result;
}


BigInteger& BigInteger::operator*=(const BigInteger& num) {
    BigInteger tmp = multiplication(*this, num);
    *this = tmp;
    return *this;
}

BigInteger operator*(const BigInteger& num1, const BigInteger& num2) {
    BigInteger result = num1;
    return result *= num2;
}




// работает и с положительными и отрицательными числами
BigInteger BigInteger::division(const BigInteger& num1, const BigInteger& num2, short int type) {
    BigInteger result, current_borrow; // первое число будет являться ответом, второе число - та часть которую на текущий момент занимаем у num1

    result.number.resize(num1.number.size(), 0);
    result.sign = (num1.sign == num2.sign);

    BigInteger absCopy = num2; // для того чтобы умножения были корректны создадим беззнаковую копию num2
    absCopy.sign = true;

    for(int i = static_cast<int>(num1.number.size() - 1); i >= 0; --i) {

        current_borrow.number.insert(current_borrow.number.begin(), 0);
        current_borrow.number[0] = num1.number[i];
        current_borrow.normalize();

        int currentMaxDivisor = 0;
        for(int divisor = 0; divisor <= 9; ++divisor) { // подбираем число умножение на которое даст занятую часть числа num1
            BigInteger tmp = 1;
            tmp = absCopy * divisor;
            if(tmp <= current_borrow) {
                currentMaxDivisor = divisor;
            }
            else
                break;
        }
        result.number[i] = currentMaxDivisor;
        current_borrow -= absCopy * currentMaxDivisor;
    }
    if(type == 0) {
        result.normalize();
        return result;
    }
    current_borrow.normalize(); // если type = 1
    current_borrow.sign = num1.sign;
    return current_borrow;
}


BigInteger& BigInteger::operator/=(const BigInteger& num) {
    BigInteger tmp = division(*this, num, 0);
    *this = tmp;
    return *this;
}

BigInteger operator/(const BigInteger& num1, const BigInteger& num2) {
    BigInteger result = num1;
    return result /= num2;
}




BigInteger& BigInteger::operator%=(const BigInteger& num) {
    BigInteger tmp = division(*this, num, 1);
    *this = tmp;
    return *this;
}

BigInteger operator%(const BigInteger& num1, const BigInteger& num2) {
    BigInteger result = num1;
    return result %= num2;
}


bool BigInteger::isPositive() const {
    return sign;
}

BigInteger BigInteger::abs() const {
    BigInteger temp = (*this);
    temp.sign = true;
    return temp;
}




