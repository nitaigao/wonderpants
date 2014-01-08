#ifndef Level_H_
#define Level_H_

#include "Array.h"
#include <map>

class String;
class Component;
class Entity;
class EntityManager;
class IGameView;
class IGameUI;
class Physics;
class EventSystem;
class PlayerState;

class Level {
  
public:
  
  Level();
  
  ~Level();    
  
public:
  
  static Level* level();
  
public:
  
  Level* clone();
  
public:
  
  void addTutorial(const String& tutorial);
  
  int addEntity(Entity* entity);
  
  void addComponent(Component* component);
  
public:
  
  void setup(int attempts, IGameView* view, IGameUI* ui, Physics* physics, EventSystem* eventSystem, PlayerState* playerState);
  
  void setupComponents(int label);
  
  Array<Component*> components(const String& type);
  
  Component* component(const String& type, int label);
  
  void destroyComponents(int label);
  
  void removeComponent(Component* component);
  
public:
  
  void addEntityManager(const String& type, EntityManager* manager);
  
public:
  
  void update(float dt);
    
protected:
  
  Array<String> tutorials_;
  Array<Component*> components_;
  std::map<unsigned long, Array<Component*>* > componentsByType_;
  std::map<unsigned long, Array<Component*>* > componentsByLabel_;
  std::map<String, EntityManager*> entityManagers_;
  
private:
  
  int lastEntityLabel;
  
private:
  
  EntityManager* managerForType(const String& type);
  
private:
  
  Level& operator = (const Level& other) { return *this; }
  Level(const Level& other) { };
  
};

#endif
