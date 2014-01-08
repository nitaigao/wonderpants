#ifndef PlayerState_H_
#define PlayerState_H_

class PlayerState {
  
public:
  
  PlayerState();
  
  void addBonus(int bonus);
  
  void removeBonus(int bonus);
  
  int bonus() const;
  
  int coins() const;
  
private:
  
  int bonus_;
  int coins_;
  
};

#endif
