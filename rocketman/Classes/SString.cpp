#include "SString.h"

#include "CCFileUtils.h"
USING_NS_CC;

String::String() { 

};

String::String(const std::string& string) : string_(string) {
  
}

String::String(const char* string) {
  string_ = std::string(string);
}

String String::withFormat(const char* format, ...) {
  va_list args;
  va_start(args, format);
  char buffer[50];
  vsprintf(buffer, format, args);
  va_end(args);
  return String(buffer);
}

String String::fromFile(const String& filename) {
  CCFileData data(filename.c_str(), "rb");
  unsigned char* pBuffer = data.getBuffer();
  return String((char*)pBuffer);
}

std::vector<String> String::split(char delimeter) const {
  using namespace std;
  std::vector<String> lines;
  std::stringstream stringStream(string_);  
  string item;
  while (getline(stringStream, item, delimeter)) {
    lines.push_back(item);
  }
  return lines;  
}

std::vector<String> String::lines() const {
  return split('\n');
}

const char* String::c_str() const {
  return string_.c_str();
}

size_t String::length() const {
  return string_.length();
}

std::string String::str() const {
  return string_;
}

bool String::startsWith(const String& string) const {
  if (string_.length() > 0) {
    return string_.substr(0, 1).compare(string.str()) == 0;
  }
  return false;
}

String String::replace(const String& source, const String& destination) const {
  std::string result = string_;
  std::string::size_type next;
  
  for (next = result.find(source.str()); next != std::string::npos; next = result.find(source.str(), next)) {
    result.replace(next, source.length(), destination.str());
    next += destination.length();
  }
  
  return result;
}

bool String::operator == (const String& other) const {
  return string_.compare(other.string_) == 0;
}

bool String::operator != (const String& other) const {
  return !(*this == other);
}

bool String::operator < (const String& other) const {
  return string_ < other.string_;
}

unsigned long String::hash() const {
  unsigned long hash = 5381;
  int c;
  
  const char* str = c_str();
  
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
  
  return hash;
}

bool String::contains(const String& token) const {
  return string_.find(token.str()) != std::string::npos;
}

float String::toFloat() const {
  return (float)atof(string_.c_str());
}

String String::concat(const String& other) const {
  return String::withFormat("%s%s", c_str(), other.c_str());
}

unsigned char String::charAt(int index) const {
  return string_[index];
}