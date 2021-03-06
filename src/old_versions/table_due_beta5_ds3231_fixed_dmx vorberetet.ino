#include <Adafruit_NeoPixel.h>
#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "Wire.h"
#include <DueFlashStorage.h>

DueFlashStorage dueFlashStorage;
// CHANGE THIS TO YOUR OWN UNIQUE VALUE
static uint8_t mac[6] = { 0x02, 0xAA, 0xBB, 0xCC, 0x00, 0x22 };


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
const int relais = 35;
const int fan = 37;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, 33, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel standby_strip = Adafruit_NeoPixel(1, 31, NEO_RGB + NEO_KHZ800);
//FÜR SERVER << "";
 template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }
#define PREFIX ""
WebServer webserver(PREFIX, 80);

int fillred = 0;            //integer for red darkness
int fillblue = 0;           //integer for blue darkness
int fillgreen = 0;          //integer for green darkness

int fan_state = 0;

int mode = 5; // MODE 5 = off
int rainbowspeed = 50;
int randomspeed = 10;
int randommode = 0; // 0-1
int rainbowmode = 0; // 0 oder 1
int randomefmode = 0;
int standby_strip_state = 0; //FÜR DIE STANDBYLED
 

IPAddress ip(192,168,178, 210);
IPAddress gateway(192,168,178, 1);
IPAddress subnet(255, 255, 255, 0);

const int use_ethernet = 1, enable_dhcp = 1,wait_for_DHCP = 0;
//CLOCK VARS



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

int clockcolormode = 0;
int clock_h_color;
int clock_m_color;
int clock_fix_color_h = 0;
int clock_fix_color_m = 0;
int clock_bright = 255;


int h_z = 0;
int h_e = 0; 
byte binwert_h_z;
byte binwert_h_e;

 int m_z = 0;
int m_e = 0; 
byte binwert_m_z;
byte binwert_m_e;

unsigned int localPort = 8888;      // local port to listen for UDP packets
IPAddress timeServer(132, 163, 4, 103);
const int NTP_PACKET_SIZE= 48; // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets 
// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
//hir ist die zeit die vom server gehot wurde
int ntph = 0;
int ntpm = 0;
int ntps = 0;

unsigned int zeitverschiebung = 2; //zeit um 2 stunden nach vorne verschieben


int clock_color_counter = 0;
int clock_color_speed = 50;



int nth = 22;
int nthe = 7;
int nthen = 1;
int nthstate = 0;
int nthonmode = 1;
int nthoffmode = 6;


int number_template_0[4][7];
int number_template_1[4][7];
int number_template_2[4][7];
int number_template_3[4][7];
int number_template_4[4][7];
int number_template_5[4][7];
int number_template_6[4][7];
int number_template_7[4][7];
int number_template_8[4][7];
int number_template_9[4][7];
int number_template_nothing[4][7];
int time1[4][7]; // 0 oder 1 (0 = nicht gesetzt)
int time2[4][7];
int time3[4][7];
int time4[4][7];
int time1_anchor[2] = {16,2}; // HZ
int time2_anchor[2] = {11,2}; //HE
int time3_anchor[2] = {5,2};// MZ
int time4_anchor[2] = {0,2};// ME
int template_buffer_array[4][7];
int clock_orientation = 1;
int tmp_hz,tmp_he, tmp_mz,tmp_me;
int x = 0,y = 0;
int _value;
//CLOCK VARS ENDE
void clock_copy_arr(int value, int time_array){
  
    
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 7; j++){
      switch (value) {
  case 0:template_buffer_array[i][j] =number_template_0[i][j];break;
  case 1:template_buffer_array[i][j] =number_template_1[i][j];break;
  case 2:template_buffer_array[i][j] =number_template_2[i][j];break;
  case 3:template_buffer_array[i][j] =number_template_3[i][j];break;
  case 4:template_buffer_array[i][j] =number_template_4[i][j];break;
  case 5:template_buffer_array[i][j] =number_template_5[i][j];break;
  case 6:template_buffer_array[i][j] =number_template_6[i][j];break;
  case 7:template_buffer_array[i][j] =number_template_7[i][j];break;
  case 8:template_buffer_array[i][j] =number_template_8[i][j];break;
  case 9:template_buffer_array[i][j] =number_template_9[i][j];break;
  case 10: template_buffer_array[i][j] =number_template_nothing[i][j];break;
  default: template_buffer_array[i][j] =number_template_nothing[i][j];break;    
}//ENDE CASE


  switch (time_array) {
  case 1:time1[i][j] = template_buffer_array[i][j];break;
  case 2:time2[i][j] = template_buffer_array[i][j];break;
  case 3:time3[i][j] = template_buffer_array[i][j];break;
  case 4:time4[i][j] = template_buffer_array[i][j];break;
  default:break; 
    // Befehle
}//ENDE CASE    
  }//ENDE J
}//ENDE I


  
}





// send an NTP request to the time server at the given address 
unsigned long sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE); 
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49; 
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp: 		   
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  Udp.endPacket(); 
}



void get_ntp_time()
{
  sendNTPpacket(timeServer); // send an NTP packet to a time server

    // wait to see if a reply is available
  delay(1000);  
  if ( Udp.parsePacket() ) {  
    // We've received a packet, read the data from it
    Udp.read(packetBuffer,NTP_PACKET_SIZE);  // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;  
    //Serial.print("Seconds since Jan 1 1900 = " );
    //Serial.println(secsSince1900);               

    // now convert NTP time into everyday time:
    //Serial.print("Unix time = ");
    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;     
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;  
    // print Unix time:
    Serial.println(epoch);                               


  
   
    ntph=(epoch  % 86400L) / 3600; // print the hour (86400 equals secs per day) 
    ntpm=(epoch  % 3600) / 60; // print the minute (3600 equals secs per minute) 
    ntps = 0;
    Serial.print("NTP:");Serial.print(ntph);Serial.print(":");Serial.println(ntpm);
    //Serial.println(epoch %60); // print the second
    
    
    
    
    
    
   //hier die zeitverschiebung beachten
   ntph  = ntph+zeitverschiebung;
   if(ntph == 24){
   ntph = 0;
   }if(ntph > 24){
   
   ntph = ntph -24;
   }
   
   
   
   dayOfWeek = 1;
   dayOfMonth = 1;
   month = 1;
   year= 1;
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   I2C_WRITE(zero);
   I2C_WRITE(decToBcd(ntps) & 0x7f);    // 0 to bit 7 starts the clock
   I2C_WRITE(decToBcd(ntpm));
   I2C_WRITE(decToBcd(ntph));      // If you want 12 hour am/pm you need to set
                                   // bit 6 (also need to change readDateDs1307)
   I2C_WRITE(decToBcd(dayOfWeek));
   I2C_WRITE(decToBcd(dayOfMonth));
   I2C_WRITE(decToBcd(month));
   I2C_WRITE(decToBcd(year));
   Wire.endTransmission();
   

    
    
    
    
  }
  // wait ten seconds before asking for the time again






}


void setDateDs1307()                
{ 
  get_ntp_time();
second = ntps;
   minute = ntpm;
   //hier die zeitverschiebung beachten
   hour  = ntph+zeitverschiebung;
   if(hour == 24){
   hour = 0;
   }if(hour > 24){
   
   hour = hour -24;
   }
   dayOfWeek = 1;
   dayOfMonth = 1;
   month = 1;
   year= 1;
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   I2C_WRITE(zero);
   I2C_WRITE(decToBcd(second) & 0x7f);    // 0 to bit 7 starts the clock
   I2C_WRITE(decToBcd(minute));
   I2C_WRITE(decToBcd(hour));      // If you want 12 hour am/pm you need to set
                                   // bit 6 (also need to change readDateDs1307)
   I2C_WRITE(decToBcd(dayOfWeek));
   I2C_WRITE(decToBcd(dayOfMonth));
   I2C_WRITE(decToBcd(month));
   I2C_WRITE(decToBcd(year));
   Wire.endTransmission();
   
   delay(1000);
   
  get_ntp_time();
}




