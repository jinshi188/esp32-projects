#include <Arduino.h>

#define LED_PIN 2
#define TICK_MS 8
#define KEY_PIN      4
#define DEBOUNCE_MS  25


int      duty  = 0;
int      dir   = +1;
uint32_t tTick = 0;

uint32_t tReport = 0;
uint32_t loops   = 0;
int      keyRaw     = HIGH;
int      keyStable  = HIGH;
uint32_t tKeyChange = 0;
int      pressCount = 0;
int mode = 0;   // 0=呼吸  1=长亮  2=熄灭


void setup() {
  Serial.begin(115200);
  pinMode(KEY_PIN, INPUT_PULLUP);

  ledcSetup(0, 5000, 8);
  ledcAttachPin(LED_PIN, 0);
}

void loop() {
  uint32_t now = millis();

  if (now - tTick >= TICK_MS) {
    tTick = now;
    if (mode == 0) {
      duty += dir;
      if (duty >= 255)      { duty = 255; dir = -1; }
      else if (duty <= 0)   { duty = 0;   dir = +1; }
    } else if (mode == 1) {
      duty = 255;
    } else if (mode == 2) {
      duty = 0;
    }
    duty += dir;
    if (duty >= 255)      { duty = 255; dir = -1; }
    else if (duty <= 0)   { duty = 0;   dir = +1; }
    ledcWrite(0, duty);
  }
int raw = digitalRead(KEY_PIN);
if (raw != keyRaw) {
  keyRaw = raw;
  tKeyChange = now;
}
if ((now - tKeyChange) >= DEBOUNCE_MS && keyStable != keyRaw) {
  keyStable = keyRaw;
  if (keyStable == LOW) {
    pressCount++;
    mode = (mode + 1) % 3;
if (mode == 0) { Serial.println("切到：呼吸"); }
if (mode == 1) { ledcWrite(0, 255); Serial.println("切到：长亮"); }
if (mode == 2) { ledcWrite(0, 0);   Serial.println("切到：熄灭"); }

  }
}

  loops++;
  if (now - tReport >= 1000) {
    tReport = now;
    Serial.printf("%lu 圈/秒\n", (unsigned long)loops);
    loops = 0;
  }
}
