#include "skully.h"

void Skully::drawWatchFace(){
    display.fillScreen(GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    display.drawBitmap(0, 0, pirate, 200, 200, GxEPD_WHITE);
    drawTime();
    drawWDay();
    drawDate();
    drawSteps();
    //drawTemperature();
    drawBattery();
    for(uint8_t i=0; i<3; i++){
        // Reduce ghosting
        display.display(true);
    }
}

void Skully::drawTime(){
    display.setFont(&GorgeousPixel27pt7b);
    display.setCursor(135, 153);
    if(currentTime.Hour < 10){
        display.print("0");
    }
    display.print(currentTime.Hour);
    display.setCursor(135, 196);
    if(currentTime.Minute < 10){
        display.print("0");
    }
    display.print(currentTime.Minute);
}

void Skully::drawWDay(){
    display.setFont(&GorgeousPixel11pt7b);
    display.setCursor(153, 89);
    String dayOfWeek = dayShortStr(currentTime.Wday);
    dayOfWeek.toUpperCase();
    display.print(String(dayOfWeek));
}

void Skully::drawDate(){
    display.setFont(&GorgeousPixel9pt7b);
    display.setCursor(4, 195);
    String monthStr = String(currentTime.Month);
    String dayStr = String(currentTime.Day);
    monthStr = currentTime.Month < 10 ? "0" + monthStr : monthStr;
    dayStr = currentTime.Day < 10 ? "0" + dayStr : dayStr;
    String dateStr = dayStr + "." + monthStr;
    display.print(String(dateStr));
}

void Skully::drawSteps(){
    display.setFont(&GorgeousPixel9pt7b);
    display.setCursor(143, 107);
    uint32_t stepCount = sensor.getCounter();
    String stepStr = String(stepCount);
    for(int i=1; i<5; i++){
        stepStr = stepCount < pow(10, i) ? "0" + stepStr : stepStr;
    }
    if(currentTime.Hour == 23 && currentTime.Minute == 59){
        sensor.resetStepCounter();
    }
    display.print(String(stepStr));
}

void Skully::drawTemperature(){
    bool Fh;
    Fh = false;
    display.setFont(&LcdSolid8pt7b);
    display.setCursor(2, 182);
    uint8_t temperatureRTC = RTC.temperature() / 4;
    if (Fh == true) {
      temperatureRTC = temperatureRTC * (9/5) + 32;
    }
    if(temperatureRTC < 10){
    display.print("0");
    }
    display.print(temperatureRTC);
    if (Fh == true) {
      display.print("Fh");
    } else {
      display.print("c");
    }
}

void Skully::drawBattery(){
    display.setTextColor(GxEPD_WHITE);
    display.setFont(&LcdSolid9pt7b);
    display.setCursor(188, 17);
    display.print(">");
    display.setCursor(156, 17);
    float BATTV = getBatteryVoltage();
    if(BATTV > 4.10){
        display.print("***");
    }
    else if(BATTV > 3.85 && BATTV <= 4.10){
        display.print(" **");
    }
    else if(BATTV > 3.60 && BATTV <= 3.85){
        display.print("  *");
    }
}