void display_clock(int hz = 0, int he  = 0, int mz  = 0, int me = 0){

//clear_screen();
  
  

//strip.Color(0, 0, 0)
if(clockcolormode == 0){
  if(clock_color_counter >= 256){
clock_color_counter = 0;
}else{
clock_color_counter++;
}
clock_h_color = Wheel(clock_color_counter);
clock_m_color = Wheel(256-clock_color_counter);
}else if(clockcolormode == 1){

  if(clock_fix_color_h == 0){ 
   clock_h_color =  strip.Color(clock_bright, 0, 0);
  }else  if(clock_fix_color_h == 1){
  clock_h_color =  strip.Color(0, clock_bright, 0);
  }else  if(clock_fix_color_h == 2){
  clock_h_color =  strip.Color(0, 0, clock_bright);
  }else  if(clock_fix_color_h == 3){
  clock_h_color =  strip.Color(0, clock_bright, clock_bright);
   }else  if(clock_fix_color_h == 4){
  clock_h_color =  strip.Color(clock_bright, 0, clock_bright);
   }else  if(clock_fix_color_h == 5){
  clock_h_color =  strip.Color(clock_bright, clock_bright, 0);
  }else{
  clock_h_color =  strip.Color(0, 0, 255);
  }
  
  
  
    if(clock_fix_color_m == 0){ 
   clock_m_color =  strip.Color(clock_bright, 0, 0);
  }else  if(clock_fix_color_m == 1){
  clock_m_color =  strip.Color(0, clock_bright, 0);
  }else  if(clock_fix_color_m == 2){
  clock_m_color =  strip.Color(0, 0, clock_bright);
  }else  if(clock_fix_color_m == 3){
  clock_m_color =  strip.Color(0, clock_bright, clock_bright);
   }else  if(clock_fix_color_m == 4){
  clock_m_color =  strip.Color(clock_bright, 0, clock_bright);
   }else  if(clock_fix_color_m == 5){
  clock_m_color =  strip.Color(clock_bright, clock_bright, 0);
  }else{
  clock_m_color =  strip.Color(0, 0, 255);
  }
  
  
  
}else{
clockcolormode = 0;
}

  clock_copy_arr(hz, 1);
  clock_copy_arr(he, 2);
  clock_copy_arr(mz, 3);
  clock_copy_arr(me, 4);

  
    for (int i = 0; i < 4; i++){
    for (int j = 0; j < 7; j++){       
      if(clock_orientation == 1){
      if(time1[3-i][6-j] == 1){    
        strip.setPixelColor(get_led_number(i+time1_anchor[0],j+time1_anchor[1]),  clock_h_color); 
      }else{    
      strip.setPixelColor(get_led_number(i+time1_anchor[0],j+time1_anchor[1]),  strip.Color(0, 0, 0)); 
      }  
    }else if(clock_orientation == 0){
      if(time1[i][j] == 1){    
        strip.setPixelColor(get_led_number(i+time1_anchor[0],j+time1_anchor[1]),  clock_h_color); 
      }else{    
      strip.setPixelColor(get_led_number(i+time1_anchor[0],j+time1_anchor[1]),  strip.Color(0, 0, 0)); 
      }  
    }   
    }}
    
    
        for (int i = 0; i < 4; i++){
    for (int j = 0; j < 7; j++){       
      if(clock_orientation == 1){
      if(time2[3-i][6-j] == 1){    
        strip.setPixelColor(get_led_number(i+time2_anchor[0],j+time2_anchor[1]),  clock_h_color); 
      }else{    
      strip.setPixelColor(get_led_number(i+time2_anchor[0],j+time2_anchor[1]),  strip.Color(0, 0, 0)); 
      }  
    }else if(clock_orientation == 0){
      if(time2[i][j] == 1){    
        strip.setPixelColor(get_led_number(i+time2_anchor[0],j+time2_anchor[1]),  clock_h_color); 
      }else{    
      strip.setPixelColor(get_led_number(i+time2_anchor[0],j+time2_anchor[1]),  strip.Color(0, 0, 0)); 
      }  
    }   
    }}
    
    
      for (int i = 0; i < 4; i++){
    for (int j = 0; j < 7; j++){       
      if(clock_orientation == 1){
      if(time3[3-i][6-j] == 1){    
        strip.setPixelColor(get_led_number(i+time3_anchor[0],j+time3_anchor[1]),  clock_m_color); 
      }else{    
      strip.setPixelColor(get_led_number(i+time3_anchor[0],j+time3_anchor[1]),  strip.Color(0, 0, 0)); 
      }  
    }else if(clock_orientation == 0){
      if(time3[i][j] == 1){    
        strip.setPixelColor(get_led_number(i+time3_anchor[0],j+time3_anchor[1]),  clock_m_color); 
      }else{    
      strip.setPixelColor(get_led_number(i+time3_anchor[0],j+time3_anchor[1]),  strip.Color(0, 0, 0)); 
      }  
    }   
    }}  
      
    for (int i = 0; i < 4; i++){
    for (int j = 0; j < 7; j++){       
      if(clock_orientation == 1){
      if(time4[3-i][6-j] == 1){    
        strip.setPixelColor(get_led_number(i+time4_anchor[0],j+time4_anchor[1]),  clock_m_color); 
      }else{    
      strip.setPixelColor(get_led_number(i+time4_anchor[0],j+time4_anchor[1]),  strip.Color(0, 0, 0)); 
      }  
    }else if(clock_orientation == 0){
      if(time4[i][j] == 1){    
        strip.setPixelColor(get_led_number(i+time4_anchor[0],j+time4_anchor[1]),  clock_m_color); 
      }else{    
      strip.setPixelColor(get_led_number(i+time4_anchor[0],j+time4_anchor[1]),  strip.Color(0, 0, 0)); 
      }  
    }   
    }}
    strip.show();
    delay(clock_color_speed);

}


void clock_create_template(){
  
    // NOTHING
  number_template_nothing[0][0]=0;number_template_nothing[1][0]=0;number_template_nothing[2][0]=0;number_template_nothing[3][0]=0;
  number_template_nothing[0][1]=0;number_template_nothing[1][1]=0;number_template_nothing[2][1]=0;number_template_nothing[3][1]=0;
  number_template_nothing[0][2]=0;number_template_nothing[1][2]=0;number_template_nothing[2][2]=0;number_template_nothing[3][2]=0;
  number_template_nothing[0][3]=0;number_template_nothing[1][3]=0;number_template_nothing[2][3]=0;number_template_nothing[3][3]=0;
  number_template_nothing[0][4]=0;number_template_nothing[1][4]=0;number_template_nothing[2][4]=0;number_template_nothing[3][4]=0;
  number_template_nothing[0][5]=0;number_template_nothing[1][5]=0;number_template_nothing[2][5]=0;number_template_nothing[3][5]=0;
  number_template_nothing[0][6]=0;number_template_nothing[1][6]=0;number_template_nothing[2][6]=0;number_template_nothing[3][6]=0;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;

  
  // 0
  number_template_0[0][0]=1;number_template_0[1][0]=1;number_template_0[2][0]=1;number_template_0[3][0]=1;
  number_template_0[0][1]=1;number_template_0[1][1]=0;number_template_0[2][1]=0;number_template_0[3][1]=1;
  number_template_0[0][2]=1;number_template_0[1][2]=0;number_template_0[2][2]=0;number_template_0[3][2]=1;
  number_template_0[0][3]=1;number_template_0[1][3]=0;number_template_0[2][3]=0;number_template_0[3][3]=1;
  number_template_0[0][4]=1;number_template_0[1][4]=0;number_template_0[2][4]=0;number_template_0[3][4]=1;
  number_template_0[0][5]=1;number_template_0[1][5]=0;number_template_0[2][5]=0;number_template_0[3][5]=1;
  number_template_0[0][6]=1;number_template_0[1][6]=1;number_template_0[2][6]=1;number_template_0[3][6]=1;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;
  
  

  // 1
  number_template_1[0][0]=0;number_template_1[1][0]=0;number_template_1[2][0]=1;number_template_1[3][0]=0;
  number_template_1[0][1]=0;number_template_1[1][1]=1;number_template_1[2][1]=1;number_template_1[3][1]=0;
  number_template_1[0][2]=1;number_template_1[1][2]=0;number_template_1[2][2]=1;number_template_1[3][2]=0;
  number_template_1[0][3]=0;number_template_1[1][3]=0;number_template_1[2][3]=1;number_template_1[3][3]=0;
  number_template_1[0][4]=0;number_template_1[1][4]=0;number_template_1[2][4]=1;number_template_1[3][4]=0;
  number_template_1[0][5]=0;number_template_1[1][5]=0;number_template_1[2][5]=1;number_template_1[3][5]=0;
  number_template_1[0][6]=1;number_template_1[1][6]=1;number_template_1[2][6]=1;number_template_1[3][6]=1;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;



    // 2
  number_template_2[0][0]=1;number_template_2[1][0]=1;number_template_2[2][0]=1;number_template_2[3][0]=1;
  number_template_2[0][1]=0;number_template_2[1][1]=0;number_template_2[2][1]=0;number_template_2[3][1]=1;
  number_template_2[0][2]=0;number_template_2[1][2]=0;number_template_2[2][2]=0;number_template_2[3][2]=1;
  number_template_2[0][3]=0;number_template_2[1][3]=1;number_template_2[2][3]=1;number_template_2[3][3]=0;
  number_template_2[0][4]=1;number_template_2[1][4]=0;number_template_2[2][4]=0;number_template_2[3][4]=0;
  number_template_2[0][5]=1;number_template_2[1][5]=0;number_template_2[2][5]=0;number_template_2[3][5]=0;
  number_template_2[0][6]=1;number_template_2[1][6]=1;number_template_2[2][6]=1;number_template_2[3][6]=1;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;
  
  
  
      // 3
  number_template_3[0][0]=1;number_template_3[1][0]=1;number_template_3[2][0]=1;number_template_3[3][0]=0;
  number_template_3[0][1]=0;number_template_3[1][1]=0;number_template_3[2][1]=0;number_template_3[3][1]=1;
  number_template_3[0][2]=0;number_template_3[1][2]=0;number_template_3[2][2]=0;number_template_3[3][2]=1;
  number_template_3[0][3]=1;number_template_3[1][3]=1;number_template_3[2][3]=1;number_template_3[3][3]=0;
  number_template_3[0][4]=0;number_template_3[1][4]=0;number_template_3[2][4]=0;number_template_3[3][4]=1;
  number_template_3[0][5]=0;number_template_3[1][5]=0;number_template_3[2][5]=0;number_template_3[3][5]=1;
  number_template_3[0][6]=1;number_template_3[1][6]=1;number_template_3[2][6]=1;number_template_3[3][6]=0;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;



    // 4
  number_template_4[0][0]=1;number_template_4[1][0]=0;number_template_4[2][0]=0;number_template_4[3][0]=1;
  number_template_4[0][1]=1;number_template_4[1][1]=0;number_template_4[2][1]=0;number_template_4[3][1]=1;
  number_template_4[0][2]=1;number_template_4[1][2]=0;number_template_4[2][2]=0;number_template_4[3][2]=1;
  number_template_4[0][3]=0;number_template_4[1][3]=1;number_template_4[2][3]=1;number_template_4[3][3]=1;
  number_template_4[0][4]=0;number_template_4[1][4]=0;number_template_4[2][4]=0;number_template_4[3][4]=1;
  number_template_4[0][5]=0;number_template_4[1][5]=0;number_template_4[2][5]=0;number_template_4[3][5]=1;
  number_template_4[0][6]=0;number_template_4[1][6]=0;number_template_4[2][6]=0;number_template_4[3][6]=1;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;


    // 5
  number_template_5[0][0]=1;number_template_5[1][0]=1;number_template_5[2][0]=1;number_template_5[3][0]=1;
  number_template_5[0][1]=1;number_template_5[1][1]=0;number_template_5[2][1]=0;number_template_5[3][1]=0;
  number_template_5[0][2]=1;number_template_5[1][2]=0;number_template_5[2][2]=0;number_template_5[3][2]=0;
  number_template_5[0][3]=0;number_template_5[1][3]=1;number_template_5[2][3]=1;number_template_5[3][3]=0;
  number_template_5[0][4]=0;number_template_5[1][4]=0;number_template_5[2][4]=0;number_template_5[3][4]=1;
  number_template_5[0][5]=0;number_template_5[1][5]=0;number_template_5[2][5]=0;number_template_5[3][5]=1;
  number_template_5[0][6]=1;number_template_5[1][6]=1;number_template_5[2][6]=1;number_template_5[3][6]=1;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;



    // 6
  number_template_6[0][0]=1;number_template_6[1][0]=1;number_template_6[2][0]=1;number_template_6[3][0]=1;
  number_template_6[0][1]=1;number_template_6[1][1]=0;number_template_6[2][1]=0;number_template_6[3][1]=0;
  number_template_6[0][2]=1;number_template_6[1][2]=0;number_template_6[2][2]=0;number_template_6[3][2]=0;
  number_template_6[0][3]=1;number_template_6[1][3]=1;number_template_6[2][3]=1;number_template_6[3][3]=1;
  number_template_6[0][4]=1;number_template_6[1][4]=0;number_template_6[2][4]=0;number_template_6[3][4]=1;
  number_template_6[0][5]=1;number_template_6[1][5]=0;number_template_6[2][5]=0;number_template_6[3][5]=1;
  number_template_6[0][6]=1;number_template_6[1][6]=1;number_template_6[2][6]=1;number_template_6[3][6]=1;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;



    // 7
  number_template_7[0][0]=1;number_template_7[1][0]=1;number_template_7[2][0]=1;number_template_7[3][0]=1;
  number_template_7[0][1]=0;number_template_7[1][1]=0;number_template_7[2][1]=0;number_template_7[3][1]=1;
  number_template_7[0][2]=0;number_template_7[1][2]=0;number_template_7[2][2]=0;number_template_7[3][2]=1;
  number_template_7[0][3]=0;number_template_7[1][3]=0;number_template_7[2][3]=0;number_template_7[3][3]=1;
  number_template_7[0][4]=0;number_template_7[1][4]=0;number_template_7[2][4]=0;number_template_7[3][4]=1;
  number_template_7[0][5]=0;number_template_7[1][5]=0;number_template_7[2][5]=0;number_template_7[3][5]=1;
  number_template_7[0][6]=0;number_template_7[1][6]=0;number_template_7[2][6]=0;number_template_7[3][6]=1;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;


    // 8
  number_template_8[0][0]=1;number_template_8[1][0]=1;number_template_8[2][0]=1;number_template_8[3][0]=1;
  number_template_8[0][1]=1;number_template_8[1][1]=0;number_template_8[2][1]=0;number_template_8[3][1]=1;
  number_template_8[0][2]=1;number_template_8[1][2]=0;number_template_8[2][2]=0;number_template_8[3][2]=1;
  number_template_8[0][3]=1;number_template_8[1][3]=1;number_template_8[2][3]=1;number_template_8[3][3]=1;
  number_template_8[0][4]=1;number_template_8[1][4]=0;number_template_8[2][4]=0;number_template_8[3][4]=1;
  number_template_8[0][5]=1;number_template_8[1][5]=0;number_template_8[2][5]=0;number_template_8[3][5]=1;
  number_template_8[0][6]=1;number_template_8[1][6]=1;number_template_8[2][6]=1;number_template_8[3][6]=1;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;



    // NOTHING
  number_template_9[0][0]=1;number_template_9[1][0]=1;number_template_9[2][0]=1;number_template_9[3][0]=1;
  number_template_9[0][1]=1;number_template_9[1][1]=0;number_template_9[2][1]=0;number_template_9[3][1]=1;
  number_template_9[0][2]=1;number_template_9[1][2]=0;number_template_9[2][2]=0;number_template_9[3][2]=1;
  number_template_9[0][3]=1;number_template_9[1][3]=1;number_template_9[2][3]=1;number_template_9[3][3]=1;
  number_template_9[0][4]=0;number_template_9[1][4]=0;number_template_9[2][4]=0;number_template_9[3][4]=1;
  number_template_9[0][5]=0;number_template_9[1][5]=0;number_template_9[2][5]=0;number_template_9[3][5]=1;
  number_template_9[0][6]=1;number_template_9[1][6]=1;number_template_9[2][6]=1;number_template_9[3][6]=1;
  //number_template_0[0][7]=0;number_template_0[1][7]=0;number_template_0[2][7]=0;number_template_0[3][7]=0;

}

