#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

String inputString = "";
bool engaged = false;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Followers:");
  display.setCursor(0, 30);
  display.print("0");
  display.display();
}

void loop() {
  Serial.println("TT COUNT");
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    if (inChar == '\n') {
      engaged = true;
      int count = inputString.toInt();
      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.print("Followers:");
      display.setCursor(0, 30);
      display.print(count);
      display.display();
      inputString = "";
    } else {
      inputString += inChar;
    }
  }
  delay(500);
}
