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
    display.setCursor(137, 150);
    String h = String(currentTime.Hour);
    String m = String(currentTime.Minute);
    if(currentTime.Hour < 10){
        display.print("0");
        display.setCursor(165, 150);
        display.print(String(h.substring(0,1)));
    } else {
        display.print(String(h.substring(0,1)));
        display.setCursor(165, 150);
        display.print(String(h.substring(1,2)));
    }
    display.setCursor(137, 193);
    if(currentTime.Minute < 10){
        display.print("0");
        display.setCursor(165, 193);
        display.print(String(m.substring(0,1)));
    } else {
        display.print(String(m.substring(0,1)));
        display.setCursor(165, 193);
        display.print(String(m.substring(1,2)));
    }
}

void Skully::drawWDay(){
    display.setFont(&GorgeousPixel11pt7b);
    display.setCursor(151, 69);
    String dayOfWeek = dayShortStr(currentTime.Wday);
    dayOfWeek.toUpperCase();
    display.print(String(dayOfWeek));
}

void Skully::drawSteps(){
    display.setFont(&GorgeousPixel9pt7b);
    display.setCursor(143, 87);
    uint32_t stepCount = sensor.getCounter();
    char stepStr[32];
    itoa(stepCount, stepStr, 10);
    int stepStrL = strlen(stepStr);
    memset(stepStr, '0', 5);
    itoa(stepCount, stepStr + max(5-stepStrL, 0), 10);
    if(currentTime.Hour == 23 && currentTime.Minute == 59){
        sensor.resetStepCounter();
    }
    display.print(stepStr);
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

void Skully::drawTemperature(){
    bool Fh;
    Fh = false;
    display.setFont(&GorgeousPixel8pt7b);
    display.setCursor(4, 179);
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
