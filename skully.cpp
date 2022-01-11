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
    display.setFont(&GorgeousPixel29pt7b);
    display.setCursor(134, 147);
    String h = String(currentTime.Hour);
    String m = String(currentTime.Minute);
    if(currentTime.Hour < 10){
        display.print("0");
        display.setCursor(164, 147);
        display.print(String(h.substring(0,1)));
    } else {
        display.print(String(h.substring(0,1)));
        display.setCursor(164, 147);
        display.print(String(h.substring(1,2)));
    }
    display.setCursor(134, 193);
    if(currentTime.Minute < 10){
        display.print("0");
        display.setCursor(164, 193);
        display.print(String(m.substring(0,1)));
    } else {
        display.print(String(m.substring(0,1)));
        display.setCursor(164, 193);
        display.print(String(m.substring(1,2)));
    }
}

void Skully::drawWDay(){
    display.setFont(&GorgeousPixel11pt7b);
    int16_t  x1, y1;
    uint16_t w, h;
    String dayOfWeek = dayShortStr(currentTime.Wday);
    display.getTextBounds(String(dayOfWeek), 0, 0, &x1, &y1, &w, &h);
    display.drawRect(188 - w, 46, w + 8, h + 10, GxEPD_WHITE);
    display.setCursor(191 - w, 66);
    display.println(String(dayOfWeek));
}

void Skully::drawSteps(){
    display.setFont(&GorgeousPixel9pt7b);
    int16_t  x1, y1;
    uint16_t w, h;
    if(currentTime.Hour == 23 && currentTime.Minute == 59){
        sensor.resetStepCounter();
    }
    uint32_t stepCount = sensor.getCounter();
    char stepStr[32];
    itoa(stepCount, stepStr, 10);
    int stepStrL = strlen(stepStr);
    memset(stepStr, '0', 5);
    itoa(stepCount, stepStr + max(5-stepStrL, 0), 10);
    display.getTextBounds(String(stepStr), 0, 0, &x1, &y1, &w, &h);
    display.drawRect(188 - w, 71, w + 8, h + 8, GxEPD_WHITE);
    display.setCursor(191 - w, 87);
    display.println(stepStr);
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
