#ifndef Value_H_
#define Value_H_

#include "Common.h"

class Value {
  
public:
  
  enum ValueType {
    StringValueType,
    IntValue,
    FloatValue,
    UIntValue,
    BoolValue,
    ArrayValue,
    MapValue,
    NullValue
  };
  
public:
  
  Value();
  
  Value(bool value);
  
  Value(int value);
  
  Value(float value);
  
  Value(unsigned int value);
  
  Value(const String& value);
  
  Value(const char* value);
  
  Value(const Array<Value> value);
  
  Value(const std::map<String, Value> value);
  
public:
  
  String string() const;
  
  int intValue() const;
  
  float floatValue() const;
  
  Array<Value> arrayValue() const;
  
  std::map<String, Value> mapValue() const;
  
  bool boolValue() const;
  
  bool isNull() const;
  
public:
  
  ValueType type() const;
  
private:
  
  int intValue_;
  
  float floatValue_;
  
  unsigned int uintValue_;
  
  String stringValue_;
  
  Array<Value> arrayValue_;
  
  std::map<String, Value> mapValue_;
  
  bool boolValue_;
  
private:
  
  ValueType type_;
  
};

#endif
