#ifndef TIMER_H
#define TIMER_H

class Timer {
private:
  unsigned long duration;
  unsigned long count;

public:
  Timer(unsigned long duration);
  void setDuration(unsigned long duration);
  bool isOver();
  void reset();
  void neutralize();
};

#endif