//PONG VARS -------------------------------------

const unsigned int feldx = 20;
const unsigned int feldy = 10;
int ballx = feldx/2;
int bally = feldy/2;
int balldir = 4; //random 
int player1score = 0;
int player2score = 0;
int paddle1x = 0; 
int paddle2x = feldx-1;
int paddle1y = 0;
int paddle2y = 0;
int paddle1size = 3;
int paddle2size = 3;
int tmp_paddle1y = 0;
int tmp_paddle2y = 0;
const int action_timer = 3; //WIE VIELE KONTROLLERABFRAGEN PRO BALLBEWEGUNG
int unsigned pong_game_speed = 50; //ANFANGSSPEED
const unsigned int min_game_speed = 10; //MINIMUM SPEED
 int tmp_speed = 0; //HIER IST IMME DER AKTUELLE SPPED DRINNE
const int score_delay = 3000;
int player1score_tmp = 0; //FÜR DIE SPEED BERECHNUNG
int player2score_tmp = 0;    
int ball_r =0, ball_g = 0, ball_b = 255; 
int p1_r = 0, p1_g = 255, p1_b = 0;
int p2_r = 255, p2_g = 0, p2_b = 0;
int p1_latch = A1; // set the latch pin
int p1_clock = A0; // set the clock pin
int p1_datin = A2;// set the data in pin
int p2_latch = A4;// set the latch pin
int p2_clock = A3; // set the clock pin
int p2_datin = A5;// set the data in pin
byte p1_controller_data = 0; 
byte p2_controller_data = 0; 
int counter = 0;//WIE VIELE KONTROLLERABFRAGEN haben bereits stattgefunden PRO BALLBEWEGUNG
const int max_score = feldy; //MAXIMALE MPUNKTE MUSS KLEINER ALS Y PIXELANZAHL
int last_looser = 0; //WER HAT ZULETZT VERLOREN FÜR DIE FARBEN BEIM SCORESCREEN
int color_state = 0; // 0-> nach rot 1-> nach grün 2-> nach blau
int tmp_green = 0;
int tmp_red = 0;
int tmp_blue = 0;
int fade_speed = 5;
int pongmode = 1;
int chenp1 = 0;
int chenp2 = 0;
int pongenreset=0;
int pong_invert_p1 = 1;
int pong_invert_p2 = 1;

// ENDE PONG VARS -------------------------------


    P(phead) = 
"<!DOCTYPE html><html><head>"
  "<title>RBN LED TABLE</title>"
  "<link href='http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.16/themes/base/jquery-ui.css' rel=stylesheet />"
  "<script src='http://ajax.googleapis.com/ajax/libs/jquery/1.6.4/jquery.min.js'></script>"
  "<script src='http://ajax.googleapis.com/ajax/libs/jqueryui/1.8.16/jquery-ui.min.js'></script>"
"<style> body {  } #red, #green, #blue { margin: 10px; } #red { background: #f00; } #green { background: #0f0; } #blue { background: #00f; } </style>"
  "<script>"
    "function changeRGB(event, ui) { jQuery.ajaxSetup({timeout: 110}); /*not to DDoS the Arduino, you might have to change this to some threshold value that fits your setup*/ var id = $(this).attr('id'); if (id == 'red') $.post('/rgb', { red: ui.value } ); if (id == 'green') $.post('/rgb', { green: ui.value } ); if (id == 'blue') $.post('/rgb', { blue: ui.value } ); } "
    "$(document).ready(function(){ $('#red, #green, #blue').slider({min: 0, max:255, change:changeRGB, slide:changeRGB}); });"
  "</script>"
"<style>"
"html, body {"
"	background: #F2F2F2;"
"	width: 100%;"
"	height: 100%;"
"	margin: 0px;"
"	padding: 0px;"
"	font-family: 'Verdana';"
"	font-size: 16px;"
"	color: #404040;"
"	}"
"img {"
"	border: 0px;"
"}"
"span.title {"
"	display: block;"
"	color: #000000;"
"	font-size: 30px;"
"}"
"span.subtitle {"
"	display: block;"
"	color: #000000;"
"	font-size: 20px;"
"}"
".sidebar {"
"	background: #FFFFFF;"
"	width: 250px;"
"	min-height: 100%;"
"	height: 100%;"
"	height: auto;"
"	position: fixed;"
"	top: 0px;"
"	left: 0px;"
"	border-right: 1px solid #D8D8D8;"
"}"
".logo {"
"	padding: 25px;"
"	text-align: center;"
"	border-bottom: 1px solid #D8D8D8;"
"}"
".menu {"
"	padding: 25px 0px 25px 0px;"
"	border-bottom: 1px solid #D8D8D8;"
"}"
".menu a {"
"	padding: 15px 25px 15px 25px;"
"	display: block;"
"	color: #000000;"
"	text-decoration: none;"
"	transition: all 0.25s;"
"}"
".menu a:hover {"
"	background: #0088CC;"
"	color: #FFFFFF;"
"}"
".right {"
"	margin-left: 250px;"
"	padding: 50px;"
"}"
".content {"
"	background: #FFFFFF;"
"	padding: 25px;"
"	border-radius: 5px;"
"	border: 1px solid #D8D8D8;"
"}"
"</style>"
"</head>";

P(pstart)="<body style='font-size:62.5%;'>"
"<div class='sidebar'>"
"<div class='logo'>"
"<span class='title'>LED TABLE</span>"
"<span class='subtitle'>- Backend -</span>"
"</div>"
"<div class='menu'>"
"<a href='index.html'>Dashboard</a>"
"<a href='/rgb'>MODE</a>"
"<a href='settings.html'>SETTINGS</a>"
"</div>"
"</div>"
"<div class='right'>"
"<div class='content'>";
P(pend)="</div>"
"</div>"
"</body>"
"</html>";









