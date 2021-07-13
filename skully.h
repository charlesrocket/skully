#ifndef SKULLY_H
#define SKULLY_H

#include <Watchy.h>
#include "fonts/LcdSolid27pt7b.h"
#include "fonts/LcdSolid10pt7b.h"
#include "fonts/LcdSolid9pt7b.h"
#include "fonts/LcdSolid8pt7b.h"
#include "skull.h"

class Skully : public Watchy{
    public:
        Skully();
        void drawWatchFace();
        void drawTime();
        void drawWDay();
        void drawDate();
        void drawSteps();
        void drawBattery();
};

#endif
