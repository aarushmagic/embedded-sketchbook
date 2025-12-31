#include <WiFi.h>
#include "time.h"
#include <TFT_eSPI.h> 

const char* ssid     = ""; 
const char* password = "";

const char* ntpServer = "time.nist.gov"; 
const char* timeZone = "EST5EDT,M3.2.0,M11.1.0"; 
const int targetYear = 2026; 

TFT_eSPI tft = TFT_eSPI(); 

int prevDay = -1, prevHour = -1, prevMin = -1, prevSec = -1;

void setup() {
  Serial.begin(115200);

  tft.init();
  tft.setRotation(0); 
  tft.fillScreen(TFT_BLACK);
  
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.setTextDatum(MC_DATUM); 
  tft.drawString("Connecting to WiFi...", tft.width()/2, 100, 4);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }

  tft.fillScreen(TFT_BLACK);
  tft.drawString("Syncing Clock...", tft.width()/2, 100, 4);
  
  configTime(0, 0, ntpServer); 
  setenv("TZ", timeZone, 1);
  tzset();

  struct tm timeinfo;
  while(!getLocalTime(&timeinfo)){ delay(100); }
  
  tft.fillScreen(TFT_BLACK);
  tft.drawString("2026 COUNTDOWN", tft.width()/2, 40, 2);
  
  tft.setTextColor(TFT_SILVER, TFT_BLACK);
  tft.drawString("DAYS", 40, 180, 2);
  tft.drawString("HRS", 95, 180, 2);
  tft.drawString("MIN", 150, 180, 2);
  tft.drawString("SEC", 205, 180, 2);
}

void loop() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)) return;

  struct tm targetTm = {0};
  targetTm.tm_year = targetYear - 1900; 
  targetTm.tm_mon = 0; targetTm.tm_mday = 1;  
  targetTm.tm_hour = 0; targetTm.tm_min = 0; targetTm.tm_sec = 0;
  targetTm.tm_isdst = -1;

  time_t now = mktime(&timeinfo);
  time_t target = mktime(&targetTm);
  double secondsLeft = difftime(target, now);

  if (secondsLeft > 0) {
    int days = secondsLeft / 86400;
    int hours = ( (int)secondsLeft % 86400 ) / 3600;
    int mins = ( (int)secondsLeft % 3600 ) / 60;
    int secs = (int)secondsLeft % 60;

    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    
    if(days != prevDay) {
        tft.fillRect(10, 100, 60, 50, TFT_BLACK); 
        tft.drawNumber(days, 40, 125, 6); 
        prevDay = days;
    }
    if(hours != prevHour) {
        tft.fillRect(70, 100, 50, 50, TFT_BLACK);
        tft.drawNumber(hours, 95, 125, 6);
        prevHour = hours;
    }
    if(mins != prevMin) {
        tft.fillRect(125, 100, 50, 50, TFT_BLACK);
        tft.drawNumber(mins, 150, 125, 6);
        prevMin = mins;
    }
    if(secs != prevSec) {
        tft.setTextColor(TFT_RED, TFT_BLACK); 
        tft.fillRect(180, 100, 50, 50, TFT_BLACK);
        tft.drawNumber(secs, 205, 125, 6);
        prevSec = secs;
    }

  } else {
     tft.fillScreen(TFT_RED);
     tft.setTextColor(TFT_YELLOW, TFT_RED);
     tft.drawCentreString("HAPPY", tft.width()/2, 80, 4);
     tft.drawCentreString("NEW YEAR!", tft.width()/2, 130, 4);
     delay(1000);
     tft.invertDisplay(true);
     delay(1000);
     tft.invertDisplay(false);
  }
  
  delay(100); 
}