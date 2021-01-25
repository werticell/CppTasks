#include "myString.h"


size_t String::FindMostSignificantBit(size_t value) {
  size_t tmp = 1;
  size_t msb_index = 0;
  for (uint32_t i = 0; i < sizeof(size_t) * 8; ++i, (tmp <<= 1u)) {
    if ((tmp & value) != 0) {
      msb_index = i;
    }
  }
  return msb_index;
}

String::String() : data_(new char[INITIAL_SIZE]), size_(0), capacity_(INITIAL_SIZE) {
  std::memset(data_, '\0', sizeof(char) * capacity_);
}

String::String(const char *other) {
  size_t other_size = std::strlen(other);
  size_t msb_index = FindMostSignificantBit(other_size);

  capacity_ = 1u << (msb_index + 1);
  size_ = other_size;
  data_ = new char[capacity_];
  std::strcpy(data_, other);
  std::memset(data_ + other_size, '\0', sizeof(char) * (capacity_ - other_size));
}

String::String(size_t n, char c) {
  size_t msb_index = FindMostSignificantBit(n);

  capacity_ = 1u << (msb_index + 1);
  size_ = n;
  data_ = new char[capacity_];
  std::memset(data_, c, sizeof(char) * size_);
  std::memset(data_ + n, '\0', sizeof(char) * (capacity_ - n));
}

String::~String() {
  delete [] data_;
}

String::String(const String &other) : data_(new char[other.capacity_]), size_(other.size_),
                                      capacity_(other.capacity_) {
  std::memcpy(data_, other.data_, sizeof(char) * capacity_);
}

String::String(size_t n) : size_(0) {
  size_t msb_index = FindMostSignificantBit(n);
  capacity_ = 1u << (msb_index + 1);
  data_ = new char[capacity_];
  std::memset(data_, '\0', sizeof(char) * capacity_);
}

String& String::operator=(const String &other) {
  if (this != &other) {
    delete [] data_;
    size_ = other.size_;
    capacity_ = other.capacity_;
    data_ = new char[capacity_];
    std::memcpy(data_, other.data_, sizeof(char) * capacity_);
  }
  return *this;
}

bool String::operator==(const String &other) const {
  return size_ == other.size_ && std::strcmp(data_, other.data_) == 0;
}

void String::Reallocate() {
  char* new_ptr = new char [capacity_ * 2];
  std::memcpy(new_ptr, data_, sizeof(char) * capacity_);
  std::memset(new_ptr + capacity_, '\0', sizeof(char) * capacity_);
  delete [] data_;
  data_ = new_ptr;
  capacity_ *= 2;
}


char & String::operator[](size_t ind) {
  return data_[ind];
}
const char & String::operator[](size_t ind) const {
  return data_[ind];
}

size_t String::length() const {
  return size_;
}


void String::push_back(char symbol) {
  if (size_ == capacity_ - 1) {
    Reallocate();
  }
  data_[size_] = symbol;
  ++size_;
}

void String::pop_back() {
  data_[size_ - 1] = '\0';
  --size_;
}

std::istream& operator>>(std::istream& input, String& str) {
  char new_char;
  str.clear();
  while (!input.eof() && !std::isspace(new_char = input.get()) && std::isalnum(new_char)) {
    str.push_back(new_char);
  }
  while (!input.eof() && (std::isspace(input.peek()) || !std::isalnum(input.peek()))) {
    input.get();
  }
  return input;
}

std::ostream& operator<<(std::ostream& output, const String& str) {
  for (size_t i = 0; i < str.length(); ++i) {
    output << str[i];
  }
  return output;
}

char & String::front() {
  return data_[0];
}

const char& String::front() const {
  return data_[0];
}

char & String::back() {
  return data_[size_ - 1];
}
const char& String::back() const {
  return data_[size_ - 1];
}

bool String::empty() const {
  return size_ == 0;
}

void String::clear() {
  size_ = 0;
  std::memset(data_, '\0', sizeof(char) * capacity_);
}

String& String::operator+=(char symbol) {
  push_back(symbol);
  return *this;
}

String& String::operator+=(const String& other) {
  for (size_t i = 0; i < other.size_; ++i) {
    push_back(other.data_[i]);
  }
  return *this;
}


String operator+(const char symbol, const String& str) {
  String temp (1, symbol);
  temp += str;
  return temp;
}

String operator+(const String& str, char symbol) {
  String temp (str);
  temp += symbol;
  return temp;
}

String operator+(const String& str1, const String& str2) {
  String temp (str1);
  temp += str2;
  return temp;
}

String String::substr(size_t start, size_t count) const {
  String temp(count);
  for (size_t i = start; i < start + count; ++i) {
    temp.push_back(data_[i]);
  }
  return temp;
}

size_t String::find(const String &substring) const {
  char * result = std::strstr(data_, substring.data_);
  return result == nullptr ? size_ : result - data_;
}

size_t String::rfind(const String &substring) const {
  if (substring.size_ > size_) return size_;

  for (int64_t i = static_cast<int64_t>(size_) - substring.size_; i >= 0; --i) {
    bool flag = true;
    for (size_t j = 0; j < substring.size_; ++j) {
      if (data_[i + j] != substring.data_[j]) {
        flag = false;
      }
    }
    if (flag) {
      return i;
    }
  }
  return size_;
}
