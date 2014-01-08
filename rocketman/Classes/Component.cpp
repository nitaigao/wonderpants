#include "Component.h"

#include "Value.h"

Component* Component::clone() {
  Component* component = new Component();
  
  component->label_ = label_;
  component->markedForDeletion_ = markedForDeletion_;
  component->attrs_ = attrs_;
  component->attrss_ = attrss_;
  component->type_ = type_;
  
  return component;
}

Component::Component() 
  : markedForDeletion_(false)
  , label_(0) { }

void Component::setStringAttr(const String& key, const Value& value) {
  attrs_[key.hash()] = value;
  attrss_[key] = value;
}

void Component::setAttr(const String& key, const Value& value) {
  attrs_[key.hash()] = value;
  attrss_[key] = value;
}

Value Component::attr(const String& key) const {
  unsigned long hash = key.hash();
  auto result = attrs_.find(hash);
  if (result == attrs_.end()) {
    return Value();
  }
  return (*result).second;
}

std::map<String, Value> Component::attrs() const {
  return attrss_;
}

void Component::setLabel(int label) {
  setAttr("label", label);
  label_ = label;
}

void Component::markForDeletion() {
  markedForDeletion_  = true;
}

bool Component::isMarkedForDeletion() const {
  return markedForDeletion_;
}
