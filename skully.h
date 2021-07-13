#ifndef SKULLY_H
#define SKULLY_H

#include <Watchy.h>
#include "fonts/LcdSolid32pt7b.h"
#include "fonts/LcdSolid23pt7b.h"
#include "fonts/LcdSolid15pt7b.h"
#include "fonts/LcdSolid13pt7b.h"
#include "fonts/LcdSolid11pt7b.h"
#include "fonts/LcdSolid9pt7b.h"
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
