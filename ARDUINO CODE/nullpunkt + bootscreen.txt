//table_os_bootscreen
#include "Adafruit_NeoPixel.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, 7, NEO_RGB + NEO_KHZ800);


int nullpunkt = 0; //0: oben links, 1: oben rechts, 2: unten links, 3: unten rechts


int feldx = 20, feldy = 10;

//-----------------------------------------------------für bootscreeen + animation-------------------------------------------------------------------------------
int table_os_table_strip[47] = {get_led_number(0, 0), get_led_number(1, 0), get_led_number(1, 1), get_led_number(1, 2), get_led_number(1, 3), get_led_number(1, 4), get_led_number(2, 0), get_led_number(4, 1), get_led_number(4, 2), get_led_number(4, 3), get_led_number(4, 4), get_led_number(5, 0), get_led_number(5, 2), get_led_number(6, 0), get_led_number(6, 2), get_led_number(7, 1), get_led_number(7, 2), get_led_number(7, 3), get_led_number(7, 4), get_led_number(9, 0), get_led_number(9, 1), get_led_number(9, 2), get_led_number(9, 3), get_led_number(9, 4), get_led_number(10, 0), get_led_number(10, 2), get_led_number(10, 4), get_led_number(11, 1), get_led_number(11, 3), get_led_number(13, 0), get_led_number(13, 1), get_led_number(13, 2), get_led_number(13, 3), get_led_number(13, 4), get_led_number(14, 4), get_led_number(15, 4), get_led_number(17, 0), get_led_number(17, 1), get_led_number(17, 2), get_led_number(17, 3), get_led_number(17, 4), get_led_number(18, 0), get_led_number(18, 2), get_led_number(18, 4), get_led_number(19, 0), get_led_number(19, 2), get_led_number(19, 4) };
int table_os_os_strip[32] = {get_led_number(1, 6), get_led_number(1, 7), get_led_number(1, 8), get_led_number(2, 5), get_led_number(2, 9), get_led_number(3, 5), get_led_number(3, 9), get_led_number(4, 6), get_led_number(4, 7), get_led_number(4, 8), get_led_number(6, 6), get_led_number(6, 9), get_led_number(7, 5), get_led_number(7, 7), get_led_number(7, 9), get_led_number(8, 5), get_led_number(8, 8), get_led_number(11, 6), get_led_number(12, 5), get_led_number(12, 6), get_led_number(12, 7), get_led_number(12, 8), get_led_number(12, 9), get_led_number(14, 9), get_led_number(16, 6), get_led_number(16, 7), get_led_number(16, 8), get_led_number(17, 5), get_led_number(17, 9), get_led_number(18, 6), get_led_number(18, 7), get_led_number(18, 8)};
unsigned int table_os_boot_animation_strip[20] = { get_led_number(8, 7), get_led_number(7, 7), get_led_number(6, 6), get_led_number(6, 5), get_led_number(6, 4), get_led_number(6, 3), get_led_number(7, 2), get_led_number(8, 2), get_led_number(9, 2), get_led_number(10, 2), get_led_number(11, 2), get_led_number(12, 2),get_led_number(13, 3), get_led_number(13, 4), get_led_number(13, 5), get_led_number(13, 6),get_led_number(12, 7), get_led_number(11, 7), get_led_number(10, 7), get_led_number(9, 7)};
int table_os_animation_counter = 0;
int table_os_animation_timer = 2;

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


int wheelpos = 0;


void setup() {
  // put your setup code here, to run once:
strip.begin();
draw_debug_information(); //eig unwichtig
//---------------------------------------------------------------------müssen im setup ausgeführt werden (bootscreen)----------------------------------------------
table_os_strip_draw();
table_os_animation();
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 200; i++) {
strip.setPixelColor(i, Wheel(wheelpos));
wheelpos+=6;
strip.show();
}
strip.show();
wheelpos++;
if (wheelpos == 255) {wheelpos = 0; }
delay(50);


}

