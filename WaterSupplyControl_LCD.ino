#include <U8g2lib.h>
#include <SPI.h>

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ D5 /* A4 */ , /* data=*/ D7 /* A2 */, /* CS=*/ D6 /* A3 */, /* reset=*/ U8X8_PIN_NONE);

#define BACKLIGHT_PIN D9

/*
 Выбор:
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
}

void loop() {

  //drawScreen1();
  //delay(1000);

  //drawScreen2();
  //delay(1000);

  drawScreen0();
  delay(1000);

}

boolean vaneOpen = true;
int ConnectionType = 2;

#define u8g_vaneIco_width 16
#define u8g_vaneIco_height 16
static unsigned char u8g_vaneClose_bits[] = {
0x0c, 0x30, 0x14, 0x28, 0xa4, 0x25, 0x44, 0x22, 0xc4, 0x23, 0x44, 0x22, 0xfc, 0x3f, 0x30, 0x0c, 0x7f, 0xfe, 0xd0, 0x0b, 0x90, 0x09, 0x90, 0x09, 0xd0, 0x0b, 0x70, 0x0e, 0x3f, 0xfc, 0xf0, 0x0f
};
static unsigned char u8g_vaneUnknown_bits[] = {
0x0c, 0x30, 0x10, 0x08, 0x84, 0x21, 0x40, 0x02, 0x84, 0x21, 0x40, 0x02, 0xf4, 0x2f, 0x10, 0x08, 0x9f, 0xf9, 0x50, 0x0a, 0x10, 0x0a, 0x90, 0x09, 0x10, 0x08, 0x90, 0x09, 0x1f, 0xf8, 0xf0, 0x0f
};
static unsigned char u8g_vaneOpen_bits[] = {
0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0xf0, 0x0f, 0x10, 0x08, 0x1f, 0xf8, 0x90, 0x08, 0x90, 0x0b, 0xf8, 0x1f, 0x90, 0x0b, 0x90, 0x08, 0x1f, 0xf8, 0xf0, 0x0f
};
static unsigned char u8g_vaneOpen1_bits[] = {
0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0x80, 0x01, 0xe0, 0x07, 0xf0, 0x0f, 0x1f, 0xf8, 0x90, 0x08, 0x90, 0x0b, 0xf8, 0x1f, 0x90, 0x0b, 0x90, 0x08, 0x1f, 0xf8, 0xf0, 0x0f
};
static unsigned char u8g_vaneClose1_bits[] = {
0x0c, 0x30, 0x14, 0x28, 0xa4, 0x25, 0x44, 0x22, 0xc4, 0x23, 0x44, 0x22, 0xfc, 0x3f, 0xf0, 0x0f, 0x3f, 0xfc, 0x50, 0x0a, 0x90, 0x09, 0x90, 0x09, 0x90, 0x09, 0x50, 0x0a, 0x3f, 0xfc, 0xf0, 0x0f
};
static unsigned char u8g_vaneUnknown1_bits[] = {
0x0c, 0x30, 0x14, 0x28, 0xa4, 0x25, 0x44, 0x22, 0xc4, 0x23, 0x44, 0x22, 0xfc, 0x3f, 0x10, 0x08, 0x9f, 0xf9, 0x50, 0x0a, 0x10, 0x0a, 0x90, 0x09, 0x10, 0x08, 0x90, 0x09, 0x1f, 0xf8, 0xf0, 0x0f
};
//0x0c, 0x30, 0x10, 0x08, 0x84, 0x21, 0x40, 0x02, 0x84, 0x21, 0x40, 0x02, 0xf4, 0x2f, 0x10, 0x08, 0x9f, 0xf9, 0x40, 0x02, 0x10, 0x0a, 0x80, 0x01, 0x10, 0x08, 0x80, 0x01, 0x1f, 0xf8, 0xf0, 0x0f
//0x0c, 0x30, 0x10, 0x08, 0x84, 0x21, 0x40, 0x02, 0x84, 0x21, 0x40, 0x02, 0xf4, 0x2f, 0x10, 0x08, 0x9f, 0xf9, 0x50, 0x0a, 0x10, 0x0a, 0x90, 0x09, 0x10, 0x08, 0x90, 0x09, 0x1f, 0xf8, 0xf0, 0x0f
void drawScreen0() {
  u8g2.clearBuffer();

  drawTankLevel(114, 0);
  drawVent1(5, 2, "Линия", 1);  
  drawVent1(40, 2, "Насос", 0);
  drawVent1(75, 2, "Бак", 2);
  
  drawTankInflow (96, 6, 0, 0);

  drawConnection(0,28, ConnectionType);

  drawPressureLevel (-1,45);
  drawPressureGraph(21,48);

  u8g2.sendBuffer();
}


/*
 * Draw tank inflow
 */
void drawTankInflow(int x0, int y0, float TankInflow, int ETA) {

  u8g2.setFont(u8g2_font_profont10_tr  ); // 6px font

  if (TankInflow < 10)
    u8g2.setCursor(x0+2, y0);
  else
    u8g2.setCursor(x0, y0);
  u8g2.print(TankInflow,0);

  //u8g2.setFont(u8g2_font_p01type_tr ); // 4px font
  // u8g2.setFont(u8g2_font_u8glib_4_tr  ); // 4px
  u8g2.setFont(u8g2_font_tom_thumb_4x6_tr  ); // 5px
  u8g2.drawStr(x0-1,y0+6,"l/m");

  u8g2.drawHLine(x0-2,y0+7,16);
  u8g2.drawPixel(x0+11, y0+6);u8g2.drawPixel(x0+11, y0+5);
  u8g2.drawPixel(x0+11, y0+8);u8g2.drawPixel(x0+11, y0+9);
  u8g2.drawPixel(x0+12, y0+6);u8g2.drawPixel(x0+12, y0+8);
  
  u8g2.setFont(u8g2_font_profont10_tr  ); // 6px font
  if (ETA < 10)
    u8g2.setCursor(x0+2, y0+15);
  else if (ETA < 100)
    u8g2.setCursor(x0, y0+15);
  else
      u8g2.setCursor(x0-3, y0+15);

  if (ETA == 0) 
     u8g2.print("-");
  else if (ETA >= 1000) 
       u8g2.print("999");
  else
    u8g2.print(ETA);
  u8g2.setFont(u8g2_font_tom_thumb_4x6_tr  ); // 5px
  u8g2.drawStr(x0-1,y0+21,"min");
  
}



