#include "biginteger.h"

class Rational {
public:
    Rational();
    Rational(const BigInteger& num);
    Rational(const BigInteger& numerator, const BigInteger& denominator);
    Rational(int);
    Rational(const Rational&);

    Rational& operator+=(const Rational& other);
    Rational& operator-=(const Rational& other);
    Rational& operator*=(const Rational& other);
    Rational& operator/=(const Rational& other);

    Rational operator-() const;
    explicit operator double() const;

    string toString() const;
    string asDecimal(size_t precision) const;
    BigInteger getNumerator() const;
    BigInteger getDenominator() const ;

private:
    BigInteger numerator;
    BigInteger denominator;

    void normalize();
};

Rational operator-(const Rational& num1, const Rational& num2);
Rational operator+(const Rational& num1, const Rational& num2);
Rational operator*(const Rational& num1, const Rational& num2);
Rational operator/(const Rational& num1, const Rational& num2);

bool operator<(const Rational& num1, const Rational& num2) ;
bool operator>(const Rational& num1, const Rational& num2) ;
bool operator<=(const Rational& num1, const Rational& num) ;
bool operator>=(const Rational& num1, const Rational& num) ;
bool operator==(const Rational& num1, const Rational& num) ;
bool operator!=(const Rational& num1, const Rational& num) ;

std::ostream& operator<<(std::ostream& output, const Rational& num);
