#include "EventSystem.h"

#include "Common.h"
#include "Event.h"

EventSystem::~EventSystem() {
  while (eventQueue_.size()) {
    Event* event = eventQueue_.front();
    eventQueue_.pop();
    SAFE_DELETE(event);
  }
}

void EventSystem::update() {
  while (eventQueue_.size()) {
    Event* event = eventQueue_.front();
    eventQueue_.pop();
    EventHandlerList handlers = EventHandlerList::fromArray(eventHandlers_[event->type()]);
    for (IEventHandler* handler : handlers) {
      handler->onEvent(event->type(), event->parameters());
    }
    SAFE_DELETE(event);
  } 
}

void EventSystem::postEvent(const String& type) {
  postEventWithParams(type, Array<Value>());
}

void EventSystem::postEventWithParams(const String& type, const Array<Value>& parameters) {
  Event* event = new Event(type, parameters);
  eventQueue_.push(event);
}