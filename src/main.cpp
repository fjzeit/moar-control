#include <Arduino.h>
#include "TauOfTone.hpp"

TauOfTone board;

void setup()
{
  board.Initialise();
}

void loop()
{
  board.UpdateStatus();
  board.UpdateState();
}
