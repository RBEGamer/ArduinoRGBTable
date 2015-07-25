#include <Adafruit_NeoPixel.h>
#include <Scheduler.h>
#include "Wire.h"
const int led_amount = 15;
const int led_pin = 2;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(led_amount, led_pin, NEO_RGB + NEO_KHZ800);



#define DS1307_I2C_ADDRESS 0x68  // This is the I2C address
// Arduino version compatibility Pre-Compiler Directives
#if defined(ARDUINO) && ARDUINO >= 100   // Arduino v1.0 and newer
  #define I2C_WRITE Wire.write 
  #define I2C_READ Wire.read
#else                                   // Arduino Prior to v1.0 
  #define I2C_WRITE Wire.send 
  #define I2C_READ Wire.receive
#endif


long previousMillis = 0;        // will store last time Temp was updated
byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
byte test;
byte zero;



int nth = 22;
int nthe = 12;
int nthen = 1;
int nthstate = 0;


// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val/10*16) + (val%10) );
}
 
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val/16*10) + (val%16) );
}









int led_blocked_z1 = 0;
int led_blocked_z2 = 0;
int led_blocked_z3 = 0;




int led_can_change[led_amount] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int led_can_change_z1[led_amount] = {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1};
int led_can_change_z2[led_amount] = {0,1,1,1,1,0,0,0,0,0,0,0,0,0,0};
int led_can_change_z3[led_amount] = {0,0,0,0,1,1,1,1,1,1,1,0,0,0,0};

void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();
   Wire.begin();
  pinMode(3, INPUT);
  pinMode(6, INPUT);
    pinMode(7, INPUT);
  Scheduler.startLoop(loop1);
  Scheduler.startLoop(loop2);
Scheduler.startLoop(loop3);
   // for (int i = 0; i < led_amount; i++) {strip.setPixelColor(i,getColor(0,255,0));strip.show();}
   
// setDateDs1307();
 zero=0x00;
}

void loop() {

 getDateDs1307();
  
  

   Serial.print(hour); Serial.print(":"); Serial.print(minute); Serial.print(":");Serial.println(second);
   for (int i = 0; i < led_amount; i++) {
     led_can_change[i] = 1;

  
   if(led_can_change_z1[i] == 1 && led_blocked_z1 == 1){led_can_change[i] = 0;}
   if(led_can_change_z2[i] == 1 && led_blocked_z2 == 1){led_can_change[i] = 0;}
   if(led_can_change_z3[i] == 1 && led_blocked_z3 == 1){led_can_change[i] = 0;}

if(led_can_change[i] == 1){
if(nthstate == 1 && nthen == 1){
strip.setPixelColor(i,getColor(0,0,0));strip.show();//NTH AN
}else{
strip.setPixelColor(i,getColor(255,0,0));strip.show();//NTH AUS
}
}else{
  
  strip.setPixelColor(i, getColor(255,0,255)); strip.show(); //sensor an



}
  



 
 

 
 
 }//ende for
  
  
   
 
  
    yield();
}






void loop1() {
  
  if(digitalRead(3) == HIGH){
    Serial.println("kueche aktiv");
  led_blocked_z1 = 1;
  
  delay(10000);
  }else{
  led_blocked_z1 = 0;
  }
yield();
}


void loop2() {
  if(digitalRead(6) == HIGH){
    Serial.println("alk aktiv");
  led_blocked_z2 = 1;
  delay(60000);
  }else{
  led_blocked_z2 = 0;
  }
yield();
}

void loop3() {
  if(digitalRead(7) == HIGH){
    Serial.println("alk aktiv");
  led_blocked_z3 = 1;
  delay(60000);
  }else{
  led_blocked_z3 = 0;
  }
yield();
}





//get Color (weil R und G vertauscht
uint32_t getColor(int r, int g, int b) {
  return strip.Color(g, r, b);
}






























void setDateDs1307()                
{ 
 
   dayOfWeek = 1;
   dayOfMonth = 1;
   month = 1;
   year= 1;
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   I2C_WRITE(zero);
   I2C_WRITE(decToBcd(0) & 0x7f);    // 0 to bit 7 starts the clock
   I2C_WRITE(decToBcd(36));//m
   I2C_WRITE(decToBcd(22));      // hour If you want 12 hour am/pm you need to set
                                   // bit 6 (also need to change readDateDs1307)
   I2C_WRITE(decToBcd(dayOfWeek));
   I2C_WRITE(decToBcd(dayOfMonth));
   I2C_WRITE(decToBcd(month));
   I2C_WRITE(decToBcd(year));
   Wire.endTransmission();
   

}






int nthswstate = 0;
int nthswstate1 = 0;
void getDateDs1307()
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  I2C_WRITE(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
  // A few of these need masks because certain bits are control bits
  second     = bcdToDec(I2C_READ() & 0x7f);
  minute     = bcdToDec(I2C_READ());
  hour       = bcdToDec(I2C_READ() & 0x3f);  // Need to change this if 12 hour am/pm
  dayOfWeek  = bcdToDec(I2C_READ());
  dayOfMonth = bcdToDec(I2C_READ());
  month      = bcdToDec(I2C_READ());
  year       = bcdToDec(I2C_READ());
  
  
 if(nthen == 1){
//LIEGT DIE ZEIT ZWISCHEN DEN BEIDEN GERENDZEN
if(nth > nthe){
//WENN ANFANG > ALS ENDE
if(hour <= nth && hour <= nthe){
nthstate = 1;
}else if(hour >= nth && hour >= nthe){
nthstate = 1;
}else{
nthstate = 0;
}
}else if (nth < nthe){
  //WENN ANFANG > ALS ENDE
if(hour <= nth && hour >= nthe){
nthstate = 1;
}else if(hour >= nth && hour <= nthe){
nthstate = 1;
}else{
nthstate = 0;
}
}else if( nth == nthe){
  if(hour == nth || hour == nthe){
  nthstate = 1;
  }else{
  nthstate = 0;
  }
}else{
nthstate = 0;
}
}else{
nthstate == 0;
}
/*
if(nthstate == 1 && nthen == 1){

//NACHTMODE AKTIV
 if(nthswstate1 == 0){
mode =nthonmode;
nthswstate = 0;
nthswstate1 = 1;
 }
 
}else{
  if(nthswstate == 0){
  mode = nthoffmode;
  nthswstate = 1;
  nthswstate1 = 0;
  }
  
  //NIGHTAKTIVE
  
}
*/
}



