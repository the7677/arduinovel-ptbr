#include "timer.h"


Timer::Timer(unsigned long duration) {
  this->duration = duration;
  this->count = 0;
}

void Timer::setDuration(unsigned long duration) {
  this->duration = duration;
}

bool Timer::isOver() {
  return millis() - this->count > this->duration;
}

void Timer::reset() {
  this->count = millis();
}

void Timer::neutralize() {
  this->count -= this->duration;
}