void draw_debug_information() {
  strip.setPixelColor(get_led_number(0, 0), strip.Color(255, 0, 0));
  strip.show();
  delay(700);
  strip.setPixelColor(get_led_number(0, 0), strip.Color(0, 0, 0));
  strip.setPixelColor(get_led_number(19, 9), strip.Color(255, 0, 0));
  strip.show();
  delay(700);
    strip.setPixelColor(get_led_number(19, 9), strip.Color(0, 0, 0));
      strip.setPixelColor(get_led_number(19, 0), strip.Color(255, 0, 0));
  strip.show();
  delay(700);
    strip.setPixelColor(get_led_number(19, 0), strip.Color(0, 0, 0));
      strip.setPixelColor(get_led_number(0, 9), strip.Color(255, 0, 0));
  strip.show();
  delay(700);
    strip.setPixelColor(get_led_number(0, 9), strip.Color(0, 0, 0));
    strip.show();
    delay(700);
  }

uint32_t Wheel(byte WheelPos) {

  if (WheelPos < 85) {

    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);

  } else if (WheelPos < 170) {

    WheelPos -= 85;

    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);

  } else {

    WheelPos -= 170;

    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);

  }

}

//---------------------------------------------------------------------------bootscreen---------------------------------------------------------------------

void table_os_strip_draw() {
  for (int i = 0; i < 47; i++) {
    strip.setPixelColor(table_os_table_strip[i], strip.Color(255, 0, 0));
    strip.show();
    delay(10);
  }
  for (int i = 0; i < 32; i++) {
    strip.setPixelColor(table_os_os_strip[i], strip.Color(0, 255, 0));
    strip.show();
    delay(100);
  }
  delay(1000);
  clear_screen();
}

void table_os_animation() {
  for (int i = 0; i < 20; i++) {
    strip.setPixelColor(table_os_boot_animation_strip[i], strip.Color(0, 0, 255));
    strip.show();
    delay(50);
    strip.setPixelColor(table_os_boot_animation_strip[i], strip.Color(0, 0, 0));
    strip.show();

  }
  for (int i = 0; i < 18; i++) {
    strip.setPixelColor(table_os_boot_animation_strip[i], strip.Color(0, 0, 255));
    strip.show();
    delay(50);
    strip.setPixelColor(table_os_boot_animation_strip[i], strip.Color(0, 0, 0));
    strip.show();

  }
  delay (400);
  if (table_os_animation_counter == table_os_animation_timer) {
    clear_screen();
    return;
  }
  table_os_animation_counter ++;
  table_os_animation();

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------auf nullpunkt angepasst (siehe vars)---------------------------------------------------------------------------

unsigned int get_led_number(int x, int y) {

  if (y % 2) { //ungerade
    switch (nullpunkt)
    {
      case 0: //oben links
        return (y * feldx) + feldx - 1 - x; //ungerade
      case 1: //oben rechts
        return (y * feldx) + x;
      case 2: //unten links
        return (feldx * feldy) - 1 - 19 - (y * feldx) + x;
      case 3: //unten rechts
        return (feldx * feldy) - 1  - 19 - (y * feldx) + feldx - 1 - x;
    }
  } else { //gerade
    switch (nullpunkt) {
      case 0: //oben links
        return (y * feldx) + x;

      case 1: //oben rechts
        return (y * feldx) + feldx - 1 - x;
      case 2: //unten links
        return (feldx * feldy) - 1 - 19 - (y * feldx) + feldx - 1 - x;
      case 3: //unten rechts
        return (feldx * feldy) - 1 - 19 - (y * feldx) + x;
    }
  }

}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void clear_screen() {

  uint16_t i;

  for (i = 0; i < strip.numPixels(); i++) {

    strip.setPixelColor(i, strip.Color(0, 0, 0));

  }

  strip.show();

}