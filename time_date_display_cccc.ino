/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-oled-clock
 */

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <U8g2lib.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

RTC_DS3231 rtc;

String time;
String date;
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  Serial.begin(9600);
  u8g2.begin();

  // initialize OLED display with address 0x3C for 128x64
 
       // position to display

  // SETUP RTC MODULE
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    while (true);
  }

  // automatically sets the RTC to the date & time on PC this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  time.reserve(10); // to avoid fragmenting memory when using String
}

void loop() {
  DateTime now = rtc.now();

  time = "";
  time += now.hour();
  time += ':';
  time += now.minute();
  time += ':';
  time += now.second();

  date = "";
  date += now.day();
  date += '/';
  date += now.month();
  date += '/';
  date += now.year();

//  oledDisplayCenter(time);


u8g2.firstPage();
    do {
      u8g2.setFont(u8g2_font_timB10_tr);
  u8g2.setCursor(0, 12);
  u8g2.print("Time");
  u8g2.setFont(u8g2_font_timB10_tr);
  u8g2.setCursor(8, 24);
  u8g2.print(time);

   u8g2.setFont(u8g2_font_timB10_tr);
  u8g2.setCursor(0, 40);
  u8g2.print("Date");
  u8g2.setFont(u8g2_font_timB10_tr);
  u8g2.setCursor(8, 58);
  u8g2.print(date);
    } while ( u8g2.nextPage() );
}
