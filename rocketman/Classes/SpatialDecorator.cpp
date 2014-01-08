#include "SpatialDecorator.h"

#include "Component.h"
#include "Value.h"

SpatialDecorator::SpatialDecorator(Component* component) : component_(component) { 

}

float SpatialDecorator::x() {
  return component_->attr("x").floatValue();
}

float SpatialDecorator::y() {
  return component_->attr("y").floatValue();
}

int SpatialDecorator::rotation() {
  return component_->attr("rotation").intValue();
}

