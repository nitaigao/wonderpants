#include "SoundDescriptor.h"

#include <stdlib.h>

String SoundDescriptor::sound() const {
  int max = sounds_.size();
  int index = rand() % max;
  return sounds_[index];
}