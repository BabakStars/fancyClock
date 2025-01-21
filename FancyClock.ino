//-------------------------Written by: Babak Stars  ---------------------
//------Help taken by:https://randomnerdtutorials.com/tca9548a-i2c-multiplexer-esp32-esp8266-arduino/  -------------
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

const char *ssid     = "YOUR SSID";
const char *password = "YOUR PASSWORD";

const long utcOffsetInSeconds = TIME DIFFERENCE;  // TIME DIFFERENCE *60 *60
 int hou;
 int minutess;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);


// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
  Serial.print(bus);
}

 
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  
  // Start I2C communication with the Multiplexer
  Wire.begin();

  TCA9548A(0);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  } 

  TCA9548A(1);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  } 
  
  // Init OLED display on bus number 2
  
  TCA9548A(2);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  } 
  // Clear the buffer
  display.clearDisplay();

  // Init OLED display on bus number 3
 
  TCA9548A(3);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  } 
  // Clear the buffer
  display.clearDisplay();
  /*
  // Init OLED display on bus number 4
  TCA9548A(4);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  } 
  // Clear the buffer
  display.clearDisplay();

  // Init OLED display on bus number 5
  TCA9548A(5);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  } 
  */
  // Clear the buffer
  display.clearDisplay();

  // Write to OLED on bus number 2
   
  
  // Write to OLED on bus number 4
  
}
void dis() {
  int hd = hou/10;
  int hy = hou%10;

  int md = minutess/10;
  int my = minutess%10;

  TCA9548A(0);
  display.clearDisplay();
  display.setTextSize(8);
  display.setTextColor(WHITE);
  display.setRotation(2);
  display.setCursor(45, 0);
  // Display static text
  display.println(String(my));
  display.display(); 

  TCA9548A(1);
  display.clearDisplay();
  display.setTextSize(8);
  display.setTextColor(WHITE);
  display.setRotation(2);
  display.setCursor(45, 0);
  display.println(String(md));
  display.display();

  TCA9548A(2);
  display.clearDisplay();
  display.setTextSize(8);
  display.setTextColor(WHITE);
  display.setRotation(2);
  display.setCursor(45, 0);
  display.println(String(hy));
  display.display();

  TCA9548A(3);
  display.clearDisplay();
  display.setTextSize(8);
  display.setTextColor(WHITE);
  display.setRotation(2);
  display.setCursor(45, 0);
  display.println(String(hd));
  display.display();
}
 
void loop() {
  timeClient.update();
  
  hou = String(timeClient.getHours()).toInt();
  minutess = String(timeClient.getMinutes()).toInt();
  dis();
  delay(1000);
}
