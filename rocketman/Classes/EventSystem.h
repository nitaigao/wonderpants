#ifndef EventSystem_H_
#define EventSystem_H_

#include "Common.h"
#include "EventHandler.h"

class Event;
class Value;

class EventSystem {
  
public:
  
  ~EventSystem();
  
public:
  
  void update();
  
public:
  
  template<class T>
  void unsubscribeEvent(const String& type, T* subject, void(T::*eventHandler)(const String& event, const Array<Value>& parameters)) {
    if (eventHandlers_.find(type) == eventHandlers_.end()) return;
    
    for (IEventHandler* ihandler : eventHandlers_[type]) {
      EventHandler<T>* handler = (EventHandler<T>*)ihandler;
      if (handler->isEqual(subject, eventHandler)) {
        eventHandlers_[type].removeObject(handler);
        SAFE_DELETE(handler);
      }
    }
    
    if (!eventHandlers_[type].count()) {
      eventHandlers_.erase(type);
    }
  }
    
  template<class T>
  void subscribeEvent(const String& type, T* subject, void(T::*eventHandler)(const String& event, const Array<Value>& parameters)) { 
    IEventHandler* handler = new EventHandler<T>(subject, eventHandler);
    eventHandlers_[type].addObject(handler);
  };
  
  void postEvent(const String& type);
      
  template<typename... Params>
  void postEvent(const String& type, const Params&... parameters) {
    Array<Value> params;
    unpack(params, parameters...);
    postEventWithParams(type, params);
  }
  
  void postEventWithParams(const String& type, const Array<Value>& parameters);
  
private:
  
  template<typename T, typename... Params>
  void unpack(Array<T>& params, const Value& param, const Params&... parameters) {
    params.addObject(param);
    unpack(params, parameters...);
  }

  template<typename T, typename... Params>
  void unpack(Array<T>& params) { }
  
private:

  typedef std::queue<Event*> EventQueue;
  EventQueue eventQueue_;
  typedef Array<IEventHandler*> EventHandlerList;
  std::map<String, EventHandlerList> eventHandlers_;
  
};

#endif
