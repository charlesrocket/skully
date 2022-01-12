#ifndef SKULLY_H
#define SKULLY_H

#include <Watchy.h>
#include "fonts/LcdSolid9pt7b.h"
#include "fonts/GorgeousPixel30pt7b.h"
#include "fonts/GorgeousPixel11pt7b.h"
#include "fonts/GorgeousPixel9pt7b.h"
#include "fonts/GorgeousPixel8pt7b.h"
#include "pirate.h"

class Skully : public Watchy{
    using Watchy::Watchy;
    public:
      void drawWatchFace();
      void drawTime();
      void drawWDay();
      void drawDate();
      void drawSteps();
      void drawTemperature();
      void drawBattery();
};

#endif
