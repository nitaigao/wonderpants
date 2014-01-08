#include "Value.h"

#include "Common.h"

Value::Value()
  : type_(NullValue) { }

Value::Value(bool value)
: type_(BoolValue)
, intValue_(0)
, floatValue_(0)
, uintValue_(0)
, boolValue_(value) { }

Value::Value(int value) 
  : type_(IntValue)
  , intValue_(value)
  , floatValue_(0)
  , uintValue_(0)
  , boolValue_(false) { }

Value::Value(float value)
  : type_(FloatValue)
  , intValue_(0)
  , floatValue_(value)
  , uintValue_(0)
  , boolValue_(false) { }

Value::Value(unsigned int value)
  : type_(UIntValue)
  , intValue_(0)
  , floatValue_(0)
  , uintValue_(value)
  , boolValue_(false) { }

Value::Value(const String& value) 
  : type_(StringValueType) {
  stringValue_ = (value);
}

Value::Value(const char* value) 
: type_(StringValueType) {
  stringValue_ = value;
}

Value::Value(const Array<Value> value) 
  : type_(ArrayValue)
  , arrayValue_(value) { }

Value::Value(const std::map<String, Value> value) 
  : type_(MapValue)
  , mapValue_(value) { }

String Value::string() const {
  return stringValue_;
}

int Value::intValue() const {
  return intValue_;
}

float Value::floatValue() const {
  return floatValue_;
}

Array<Value> Value::arrayValue() const {
  return arrayValue_;
}

std::map<String, Value> Value::mapValue() const {
  return mapValue_;
}

Value::ValueType Value::type() const { 
  return type_;
}

bool Value::boolValue() const {
  return boolValue_;
}

bool Value::isNull() const {
  return type_ == NullValue;
}