float pressureData[] = {
1.2, 7.1, 5.4, 0.6, 3.2, 0.2, 5.0, 6.4, 6.5, 4.2, 2.6, 3.1, 5.9, 6.7, 5.5
  };

/*
 * Draw pressure graph
 */
void drawPressureGraph(int x0, int y0) {
  int BarHeight = 16;
  int BarWidth = 2;
  float BarScale = BarHeight / 8.0;
  
  for (int i=0; i< sizeof(pressureData)/sizeof(pressureData[0]); i++) {
    int pressureBarHpx = BarScale * pressureData[i] ;
    u8g2.drawBox(x0 + BarWidth*i, y0 + (BarHeight  - pressureBarHpx), BarWidth, pressureBarHpx);
  }
}


/*
 * Draw pressure level
 */
void drawPressureLevel(int x0, int y0) {
  float PressureLevel = 6.9;

  u8g2.setFont(u8g2_font_haxrcorp4089_t_cyrillic  ); // 7px font

  //u8g2.drawCircle(x0+10, y0+10, 10);
  //u8g2.drawRFrame (x0, y0+2, 19, 18, 3);
  u8g2.setCursor(x0+3, y0+11);
  u8g2.print(PressureLevel,1);

  //u8g2.setFont(u8g2_font_p01type_tr ); // 4px font
  u8g2.setFont(u8g2_font_micro_tr ); // 5px
  u8g2.drawStr(x0+4,y0+18,"bar");
}

/*
 * Draw Connection Type
 */
void drawConnection(int x0, int y0, int ConnectionType) {
  u8g2.setFont(u8g2_font_9x15_t_cyrillic ); // 10px
  
  int framewidth = 110;
  u8g2.drawFrame(x0, y0, framewidth, 18);

  if (ConnectionType == 1) {
    u8g2.setCursor(x0+ ((framewidth - 10 * 9 ) /2) , y0+14);
    u8g2.print("МАГИСТРАЛЬ");
  } else {
    u8g2.setCursor(x0+ ((framewidth - 3 * 9 ) /2) , y0+14);
    u8g2.print("БАК");
  }

}


/*
 * Draw Vent
 */
void drawVent1(int x0, int y0, char* title, int ventStatus) {
  if (ventStatus == 1) {
    u8g2.drawXBM( x0, y0, u8g_vaneIco_width, u8g_vaneIco_height, u8g_vaneOpen_bits);
  } else if (ventStatus == 2) {
    u8g2.drawXBM( x0, y0, u8g_vaneIco_width, u8g_vaneIco_height, u8g_vaneClose_bits);
  } else {
    u8g2.drawXBM( x0, y0, u8g_vaneIco_width, u8g_vaneIco_height, u8g_vaneUnknown_bits);
  }
  u8g2.setFont(u8g2_font_5x7_t_cyrillic ); // 6px
  int sl = strlen (title) / 2; // Unicode?
  
  Serial.print("Title: ");
  Serial.print(title);
  Serial.print(" [");
  Serial.print(sl);
  Serial.print(" ");
  Serial.print(sizeof(title));
  Serial.println("]");
  
  int offset = ( sl * 5 - u8g_vaneIco_width ) / 2;
  Serial.print("Offset: ");
  Serial.println(offset);
  u8g2.setCursor(x0-offset,y0+23);
  u8g2.print(title);

}



/*
 * Draw Tank Level
 */
void drawTankLevel(int x0, int y0) {
  int FillPercent =30;
  
  int FullHeight = 56;
  int FillHeight = FullHeight * FillPercent / 100;

  u8g2.setFont(u8g2_font_profont10_tr  ); // 6px
  u8g2.setCursor(x0-1, y0+6); 
  u8g2.print(FillPercent);
//  u8g2.setCursor(124, 63);
//  u8g2.print("%");
  u8g2.setFont(u8g2_font_5x7_t_cyrillic   ); // 6px font
  u8g2.drawStr(x0+10,y0+6,"%");

  u8g2.drawFrame(x0, y0 + 7, 14, FullHeight);
  u8g2.drawBox(x0, FullHeight - FillHeight + 7, 14, FillHeight);
}


void drawScreen1() {
  u8g2.clearBuffer();
  
  u8g2.drawFrame(0,0,128,31); 
  
  u8g2.setFont(u8g2_font_haxrcorp4089_t_cyrillic); // choose a suitable font
  u8g2.setCursor(3, 12);
  u8g2.print("WATER SUPPLY. Версия 1.0");
  u8g2.setCursor(28, 24);
  u8g2.print("2021/02/22");

  u8g2.sendBuffer();
  
}

void drawScreen2() {
  //u8g2.clearBuffer();
  
  u8g2.drawFrame(0,33,128,31); 
  
  u8g2.setFont( u8g2_font_5x7_t_cyrillic ); // choose a suitable font
  u8g2.drawStr(3,43,"WATER SUPPLY CONTROL");
  u8g2.drawStr(3,53,"1.01");
  u8g2.drawStr(28,53,"2021/02/22");

  u8g2.sendBuffer();
  
}
