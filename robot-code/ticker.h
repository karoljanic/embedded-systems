#ifndef TICKER_H
#define TICKER_H

#include <Arduino.h>

class Ticker 
{
  public: 
    Ticker(unsigned long p, void(*fun)(void));
    void check();

  private: 
    unsigned long period;
    unsigned long previousStart;
    void (*trigger)(void);
};

#endif // TICKER_H
