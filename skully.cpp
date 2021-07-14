#include "skully.h"

Skully::Skully(){}

void Skully::drawWatchFace(){
    display.fillScreen(GxEPD_BLACK);
    display.drawBitmap(0, 0, skull, 200, 200, GxEPD_WHITE);
    drawTime();
    drawWDay();
    drawDate();
    drawSteps();
    drawTemperature();
    drawBattery();
    for(uint8_t i=0; i<3; i++){
        // Reduce ghosting
        display.display(true);
    }
}

void Skully::drawTime(){
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&LcdSolid27pt7b);
    display.setCursor(128, 149);
    if(currentTime.Hour < 10){
        display.print("0");
    }
    display.print(currentTime.Hour);
    display.setCursor(128, 195);
    if(currentTime.Minute < 10){
        display.print("0");
    }
    display.print(currentTime.Minute);
}

void Skully::drawWDay(){
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&LcdSolid9pt7b);
    display.setCursor(158, 103);
    String dayOfWeek = dayShortStr(currentTime.Wday);
    dayOfWeek.toUpperCase();
    display.println(String(dayOfWeek));
}

void Skully::drawDate(){
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&LcdSolid8pt7b);
    display.setCursor(6, 193);
    String monthStr = String(currentTime.Month);
    String dayStr = String(currentTime.Day);
    monthStr = currentTime.Month < 10 ? "0" + monthStr : monthStr;
    dayStr = currentTime.Day < 10 ? "0" + dayStr : dayStr;
    String dateStr = dayStr + "/" + monthStr;
    display.println(String(dateStr));
}

void Skully::drawSteps(){
    display.setTextColor(GxEPD_BLACK);
    display.setFont(&LcdSolid10pt7b);
    display.setCursor(41, 50);
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

void Skully::drawTemperature(){
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&LcdSolid8pt7b);
    display.setCursor(6, 179);
    uint8_t temperatureRTC = RTC.temperature() / 4;
    if(temperatureRTC < 10){
    display.print("0");
    }
    display.print(temperatureRTC);
    display.print("c");
}

void Skully::drawBattery(){
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&LcdSolid9pt7b);
    display.setCursor(188, 16);
    display.print(">");
    display.setCursor(157, 16);
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
