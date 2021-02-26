#include <U8g2lib.h>
#include <SPI.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <WiFiCredentials.h>
const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "LCDTEST";

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ D5 /* A4 */ , /* data=*/ D7 /* A2 */, /* CS=*/ D6 /* A3 */, /* reset=*/ U8X8_PIN_NONE);

#define BACKLIGHT_PIN D9

/*
 Выбор шрифтов:
 6 pixel: u8g2_font_5x7_t_cyrillic
          const uint8_t *fonts6P[5] = {u8g2_font_5x7_mf , u8g2_font_5x7_t_cyrillic , u8g2_font_5x8_t_cyrillic, u8g2_font_courR08_tf , u8g2_font_synchronizer_nbp_tr };
 7 pixel: u8g2_font_haxrcorp4089_t_cyrillic
 8 pixel:
 9 pixel: u8g2_font_6x13_t_cyrillic
 10 pixel: u8g2_font_unifont_t_cyrillic
*/

void setup() {
  Serial.begin(115200);
  u8g2.begin();

  pinMode(BACKLIGHT_PIN, OUTPUT);
  digitalWrite(BACKLIGHT_PIN, HIGH);

  u8g2.setFont(u8g2_font_unifont_t_cyrillic); // choose a suitable font
  u8g2.enableUTF8Print(); 

  /*
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    //digitalWrite(LED_BUILTIN, LOW); //on
    Serial.print(".");
    
    delay(400);
    //digitalWrite(LED_BUILTIN, HIGH); //off
    delay(100);
  }

  Serial.println("");
  Serial.print(F("Connected to "));
  Serial.println(ssid);
  Serial.print(F("IP address: "));
  Serial.println(WiFi.localIP());
  */
}

void loop() {

  //drawScreen1();
  //delay(1000);

  //drawScreen2();
  //delay(1000);
  Serial.print("RSSI: ");
  Serial.println(WiFi.RSSI());
  Serial.print("Quality: ");
  Serial.println(getQuality());

  drawScreen0();
  delay(1000);
  
}

boolean vaneOpen = true;
int ConnectionType = 2;
