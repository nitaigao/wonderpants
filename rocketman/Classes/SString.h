#ifndef String_H_
#define String_H_

#include "Common.h"

class String {
  
public:
  
  String();
  
  String(const std::string& string);
  
  String(const char* string);
  
public:
  
  static String withFormat(const char* format, ...);
  
  static String fromFile(const String& filename);
  
public:
  
  std::vector<String> lines() const;
  
  std::vector<String> split(char delimeter) const;
  
  size_t length() const;
  
  const char* c_str() const;
  
  std::string str() const;
  
  bool startsWith(const String& string) const;
  
  String replace(const String& source, const String& destination) const;
  
  unsigned long hash() const;
  
  bool contains(const String& token) const;
  
  String concat(const String& other) const;
  
  unsigned char charAt(int index) const;
  
public:
  
  float toFloat() const;
  
public:
  
  bool operator == (const String& other) const;
  bool operator != (const String& other) const;
  bool operator < (const String& other) const;
    
private:
  
  std::string string_;
  
  
};

#endif
