#include "skully.h"

Skully::Skully(){}

void Skully::drawWatchFace(){
    display.fillScreen(GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.drawBitmap(0, 0, skull, 200, 200, GxEPD_WHITE);
    drawTime();
    drawWDay();
    drawDate();
    drawSteps();
    drawBattery();
    for(uint8_t i=0; i<3; i++){
        display.display(true);
    }
}

void Skully::drawTime(){
    display.setFont(&LcdSolid32pt7b);
    display.setCursor(113, 73);
    if(currentTime.Hour < 10){
        display.print("0");
    }
    display.print(currentTime.Hour);
    display.setCursor(113, 133);
    if(currentTime.Minute < 10){
        display.print("0");
    }
    display.print(currentTime.Minute);
}

void Skully::drawWDay(){
    display.setFont(&LcdSolid13pt7b);
    display.setCursor(5, 170);
    String dayOfWeek = dayShortStr(currentTime.Wday);
    dayOfWeek.toUpperCase();
    display.println(String(dayOfWeek));
}

void Skully::drawDate(){
    display.setFont(&LcdSolid13pt7b);
    display.setCursor(5, 194);
    String monthStr = monthShortStr(currentTime.Month);
    String dayStr = String(currentTime.Day);
    dayStr = currentTime.Day < 10 ? "0" + dayStr : dayStr;
    String dateStr = monthStr + dayStr;
    dateStr.toUpperCase();
    display.print(dateStr);
}

void Skully::drawSteps(){
    display.setFont(&LcdSolid9pt7b);
    display.setCursor(63, 167);
    uint32_t stepCount = sensor.getCounter();
    String stepStr = String(stepCount);
    for(int i=1; i<5; i++){
        stepStr = stepCount < pow(10, i) ? "0" + stepStr : stepStr;
    }
    if(currentTime.Hour == 23 && currentTime.Minute == 59){
        sensor.resetStepCounter();
    }
    display.println(String(stepStr));
}

void Skully::drawBattery(){
    display.setFont(&LcdSolid13pt7b);
    display.setCursor(181, 194);
    display.print(">");
    display.setCursor(136, 194);
    float BATTV = getBatteryVoltage();
    if(BATTV > 4.1){
        display.print("***");
    }
    else if(BATTV > 3.85 && BATTV <= 4.1){
        display.print(" **");
    }
    else if(BATTV > 3.60 && BATTV <= 3.85){
        display.print("  *");
    }
}
