#include <iostream>
#include <cmath>
#include <cstring>

class String {
 private:
  char* data_;
  size_t size_;
  size_t capacity_;
  static const size_t INITIAL_SIZE = 4;

  static size_t FindMostSignificantBit(size_t value);
  void Reallocate();

  explicit String(size_t n);
 public:


  String();
  String(const char* other);
  String(size_t n, char c);

  ~String();


  String(const String& other);
  String& operator=(const String& other);

  bool operator==(const String& other) const;

  char & operator[](size_t ind);
  const char & operator[](size_t ind) const;

  [[nodiscard]] size_t length() const;


  void push_back(char symbol);
  void pop_back();


  char & front();
  [[nodiscard]] const char& front() const;
  char & back();
  [[nodiscard]] const char& back() const;

  String& operator+=(const String& other);
  String& operator+=(char symbol);

  friend String operator+(char symbol, const String& str);
  friend String operator+(const String& str, char symbol);
  friend String operator+(const String& str1, const String& str2);

  [[nodiscard]] size_t find(const String& substring) const;
  [[nodiscard]] size_t rfind(const String& substring) const;

  [[nodiscard]] String substr(size_t start, size_t count) const;

  [[nodiscard]] bool empty() const;
  void clear();

};

String operator+(char symbol, const String& str);
String operator+(const String& str, char symbol);
String operator+(const String& str1, const String& str2);

std::istream& operator>>(std::istream& input, String& str);
std::ostream& operator<<(std::ostream& output, const String& str);