void pong_main_reset(){
    player1score = 0;
  player2score = 0;
  last_looser = 0;
  color_state = 0;
  pong_reset_game();
}
void pong_loop() { 
        //DELETE OLD OBJs
        strip.setPixelColor(get_led_number(ballx,bally),  strip.Color(0, 0, 0));  
        for (int i=0; i<paddle1size; i++){
strip.setPixelColor(get_led_number(paddle1x,i+paddle1y),  strip.Color(0, 0, 0));}
        for (int i=0; i<paddle2size; i++){
        strip.setPixelColor(get_led_number(paddle2x,i+paddle2y),  strip.Color(0, 0, 0));}
      //PADDLEMOVEMENT
            controllerRead();
         //tmp_paddle1y = bally-paddle1size/2;  //HIER PADDLEPOS ÄNDERN
      if(tmp_paddle1y < 0){tmp_paddle1y = 0;}
      if(tmp_paddle1y > feldy-paddle1size){
      tmp_paddle1y = feldy-paddle1size;}
      //tmp_paddle2y = bally-paddle2size/2;  //HIER PADDLEPOS ÄNDERN
      if(tmp_paddle2y < 0){tmp_paddle2y = 0;}
      if(tmp_paddle2y > feldy-paddle2size){
      tmp_paddle2y = feldy-paddle2size;}   
      paddle1y = tmp_paddle1y;
      paddle2y = tmp_paddle2y;
     if(action_timer == counter){ 
      counter = 0;
   //BALL MOVE LOGIC  
   switch (balldir) {
    case 0: 
        ballx = ballx;
        bally = bally;
      break;    
      case 1:     
        ballx = ballx+1;
        bally = bally+1; 
      break;   
     case 2:    
        ballx = ballx-1;
        bally = bally-1; 
      break;     
     case 3:       
        ballx = ballx+1;
        bally = bally-1;
      break;
     case 4:   
        ballx = ballx-1;
        bally = bally+1; 
      break;   
    default:    
        ballx = ballx;
        bally = bally;
      break;
  }    
//PADDLE BOUNCE INCL CORNERCORRECTION
if(ballx == paddle1x+1){
 for (int i=paddle1y-1; i<paddle1y + paddle1size + 1; i++){
   if(bally == i){
 if(balldir == 2){
 balldir = 3;
 }else if(balldir == 4){
 balldir = 1;
 }else{
 pong_reset_game();
 }
   }//bally == i
 }//for
}//if ballx = paddle     
if(ballx == paddle2x-1){
 for (int i=paddle2y-1; i<paddle2y + paddle2size+1 ; i++){
   if(bally == i){
 if(balldir == 1){
 balldir = 4;
 }else if(balldir == 3){
 balldir = 2;
 }else{
 pong_reset_game();
 }
   }//bally == i
 }//for
}//if ballx = paddle
     //LOOSERAUSWERUNG
  if(bally <= 0){
        if(balldir == 2){
      balldir = 4; 
        }else if(balldir == 3){
        balldir = 1; 
        }        
      }else if(bally >= feldy-1){
       if(balldir == 1){
      balldir = 3; 
        }else if(balldir == 4){
        balldir = 2; 
        }        
      }else if(ballx <= 0){
       // LOOSER P2
           player1score++;
           last_looser = 2;
           pong_reset_game();     
      }else if(ballx >= feldx-1){
      //LOOSER P1
      player2score++;
      last_looser = 1;
      pong_reset_game();
      }     
    //ENDE BEREICH DER ZÄHLERGESTUERT IST
     }else{
     counter++;
     }    
      //COLOR CYCLE SHIT
     if(color_state == 0){
       if(tmp_blue <= 255){
         p1_g = 255- tmp_blue;
         p1_b = tmp_blue;
          p2_r = 255- tmp_blue;
         p2_g = tmp_blue;
          ball_b = 255- tmp_blue;
         ball_r = tmp_blue;
          tmp_blue+= fade_speed;
       }else{
      tmp_blue = 0;
      color_state = 1;
       }  
     }else if(color_state == 1){
     if(tmp_red <= 255){
         p1_b = 255- tmp_red;
         p1_r = tmp_red; 
         p2_g = 255- tmp_red;
         p2_b = tmp_red;   
         ball_r = 255- tmp_red;
         ball_g = tmp_red;
          tmp_red+= fade_speed;
       }else{
      tmp_red = 0;
      color_state = 2;
       } 
     }else if(color_state == 2){   
       if(tmp_green <= 255){
         p1_r = 255- tmp_green;
         p1_g = tmp_green;   
          p2_b = 255- tmp_green;
         p2_r = tmp_green;    
         ball_g = 255- tmp_green;
         ball_b = tmp_green;
          tmp_green+= fade_speed;
       }else{
      tmp_green = 0;
      color_state = 0;
       }   
     }else{
     color_state = 0;
     }
     
     
     
     
     
     if(pongmode == 1){
     tmp_paddle1y = bally-paddle1size/2;
     tmp_paddle2y = bally-paddle1size/2;
     }else{
     
     }
     
     
   
                for (int i=0; i<paddle1size; i++){
                 strip.setPixelColor(get_led_number(paddle1x,i+paddle1y),  strip.Color(p1_r, p1_g, p1_b));} 
                 for (int i=0; i<paddle2size; i++){
                    strip.setPixelColor(get_led_number(paddle2x,i+paddle2y),  strip.Color(p2_r, p2_g, p2_b));}      
                strip.setPixelColor(get_led_number(ballx,bally),  strip.Color(ball_r, ball_g, ball_b));
                standby_strip.setPixelColor(0,  strip.Color(ball_r, ball_g, ball_b));
               
               strip.show();
               standby_strip.show();
  //GAMESPEED
     if(player1score <= 0){player1score_tmp = 1;}else{player1score_tmp = player1score;}
     if(player2score <= 0){player2score_tmp = 1;}else{player2score_tmp = player2score;}  
      if(player1score_tmp*player2score_tmp > pong_game_speed){
      tmp_speed = min_game_speed;
      }else{
      tmp_speed = pong_game_speed - (player1score_tmp*player2score_tmp);}
     delay(tmp_speed);
}

void pong_reset_game(){
for (int i = 0; i < feldx; i++){for (int j = 0; j < feldy; j++){
strip.setPixelColor(get_led_number(i,j),  strip.Color(0, 0, 0));
}}
ballx = feldx/2;
bally = feldy/2;
tmp_paddle1y = bally-paddle1size/2;  //HIER PADDLEPOS ÄNDERN
tmp_paddle2y = bally-paddle2size/2;  //HIER PADDLEPOS ÄNDERN
balldir =  random(1, 5);
strip.show();
pong_draw_score(player1score,player2score);
 strip.show();
 delay(score_delay);
 for (int i = 0; i < feldx; i++){for (int j = 0; j < feldy; j++){
strip.setPixelColor(get_led_number(i,j),  strip.Color(0, 0, 0));
}}}


void pong_draw_score(int a, int b){
  if(player1score >= max_score || player2score >= max_score){
  player1score = 0;
  player2score = 0;
  }  
for (int i = 0; i < feldy; i++){
if(b> i){
  strip.setPixelColor(get_led_number(paddle1x,i),  strip.Color(p1_r, p1_g, p1_b));  
}else{
strip.setPixelColor(get_led_number(paddle1x,i),  strip.Color(0, 0, 0));
 
}//ENDE IF
if(a > i){
    strip.setPixelColor(get_led_number(paddle2x,i),  strip.Color(p2_r, p2_g, p2_b));
}else{
    strip.setPixelColor(get_led_number(paddle2x,i),  strip.Color(0, 0, 0)); 
}//ENDE IF
}//ENDE FOR I
//FARBE DES GWEWINNSERS FÜLLEN
for (int i = paddle1x+2; i < paddle2x-1; i++){
for (int j = 0; j < feldy; j++){
  if(last_looser == 1){
  strip.setPixelColor(get_led_number(i,j),  strip.Color(p1_r, p1_g, p1_b)); 
  }else if(last_looser == 2){
  strip.setPixelColor(get_led_number(i,j),  strip.Color(p2_r, p2_g, p2_b)); 
  }else{
  strip.setPixelColor(get_led_number(i,j),  strip.Color(ball_r, ball_g, ball_b)); 
  }}}
}



void controllerRead() {
p1_controller_data = 0;
digitalWrite(p1_latch,LOW);digitalWrite(p1_clock,LOW);digitalWrite(p1_latch,HIGH);
delayMicroseconds(2);
digitalWrite(p1_latch,LOW);
p1_controller_data = digitalRead(p1_datin);
for (int i = 1; i <= 7; i ++) {
digitalWrite(p1_clock,HIGH);
delayMicroseconds(2);
p1_controller_data = p1_controller_data << 1;
p1_controller_data = p1_controller_data + digitalRead(p1_datin) ;
delayMicroseconds(4);
digitalWrite(p1_clock,LOW);}
//----------------------
delayMicroseconds(4);
//----------------------
p2_controller_data = 0;
digitalWrite(p2_latch,LOW);digitalWrite(p2_clock,LOW);digitalWrite(p2_latch,HIGH);
delayMicroseconds(2);
digitalWrite(p2_latch,LOW);
p2_controller_data = digitalRead(p2_datin);
for (int i = 1; i <= 7; i ++) {
digitalWrite(p2_clock,HIGH);
delayMicroseconds(2);
p2_controller_data = p2_controller_data << 1;
p2_controller_data = p2_controller_data + digitalRead(p2_datin) ;
delayMicroseconds(4);
digitalWrite(p2_clock,LOW);}
interpret_controller();
}

