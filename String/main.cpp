#include <iostream>
#include <string>

#include "myString.h"

int main() {
  String str1 (1000, 'x');
  String str2 = "sbcdxax";
  String str_to_find (2, 'x');
  std::cout << str1;
  std::cout << str1.length();
//  str1.push_back('c');
//  String str2;
//  std::string x (5, 'c');
//  std::cin >> x;
//  std::cout << x;

//  std::cout << str1;
//  String str2(str1);
//  std::cout << '\n' << str2;
//
//  std::cin >> str2;
//  String str3;
//  str3 = str2;
//  std::cout << str3;

  return 0;
}
