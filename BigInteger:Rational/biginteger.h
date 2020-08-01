#include <iostream>
#include <vector>
#include <string>
#pragma once
using std::string;
using std::vector;
using std::cin;
using std::cout;

class BigInteger {
public:
    BigInteger();
    explicit BigInteger(string num);
    BigInteger(int num);
    BigInteger(const BigInteger& num);


    BigInteger& operator+=(const BigInteger& other);
    BigInteger& operator-=(const BigInteger& other);
    BigInteger& operator*=(const BigInteger& other);
    BigInteger& operator/=(const BigInteger& other);
    BigInteger& operator%=(const BigInteger& other);


    BigInteger& operator++();
    const BigInteger operator++(int);
    BigInteger& operator--();
    const BigInteger operator--(int);

    BigInteger operator-() const;

    explicit operator bool() const;
    explicit operator long long() const;

    string toString() const;
    bool isPositive() const;
    bool compare(const BigInteger& num) const;
    BigInteger abs() const;

private:
    vector<int> number; // начиная с 0 нумеруем наименьший разряд
    bool sign;  // знак числа

    bool modulusCompare(const BigInteger& num1, const BigInteger& num2) const;

    void sum(BigInteger& num1, const BigInteger& num2);
    BigInteger subtraction(const BigInteger& num1, const BigInteger& num2);
    BigInteger multiplication(const BigInteger& num1, const BigInteger& num2);
    BigInteger division(const BigInteger& num1, const BigInteger& num2, short int type);
    // деление зависящее от принимаемого типа: type = 0 ->целочисленное, type = 1 с остатком

    void normalize();
    BigInteger karatsuba(const BigInteger& num1, const BigInteger& num2);

};

BigInteger operator-(const BigInteger& num1, const BigInteger& num2);
BigInteger operator+(const BigInteger& num1, const BigInteger& num2);
BigInteger operator*(const BigInteger& num1, const BigInteger& num2);
BigInteger operator/(const BigInteger& num1, const BigInteger& num2);
BigInteger operator%(const BigInteger& num1, const BigInteger& num2);

std::ostream& operator<<(std::ostream& output, const BigInteger& num);
std::istream& operator>>(std::istream& input, BigInteger& num);

bool operator<(const BigInteger& num1, const BigInteger& num2);
bool operator>(const BigInteger& num1, const BigInteger& num2);
bool operator<=(const BigInteger& num1, const BigInteger& num2);
bool operator>=(const BigInteger& num1, const BigInteger& num2);
bool operator==(const BigInteger& num1, const BigInteger& num2);
bool operator!=(const BigInteger& num1, const BigInteger& num2);

BigInteger GCD(BigInteger num1, BigInteger num2);

