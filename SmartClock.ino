/*This will print the time in below format on oled 4 pin monochrome i2c display.
 *   2019-06-17T19:50:00-07:00[America/Los_Angeles]
 */
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <AceTime.h>

using namespace ace_time;
using namespace ace_time::clock;

// ZoneProcessor instance should be created statically at initialization time.
static BasicZoneProcessor pacificProcessor;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

static SystemClockLoop systemClock(nullptr /*reference*/, nullptr /*backup*/);

int currentYear = 2019;
int currentMonth = 1;
int currentDay = 1;
int currentHour = 18;
int currentMinute = 3;
int currentSecond = 5;

void setup() {
  #if ! defined(UNIX_HOST_DUINO)
    delay(1000);
  #endif

  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  
  systemClock.setup();

  // Creating timezones is cheap, so we can create them on the fly as needed.
  auto pacificTz = TimeZone::forZoneInfo(&zonedb::kZoneAmerica_Los_Angeles,
      &pacificProcessor);

  // Set the SystemClock using these components.
  auto pacificTime = ZonedDateTime::forComponents(
      currentYear, currentMonth, currentDay, currentHour, currentMinute, currentSecond, pacificTz);
  systemClock.setNow(pacificTime.toEpochSeconds());
}

void refreshDisplay()
{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
}

void printCurrentTime() {
  acetime_t now = systemClock.getNow();

  // Create Pacific Time and print.
  auto pacificTz = TimeZone::forZoneInfo(&zonedb::kZoneAmerica_Los_Angeles,
      &pacificProcessor);
  auto pacificTime = ZonedDateTime::forEpochSeconds(now, pacificTz);

  refreshDisplay();
  pacificTime.printTo(display);
  display.println();
  display.display();
}

void loop() {
  static acetime_t prevNow = systemClock.getNow();
  systemClock.loop();
  acetime_t now = systemClock.getNow();
  if (now - prevNow >= 1) {
    printCurrentTime();
    prevNow = now;
  }
}
