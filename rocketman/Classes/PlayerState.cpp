#include "PlayerState.h"

PlayerState::PlayerState() : bonus_(0), coins_(0) {
  
}

void PlayerState::addBonus(int bonus) {
  coins_ += 1;
  bonus_ += bonus;
}

void PlayerState::removeBonus(int bonus) {
  bonus_ -= bonus;
  bonus_ = (bonus_ < 0) ? 0 : bonus_;
}

int PlayerState::bonus() const {
  return bonus_;
}

int PlayerState::coins() const {
  return coins_;
}