#include <WiFi.h>
#include "time.h"
#include <TFT_eSPI.h> 
#include <vector>

const char* ssid     = ""; 
const char* password = "";
const char* ntpServer = "time.nist.gov"; 
const char* timeZone = "EST5EDT,M3.2.0,M11.1.0"; 

const int targetYear = 2026; 

#define C_BLACK      0x0000
#define C_DARK_GREY  0x10A2 
#define C_WHITE      0xFFFF
#define C_CYAN       0x07FF 
#define C_MAGENTA    0xF81F 
#define C_GOLD       0xFEA0 
#define C_RED        0xF800

TFT_eSPI tft = TFT_eSPI(); 
TFT_eSprite canvas = TFT_eSprite(&tft); 

unsigned long lastSyncTime = 0;

struct Particle { float x, y, vx, vy; uint16_t color; int life; };
std::vector<Particle> particles;

void drawLoading(const char* msg);
void syncTime();
void drawCelebration();
void drawFinalMinute(int s);
void drawFinalHour(int s);
void drawStandard(int s);

void setup() {
  Serial.begin(115200);

  tft.init();
  tft.setRotation(0); 
  tft.fillScreen(C_BLACK);
  
  canvas.setColorDepth(8); 
  canvas.createSprite(240, 280);
  
  drawLoading("SYSTEM START");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { 
    drawLoading("WIFI CONNECT..."); 
    delay(100);
  }

  drawLoading("SYNCING CLOCK...");
  syncTime();
}

void syncTime() {
  configTime(0, 0, ntpServer); 
  setenv("TZ", timeZone, 1);
  tzset();
  struct tm timeinfo;
  if(getLocalTime(&timeinfo)){ lastSyncTime = millis(); }
}

void drawLoading(const char* msg) {
  canvas.fillSprite(C_BLACK);
  canvas.setTextDatum(MC_DATUM);
  canvas.setTextColor(C_CYAN, C_BLACK);
  canvas.drawString(msg, 120, 140, 4);
  canvas.pushSprite(0, 0);
}

void loop() {
  if (millis() - lastSyncTime > 3600000) syncTime();

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

  canvas.fillSprite(C_BLACK); 

  if (secondsLeft <= 0) {
    drawCelebration();
  } 
  else if (secondsLeft <= 60) {
    drawFinalMinute((int)secondsLeft);
  } 
  else if (secondsLeft <= 3600) {
    drawFinalHour((int)secondsLeft);
  } 
  else {
    drawStandard((int)secondsLeft);
  }

  canvas.pushSprite(0, 0); 
}

void drawCard(int x, int y, int w, int h, int number, const char* label, uint16_t accentColor) {
  canvas.fillRoundRect(x, y, w, h, 8, C_DARK_GREY);
  
  canvas.drawRoundRect(x, y, w, h, 8, accentColor);
  
  canvas.setTextColor(C_WHITE, C_DARK_GREY);
  canvas.setTextDatum(MC_DATUM);
  
  canvas.drawNumber(number, x + w/2, y + h/2 - 10, 7);
  
  canvas.setTextColor(accentColor, C_DARK_GREY); 
  canvas.drawString(label, x + w/2, y + h - 15, 2);
}

void drawStandard(int s) {
  int hrs = (s % 86400) / 3600;
  int min = (s % 3600) / 60;
  int sec = s % 60;

  canvas.setTextDatum(TC_DATUM);
  canvas.setTextColor(C_CYAN, C_BLACK);
  canvas.drawString("NYE COUNTDOWN", 120, 10, 4);

  drawCard(30, 45, 180, 70, hrs, "HOURS", C_CYAN);
  
  drawCard(30, 125, 180, 70, min, "MINUTES", C_MAGENTA);
  
  drawCard(30, 205, 180, 70, sec, "SECONDS", C_GOLD);
}

void drawFinalHour(int s) {
  int min = (s % 3600) / 60;
  int sec = s % 60;

  uint16_t headerColor = (millis() % 1000 < 500) ? C_RED : C_WHITE;
  
  canvas.setTextDatum(TC_DATUM);
  canvas.setTextColor(headerColor, C_BLACK);
  canvas.drawString("FINAL HOUR", 120, 10, 4);

  drawCard(20, 50, 200, 100, min, "MINUTES", C_WHITE);
  
  drawCard(20, 165, 200, 100, sec, "SECONDS", C_GOLD);
}

void drawFinalMinute(int s) {
  uint16_t color = C_CYAN;
  if(s <= 30) color = C_MAGENTA;
  if(s <= 10) color = C_RED;

  canvas.setTextDatum(MC_DATUM);
  canvas.setTextColor(color, C_BLACK);
  
  canvas.drawNumber(s, 118, 120, 7); 
  canvas.drawNumber(s, 122, 120, 7);
  canvas.drawNumber(s, 120, 120, 7); 
  
  canvas.setTextColor(C_WHITE, C_BLACK);
  canvas.drawString("SECONDS REMAINING", 120, 200, 4);
  
  int barWidth = map(s, 0, 60, 0, 240);
  int startX = (240 - barWidth) / 2; 
  
  canvas.fillRect(startX, 240, barWidth, 15, color);
  canvas.drawRect(0, 240, 240, 15, C_DARK_GREY); 
}

void drawCelebration() {
  canvas.setTextDatum(MC_DATUM);
  canvas.setTextColor(random(0xFFFF), C_BLACK); 
  canvas.drawString("HAPPY", 120, 80, 4);
  canvas.drawString("NEW YEAR!", 120, 120, 4);
  
  canvas.setTextColor(C_GOLD, C_BLACK);
  canvas.drawString("2026", 120, 180, 7);

  if (random(100) < 30) { 
    for (int i = 0; i < 15; i++) {
      Particle p;
      p.x = random(40, 200);
      p.y = random(50, 150);
      float angle = random(0, 360) * 0.0174533; 
      float speed = random(10, 40) / 10.0;
      p.vx = cos(angle) * speed;
      p.vy = sin(angle) * speed;
      p.life = random(10, 30);
      p.color = random(0xFFFF); 
      particles.push_back(p);
    }
  }

  for (int i = particles.size() - 1; i >= 0; i--) {
    Particle &p = particles[i];
    p.x += p.vx;
    p.y += p.vy;
    p.vy += 0.1; 
    p.life--;

    if(p.x > 0 && p.x < 240 && p.y > 0 && p.y < 280) {
      canvas.drawPixel((int)p.x, (int)p.y, p.color);
      canvas.drawPixel((int)p.x+1, (int)p.y, p.color);
      canvas.drawPixel((int)p.x, (int)p.y+1, p.color);
    }

    if (p.life <= 0) particles.erase(particles.begin() + i);
  }
}