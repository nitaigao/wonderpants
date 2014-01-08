#ifndef SAVESTATE_H
#define SAVESTATE_H

class PlayerState;

class SaveState {
  
  
public:
  
  SaveState(int chapterIndex, int levelIndex, int coins, int bonus, int attempts, long time);
  
public:
  
  int level() const;
  int chapter() const;
  int attempts() const;
  int coins() const;
  int bonus() const;
  int score() const;
  
  int chapterIndex() const;
  int levelIndex() const; 
      
  long levelTime() const;
  
private:

  int chapterIndex_;
  int levelIndex_;
  int coins_;
  int bonus_;
  int attempts_;
  long time_;
  
};

#endif
