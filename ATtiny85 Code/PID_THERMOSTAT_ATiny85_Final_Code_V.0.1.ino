#include <OneWire.h>
#include <DallasTemperature.h>
#include <Tiny4kOLED.h>

#define ONE_WIRE_BUS 3 
#define BUTTON_PIN 4   
#define MOC_PIN 1      

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

int setTemp10 = 220; 
int currentTemp10 = 0;
unsigned long lastMeasureTime = 0;
unsigned long lastButtonTime = 0; 
unsigned long cycleStartTime = 0;
bool screenOn = true;

const unsigned long windowSize = 20000; 
unsigned long onTime = 0; 

// Thermometer Icon (8x8 pixels)
const uint8_t thermometer_icon[] PROGMEM = {
  0b01000100, //   #   #
  0b00101000, //    # # 
  0b00101000, //    # # 
  0b00101000, //    # # 
  0b01010100, //   # # #
  0b01010100, //   # # #
  0b00111000, //    ### 
  0b00000000  
};

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(MOC_PIN, OUTPUT);
  digitalWrite(MOC_PIN, LOW);
  
  sensors.begin();
  oled.begin(128, 32, sizeof(tiny4koled_init_128x32br), tiny4koled_init_128x32br);
  oled.clear();
  oled.setFont(FONT6X8);
  oled.on();

  oled.setCursor(45, 1);
  oled.print(F("ANALOG"));
  delay(2000);
  oled.clear();

  sensors.requestTemperatures();
  currentTemp10 = (int)(sensors.getTempCByIndex(0) * 10);
  sensors.setWaitForConversion(false);
  
  updateDisplay(); 
  lastButtonTime = millis(); 
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    if (!screenOn) { oled.on(); screenOn = true; updateDisplay(); }
    else { setTemp10 += 5; if (setTemp10 > 300) setTemp10 = 180; updateDisplay(); }
    lastButtonTime = millis(); 
    delay(250); 
  }

  if (screenOn && (millis() - lastButtonTime >= 10000)) { oled.off(); screenOn = false; }

  if (millis() - lastMeasureTime >= 2000) {
    currentTemp10 = (int)(sensors.getTempCByIndex(0) * 10);
    sensors.requestTemperatures();
    if (screenOn) updateDisplay(); 
    lastMeasureTime = millis();
  }

  int diff = setTemp10 - currentTemp10;
  bool shouldBeActive = false;

  if (diff <= 0) {
    onTime = 0; 
  } else if (diff >= 15) { 
    onTime = windowSize;
    shouldBeActive = true;
  } else {
    onTime = (windowSize / 15) * diff; 
    shouldBeActive = true;
  }

  unsigned long now = millis();
  if (now - cycleStartTime >= windowSize) cycleStartTime = now;

  bool shouldBeOn = (onTime > (now - cycleStartTime));
  digitalWrite(MOC_PIN, (shouldBeOn && currentTemp10 > -500) ? HIGH : LOW);

  // Show Icon
  if (screenOn) {
    oled.setCursor(115, 3);
    if (shouldBeActive) {
      oled.bitmap(115, 3, 115 + 8, 4, thermometer_icon); 
    } else {
      oled.print(F("   "));
    }
  }
}

void printValue(int val10) {
  oled.print(val10 / 10);
  oled.print(F("."));
  oled.print(val10 % 10);
}

void updateDisplay() {
  oled.setCursor(0, 0); oled.print(F("Now: "));
  if (currentTemp10 < -500) oled.print(F("Err   "));
  else { printValue(currentTemp10); oled.print(F(" C  ")); }

  oled.setCursor(0, 2); oled.print(F("Set: "));
  printValue(setTemp10); oled.print(F(" C  "));
}