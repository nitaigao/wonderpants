#ifndef Array_H_
#define Array_H_

#include <cstddef>
#include <vector>
#include <algorithm>

template<class T>
class Array {
  
  typedef typename std::vector<T>::const_iterator ConstIterator;
  typedef typename std::vector<T>::iterator Iterator;
  
public:
  
  Array(std::vector<T> data)
    : data_(data) 
  { }
  
  Array(size_t size)
    : data_(std::vector<T>(size)) 
  { }
  
public:
  
  Array() { };
  
private:
  
//  T& operator [](const int index) = delete;
//  T& operator = (const T& other) = delete;
  
public:
  
  Array<T> reverse() const {
    std::vector<T> reversed(data_.size());
    std::reverse_copy(data_.begin(), data_.end(), reversed.begin());
    return reversed;
  }
    
  Array<T> subArray(size_t from, size_t count) const {
    std::vector<T> newArray(count);
    std::copy(data_.begin() + from, data_.begin() + from + count, newArray.begin());
    return newArray;
  }

public:

  size_t indexOf(T obj) const {
    return std::find(data_.begin(), data_.end(), obj) - data_.begin();
  }
  
  size_t count() const {
    return data_.size();
  }

  
public:
  
  ConstIterator begin() const {
    return data_.begin();
  }

  ConstIterator end() const {
    return data_.end();
  }
      
public:
  
  T first() const {
    return data_.front();
  }
  
  T second() const {
    return *(data_.begin() + 1);
  }
  
  T third() const {
    return *(data_.begin() + 2);
  }
  
  T last() const {
    return data_.back();
  }
  
  T objectAtIndex(unsigned int index) {
    return data_[index];
  }
  
public:
  
  static Array<T> fromArray(Array<T> other) {
    std::vector<T> newArray(other.count());
    std::copy(other.begin(), other.end(), newArray.begin());
    return newArray;
  }
  
  template<typename... Params>
  static Array<T> fromObjects(Params... objects) {
    Array<T> array;
    unpack(array, objects...);
    return array;
  }
  
private:
  
  template<typename... Params>
  static void unpack(Array<T>& params, const T& param, const Params&... parameters) {
    params.addObject(param);
    unpack(params, parameters...);
  }
  
  template<typename... Params>
  static void unpack(Array<T>& params) { }

  
public:
  
  void addObject(T obj) {
    data_.push_back(obj);
  }
  
  void removeObject(const T& obj) {
    for (Iterator i = data_.begin(); i != data_.end(); ) {
      if (obj == (*i)) {
        i = data_.erase(i);
      } else {
        ++i;
      }
    }
  }
  
  void removeAllObjects() {
    data_.clear();
  }


private:
  
  std::vector<T> data_;
  
};

#endif
