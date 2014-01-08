#ifndef EventHandler_H_
#define EventHandler_H_

#include "IEventHandler.h"

template <class T>
class EventHandler : public IEventHandler {
  
  typedef void (T::*EventFunctor)(const String& event, const Array<Value>& parameters);
  
public:
  
  EventHandler(T* subject, EventFunctor functor)
    : subject_(subject)
    , functor_(functor) 
  { };
  
public:
  
  inline void onEvent(const String& event, const Array<Value>& parameters) {
    (subject_->*functor_)(event, parameters);
  }
  
  inline bool isEqual(T* subject, EventFunctor functor) {
    return subject == subject_ && functor == functor_;
  }
      
private:
  
  T* subject_;
  EventFunctor functor_;
  
};

#endif
