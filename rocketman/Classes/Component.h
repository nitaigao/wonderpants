#ifndef Component_H_
#define Component_H_

#include <map>
#include "Value.h"

class String;

class Component {
  
public:
  
  Component();
  
public:
  
  Component* clone();
  
public:

  /* TODO: Find a better design.
   This method exists because the script manager 
   needs the actual string of the attributes to set its globals
   which are set from the attrs() method of the component.
   Normally we would be using hashed keys during the update loop 
   */
  void setStringAttr(const String& key, const Value& value);
  
  void setAttr(const String& key, const Value& value);
  
  Value attr(const String& key) const;
  
public:
  
  void markForDeletion();
  
  bool isMarkedForDeletion() const;
  
public:
  
  inline unsigned long typeHash() const { return type_.hash(); };
  
  inline String type() const { return type_; };
  
  inline void setType(const String& type) { type_ = type; };
  
public:
  
  inline int label() const { return label_; };
  
  void setLabel(int label);  
  
public:
  
  std::map<String, Value> attrs() const;
  
private:
    
  Component& operator = (const Component& other) = delete;
  Component(const Component& other) = delete;
  
private:
  
  std::map<unsigned long, Value> attrs_;
  std::map<String, Value> attrss_;
  String type_;
  int label_;
  bool markedForDeletion_;
  
};

#endif