void interpret_controller(){
if(p1_controller_data==B01111111){ }//A   
if(p1_controller_data==B10111111){ }// B
if(pong_invert_p1 == 0){
if(p1_controller_data==B11110111){tmp_paddle1y++; } //UP
if(p1_controller_data==B11111011){tmp_paddle1y--; }// DOWN
if(p1_controller_data==B11111110){tmp_paddle1y--; }//RIGHT
if(p1_controller_data==B11111101){tmp_paddle1y++; }//LEFT
}else if(pong_invert_p1 == 1){
if(p1_controller_data==B11110111){tmp_paddle1y--; } //UP
if(p1_controller_data==B11111011){tmp_paddle1y++; }// DOWN
if(p1_controller_data==B11111110){tmp_paddle1y--; }//RIGHT
if(p1_controller_data==B11111101){tmp_paddle1y++; }//LEFT
}else{
if(p1_controller_data==B11110111){tmp_paddle1y++; } //UP
if(p1_controller_data==B11111011){tmp_paddle1y--; }// DOWN
if(p1_controller_data==B11111110){tmp_paddle1y--; }//RIGHT
if(p1_controller_data==B11111101){tmp_paddle1y++; }//LEFT
}
if(p1_controller_data==B11011111 && chenp1 == 1){tmp_paddle1y = bally-paddle1size/2; }//SELCET
if(p1_controller_data==B11101111 && pongenreset == 1){pong_reset_game(); }//START
if(p2_controller_data==B01111111){ }//A   
if(p2_controller_data==B10111111){ }// B
if(pong_invert_p2 == 0){
if(p2_controller_data==B11110111){tmp_paddle2y++; } //UP
if(p2_controller_data==B11111011){tmp_paddle2y--; }// DOWN
if(p2_controller_data==B11111110){tmp_paddle2y--; }//RIGHT
if(p2_controller_data==B11111101){tmp_paddle2y++; }//LEFT
}else if(pong_invert_p2 == 1){
if(p2_controller_data==B11110111){tmp_paddle2y--; } //UP
if(p2_controller_data==B11111011){tmp_paddle2y++; }// DOWN
if(p2_controller_data==B11111110){tmp_paddle2y--; }//RIGHT
if(p2_controller_data==B11111101){tmp_paddle2y++; }//LEFT
}else{
if(p2_controller_data==B11110111){tmp_paddle2y++; } //UP
if(p2_controller_data==B11111011){tmp_paddle2y--; }// DOWN
if(p2_controller_data==B11111110){tmp_paddle2y--; }//RIGHT
if(p2_controller_data==B11111101){tmp_paddle2y++; }//LEFT
}
if(p2_controller_data==B11011111 && chenp2 == 1){tmp_paddle2y = bally-paddle1size/2; }//SELCET
if(p2_controller_data==B11101111 && pongenreset == 1){pong_reset_game(); }//START
}

//COORDS TO LED NUMBER
unsigned int get_led_number(int x, int y){
 if (y % 2) {
  return (y*feldx)+feldx-1-x; //ungerade
} else {
  return (y*feldx)+x; //y=1; //GERADE
} 
}
































int i=0,val;

char im[128], data[128];

char data_avgs[14];







void loop() {
 main_process();
if(mode == 5){ //OFF
digitalWrite(relais,LOW);
colorfill(strip.Color(0, 0, 0)); // G;R;B
if(standby_strip_state == 0){standby_strip.setPixelColor(0,strip.Color(0, 0, 40));standby_strip_state = 1;
}else{standby_strip.setPixelColor(0,strip.Color(0, 0, 0));standby_strip_state = 0;}
delay(200);
}else if(mode == 0){ //STANDBY
  digitalWrite(relais,HIGH);
   clear_screen();
     strip.setPixelColor(get_led_number(0,0),strip.Color(0, 0, 10));
     strip.setPixelColor(get_led_number(0,9),strip.Color(0, 0, 10));
     strip.setPixelColor(get_led_number(19,9),strip.Color(0, 0, 10));
     strip.setPixelColor(get_led_number(19,0),strip.Color(0, 0, 10));
     standby_strip.setPixelColor(0,strip.Color(0, 0, 70));
  strip.show();
     digitalWrite(relais,HIGH);
  }else if(mode == 1){ // CONST COLOR
   colorfill(strip.Color(fillred, fillgreen, fillblue)); // G;R;B
     digitalWrite(relais,HIGH);
  }else if(mode == 2){  //RAINBOW
  if(rainbowmode == 0){rainbow();}else if(rainbowmode == 1){rainbowCycle();}else if(rainbowmode == 2){rainbow_complete();}else if(rainbowmode == 3){rainbowCycleCol();}else{rainbowmode = 0;}
    digitalWrite(relais,HIGH);
  }else if (mode == 3){ //RANDOM
    randomCycle();
      digitalWrite(relais,HIGH);   
  }else if(mode == 4){ //PONG
  digitalWrite(relais,HIGH);
  pong_loop();
  main_process();



  }else if(mode == 6){
    
    _value = hour;
 h_z = (_value % 100) / 10;
 h_e = _value % 10;
 binwert_h_z = byte(h_z);
 binwert_h_e = byte(h_e);
    
    
     _value = minute;
 m_z = (_value % 100) / 10;
 m_e = _value % 10;
binwert_m_z = byte(m_z);
binwert_m_e = byte(m_e);
    
   Serial.print(m_z);Serial.println(m_e); 
       
  //h_z = 0  
    
if(clock_orientation == 0 ){
display_clock(m_e,m_z,h_e,h_z);
}else{
  //hz he mz me
display_clock(h_z,h_e,m_z,m_e);
}
   
  }else if(mode == 7){    
//DMX








  }else{
    //ERR
  show_error("could not find mode");
  }//end mode
  
  
  
  standby_strip.show();
    strip.show();
}//ENDE LOOP



void show_error(String reason ){
clear_screen();
strip.setPixelColor(get_led_number(0,0),strip.Color(255, 0, 0));
strip.setPixelColor(get_led_number(0,9),strip.Color(255, 0, 0));
strip.setPixelColor(get_led_number(19,9),strip.Color(255, 0, 0));
strip.setPixelColor(get_led_number(19,0),strip.Color(255, 0, 0));

if(standby_strip_state == 0){
standby_strip.setPixelColor(0,strip.Color(255, 0, 0));
standby_strip_state = 1;
}else{
standby_strip.setPixelColor(0,strip.Color(0, 0, 0));
standby_strip_state = 0;
}

standby_strip.show();
strip.show();
delay(100);
Serial.print("ERROR : ");Serial.println(reason);



}
// Fill the dots one after the other with a color
void colorfill(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);  
      standby_strip.setPixelColor(0,c); 
  }
  standby_strip.show();
  strip.show();      
}

void rainbow() {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
       standby_strip.setPixelColor(0,Wheel((i+j) & 255 ));
    }
    standby_strip.show();
    strip.show();
    main_process();
    delay(rainbowspeed);
  }
}

void rainbow_complete() {
  uint16_t i, j;
  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((j) & 255));
  standby_strip.setPixelColor(0,Wheel((j) & 255));  
  }
  standby_strip.show();
    strip.show();
    main_process();
    delay(rainbowspeed);
  }
}



// Slightly different, this makes the rainbow equally distributed throughout
void randomCycle() {
  uint16_t i, j;
  if(randommode == 2){
  int color =  Wheel(random(0,257));

  for(i=0; i< strip.numPixels(); i++) {
    strip.setPixelColor(i,color);
  }
  strip.show();main_process(); delay(randomspeed);
  }else{

    for(i=0; i< strip.numPixels(); i++) {
      standby_strip.setPixelColor(0,Wheel(random(0,257)));
       if(randomefmode == 1){strip.setPixelColor(random(0,201), Wheel(random(0,257)));}else if( randomefmode == 0){strip.setPixelColor(i, Wheel(random(0,257)));
       }
      if(randommode == 0){ strip.show();main_process(); standby_strip.show(); delay(randomspeed);}
    }
    if(randommode == 1){ strip.show();standby_strip.show();main_process(); delay(randomspeed);}
  }
}



void rainbowCycle() {
  uint16_t i, j;
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    main_process();
    delay(rainbowspeed);
  }
}

    uint16_t i1, j;
void rainbowCycleCol() {

      i1++;
       for(int x=0; x< feldx; x++) {
       for(int y=0; y< feldy; y++) {
       strip.setPixelColor(get_led_number(x,y),Wheel(i1));
       if(i1 > 255){
      i1 = 0;
      }else{
      i1++;
      }  
       } 
     strip.show();
    main_process();
    delay(rainbowspeed);
       }
    }

  





// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}





void clear_screen() {
  uint16_t i, j;
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, strip.Color(0,0,0));
    }
    strip.show();

  
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
}






void defaultCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  if (type == WebServer::POST)
  {
  
  }
  server.httpSuccess();
  if (type == WebServer::GET)
  {

    server.printP(phead);
    server.printP(pstart);
server.print("<span class='title'>Dashboard</span><hr><br><br>");    
server<<"<p><h2> Current table-mode : ";
if(mode == 5){

}
if(mode == 5){
  server<<" OFF ";
}else if(mode == 0){
server<<" STANDBY ";
}else if(mode == 1){
server<< " constant color ";
}else if(mode == 2){
server<< " rainbow ";
}else if(mode == 3){
server<< " random ";
}else if(mode == 4){
server<< " pong ("; 
if(pongmode == 0){server<<"2 player";}else if(pongmode == 1){server<<"auto-mode";}
server<< " ) ";
}else if(mode == 6){
server<< " CLOCK ";
}else if(mode == 7){
server<< " DMX ";
}

server<<".</h2><br><br> <h3> BEIM STARTEN UND WAEHREND DES BETRIEBS DES TISCHES IST EINE INTERNETVERBINDUNG ERFORDERLICH ! <br><br> WENN BEIM STARTEN DIE STANDBYLED LAENGER ALS EINE MINUTE DAUERHAFT LEUCHTET ODER BLINKT: <br>"


"1) GRUENEN RESET SCHALTER DRUECKEN. WENN DANACH DER FEHLER NICHT BEHOBEN IST, SIEHE SCHRITT 2<br>"
"2) NETZWERK-VERBINDUNG PRÜFEN. WENN DANACH DER FEHLER NICHT BEHOBEN IST, SIEHE SCHRITT 3<br>"
"3) MIT EINEM USB-KABEL DEN TISCH UND EINEN PC VERBINDEN. <br>"
"3.1) DIE ARDUINO SOFTWARE (>= 1.5.6-r2) LADEN UND DEN SERIAL-MONITOR AUFRUFEN (9600 BAUD). <br>"
"3.2) GRUENEN RESET SCHALTER DRUECKEN UND AUF AUSGABEN IN DER CONSOLE WARTEN. <br>"
"</h3></p>";

    server.printP(pend);

  }
}

void settingsCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
 if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    do
    {
      repeat = server.readPOSTparam(name, 16, value, 16);

      
      
      
      
      if (strcmp(name, "nthen") == 0)
      {
         nthen = strtoul(value, NULL, 10);
      }
      
            if (strcmp(name, "nth") == 0){
         nth = strtoul(value, NULL, 10);
      }
      
                  if (strcmp(name, "nthe") == 0){
         nthe = strtoul(value, NULL, 10);
      }
      
                  if (strcmp(name, "nthoffmode") == 0){
         nthoffmode = strtoul(value, NULL, 10);
      }
      
                        if (strcmp(name, "nthonmode") == 0){
         nthonmode = strtoul(value, NULL, 10);
      }
      
      
     
       if (strcmp(name, "restore") == 0)
      {
        restore_settings(1);
     }
     
               if (strcmp(name, "setDate") == 0)
      {
          get_ntp_time();       
      }
      
                  if (strcmp(name, "zz") == 0)
      {
         zeitverschiebung = strtoul(value, NULL, 10);
         delay(100);
         get_ntp_time();  
      }

     
     
                            if (strcmp(name, "fanstate") == 0){
         fan_state = strtoul(value, NULL, 10);
      }
 
     

    } while (repeat);
        clear_screen();
        save_settings();
    server.httpSeeOther("/settings.html");
    return;
  }
  
  
  
  server.httpSuccess();
  if (type == WebServer::GET)
  {
    server.printP(phead);
    server.printP(pstart);
server.print("<span class='title'>SETTINGS</span><p>");    
server<<"<hr>";


server<<" <form id='nthen' name='nthen' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='nthen'>NIGHTMODE STATE</label> </td>";
server<<"    <td scope='col'><input type='radio' name='nthen' id='nthen' value='0' ";if(nthen == 0){server <<"checked";}server<<">DISABLE</td>";
server<<"    <td scope='col'><input type='radio' name='nthen' id='nthen'  value='1' ";if(nthen == 1){server <<"checked";}server<<">ENABLE</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";



server<<"   <form id='speed' name='nth' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='nth'>NIGHTMODE START</label></td>";

server<<"    <td scope='col' >";
server<<"    <input name='nth' type='number' id='nth' max='23' min='0' step='1' value='"; server<<nth;server <<"' size='5'><br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";


server<<"   <form id='speed' name='nth' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='nthe'>NIGHTMODE STOP</label></td>";

server<<"    <td scope='col' >";
server<<"    <input name='nthe' type='number' id='nthe' max='23' min='0' step='1' value='"; server<<nthe;server <<"' size='5'><br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";



server<<" <form id='colorsettings' name='nthonmode' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='mode'>NIGHTMODE ON MODE</label> </td>";
server<<"    <td scope='col'><input type='radio' name='nthonmode' id='nthonmode' value='5' ";if(nthonmode == 5){server <<"checked";}server<<">OFF</td>  ";
server<<"    <td scope='col'><input type='radio' name='nthonmode' id='nthonmode' value='0' ";if(nthonmode == 0){server <<"checked";}server<<">STANDBY (STILL ALIVE)</td>  ";
server<<"    <td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='1' ";if(nthonmode == 1){server <<"checked";}server<<">CONST COLOR </td>";
server<<"     <td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='2' ";if(nthonmode == 2){server <<"checked";}server<<">RAINBOW</td>";
server<<"     <td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='3' ";if(nthonmode == 3){server <<"checked";}server<<">RANDOM</td>";
server<<"     <td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='4' ";if(nthonmode == 4){server <<"checked";}server<<">PONG (GAME)</td>";
server<<"     <td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='6' ";if(nthonmode == 6){server <<"checked";}server<<">CLOCK</td>";
//server<<"     <td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='7' ";if(nthonmode == 7){server <<"checked";}server<<">DMX</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";

server<<" <form id='colorsettings' name='nthoffmode' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='mode'>NIGHTMODE OFF MODE</label> </td>";
server<<"    <td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode' value='5' ";if(nthoffmode == 5){server <<"checked";}server<<">OFF</td>  ";
server<<"    <td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode' value='0' ";if(nthoffmode == 0){server <<"checked";}server<<">STANDBY (STILL ALIVE)</td>  ";
server<<"    <td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='1' ";if(nthoffmode == 1){server <<"checked";}server<<">CONST COLOR </td>";
server<<"     <td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='2' ";if(nthoffmode == 2){server <<"checked";}server<<">RAINBOW</td>";
server<<"     <td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='3' ";if(nthoffmode == 3){server <<"checked";}server<<">RANDOM</td>";
server<<"     <td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='4' ";if(nthoffmode == 4){server <<"checked";}server<<">PONG (GAME)</td>";
server<<"     <td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='6' ";if(nthoffmode == 6){server <<"checked";}server<<">CLOCK</td>";
//server<<"     <td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='7' ";if(nthoffmode == 7){server <<"checked";}server<<">DMX</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";

server<<"<br><br> <hr><br>";

server<<"   <form id='speed' name='zz' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='paddle1size'>TimeZone</label></td>";
server<<"    <td scope='col' >";
server<<"   + <input name='zz' type='number' id='zz' max='23' min='0' step='1' value='"; server<<zeitverschiebung;server <<"' size='5'>h<br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='REFRESH' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";

server<<"<form id='setDate' name='setDate' action=''  method='post'>";
server<<"<input type='hidden' id='setDate' name='setDate' value='1'>";
server<<"<input type='submit' value='GET NTP TIME' />";
server<<"</form>";


server<<"<br><br> <hr><br>";



server<<" <form id='fanstate' name='fanstate' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='fanstate'>FAN STATE</label> </td>";
server<<"    <td scope='col'><input type='radio' name='fanstate' id='fanstate' value='0' ";if(fan_state == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"    <td scope='col'><input type='radio' name='fanstate' id='fanstate'  value='1' ";if(fan_state == 1){server <<"checked";}server<<">ENABLE</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";



server<<"<br><hr><br>";
server<<"<form id='restore' name='restore' action=''  method='post'>";
server<<"<input type='hidden' id='restore' name='restore' value='1'>";
server<<"<input type='submit' value='RESTORE SETTINGS TO DEFAULT' />";
server<<"</form>";

server<<"</p>";
 server.printP(pend);

  }
}


void rgbCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{

    
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[16], value[16];
    do
    {
      repeat = server.readPOSTparam(name, 16, value, 16);
      if (strcmp(name, "red") == 0)
      {
        fillred = strtoul(value, NULL, 10);
      }
      if (strcmp(name, "green") == 0)
      {
        fillgreen = strtoul(value, NULL, 10);
      }
      if (strcmp(name, "blue") == 0)
      {
        fillblue = strtoul(value, NULL, 10);
      }  
       if (strcmp(name, "mode") == 0)
      {
        
        
        if(mode == 5 && strtoul(value, NULL, 10) != 5){
          delay(2000);
        digitalWrite(relais,HIGH); 
        clear_screen();
        }
        
        
        
         mode = strtoul(value, NULL, 10);    
         if(mode == 1){
         fillred= 0;
         fillgreen = 0;
         fillblue = 0;
         }else if(mode == 4){
         pong_main_reset();
         }
         
         clear_screen();
      }
      
      if (strcmp(name, "rmode") == 0)
      {
         rainbowmode = strtoul(value, NULL, 10);

      }
      

      
      
           if (strcmp(name, "ccm") == 0){
         clock_fix_color_m = strtoul(value, NULL, 10);       
      }
      
                 if (strcmp(name, "cch") == 0){
         clock_fix_color_h = strtoul(value, NULL, 10);       
      }
      
                 if (strcmp(name, "clockcolor") == 0){
         clockcolormode = strtoul(value, NULL, 10);       
      }
      
      

      
          if (strcmp(name, "ranmode") == 0)
      {
         randommode = strtoul(value, NULL, 10);
             clear_screen();    
      }
      
      
      

      
         if (strcmp(name, "ranefmode") == 0)
      {
         randomefmode = strtoul(value, NULL, 10);     
      }
      
      
      
      
      if (strcmp(name, "chenp1") == 0)
      {
         chenp1 = strtoul(value, NULL, 10);     
      }
      
           
      if (strcmp(name, "chenp2") == 0)
      {
         chenp2 = strtoul(value, NULL, 10);     
      }
      
        if (strcmp(name, "pongenreset") == 0)
      {
         pongenreset = strtoul(value, NULL, 10);    
      }
      
      
      
         if (strcmp(name, "paddle1size") == 0)
      {
         paddle1size = strtoul(value, NULL, 10);   
      }
      
      
          if (strcmp(name, "paddle2size") == 0)
      {
         paddle2size = strtoul(value, NULL, 10);   
      }
      
 
          if (strcmp(name, "clockor") == 0)
      {
         clock_orientation = strtoul(value, NULL, 10); 
      }
 

      
      
                  if (strcmp(name, "clockspeed") == 0){
         clock_color_speed = strtoul(value, NULL, 10); 
      }
      
      
   
      
      
     
               if (strcmp(name, "ponginvp2") == 0)
      {
         pong_invert_p2 = strtoul(value, NULL, 10);  
      }
      
                     if (strcmp(name, "ponginvp1") == 0)
      {
         pong_invert_p1= strtoul(value, NULL, 10);  
      }
     
      
      
      
               if (strcmp(name, "pongresetp1") == 0)
      {
        player1score = 0;  
      }
      
      
               if (strcmp(name, "pongresetp2") == 0)
      {
           player2score = 0;
      }
      
       if (strcmp(name, "pong_game_speed") == 0)
      {
         pong_game_speed = strtoul(value, NULL, 10);
      }
      
      
      
       if (strcmp(name, "pongmode") == 0)
      {
         pongmode = strtoul(value, NULL, 10);
      }
      
      
      
            if (strcmp(name, "rsp") == 0)
      {
         rainbowspeed = strtoul(value, NULL, 10);
      }
      
      
      
      
                  if (strcmp(name, "cb") == 0)
      {
         clock_bright = strtoul(value, NULL, 10);
      }
      
      
      
               if (strcmp(name, "ransp") == 0)
      {
     randomspeed = strtoul(value, NULL, 10);
      }
    } while (repeat);
        clear_screen();
        save_settings();
    server.httpSeeOther("/rgb");
    return;
  }
  
  
  
  server.httpSuccess();
  if (type == WebServer::GET)
  {
    server.printP(phead);
    server.printP(pstart);
server.print("<span class='title'>MODE</span><p>");    
server<<"<hr>";
server<<" <form id='colorsettings' name='colorsettings' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='mode'>TABLE MODE</label> </td>";
server<<"    <td scope='col'><input type='radio' name='mode' id='mode' value='5' ";if(mode == 5){server <<"checked";}server<<">OFF</td>  ";
server<<"    <td scope='col'><input type='radio' name='mode' id='mode' value='0' ";if(mode == 0){server <<"checked";}server<<">STANDBY (STILL ALIVE)</td>  ";
server<<"    <td scope='col'><input type='radio' name='mode' id='mode'  value='1' ";if(mode == 1){server <<"checked";}server<<">CONST COLOR </td>";
server<<"     <td scope='col'><input type='radio' name='mode' id='mode'  value='2' ";if(mode == 2){server <<"checked";}server<<">RAINBOW</td>";
server<<"     <td scope='col'><input type='radio' name='mode' id='mode'  value='3' ";if(mode == 3){server <<"checked";}server<<">RANDOM</td>";
server<<"     <td scope='col'><input type='radio' name='mode' id='mode'  value='4' ";if(mode == 4){server <<"checked";}server<<">PONG (GAME)</td>";
server<<"     <td scope='col'><input type='radio' name='mode' id='mode'  value='6' ";if(mode == 6){server <<"checked";}server<<">CLOCK</td>";
//server<<"     <td scope='col'><input type='radio' name='mode' id='mode'  value='7' ";if(mode == 7){server <<"checked";}server<<">DMX</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";
server.print("<br><br>");  
server.print("<span class='title'>MODE OPTIONS</span>");  
if(mode == 1){ 
server.print("<p>");
server.print("<div width='50%' id=red></div>");
server.print("<div width='50%' id=green></div>");
server.print("<div  width='50%' id=blue></div>");
server.println("</p>");
}else if(mode == 2){
 server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='rmode'>RAINBOW TYPE</label> </td>";
server<<"    <td scope='col'><input type='radio' name='rmode' id='rmode' value='0' ";if(rainbowmode == 0){server <<"checked";}server<<">THEATRE (ROW)</td>  ";
server<<"    <td scope='col'><input type='radio' name='rmode' id='rmode'  value='1' ";if(rainbowmode == 1){server <<"checked";}server<<">CYCLE (ROW)</td>";
server<<"    <td scope='col'><input type='radio' name='rmode' id='rmode'  value='2' ";if(rainbowmode == 2){server <<"checked";}server<<">COMPLETE (ROW)</td>";
server<<"    <td scope='col'><input type='radio' name='rmode' id='rmode'  value='3' ";if(rainbowmode == 3){server <<"checked";}server<<">STACCATO (COL)</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";
server<<"   <form id='speed' name='speed' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='rsp'>RAINBOW SPEED</label></td>";
server<<"    <td>";
server<<"    SPEED : <br>";
server<<"    </td> ";
server<<"    <td scope='col' >";
server<<"    <input name='rsp' type='number' id='rsp' max='100000' min='0' step='1' value='"; server<<rainbowspeed;server <<"' size='5'><br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";
}else if (mode == 3){
server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='ranmode'>RANDOM TYPE</label> </td>";
server<<"    <td scope='col'><input type='radio' name='ranmode' id='ranmode' value='0' ";if(randommode == 0){server <<"checked";}server<<">ROW BY ROW</td>  ";
server<<"    <td scope='col'><input type='radio' name='ranmode' id='ranmode'  value='1' ";if(randommode == 1){server <<"checked";}server<<">DIRECT</td>";
server<<"    <td scope='col'><input type='radio' name='ranmode' id='ranmode'  value='2' ";if(randommode == 2){server <<"checked";}server<<">COMPLETE</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";
 server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='ranmode'>PIXEL APPEAR</label> </td>";
server<<"    <td scope='col'><input type='radio' name='ranefmode' id='ranefmode' value='0' ";if(randomefmode == 0){server <<"checked";}server<<">SHIFTING</td>  ";
server<<"    <td scope='col'><input type='radio' name='ranefmode' id='ranefmode'  value='1' ";if(randomefmode == 1){server <<"checked";}server<<">RANDOM</td>";
server<<"   </table> ";
server<<"   </form>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";
server<<"   <form id='speed' name='speed' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='ransp'>RANDOM SPEED</label></td>";
server<<"    <td>";
server<<"    SPEED : <br>";
server<<"    </td> ";
server<<"    <td scope='col' >";
server<<"    <input name='ransp' type='number' id='ransp' max='100000' min='0' step='1' value='"; server<<randomspeed;server <<"' size='5'><br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";

}else if (mode == 6){
  

  
  server<<" <form id='clockcolor' name='clockcolor' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='fanstate'>CLOCK COLOR MODE</label> </td>";
server<<"    <td scope='col'><input type='radio' name='clockcolor' id='clockcolor' value='0' ";if(clockcolormode == 0){server <<"checked";}server<<">RAINBOW </td>  ";
server<<"    <td scope='col'><input type='radio' name='clockcolor' id='clockcolor'  value='1' ";if(clockcolormode == 1){server <<"checked";}server<<">FIX</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";
  
  
  

if(clockcolormode == 0){
server<<"   <form id='speed' name='clockspeed' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='paddle1size'>COLOR FADING SPEED</label></td>";
server<<"    <td scope='col' >";
server<<"    <input name='clockspeed' type='number' id='clockspeed' max='900' min='0' step='1' value='"; server<<clock_color_speed;server <<"' size='5'><br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";
}else if(clockcolormode == 1){

server<<" <form id='cch' name='cch' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='cch'HOUR COLOR</label> </td>";
server<<"    <td scope='col'><input type='radio' name='cch' id='cch' value='0' ";if(clock_fix_color_h == 0){server <<"checked";}server<<">RED </td>  ";
server<<"    <td scope='col'><input type='radio' name='cch' id='cch'  value='1' ";if(clock_fix_color_h == 1){server <<"checked";}server<<">GREEN</td>";
server<<"    <td scope='col'><input type='radio' name='cch' id='cch'  value='2' ";if(clock_fix_color_h == 2){server <<"checked";}server<<">BLUE</td>";
server<<"    <td scope='col'><input type='radio' name='cch' id='cch'  value='3' ";if(clock_fix_color_h == 3){server <<"checked";}server<<">CYAN</td>";
server<<"    <td scope='col'><input type='radio' name='cch' id='cch'  value='4' ";if(clock_fix_color_h == 4){server <<"checked";}server<<">PINK</td>";
server<<"    <td scope='col'><input type='radio' name='cch' id='cch'  value='5' ";if(clock_fix_color_h == 5){server <<"checked";}server<<">YELLOW</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";
  
  
server<<" <form id='cch' name='cch' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='ccm'MINUTE COLOR</label> </td>";
server<<"    <td scope='col'><input type='radio' name='ccm' id='ccm' value='0' ";if(clock_fix_color_m == 0){server <<"checked";}server<<">RED </td>  ";
server<<"    <td scope='col'><input type='radio' name='ccm' id='ccm'  value='1' ";if(clock_fix_color_m == 1){server <<"checked";}server<<">GREEN</td>";
server<<"    <td scope='col'><input type='radio' name='ccm' id='ccm'  value='2' ";if(clock_fix_color_m == 2){server <<"checked";}server<<">BLUE</td>";
server<<"    <td scope='col'><input type='radio' name='ccm' id='ccm'  value='3' ";if(clock_fix_color_m == 3){server <<"checked";}server<<">CYAN</td>";
server<<"    <td scope='col'><input type='radio' name='ccm' id='ccm'  value='4' ";if(clock_fix_color_m == 4){server <<"checked";}server<<">PINK</td>";
server<<"    <td scope='col'><input type='radio' name='ccm' id='ccm'  value='5' ";if(clock_fix_color_m == 5){server <<"checked";}server<<">YELLOW</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";


server<<"   <form id='speed' name='cb' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='cb'>CLOLOR BRIGHTNESS</label></td>";
server<<"    <td scope='col' >";
server<<"    <input name='cb' type='number' id='cb' max='255' min='0' step='1' value='"; server<<clock_bright;server <<"' size='5'><br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";





}else{


}









server<<" <form id='clock_orientation' name='clockor' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='clockor'>DISPLAY ORIENTATION</label> </td>";
server<<"    <td scope='col'><input type='radio' name='clockor' id='clockor' value='0' ";if(clock_orientation == 0){server <<"checked";}server<<">LEFT</td>  ";
server<<"    <td scope='col'><input type='radio' name='clockor' id='clockor'  value='1' ";if(clock_orientation == 1){server <<"checked";}server<<">RIGHT</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";


  
}else if (mode == 4){
server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='pongmode'>PONG MODE</label> </td>";
server<<"    <td scope='col'><input type='radio' name='pongmode' id='pongmode' value='0' ";if(pongmode == 0){server <<"checked";}server<<">2 PLAYER MODE ( with NES Controller)</td>  ";
server<<"    <td scope='col'><input type='radio' name='pongmode' id='pongmode'  value='1' ";if(pongmode == 1){server <<"checked";}server<<">AUTO PONG</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";

if(pongmode == 0){

server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='pongmode'>CHEATMODE PLAYER 1</label> </td>";
server<<"    <td scope='col'><input type='radio' name='chenp1' id='chenp1' value='0' ";if(chenp1 == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"    <td scope='col'><input type='radio' name='chenp1' id='chenp1'  value='1' ";if(chenp1 == 1){server <<"checked";}server<<">ENABLE</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";
server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='pongmode'>CHEATMODE PLAYER 2</label> </td>";
server<<"    <td scope='col'><input type='radio' name='chenp2' id='chenp2' value='0' ";if(chenp2 == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"    <td scope='col'><input type='radio' name='chenp2' id='chenp2'  value='1' ";if(chenp2 == 1){server <<"checked";}server<<">ENABLE</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";
 server<<"   <form id='speed' name='speed' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='paddle1size'>PADDLE SIZE PLAYER 1</label></td>";
server<<"    <td>";
server<<"    SPEED : <br>";
server<<"    </td> ";
server<<"    <td scope='col' >";
server<<"    <input name='paddle1size' type='number' id='paddle1size' max='10' min='1' step='1' value='"; server<<paddle1size;server <<"' size='5'><br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";
server<<"   <form id='speed' name='speed' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='paddle2size'>PADDLE SIZE PLAYER 2</label></td>";
server<<"    <td>";
server<<"    SPEED : <br>";
server<<"    </td> ";
server<<"    <td scope='col' >";
server<<"    <input name='paddle2size' type='number' id='paddle2size' max='10' min='1' step='1' value='"; server<<paddle2size;server <<"' size='5'><br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";





server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='pongmode'>INVERT PLAYER 1</label> </td>";
server<<"    <td scope='col'><input type='radio' name='ponginvp1' id='ponginvp1' value='0' ";if(pong_invert_p1 == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"    <td scope='col'><input type='radio' name='ponginvp1' id='ponginvp1'  value='1' ";if(pong_invert_p1 == 1){server <<"checked";}server<<">ENABLE</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";


server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='pongmode'>INVERT PLAYER 2</label> </td>";
server<<"    <td scope='col'><input type='radio' name='ponginvp1' id='ponginvp2' value='0' ";if(pong_invert_p2 == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"    <td scope='col'><input type='radio' name='ponginvp1' id='ponginvp2'  value='1' ";if(pong_invert_p2 == 1){server <<"checked";}server<<">ENABLE</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";



server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"  <tr>";
server<<"    <td><label for='pongmode'>ALLOW PLAYER RESET</label> </td>";
server<<"    <td scope='col'><input type='radio' name='pongenreset' id='pongenreset' value='0' ";if(pongenreset == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"    <td scope='col'><input type='radio' name='pongenreset' id='pongenreset'  value='1' ";if(pongenreset == 1){server <<"checked";}server<<">ENABLE</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";

server<<"<form id='pongresetp1' name='pongresetp1' action=''  method='post'>";
server<<"<input type='hidden' id='pongresetp1' name='pongresetp1' value='1'>";
server<<"<input type='submit' value='RESET PLAYER 1 SCORE' />";
server<<"</form>";

server<<"<form id='pongresetp2' name='pongresetp1' action=''  method='post'>";
server<<"<input type='hidden' id='pongresetp2' name='pongresetp2' value='1'>";
server<<"<input type='submit' value='RESET PLAYER 2 SCORE' />";
server<<"</form>";

server<<"<form id='reset_pong' name='reset_pong' action=''  method='post'>";
server<<"<input type='hidden' id='reset_pong' name='reset_pong' value='1'>";
server<<"<input type='submit' value='RESET GAME' />";
server<<"</form>";
}
server<<"   <form id='speed' name='speed' action=''  method='post'>";
server<<"   <table width='50%' border='0'>";
server<<"   <tr>";
server<<"    <td scope='col'> <label for='paddle1size'>START SPEED</label></td>";
server<<"    <td>";
server<<"    SPEED : <br>";
server<<"    </td> ";
server<<"    <td scope='col' >";
server<<"    <input name='pong_game_speed' type='number' id='pong_game_speed' max='100000' min='1' step='1' value='"; server<<pong_game_speed;server <<"' size='5'><br>";
server<<"     </td>  ";
server<<"      <td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"  </tr>";
server<<"   </table> ";
server<<"   </form>";
}else{
server<<" - NO OPTIONS FOR THIS MODE - ";
}


server<<"</p>";
    server.printP(pend);

  }
}


void load_settings(){

nth = dueFlashStorage.read(0);
nthe = dueFlashStorage.read(1);
nthen = dueFlashStorage.read(2);
nthonmode = dueFlashStorage.read(3);
nthoffmode = dueFlashStorage.read(4);
rainbowmode = dueFlashStorage.read(5);
pong_game_speed = dueFlashStorage.read(6);
pong_invert_p2 = dueFlashStorage.read(7);
pong_invert_p1 = dueFlashStorage.read(8);
paddle2size = dueFlashStorage.read(9);
paddle1size = dueFlashStorage.read(10);
chenp2 = dueFlashStorage.read(11);
chenp1 = dueFlashStorage.read(12);
clock_orientation = dueFlashStorage.read(13);
clock_color_speed = dueFlashStorage.read(14);
zeitverschiebung = dueFlashStorage.read(15);
randomspeed = dueFlashStorage.read(16);
randommode = dueFlashStorage.read(17);
randomefmode = dueFlashStorage.read(18);
rainbowspeed = dueFlashStorage.read(19);
mode = dueFlashStorage.read(20);
fan_state = dueFlashStorage.read(21);

clock_fix_color_h = dueFlashStorage.read(22);
clock_fix_color_m = dueFlashStorage.read(23);
clock_bright = dueFlashStorage.read(24);
clockcolormode = dueFlashStorage.read(25);


}


void save_settings(){
dueFlashStorage.write(0,nth);
dueFlashStorage.write(1,nthe);
dueFlashStorage.write(2,nthen);
dueFlashStorage.write(3,nthonmode);
dueFlashStorage.write(4,nthoffmode);
dueFlashStorage.write(5,rainbowmode);
dueFlashStorage.write(6,pong_game_speed);
dueFlashStorage.write(7,pong_invert_p2);
dueFlashStorage.write(8,pong_invert_p1);
dueFlashStorage.write(9,paddle2size);
dueFlashStorage.write(10,paddle1size);
dueFlashStorage.write(11,chenp2);
dueFlashStorage.write(12,chenp1);
dueFlashStorage.write(13,clock_orientation);
dueFlashStorage.write(14,clock_color_speed);
dueFlashStorage.write(15,zeitverschiebung);
dueFlashStorage.write(16,randomspeed);
dueFlashStorage.write(17,randommode);
dueFlashStorage.write(18,randomefmode);
dueFlashStorage.write(19,rainbowspeed);
dueFlashStorage.write(20,mode);
dueFlashStorage.write(21,fan_state);

dueFlashStorage.write(22,clock_fix_color_h);
dueFlashStorage.write(23,clock_fix_color_m);
dueFlashStorage.write(24,clock_bright);
dueFlashStorage.write(25,clockcolormode);
Serial.println("SAVE SETTINGS");

}

void restore_settings(int with_save){
nth = 22;
nthe = 7;
nthen = 1;
nthonmode = 0;
nthoffmode = 6;
rainbowmode = 0;
pong_game_speed = 50;
pong_invert_p2 = 1;
pong_invert_p1 = 1;
paddle2size = 3;
paddle1size = 3;
chenp2 = 0;
chenp1 = 0;
clock_orientation  = 0;
clock_color_speed = 200;
zeitverschiebung = 2;
randomspeed = 50;
randommode = 0;
randomefmode = 0;
rainbowspeed = 50;
mode = 0;
fan_state = 0;


clock_fix_color_h = 0;
clock_fix_color_m = 0;
clock_bright = 255;
clockcolormode = 0;

if(with_save == 1){
save_settings();
}

delay(100);
Serial.println("SETTINGS RESTORED");
}


void setup() {
  Serial.begin(9600);
  restore_settings(0);
   analogReadResolution(12);
  Serial.println("START BOOT");
 pinMode(relais,OUTPUT); 
  pinMode(fan,OUTPUT); 
 //digitalWrite(relais,LOW);
 //digitalWrite(fan,LOW);
 clock_create_template();
   Serial.println("INIT LEDs");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 standby_strip.begin();
  standby_strip.show(); // Initialize all pixels to 'off'

  
  Serial.println("I2C START");
    Wire.begin();
      zero=0x00;
  
randomSeed(analogRead(7));
   //CONTROLLER INIT
   Serial.println("NES CONTROLLER INIT");
pinMode(p1_latch,OUTPUT);
pinMode(p1_clock,OUTPUT);
pinMode(p1_datin,INPUT);
digitalWrite(p1_latch,HIGH);
digitalWrite(p1_clock,HIGH);
pinMode(p2_latch,OUTPUT);
pinMode(p2_clock,OUTPUT);
pinMode(p2_datin,INPUT);
digitalWrite(p2_latch,HIGH);
digitalWrite(p2_clock,HIGH);
    // setup the Ehternet library to talk to the Wiznet board
    
    
      Serial.println("LOAD SETTINGS");
  load_settings();
  
  
  
  
    if(use_ethernet == 1){
   if(enable_dhcp == 1){
     Serial.println("DHCP ENAVBLED : Trying to get an IP address using DHCP");
  if (Ethernet.begin(mac) == 0) {
 show_error("Failed to configure Ethernet using DHCP // TRY TO USE ALTERNATIVE IP CONFIGURATION");
  Ethernet.begin(mac, ip, gateway, subnet);
 
  }
   }else{
     Ethernet.begin(mac, ip, gateway, subnet); 
   }
  // print your local IP address:
  Serial.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(ip[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println("START WEBSERVER");
 webserver.setDefaultCommand(&rgbCmd);
  webserver.addCommand("rgb", &rgbCmd);
 webserver.addCommand("index.html", &defaultCmd);
  webserver.addCommand("settings.html", &settingsCmd);
  /* start the server to wait for connections */
  webserver.begin();
  Serial.println("START UPD CLIENT");
   Udp.begin(localPort);

 
  }
Serial.println("BOOT FINISHED");
}

void main_process(){
 if(use_ethernet == 1){webserver.processConnection();}
 getDateDs1307();
 
 if(fan_state == 1){
 digitalWrite(fan,HIGH);
 }else{
  digitalWrite(fan,LOW);
 }
 
 
}


