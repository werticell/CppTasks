#include "rational.h"

Rational::Rational() : numerator(0), denominator(1) {}

Rational::Rational(const BigInteger& num) : numerator(num), denominator(1) {}

Rational::Rational(int num) : numerator(num), denominator(1) {}

Rational::Rational(const Rational& other) : numerator(other.numerator), denominator(other.denominator) {
    if(denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    normalize();
}

Rational::Rational(const BigInteger& numerator_other, const BigInteger& denominator_other) : numerator(numerator_other),
                                                                                        denominator(denominator_other) {
    if(denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    normalize();
}


void Rational::normalize() {
    BigInteger tmp = GCD((numerator < 0 ? -numerator : numerator), denominator);
    numerator /= tmp;
    denominator /= tmp;
}

BigInteger Rational::getNumerator() const {
    return numerator;
}
BigInteger Rational::getDenominator() const {
    return denominator;
}


Rational& Rational::operator+=(const Rational& other) {
    Rational tmp(numerator * other.denominator + denominator * other.numerator, denominator * other.denominator);
    *this = tmp;
    return *this;
}

Rational operator+(const Rational& num1, const Rational& num2) {
    Rational temp = num1;
    return temp +=num2;
}

Rational& Rational::operator-=(const Rational& other) {
    Rational tmp(numerator * other.denominator - denominator * other.numerator, denominator * other.denominator);
    *this = tmp;
    return *this;
}

Rational operator-(const Rational& num1, const Rational& num2) {
    Rational temp = num1;
    return temp -=num2;
}

Rational& Rational::operator*=(const Rational& other) {
    Rational tmp(numerator * other.numerator, denominator * other.denominator);
    *this = tmp;
    return *this;
}

Rational operator*(const Rational& num1, const Rational& num2) {
    Rational temp = num1;
    return temp *=num2;
}

Rational& Rational::operator/=(const Rational& other) {
    Rational tmp(numerator * other.denominator, denominator * other.numerator );
    *this = tmp;
    return *this;
}

Rational operator/(const Rational& num1, const Rational& num2) {
    Rational temp = num1;
    return temp /=num2;
}

Rational Rational::operator-() const {
    Rational copy( -numerator, denominator);
    return copy;
}

/***********************************************ArithmeticOperators End************************************************/
/***********************************************ComparisonOperators****************************************************/

bool operator<(const Rational& num1, const Rational& num2) {
    return num1.getNumerator() * num2.getDenominator() < num1.getDenominator() * num2.getNumerator();
}

bool operator>(const Rational& num1, const  Rational& num2) {
    return num2 < num1 ;
}

bool operator==(const Rational& num1, const  Rational& num2) {
    return !(num2 > num1) && !(num1 > num2);
}

bool operator<=(const Rational& num1, const  Rational& num2) {
    return !(num1 > num2);
}
bool operator>=(const Rational& num1, const  Rational& num2) {
    return !(num1 < num2);
}
bool operator!=(const Rational& num1, const Rational&  num2) {
    return (num2 > num1) || (num1 > num2);
}


string Rational::toString() const {
    string result;
    if (numerator == 0) {
        result = '0';
        return result;
    }
    if(denominator == 1)
        result = numerator.toString();
    else
        result = numerator.toString() + '/' + denominator.toString();

    return result;
}

std::ostream& operator<<(std::ostream& output, const Rational& num) {
    string s;
    s = num.toString();
    output << s;
    return output;
}

/***********************************************ComparisonOperators End************************************************/
/***********************************************asDecimal**************************************************************/

string Rational::asDecimal(size_t precision) const {
    Rational copy = *this;
    string result;

    if(copy.numerator == 0) {
        result = '0';
        return result;
    }

    if(!copy.numerator.isPositive()) {
        result = "-";
        copy.numerator = -copy.numerator;
    }
    else
        result = "";

    BigInteger tmp = copy.numerator / copy.denominator;
    result += tmp.toString() + ".";

    copy.numerator %= copy.denominator;
    copy.normalize(); // на это шаге имеем несократимую положительную дробь где numerator < denominator

    while(precision >= 1) {
        copy.numerator *= 10;
        tmp = copy.numerator / copy.denominator;
        result += tmp.toString();

        copy.numerator %= copy.denominator;
        copy.normalize();

        --precision;
    }
    return result;

}


/***********************************************asDecimal End**********************************************************/
/***********************************************Double conversion operator*********************************************/

Rational::operator double() const {
    Rational copy = *this;
    long long temp1 = static_cast<long long>(copy.numerator / copy.denominator);
    copy.numerator %= copy.denominator;
    auto temp2 = static_cast<long long>(copy.numerator );
    auto temp3 = static_cast<long long>(copy.denominator );
    double result = (double)temp1 + (double)temp2/(double)temp3;
    return result;
}

/***********************************************Double conversion End**************************************************/
