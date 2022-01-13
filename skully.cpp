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
    display.setFont(&GorgeousPixel30pt7b);
    display.setTextColor(GxEPD_WHITE);
    int16_t  xh1, yh1;
    uint16_t wh1, hh1;
    int16_t  xh2, yh2;
    uint16_t wh2, hh2;
    int16_t  xm1, ym1;
    uint16_t wm1, hm1;
    int16_t  xm2, ym2;
    uint16_t wm2, hm2;
    String h = String(currentTime.Hour);
    String m = String(currentTime.Minute);
    String h1 = String(h.substring(0,1));
    String h2 = String(h.substring(1,2));
    String m1 = String(m.substring(0,1));
    String m2 = String(m.substring(1,2));
    display.getTextBounds(String(h1), 0, 0, &xh1, &yh1, &wh1, &hh1);
    display.getTextBounds(String(h2), 0, 0, &xh2, &yh2, &wh2, &hh2);
    display.getTextBounds(String(m1), 0, 0, &xm1, &ym1, &wm1, &hm1);
    display.getTextBounds(String(m2), 0, 0, &xm2, &ym2, &wm2, &hm2);
    display.setCursor(142 - wh1/2, 145);
    if(currentTime.Hour < 10){
        display.print("0");
        display.setCursor(174 - wh1/2, 145);
        display.print(String(h1));
    } else {
        display.print(String(h1));
        display.setCursor(174 - wh2/2, 145);
        display.print(String(h2));
    }
    display.setCursor(142 - wm1/2, 193);
    if(currentTime.Minute < 10){
        display.print("0");
        display.setCursor(174 - wm1/2, 193);
        display.print(String(m1));
    } else {
        display.print(String(m1));
        display.setCursor(174 - wm2/2, 193);
        display.print(String(m2));
    }
}

void Skully::drawWDay(){
    display.setFont(&GorgeousPixel11pt7b);
    display.setTextColor(GxEPD_BLACK);
    int16_t  x1, y1;
    uint16_t w, h;
    String dayOfWeek = dayShortStr(currentTime.Wday);
    dayOfWeek.toUpperCase();
    display.getTextBounds(String(dayOfWeek), 0, 0, &x1, &y1, &w, &h);
    display.fillRect(186 - w, 46, w + 8, h + 10, GxEPD_WHITE);
    display.setCursor(189 - w, 66);
    display.println(String(dayOfWeek));
}

void Skully::drawSteps(){
    display.setFont(&GorgeousPixel9pt7b);
    display.setTextColor(GxEPD_WHITE);
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
    display.drawRect(186 - w, 71, w + 8, h + 8, GxEPD_WHITE);
    display.setCursor(189 - w, 87);
    display.println(stepStr);
}

void Skully::drawDate(){
    display.setFont(&GorgeousPixel9pt7b);
    display.setTextColor(GxEPD_WHITE);
    display.setCursor(4, 195);
    String monthStr = String(currentTime.Month);
    String dayStr = String(currentTime.Day);
    monthStr = currentTime.Month < 10 ? "0" + monthStr : monthStr;
    dayStr = currentTime.Day < 10 ? "0" + dayStr : dayStr;
    String dateStr = dayStr + "." + monthStr;
    display.print(String(dateStr));
}

void Skully::drawTemperature(){
    display.setFont(&GorgeousPixel8pt7b);
    display.setTextColor(GxEPD_WHITE);
    display.setCursor(4, 179);
    uint8_t temperatureRTC = RTC.temperature() / 4;
    if (settings.weatherUnit == "imperial") {
      temperatureRTC = temperatureRTC * (9/5) + 32;
    }
    if(temperatureRTC < 10){
    display.print("0");
    }
    display.print(temperatureRTC);
    if (settings.weatherUnit == "imperial") {
      display.print("f");
    } else {
      display.print("c");
    }
}

void Skully::drawBattery(){
    float BATTV = getBatteryVoltage() - 3.60;
    int batt_w = constrain(((33.33 * BATTV) + 0.9), 0, 20);
    display.fillRect(168, 5, 28, 12, GxEPD_WHITE);
    display.fillRect(165, 9, 3, 4, GxEPD_WHITE);
    display.fillRect(170, 7, 24, 8, GxEPD_BLACK);
    if (BATTV > 0) {
        display.fillRect(192 - batt_w, 9, batt_w, 4, GxEPD_WHITE);
    }
}
