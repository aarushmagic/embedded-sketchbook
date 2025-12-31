#include <WiFi.h>
#include "time.h"
#include <TFT_eSPI.h> 

const char* ssid     = "";
const char* password = "";
const char* ntpServer = "time.nist.gov"; 
const char* timeZone = "EST5EDT,M3.2.0,M11.1.0"; 

const int targetYear = 2026; 

TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite spr = TFT_eSprite(&tft); 

struct Particle {
  float x, y;
  float vx, vy;
  uint16_t color;
  int life;
};

const int MAX_PARTICLES = 100;
Particle particles[MAX_PARTICLES];
bool showFireworks = false;

void spawnFirework(int x, int y) {
  uint16_t color = random(0xFFFF); 
  for(int i=0; i<MAX_PARTICLES; i++) {
    if(particles[i].life <= 0) {
      particles[i].x = x;
      particles[i].y = y;
      float angle = random(0, 360) * (PI/180);
      float speed = random(1, 5);
      particles[i].vx = cos(angle) * speed;
      particles[i].vy = sin(angle) * speed;
      particles[i].color = color;
      particles[i].life = random(20, 50); 
      
      if(random(0,10) > 8) break; 
    }
  }
}

void updateFireworks() {
  for(int i=0; i<MAX_PARTICLES; i++) {
    if(particles[i].life > 0) {
      particles[i].x += particles[i].vx;
      particles[i].y += particles[i].vy;
      particles[i].vy += 0.1; 
      particles[i].life--;
      
      if(particles[i].x > 0 && particles[i].x < 240 && particles[i].y > 0 && particles[i].y < 280) {
        spr.drawPixel((int)particles[i].x, (int)particles[i].y, particles[i].color);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);

  tft.init();
  tft.setRotation(1); 
  tft.fillScreen(TFT_BLACK);
  
  spr.createSprite(280, 240); 
  
  spr.fillSprite(TFT_BLACK);
  spr.setTextColor(TFT_WHITE);
  spr.drawString("Connecting to WiFi...", 10, 100, 4);
  spr.pushSprite(0, 0);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }

  spr.fillSprite(TFT_BLACK);
  spr.drawString("Syncing Atomic Clock...", 10, 100, 4);
  spr.pushSprite(0, 0);
  
  configTime(0, 0, ntpServer); 
  setenv("TZ", timeZone, 1);
  tzset();

  struct tm timeinfo;
  while(!getLocalTime(&timeinfo)){ delay(100); }
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

  spr.fillSprite(TFT_BLACK); 

  if (secondsLeft > 0) {
    int days = secondsLeft / 86400;
    int hours = ( (int)secondsLeft % 86400 ) / 3600;
    int mins = ( (int)secondsLeft % 3600 ) / 60;
    int secs = (int)secondsLeft % 60;

    spr.setTextColor(TFT_WHITE, TFT_BLACK);
    spr.setTextDatum(MC_DATUM);
    spr.drawString("ATLANTA COUNTDOWN", 140, 40, 2);

    uint16_t timeColor = (secondsLeft < 60) ? TFT_RED : TFT_CYAN;
    if (secondsLeft < 10 && (millis() % 500 < 250)) timeColor = TFT_WHITE; 

    spr.setTextColor(timeColor, TFT_BLACK);
    
    char buf[32];
    sprintf(buf, "%02d:%02d:%02d:%02d", days, hours, mins, secs);
    spr.drawString(buf, 140, 120, 7); 
    
    spr.setTextColor(TFT_SILVER, TFT_BLACK);
    spr.drawString("DAYS  HRS  MIN  SEC", 140, 160, 2);

  } else {
    showFireworks = true;
    
    spr.setTextDatum(MC_DATUM);
    spr.setTextColor(TFT_YELLOW, TFT_BLACK);
    spr.drawString("HAPPY NEW YEAR!", 140, 120, 4);
    
    if (random(0, 10) > 8) {
       spawnFirework(random(20, 260), random(20, 220));
    }
    
    updateFireworks();
  }

  spr.pushSprite(0, 0); 
}