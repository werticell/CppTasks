#include <iostream>
#include "biginteger.h"
#include "rational.h"

int main() {
    BigInteger a, b, k;
    b = 0, k = 1234567;
    std::ostream& oss = std::cout;
    oss << b << ' ' << k;
    a = -a;
    cout <<"yessss1";
    std::string testString = a.toString() + " " + (-k).toString();
    oss <<"yessss2";
    oss << testString << std::endl;
    oss <<"yessss2 " <<std::endl;
    a = 999, b = 1000;


    a = a += a;

    testString = a.toString();
    ++a %= a /= a *= a -= b++;
    oss << 5+a << ' ' << 1-b; // 5 -1000
    oss << (a = (bool(a) ? -1 : -2));
    std::cin >> a >> b;
    oss << b << ' ' << a << ' ';
    oss << a+b << ' ' << a-b << ' ' << a*b << ' ' << a/b << ' ' << a%b << '\n';
    std::vector<BigInteger> v;
    for (int i = 0; i <1000 ; ++i) {
        v.push_back(1000 - i);
    }
    oss << v[0] << ' ' << v[500] << ' ' << v[999] << ' ';
    oss << (a != b) << ' ' << (a < b) << ' ' << (a > b) << ' ';
    oss << (a <= b) << ' ' << (a >= b);
    BigInteger c, d, e, f;
    std::istream& iss = std::cin;
    iss >> a >> b;
    oss << b << a;
    iss >> c >> d;
    iss >> e >> f;
    oss << a+b << ' ' << c+d << ' ' << e+f;
    oss << a-b << ' ' << c-d << ' ' << e-f;
    oss << a*b << ' ' << c*d << ' ' << e*f;
    oss << a/b << ' ' << c/d << ' ' << e/f;
    oss << a%b << ' ' << c%d << ' ' << e%f;


    Rational r;
    r = 5;
    r += 3;
    r *= 7; // r==56
    b = 15;
    Rational s = Rational(85)/37, t = Rational(29)/BigInteger(-163);
    s = 4*3*7*13*19*41*43*11;
    t = -17*13*23*79;
    s *= s*s;
    t *= t*t;
    Rational q = s/t;
    if (q.toString() == "-29650611427828166204352/29472131485369") std::cout << 1 << std::endl;
    if (q/1000000000 < 1) std::cout << 2 << std::endl;
    if (0/q == 0) std::cout << 3 << std::endl;
    q *= t/s;

    s = 4*3*7*13*19*41*43*11;
    t = s - 25; // t=402365939
    ((s = 1000000007) *= 1000000009) *= 2147483647;
    if ((s/t).asDecimal(10) == "5337140829307966068.3989202202") std::cout <<4<< std::endl;
    t = -t;
    if ((t/s).asDecimal(25) == "-0.0000000000000000001873662")  std::cout << 5 << std::endl;
}
