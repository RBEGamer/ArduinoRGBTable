#include <Adafruit_NeoPixel.h>
#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"
#include "Wire.h"
#include <DueFlashStorage.h>
#include <TextFinder.h>

DueFlashStorage dueFlashStorage;
static uint8_t mac[6] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x22 };
Adafruit_NeoPixel standby_strip = Adafruit_NeoPixel(1, 31, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, 33, NEO_RGB + NEO_KHZ800);
const int relais = 35;
const int fan = 37;
const int pi_en = 39;
const int reset_jumper = 41;






//FÜR SERVER << "";
 template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }
#define PREFIX "" //WEBSERVER ROOT URL (http://ip/xxx
WebServer webserver(PREFIX, 80);
const unsigned int feldx = 20;
const unsigned int feldy = 10;

const int baud_rate= 115200;

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
const int use_ethernet = 1,wait_for_DHCP = 0;
int enable_dhcp = 1;
int api_enable = 1;
//CLOCK VARS---------------------------------------------------------------------------------------------------
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
byte decToBcd(byte val){return ( (val/10*16) + (val%10) );}
// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val){return ( (val/16*10) + (val%16) );}
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
EthernetUDP Udp;
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



//LAUFSCHRIFT VARS  ----------------------------------------------------------------------------------
const int st_prev_begin = 21; //versatz zum ersten buchstaben damit pixelfehler am anfang nicht auffahlen
const int st_after_end = feldx;//muss einmal die feldbreite sein damit auch die ersten buchstaben eingeflogen kommen und nicht schon am anfang da stehen
int st_text_pos = 0;
const int st_maxchar = 60;
char st_chars[st_maxchar] = {'h','e','l','l','o'};
int st_char_count = 5;
int st_speed = 70;
const int st_spacing = 2;
int st_laufschrift_complete_arr[((5+st_spacing)*st_maxchar)+st_after_end+st_prev_begin][7];
int st_anchor[2] = {0,0};



//TIS VARS ----------------------------------------------------------------------------------
const int rss_prev_begin = 21; //versatz zum ersten buchstaben damit pixelfehler am anfang nicht auffahlen
const int rss_after_end = feldx;//muss einmal die feldbreite sein damit auch die ersten buchstaben eingeflogen kommen und nicht schon am anfang da stehen
int rss_text_pos = 0;
const int rss_maxchar = 140;
char rss_chars[rss_maxchar] = {'h','e','l','l','o'};
int rss_char_count = 5;
int rss_speed = 70;
const int rss_spacing = 2;
int rss_laufschrift_complete_arr[((5+rss_spacing)*rss_maxchar)+rss_after_end+rss_prev_begin][7];
int rss_anchor[2] = {0,0};


int rss_enable = 1;
int rss_state = 0;
int rss_prev_mode = 3;
const int rss_mode = 9;


int char_template[5][7];
int char_template_a[5][7];
int char_template_b[5][7];
int char_template_c[5][7];
int char_template_d[5][7];
int char_template_e[5][7];
int char_template_f[5][7];
int char_template_g[5][7];
int char_template_h[5][7];
int char_template_i[5][7];
int char_template_j[5][7];
int char_template_k[5][7];
int char_template_l[5][7];
int char_template_m[5][7];
int char_template_n[5][7];
int char_template_o[5][7];
int char_template_p[5][7];
int char_template_q[5][7];
int char_template_r[5][7];
int char_template_s[5][7];
int char_template_t[5][7];
int char_template_u[5][7];
int char_template_v[5][7];
int char_template_w[5][7];
int char_template_x[5][7];
int char_template_y[5][7];
int char_template_z[5][7];
int char_template_1[5][7];
int char_template_2[5][7];
int char_template_3[5][7];
int char_template_4[5][7];
int char_template_5[5][7];
int char_template_6[5][7];
int char_template_7[5][7];
int char_template_8[5][7];
int char_template_9[5][7];
int char_template_0[5][7];
int char_template_nothing[5][7];


int char_template_sharp[5][7];
int char_template_dot[5][7];
int char_template_comma[5][7];
int char_template_bracketopen[5][7];
int char_template_bracketclose[5][7];
int char_template_equal[5][7];
int char_template_plus[5][7];
int char_template_minus[5][7];
int char_template_bang[5][7];
int char_template_doubledot[5][7];
int char_template_underline[5][7];
int char_template_quest[5][7];
int char_template_percent[5][7];
int char_template_high[5][7];
int char_template_simikolon[5][7];
int char_template_smaller[5][7];
int char_template_bigger[5][7];
int char_template_hline[5][7];
int char_template_star[5][7];
int char_template_at[5][7];
//ENDE LAUFSCHRIFT VARS ----------------------------------------------------------------------------------






void st_text_to_arr(){

  
  for (int i = 0; i < ((5+st_spacing)*st_maxchar)+st_after_end+st_prev_begin; i++){for (int j = 0; j < 7; j++){   
st_laufschrift_complete_arr[i][j] =0;
}}
  
  
  
  
   for (int k = 0; k < st_char_count; k++){
   

  if(st_chars[k] == 'a' || st_chars[k] == 'A'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_a[i][j];      
    }} 
  }
    if(st_chars[k] == 'b'|| st_chars[k] == 'B'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_b[i][j];      
    }} 
  }
      if(st_chars[k] == 'c'|| st_chars[k] == 'C'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_c[i][j];      
    }} 
  }
  
        if(st_chars[k] == 'd'|| st_chars[k] == 'D'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_d[i][j];      
    }} 
  }

        if(st_chars[k] == 'e'|| st_chars[k] == 'E'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_e[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'f'|| st_chars[k] == 'F'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_f[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'g'|| st_chars[k] == 'G'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_g[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'h'|| st_chars[k] == 'H'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_h[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'i'|| st_chars[k] == 'I'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_i[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'j'|| st_chars[k] == 'J'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_j[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'k'|| st_chars[k] == 'K'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_k[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'l'|| st_chars[k] == 'L'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_l[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'm'|| st_chars[k] == 'M'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_m[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'n'|| st_chars[k] == 'N'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_n[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'o'|| st_chars[k] == 'O'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_o[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'p'|| st_chars[k] == 'P'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_p[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'q'|| st_chars[k] == 'Q'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_q[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'r'|| st_chars[k] == 'R'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_r[i][j];      
    }} 
  }
  
          if(st_chars[k] == 's'|| st_chars[k] == 'S'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_s[i][j];      
    }} 
  }
  
          if(st_chars[k] == 't'|| st_chars[k] == 'T'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_t[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'u'|| st_chars[k] == 'U'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_u[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'v'|| st_chars[k] == 'V'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_v[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'w'|| st_chars[k] == 'W'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_w[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'x'|| st_chars[k] == 'X'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_x[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'y'|| st_chars[k] == 'Y'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_y[i][j];      
    }} 
  }
  
          if(st_chars[k] == 'z'|| st_chars[k] == 'Z'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_z[i][j];      
    }} 
  }
  
          if(st_chars[k] == '1'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_1[i][j];      
    }} 
  }
  
          if(st_chars[k] == '2'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_2[i][j];      
    }} 
  }
  
          if(st_chars[k] == '3'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_3[i][j];      
    }} 
  }
  
          if(st_chars[k] == '4'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_4[i][j];      
    }} 
  }
  
          if(st_chars[k] == '5'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_5[i][j];      
    }} 
  }
  
          if(st_chars[k] == '6'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_6[i][j];      
    }} 
  }
  
          if(st_chars[k] == '7'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_7[i][j];      
    }} 
  }
  
          if(st_chars[k] == '8'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_8[i][j];      
    }} 
  }
  
          if(st_chars[k] == '9'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_9[i][j];      
    }} 
  }
  
          if(st_chars[k] == '0'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_0[i][j];      
    }} 
  }
  
  
  
            if(st_chars[k] == '#'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_sharp[i][j];      
    }} 
  }
  
              if(st_chars[k] == '.'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_dot[i][j];      
    }} 
  }
  
    
              if(st_chars[k] == ','){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_comma[i][j];      
    }} 
  }
     
              if(st_chars[k] == '(' || st_chars[k] == '['){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_bracketopen[i][j];      
    }} 
  } 
  
  
                if(st_chars[k] == ')' || st_chars[k] == ']'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_bracketclose[i][j];      
    }} 
  } 
  
  
    
            if(st_chars[k] == '='){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_equal[i][j];      
    }} 
  }
  
      
            if(st_chars[k] == '+'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_plus[i][j];      
    }} 
  }
  
              if(st_chars[k] == '-'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_minus[i][j];      
    }} 
  }
  
                if(st_chars[k] == '!'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_bang[i][j];      
    }} 
  }


            if(st_chars[k] == ':'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_doubledot[i][j];      
    }} 
  }

            if(st_chars[k] == '_'){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_underline[i][j];      
    }} 
  }
  
  if(st_chars[k] == '?'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_quest[i][j]; }}}
  
  if(st_chars[k] == '%'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_percent[i][j]; }}}
  
  if(st_chars[k] == '^'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_high[i][j]; }}}
  
  if(st_chars[k] == ';'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_simikolon[i][j]; }}}
  
  if(st_chars[k] == '<'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_smaller[i][j]; }}}
  
  if(st_chars[k] == '>'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_bigger[i][j]; }}}
  
  if(st_chars[k] == '|'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_hline[i][j]; }}}
  
  if(st_chars[k] == '*'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_star[i][j]; }}}
  
  if(st_chars[k] == '@'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_at[i][j]; }}}
  
  
            if(st_chars[k] == ' '){
     for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
  char_template[i][j] = char_template_nothing[i][j];      
    }} 
  }


for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){ 
  
st_laufschrift_complete_arr[(k*st_spacing*3)+st_prev_begin+i][j] = char_template[i][j];
}}
 
 }






}











void rss_text_to_arr(){
    
    
for (int i = 0; i < ((5+rss_spacing)*rss_maxchar)+rss_after_end+rss_prev_begin; i++){for (int j = 0; j < 7; j++){
    rss_laufschrift_complete_arr[i][j] =0;
}}
    
    
    for (int k = 0; k < rss_char_count; k++){
        
        
        if(rss_chars[k] == 'a' || rss_chars[k] == 'A'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_a[i][j];
            }}
        }
        if(rss_chars[k] == 'b'|| rss_chars[k] == 'B'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_b[i][j];
            }}
        }
        if(rss_chars[k] == 'c'|| rss_chars[k] == 'C'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_c[i][j];
            }}
        }
        
        if(rss_chars[k] == 'd'|| rss_chars[k] == 'D'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_d[i][j];
            }}
        }
        
        if(rss_chars[k] == 'e'|| rss_chars[k] == 'E'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_e[i][j];
            }}
        }
        
        if(rss_chars[k] == 'f'|| rss_chars[k] == 'F'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_f[i][j];
            }}
        }
        
        if(rss_chars[k] == 'g'|| rss_chars[k] == 'G'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_g[i][j];
            }}
        }
        
        if(rss_chars[k] == 'h'|| rss_chars[k] == 'H'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_h[i][j];
            }}
        }
        
        if(rss_chars[k] == 'i'|| rss_chars[k] == 'I'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_i[i][j];
            }}
        }
        
        if(rss_chars[k] == 'j'|| rss_chars[k] == 'J'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_j[i][j];
            }}
        }
        
        if(rss_chars[k] == 'k'|| rss_chars[k] == 'K'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_k[i][j];
            }}
        }
        
        if(rss_chars[k] == 'l'|| rss_chars[k] == 'L'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_l[i][j];
            }}
        }
        
        if(rss_chars[k] == 'm'|| rss_chars[k] == 'M'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_m[i][j];
            }}
        }
        
        if(rss_chars[k] == 'n'|| rss_chars[k] == 'N'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_n[i][j];
            }}
        }
        
        if(rss_chars[k] == 'o'|| rss_chars[k] == 'O'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_o[i][j];
            }}
        }
        
        if(rss_chars[k] == 'p'|| rss_chars[k] == 'P'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_p[i][j];
            }}
        }
        
        if(rss_chars[k] == 'q'|| rss_chars[k] == 'Q'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_q[i][j];
            }}
        }
        
        if(rss_chars[k] == 'r'|| rss_chars[k] == 'R'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_r[i][j];
            }}
        }
        
        if(rss_chars[k] == 's'|| rss_chars[k] == 'S'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_s[i][j];
            }}
        }
        
        if(rss_chars[k] == 't'|| rss_chars[k] == 'T'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_t[i][j];
            }}
        }
        
        if(rss_chars[k] == 'u'|| rss_chars[k] == 'U'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_u[i][j];
            }}
        }
        
        if(rss_chars[k] == 'v'|| rss_chars[k] == 'V'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_v[i][j];
            }}
        }
        
        if(rss_chars[k] == 'w'|| rss_chars[k] == 'W'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_w[i][j];
            }}
        }
        
        if(rss_chars[k] == 'x'|| rss_chars[k] == 'X'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_x[i][j];
            }}
        }
        
        if(rss_chars[k] == 'y'|| rss_chars[k] == 'Y'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_y[i][j];
            }}
        }
        
        if(rss_chars[k] == 'z'|| rss_chars[k] == 'Z'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_z[i][j];
            }}
        }
        
        if(rss_chars[k] == '1'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_1[i][j];
            }}
        }
        
        if(rss_chars[k] == '2'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_2[i][j];
            }}
        }
        
        if(rss_chars[k] == '3'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_3[i][j];
            }}
        }
        
        if(rss_chars[k] == '4'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_4[i][j];
            }}
        }
        
        if(rss_chars[k] == '5'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_5[i][j];
            }}
        }
        
        if(rss_chars[k] == '6'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_6[i][j];
            }}
        }
        
        if(rss_chars[k] == '7'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_7[i][j];
            }}
        }
        
        if(rss_chars[k] == '8'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_8[i][j];
            }}
        }
        
        if(rss_chars[k] == '9'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_9[i][j];
            }}
        }
        
        if(rss_chars[k] == '0'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_0[i][j];
            }}
        }
        
        
        
        if(rss_chars[k] == '#'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_sharp[i][j];
            }}
        }
        
        if(rss_chars[k] == '.'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_dot[i][j];
            }}
        }
        
        
        if(rss_chars[k] == ','){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_comma[i][j];
            }}
        }
        
        if(rss_chars[k] == '(' || rss_chars[k] == '['){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_bracketopen[i][j];
            }}
        }
        
        
        if(rss_chars[k] == ')' || rss_chars[k] == ']'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_bracketclose[i][j];
            }}
        }
        
        
        
        if(rss_chars[k] == '='){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_equal[i][j];
            }}
        }
        
        
        if(rss_chars[k] == '+'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_plus[i][j];
            }}
        }
        
        if(rss_chars[k] == '-'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_minus[i][j];
            }}
        }
        
        if(rss_chars[k] == '!'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_bang[i][j];
            }}
        }
        
        
        if(rss_chars[k] == ':'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){
                char_template[i][j] = char_template_doubledot[i][j];
            }} 
        }
        
        if(rss_chars[k] == '_'){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
                char_template[i][j] = char_template_underline[i][j];      
            }} 
        }
        
        if(rss_chars[k] == '?'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_quest[i][j]; }}}
        
        if(rss_chars[k] == '%'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_percent[i][j]; }}}
        
        if(rss_chars[k] == '^'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_high[i][j]; }}}
        
        if(rss_chars[k] == ';'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_simikolon[i][j]; }}}
        
        if(rss_chars[k] == '<'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_smaller[i][j]; }}}
        
        if(rss_chars[k] == '>'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_bigger[i][j]; }}}
        
        if(rss_chars[k] == '|'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_hline[i][j]; }}}
        
        if(rss_chars[k] == '*'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_star[i][j]; }}}
        
        if(rss_chars[k] == '@'){for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){  char_template[i][j] = char_template_at[i][j]; }}}
        
        
        if(rss_chars[k] == ' '){
            for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){       
                char_template[i][j] = char_template_nothing[i][j];      
            }} 
        }
        
        
        for (int i = 0; i < 5; i++){for (int j = 0; j < 7; j++){ 
            
            rss_laufschrift_complete_arr[(k*rss_spacing*3)+rss_prev_begin+i][j] = char_template[i][j];
        }}
        
    }
    
    
    
    
    
    
}



int st_fix_color = 0;
int st_rain_speed = 5;
int st_color_mode = 0;
int st_bright = 255;
 int st_color = 0;
int st_color_counter = 0;

void st_play(){

   
 

  if(st_text_pos >= ((5+st_spacing)*st_char_count)+st_after_end+st_prev_begin){
  st_text_pos = 0;
  }else{
  st_text_pos++;
  }
  
  
  if(st_color_counter >= 256){
  st_color_counter = 0;
  }else{
  st_color_counter += st_rain_speed;
  }
  
  
  if(st_color_mode == 0){
st_color =  Wheel(st_color_counter);
  }else if(st_color_mode == 1){
  
  
    
      if(st_fix_color == 0){ 
   st_color =  strip.Color(st_bright, 0, 0);
  }else  if(st_fix_color == 1){
  st_color =  strip.Color(0, st_bright, 0);
  }else  if(st_fix_color == 2){
  st_color =  strip.Color(0, 0, st_bright);
  }else  if(st_fix_color == 3){
  st_color =  strip.Color(0, st_bright, st_bright);
   }else  if(st_fix_color == 4){
  st_color =  strip.Color(st_bright, 0, st_bright);
   }else  if(st_fix_color == 5){
       st_color =  strip.Color(st_bright, st_bright,0);
   }else  if(st_fix_color == 6){
  st_color =  strip.Color(st_bright, st_bright, st_bright);
  }else{
  st_color =  strip.Color(0, 0, 255);
  }

    
    
    
  }else if(st_color_mode == 2){
  
  }else{
    st_color =  strip.Color(0, 0, 255);
  }
  
  
  
        for (int i = 0; i < 20; i++){
    for (int j = 0; j < 7; j++){   
      
      if(st_color_mode == 2){
       st_color =  Wheel(random(0,257));
      }
      
  if(st_laufschrift_complete_arr[st_prev_begin+st_text_pos+i-st_after_end][j] == 1){    
//if(st_laufschrift_complete_arr[st_text_pos+i-st_after_end][j] == 1){
        strip.setPixelColor(get_led_number(i+st_anchor[0],j+st_anchor[1]),  st_color); 
}else{    
      strip.setPixelColor(get_led_number(i+st_anchor[0],j+st_anchor[1]),  strip.Color(0, 0, 0));     
   }
 
   
 
    
    
    
  }
        }
  
  
 
delay(st_speed);
}//ENDE VOID





//PONG VARS ----------------------------------------------------------------------------------
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
"<meta http-equiv='content-type' content='text/html; charset=utf-8'>"
"<meta charset='utf-8'>" 
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
"<a href='api.html'>API</a>"
"<a href='tis.html'>T.I.S</a>"
"</div>"
"</div>"
"<div class='right'>"
"<div class='content'>";
P(pend)="</div>"
"</div>"
"</body>"
"</html>";

P(api_table) ="<style type='text/css'>"
".tg  {border-collapse:collapse;border-spacing:0;margin:0px auto;}"
".tg td{font-family:Arial, sans-serif;font-size:14px;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;}"
".tg th{font-family:Arial, sans-serif;font-size:14px;font-weight:normal;padding:10px 5px;border-style:solid;border-width:1px;overflow:hidden;word-break:normal;}"
".tg .tg-s6z2{text-align:center}"
"</style>"
"<table class='tg' style='undefined;table-layout: fixed; width: 520px'>"
"<colgroup>"
"<col style='width: 160px'>"
"<col style='width: 100px'>"
"<col style='width: 100px'>"
"<col style='width: 160px'>"
"</colgroup>"
"  <tr>"
"    <th class='tg-031e'>VARIABLE</th>"
"    <th class='tg-031e'>GET</th>"
"    <th class='tg-031e'>SET</th>"
"    <th class='tg-031e'>DESCRIPTION</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>baud_rate</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>Serial (0-3) Baud Rate</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>fan_state</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>Fan-State</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>mode</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>CURRENT lED-MODE</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>rainbowspeed</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>RAINBOW CYCLE SPEED</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>randomspeed</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>RANDOMMODE SPEED</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>randomefmode</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>RANDOMMODE TYPE</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>enable_dhcp</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>DHCP STATE</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>wait_for_DHCP</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>STOP IF NO DHCP-SERVER IS AVARIABLE</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>zeitverschiebung</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>TimeZone </th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>nth</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>NIGHTMODE START-HOUR</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>nthe</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>NIGHTMODE STOP HOUR</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>nthen</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>NIGHTMODE STATE</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>nthstate</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>IS NIGHTMODE CURRENTLY ON</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>nthonmode</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>LED MODE IF NIGHTMODE CURRENTLY ON</th>"
" </tr>"
"  <tr>"
"    <td class='tg-031e'>nthoffmode</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>LED MODE IF NIGHTMODE CURRENTLY OFF</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>clock_orientation</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>CLOCK DISPLAY ORIENTATION</th>"
"  </tr>"


"  <tr>"
"    <td class='tg-031e'>player1score</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>GAME-SCORE PLAYER 1</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>player2score</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>GANE-SCORE PLAYER 2</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>pong_game_speed</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>PONG GAME SPEED</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>paddle1size</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>PONG: PADDLE-SIZE PLAYER 1</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>paddle2size</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>PONG: PADDLE-SIZE PLAYER 2</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>st_speed</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>SCROLLING TEXT SPEED</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>chenp1</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>PONG: ENABLE CHEATING PLAYER 1</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>chenp2</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>PONG: ENABLE CHEATING PLAYER 2</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>feldx</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <td class='tg-031e'>LED MATRIX SIZE X</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>feldy</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <td class='tg-031e'>LED MATRIX SIZE Y</td>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>hour</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>CLOCK HOURS</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>minute</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>CLOCK MINUTES</th>"
"  </tr>"
"  <tr>"
"    <td class='tg-031e'>second</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>CLOCK SECONDS</th>"
"  </tr>"

"  <tr>"
"    <td class='tg-031e'>reset_jumper</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>STATE OF THE RESET JUMPER</th>"
"  </tr>"

"  <tr>"
"    <td class='tg-031e'>st_char_count</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>AMOUNT OF CHARS IN THE SCROLLING TEXT BUFFER</th>"
"  </tr>"

"  <tr>"
"    <td class='tg-031e'>relais</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>STATE OF THE LED-MATRIX RELAIS</th>"
"  </tr>"

"  <tr>"
"    <td class='tg-031e'>rss_enable</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>T.I.S STATE</th>"
"  </tr>"

"  <tr>"
"    <td class='tg-031e'>rss_state</td>"
"    <td class='tg-031e'>X</td>"
"    <td class='tg-031e'></td>"
"    <th class='tg-031e'>IS THE T.I.S-MODE CURRENTLY RUNNING</th>"
"  </tr>"




"  <tr>"
"    <td class='tg-031e'>save</td>"
"    <td class='tg-031e'></td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>SAVE SETTINGS (WITHOUT ANY PARAMETER)</th>"
"  </tr>"

"  <tr>"
"    <td class='tg-031e'>gettime</td>"
"    <td class='tg-031e'></td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>SYNC RTC WITH NTP (WITHOUT ANY PARAMETER)</th>"
"  </tr>"

"  <tr>"
"    <td class='tg-031e'>clearscreen</td>"
"    <td class='tg-031e'></td>"
"    <td class='tg-031e'>X</td>"
"    <th class='tg-031e'>CLEAR COMPLETE SCREEN</th>"
"  </tr>"




"</table>";


//----------------------------------------------------CLOCK------------------------------------
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
unsigned long sendNTPpacket(IPAddress& address){
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
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer,NTP_PACKET_SIZE);
  Udp.endPacket(); 
}

void get_ntp_time(int en_ds1307 = 0)
{
  sendNTPpacket(timeServer); // send an NTP packet to a time server
  delay(1000);  
  if ( Udp.parsePacket() ) {  
    Udp.read(packetBuffer,NTP_PACKET_SIZE);  // read the packet into the buffer
    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);  
    unsigned long secsSince1900 = highWord << 16 | lowWord;  
    const unsigned long seventyYears = 2208988800UL;     
    unsigned long epoch = secsSince1900 - seventyYears;  
    Serial.println(epoch);                               
    ntph=(epoch  % 86400L) / 3600; // print the hour (86400 equals secs per day) 
    ntpm=(epoch  % 3600) / 60; // print the minute (3600 equals secs per minute) 
    if(en_ds1307 == 0){ntps = epoch %60;}
    Serial.print("NTP:");Serial.print(ntph);Serial.print(":");Serial.println(ntpm);  
   //hier die zeitverschiebung beachten
   ntph  = ntph+zeitverschiebung;
   if(ntph == 24){
   ntph = 0;
   }if(ntph > 24){
   ntph = ntph -24;
      }if(ntph < 0){
   ntph = 24-ntph;
   }
   dayOfWeek = 1;
   dayOfMonth = 1;
   month = 1;
   year= 1;
   Wire.beginTransmission(DS1307_I2C_ADDRESS);
   I2C_WRITE(zero);
   I2C_WRITE(decToBcd(ntps) & 0x7f);    // 0 to bit 7 starts the clock
   I2C_WRITE(decToBcd(ntpm));
   I2C_WRITE(decToBcd(ntph));      // If you want 12 hour am/pm you need to set// bit 6 (also need to change readDateDs1307)                          
   I2C_WRITE(decToBcd(dayOfWeek));
   I2C_WRITE(decToBcd(dayOfMonth));
   I2C_WRITE(decToBcd(month));
   I2C_WRITE(decToBcd(year));
   Wire.endTransmission();
  }
}



void display_clock(int hz = 0, int he  = 0, int mz  = 0, int me = 0){
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
       clock_h_color =  strip.Color(clock_bright, clock_bright,0);
   }else  if(clock_fix_color_h == 6){
  clock_h_color =  strip.Color(clock_bright, clock_bright, clock_bright);
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
     }else  if(clock_fix_color_m == 6){
  clock_m_color =  strip.Color(clock_bright, clock_bright, clock_bright);
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




void create_fonttemplate(){ 
    // NOTHING
  number_template_nothing[0][0]=0;number_template_nothing[1][0]=0;number_template_nothing[2][0]=0;number_template_nothing[3][0]=0;
  number_template_nothing[0][1]=0;number_template_nothing[1][1]=0;number_template_nothing[2][1]=0;number_template_nothing[3][1]=0;
  number_template_nothing[0][2]=0;number_template_nothing[1][2]=0;number_template_nothing[2][2]=0;number_template_nothing[3][2]=0;
  number_template_nothing[0][3]=0;number_template_nothing[1][3]=0;number_template_nothing[2][3]=0;number_template_nothing[3][3]=0;
  number_template_nothing[0][4]=0;number_template_nothing[1][4]=0;number_template_nothing[2][4]=0;number_template_nothing[3][4]=0;
  number_template_nothing[0][5]=0;number_template_nothing[1][5]=0;number_template_nothing[2][5]=0;number_template_nothing[3][5]=0;
  number_template_nothing[0][6]=0;number_template_nothing[1][6]=0;number_template_nothing[2][6]=0;number_template_nothing[3][6]=0;
  // 0
  number_template_0[0][0]=1;number_template_0[1][0]=1;number_template_0[2][0]=1;number_template_0[3][0]=1;
  number_template_0[0][1]=1;number_template_0[1][1]=0;number_template_0[2][1]=0;number_template_0[3][1]=1;
  number_template_0[0][2]=1;number_template_0[1][2]=0;number_template_0[2][2]=0;number_template_0[3][2]=1;
  number_template_0[0][3]=1;number_template_0[1][3]=0;number_template_0[2][3]=0;number_template_0[3][3]=1;
  number_template_0[0][4]=1;number_template_0[1][4]=0;number_template_0[2][4]=0;number_template_0[3][4]=1;
  number_template_0[0][5]=1;number_template_0[1][5]=0;number_template_0[2][5]=0;number_template_0[3][5]=1;
  number_template_0[0][6]=1;number_template_0[1][6]=1;number_template_0[2][6]=1;number_template_0[3][6]=1;
  // 1
  number_template_1[0][0]=0;number_template_1[1][0]=0;number_template_1[2][0]=1;number_template_1[3][0]=0;
  number_template_1[0][1]=0;number_template_1[1][1]=1;number_template_1[2][1]=1;number_template_1[3][1]=0;
  number_template_1[0][2]=1;number_template_1[1][2]=0;number_template_1[2][2]=1;number_template_1[3][2]=0;
  number_template_1[0][3]=0;number_template_1[1][3]=0;number_template_1[2][3]=1;number_template_1[3][3]=0;
  number_template_1[0][4]=0;number_template_1[1][4]=0;number_template_1[2][4]=1;number_template_1[3][4]=0;
  number_template_1[0][5]=0;number_template_1[1][5]=0;number_template_1[2][5]=1;number_template_1[3][5]=0;
  number_template_1[0][6]=1;number_template_1[1][6]=1;number_template_1[2][6]=1;number_template_1[3][6]=1;
    // 2
  number_template_2[0][0]=1;number_template_2[1][0]=1;number_template_2[2][0]=1;number_template_2[3][0]=1;
  number_template_2[0][1]=0;number_template_2[1][1]=0;number_template_2[2][1]=0;number_template_2[3][1]=1;
  number_template_2[0][2]=0;number_template_2[1][2]=0;number_template_2[2][2]=0;number_template_2[3][2]=1;
  number_template_2[0][3]=0;number_template_2[1][3]=1;number_template_2[2][3]=1;number_template_2[3][3]=0;
  number_template_2[0][4]=1;number_template_2[1][4]=0;number_template_2[2][4]=0;number_template_2[3][4]=0;
  number_template_2[0][5]=1;number_template_2[1][5]=0;number_template_2[2][5]=0;number_template_2[3][5]=0;
  number_template_2[0][6]=1;number_template_2[1][6]=1;number_template_2[2][6]=1;number_template_2[3][6]=1;
      // 3
  number_template_3[0][0]=1;number_template_3[1][0]=1;number_template_3[2][0]=1;number_template_3[3][0]=0;
  number_template_3[0][1]=0;number_template_3[1][1]=0;number_template_3[2][1]=0;number_template_3[3][1]=1;
  number_template_3[0][2]=0;number_template_3[1][2]=0;number_template_3[2][2]=0;number_template_3[3][2]=1;
  number_template_3[0][3]=1;number_template_3[1][3]=1;number_template_3[2][3]=1;number_template_3[3][3]=0;
  number_template_3[0][4]=0;number_template_3[1][4]=0;number_template_3[2][4]=0;number_template_3[3][4]=1;
  number_template_3[0][5]=0;number_template_3[1][5]=0;number_template_3[2][5]=0;number_template_3[3][5]=1;
  number_template_3[0][6]=1;number_template_3[1][6]=1;number_template_3[2][6]=1;number_template_3[3][6]=0;
    // 4
  number_template_4[0][0]=1;number_template_4[1][0]=0;number_template_4[2][0]=0;number_template_4[3][0]=1;
  number_template_4[0][1]=1;number_template_4[1][1]=0;number_template_4[2][1]=0;number_template_4[3][1]=1;
  number_template_4[0][2]=1;number_template_4[1][2]=0;number_template_4[2][2]=0;number_template_4[3][2]=1;
  number_template_4[0][3]=0;number_template_4[1][3]=1;number_template_4[2][3]=1;number_template_4[3][3]=1;
  number_template_4[0][4]=0;number_template_4[1][4]=0;number_template_4[2][4]=0;number_template_4[3][4]=1;
  number_template_4[0][5]=0;number_template_4[1][5]=0;number_template_4[2][5]=0;number_template_4[3][5]=1;
  number_template_4[0][6]=0;number_template_4[1][6]=0;number_template_4[2][6]=0;number_template_4[3][6]=1;
   // 5
  number_template_5[0][0]=1;number_template_5[1][0]=1;number_template_5[2][0]=1;number_template_5[3][0]=1;
  number_template_5[0][1]=1;number_template_5[1][1]=0;number_template_5[2][1]=0;number_template_5[3][1]=0;
  number_template_5[0][2]=1;number_template_5[1][2]=0;number_template_5[2][2]=0;number_template_5[3][2]=0;
  number_template_5[0][3]=0;number_template_5[1][3]=1;number_template_5[2][3]=1;number_template_5[3][3]=0;
  number_template_5[0][4]=0;number_template_5[1][4]=0;number_template_5[2][4]=0;number_template_5[3][4]=1;
  number_template_5[0][5]=0;number_template_5[1][5]=0;number_template_5[2][5]=0;number_template_5[3][5]=1;
  number_template_5[0][6]=1;number_template_5[1][6]=1;number_template_5[2][6]=1;number_template_5[3][6]=1;
// 6
  number_template_6[0][0]=1;number_template_6[1][0]=1;number_template_6[2][0]=1;number_template_6[3][0]=1;
  number_template_6[0][1]=1;number_template_6[1][1]=0;number_template_6[2][1]=0;number_template_6[3][1]=0;
  number_template_6[0][2]=1;number_template_6[1][2]=0;number_template_6[2][2]=0;number_template_6[3][2]=0;
  number_template_6[0][3]=1;number_template_6[1][3]=1;number_template_6[2][3]=1;number_template_6[3][3]=1;
  number_template_6[0][4]=1;number_template_6[1][4]=0;number_template_6[2][4]=0;number_template_6[3][4]=1;
  number_template_6[0][5]=1;number_template_6[1][5]=0;number_template_6[2][5]=0;number_template_6[3][5]=1;
  number_template_6[0][6]=1;number_template_6[1][6]=1;number_template_6[2][6]=1;number_template_6[3][6]=1;
 // 7
  number_template_7[0][0]=1;number_template_7[1][0]=1;number_template_7[2][0]=1;number_template_7[3][0]=1;
  number_template_7[0][1]=0;number_template_7[1][1]=0;number_template_7[2][1]=0;number_template_7[3][1]=1;
  number_template_7[0][2]=0;number_template_7[1][2]=0;number_template_7[2][2]=0;number_template_7[3][2]=1;
  number_template_7[0][3]=0;number_template_7[1][3]=0;number_template_7[2][3]=0;number_template_7[3][3]=1;
  number_template_7[0][4]=0;number_template_7[1][4]=0;number_template_7[2][4]=0;number_template_7[3][4]=1;
  number_template_7[0][5]=0;number_template_7[1][5]=0;number_template_7[2][5]=0;number_template_7[3][5]=1;
  number_template_7[0][6]=0;number_template_7[1][6]=0;number_template_7[2][6]=0;number_template_7[3][6]=1;
// 8
  number_template_8[0][0]=1;number_template_8[1][0]=1;number_template_8[2][0]=1;number_template_8[3][0]=1;
  number_template_8[0][1]=1;number_template_8[1][1]=0;number_template_8[2][1]=0;number_template_8[3][1]=1;
  number_template_8[0][2]=1;number_template_8[1][2]=0;number_template_8[2][2]=0;number_template_8[3][2]=1;
  number_template_8[0][3]=1;number_template_8[1][3]=1;number_template_8[2][3]=1;number_template_8[3][3]=1;
  number_template_8[0][4]=1;number_template_8[1][4]=0;number_template_8[2][4]=0;number_template_8[3][4]=1;
  number_template_8[0][5]=1;number_template_8[1][5]=0;number_template_8[2][5]=0;number_template_8[3][5]=1;
  number_template_8[0][6]=1;number_template_8[1][6]=1;number_template_8[2][6]=1;number_template_8[3][6]=1;
// 9
  number_template_9[0][0]=1;number_template_9[1][0]=1;number_template_9[2][0]=1;number_template_9[3][0]=1;
  number_template_9[0][1]=1;number_template_9[1][1]=0;number_template_9[2][1]=0;number_template_9[3][1]=1;
  number_template_9[0][2]=1;number_template_9[1][2]=0;number_template_9[2][2]=0;number_template_9[3][2]=1;
  number_template_9[0][3]=1;number_template_9[1][3]=1;number_template_9[2][3]=1;number_template_9[3][3]=1;
  number_template_9[0][4]=0;number_template_9[1][4]=0;number_template_9[2][4]=0;number_template_9[3][4]=1;
  number_template_9[0][5]=0;number_template_9[1][5]=0;number_template_9[2][5]=0;number_template_9[3][5]=1;
  number_template_9[0][6]=1;number_template_9[1][6]=1;number_template_9[2][6]=1;number_template_9[3][6]=1;
  
  


//a				
char_template_a[0][0]=1;	char_template_a[1][0]=1;	char_template_a[2][0]=1;	char_template_a[3][0]=1;	char_template_a[4][0]=1;
char_template_a[0][1]=1;	char_template_a[1][1]=0;	char_template_a[2][1]=0;	char_template_a[3][1]=0;	char_template_a[4][1]=1;
char_template_a[0][2]=1;	char_template_a[1][2]=0;	char_template_a[2][2]=0;	char_template_a[3][2]=0;	char_template_a[4][2]=1;
char_template_a[0][3]=1;	char_template_a[1][3]=1;	char_template_a[2][3]=1;	char_template_a[3][3]=1;	char_template_a[4][3]=1;
char_template_a[0][4]=1;	char_template_a[1][4]=0;	char_template_a[2][4]=0;	char_template_a[3][4]=0;	char_template_a[4][4]=1;
char_template_a[0][5]=1;	char_template_a[1][5]=0;	char_template_a[2][5]=0;	char_template_a[3][5]=0;	char_template_a[4][5]=1;
char_template_a[0][6]=1;	char_template_a[1][6]=0;	char_template_a[2][6]=0;	char_template_a[3][6]=0;	char_template_a[4][6]=1;
//b				
char_template_b[0][0]=1;	char_template_b[1][0]=1;	char_template_b[2][0]=1;	char_template_b[3][0]=1;	char_template_b[4][0]=0;
char_template_b[0][1]=1;	char_template_b[1][1]=0;	char_template_b[2][1]=0;	char_template_b[3][1]=0;	char_template_b[4][1]=1;
char_template_b[0][2]=1;	char_template_b[1][2]=0;	char_template_b[2][2]=0;	char_template_b[3][2]=0;	char_template_b[4][2]=1;
char_template_b[0][3]=1;	char_template_b[1][3]=1;	char_template_b[2][3]=1;	char_template_b[3][3]=1;	char_template_b[4][3]=0;
char_template_b[0][4]=1;	char_template_b[1][4]=0;	char_template_b[2][4]=0;	char_template_b[3][4]=0;	char_template_b[4][4]=1;
char_template_b[0][5]=1;	char_template_b[1][5]=0;	char_template_b[2][5]=0;	char_template_b[3][5]=0;	char_template_b[4][5]=1;
char_template_b[0][6]=1;	char_template_b[1][6]=1;	char_template_b[2][6]=1;	char_template_b[3][6]=1;	char_template_b[4][6]=0;
//c				
char_template_c[0][0]=0;	char_template_c[1][0]=1;	char_template_c[2][0]=1;	char_template_c[3][0]=1;	char_template_c[4][0]=1;
char_template_c[0][1]=1;	char_template_c[1][1]=0;	char_template_c[2][1]=0;	char_template_c[3][1]=0;	char_template_c[4][1]=0;
char_template_c[0][2]=1;	char_template_c[1][2]=0;	char_template_c[2][2]=0;	char_template_c[3][2]=0;	char_template_c[4][2]=0;
char_template_c[0][3]=1;	char_template_c[1][3]=0;	char_template_c[2][3]=0;	char_template_c[3][3]=0;	char_template_c[4][3]=0;
char_template_c[0][4]=1;	char_template_c[1][4]=0;	char_template_c[2][4]=0;	char_template_c[3][4]=0;	char_template_c[4][4]=0;
char_template_c[0][5]=1;	char_template_c[1][5]=0;	char_template_c[2][5]=0;	char_template_c[3][5]=0;	char_template_c[4][5]=0;
char_template_c[0][6]=0;	char_template_c[1][6]=1;	char_template_c[2][6]=1;	char_template_c[3][6]=1;	char_template_c[4][6]=1;
//d				
char_template_d[0][0]=1;	char_template_d[1][0]=1;	char_template_d[2][0]=1;	char_template_d[3][0]=1;	char_template_d[4][0]=0;
char_template_d[0][1]=1;	char_template_d[1][1]=0;	char_template_d[2][1]=0;	char_template_d[3][1]=0;	char_template_d[4][1]=1;
char_template_d[0][2]=1;	char_template_d[1][2]=0;	char_template_d[2][2]=0;	char_template_d[3][2]=0;	char_template_d[4][2]=1;
char_template_d[0][3]=1;	char_template_d[1][3]=0;	char_template_d[2][3]=0;	char_template_d[3][3]=0;	char_template_d[4][3]=1;
char_template_d[0][4]=1;	char_template_d[1][4]=0;	char_template_d[2][4]=0;	char_template_d[3][4]=0;	char_template_d[4][4]=1;
char_template_d[0][5]=1;	char_template_d[1][5]=0;	char_template_d[2][5]=0;	char_template_d[3][5]=0;	char_template_d[4][5]=1;
char_template_d[0][6]=1;	char_template_d[1][6]=1;	char_template_d[2][6]=1;	char_template_d[3][6]=1;	char_template_d[4][6]=0;
//e				
char_template_e[0][0]=1;	char_template_e[1][0]=1;	char_template_e[2][0]=1;	char_template_e[3][0]=1;	char_template_e[4][0]=1;
char_template_e[0][1]=1;	char_template_e[1][1]=0;	char_template_e[2][1]=0;	char_template_e[3][1]=0;	char_template_e[4][1]=0;
char_template_e[0][2]=1;	char_template_e[1][2]=0;	char_template_e[2][2]=0;	char_template_e[3][2]=0;	char_template_e[4][2]=0;
char_template_e[0][3]=1;	char_template_e[1][3]=1;	char_template_e[2][3]=1;	char_template_e[3][3]=1;	char_template_e[4][3]=0;
char_template_e[0][4]=1;	char_template_e[1][4]=0;	char_template_e[2][4]=0;	char_template_e[3][4]=0;	char_template_e[4][4]=0;
char_template_e[0][5]=1;	char_template_e[1][5]=0;	char_template_e[2][5]=0;	char_template_e[3][5]=0;	char_template_e[4][5]=0;
char_template_e[0][6]=1;	char_template_e[1][6]=1;	char_template_e[2][6]=1;	char_template_e[3][6]=1;	char_template_e[4][6]=1;
//f				
char_template_f[0][0]=1;	char_template_f[1][0]=1;	char_template_f[2][0]=1;	char_template_f[3][0]=1;	char_template_f[4][0]=1;
char_template_f[0][1]=1;	char_template_f[1][1]=0;	char_template_f[2][1]=0;	char_template_f[3][1]=0;	char_template_f[4][1]=0;
char_template_f[0][2]=1;	char_template_f[1][2]=0;	char_template_f[2][2]=0;	char_template_f[3][2]=0;	char_template_f[4][2]=0;
char_template_f[0][3]=1;	char_template_f[1][3]=1;	char_template_f[2][3]=1;	char_template_f[3][3]=1;	char_template_f[4][3]=0;
char_template_f[0][4]=1;	char_template_f[1][4]=0;	char_template_f[2][4]=0;	char_template_f[3][4]=0;	char_template_f[4][4]=0;
char_template_f[0][5]=1;	char_template_f[1][5]=0;	char_template_f[2][5]=0;	char_template_f[3][5]=0;	char_template_f[4][5]=0;
char_template_f[0][6]=1;	char_template_f[1][6]=0;	char_template_f[2][6]=0;	char_template_f[3][6]=0;	char_template_f[4][6]=0;
//g				
char_template_g[0][0]=1;	char_template_g[1][0]=1;	char_template_g[2][0]=1;	char_template_g[3][0]=1;	char_template_g[4][0]=1;
char_template_g[0][1]=1;	char_template_g[1][1]=0;	char_template_g[2][1]=0;	char_template_g[3][1]=0;	char_template_g[4][1]=0;
char_template_g[0][2]=1;	char_template_g[1][2]=0;	char_template_g[2][2]=0;	char_template_g[3][2]=0;	char_template_g[4][2]=0;
char_template_g[0][3]=1;	char_template_g[1][3]=0;	char_template_g[2][3]=1;	char_template_g[3][3]=1;	char_template_g[4][3]=1;
char_template_g[0][4]=1;	char_template_g[1][4]=0;	char_template_g[2][4]=1;	char_template_g[3][4]=0;	char_template_g[4][4]=1;
char_template_g[0][5]=1;	char_template_g[1][5]=0;	char_template_g[2][5]=0;	char_template_g[3][5]=0;	char_template_g[4][5]=1;
char_template_g[0][6]=1;	char_template_g[1][6]=1;	char_template_g[2][6]=1;	char_template_g[3][6]=1;	char_template_g[4][6]=1;
//h				
char_template_h[0][0]=1;	char_template_h[1][0]=0;	char_template_h[2][0]=0;	char_template_h[3][0]=0;	char_template_h[4][0]=1;
char_template_h[0][1]=1;	char_template_h[1][1]=0;	char_template_h[2][1]=0;	char_template_h[3][1]=0;	char_template_h[4][1]=1;
char_template_h[0][2]=1;	char_template_h[1][2]=0;	char_template_h[2][2]=0;	char_template_h[3][2]=0;	char_template_h[4][2]=1;
char_template_h[0][3]=1;	char_template_h[1][3]=1;	char_template_h[2][3]=1;	char_template_h[3][3]=1;	char_template_h[4][3]=1;
char_template_h[0][4]=1;	char_template_h[1][4]=0;	char_template_h[2][4]=0;	char_template_h[3][4]=0;	char_template_h[4][4]=1;
char_template_h[0][5]=1;	char_template_h[1][5]=0;	char_template_h[2][5]=0;	char_template_h[3][5]=0;	char_template_h[4][5]=1;
char_template_h[0][6]=1;	char_template_h[1][6]=0;	char_template_h[2][6]=0;	char_template_h[3][6]=0;	char_template_h[4][6]=1;
//i				
char_template_i[0][0]=1;	char_template_i[1][0]=1;	char_template_i[2][0]=1;	char_template_i[3][0]=1;	char_template_i[4][0]=1;
char_template_i[0][1]=0;	char_template_i[1][1]=0;	char_template_i[2][1]=1;	char_template_i[3][1]=0;	char_template_i[4][1]=0;
char_template_i[0][2]=0;	char_template_i[1][2]=0;	char_template_i[2][2]=1;	char_template_i[3][2]=0;	char_template_i[4][2]=0;
char_template_i[0][3]=0;	char_template_i[1][3]=0;	char_template_i[2][3]=1;	char_template_i[3][3]=0;	char_template_i[4][3]=0;
char_template_i[0][4]=0;	char_template_i[1][4]=0;	char_template_i[2][4]=1;	char_template_i[3][4]=0;	char_template_i[4][4]=0;
char_template_i[0][5]=0;	char_template_i[1][5]=0;	char_template_i[2][5]=1;	char_template_i[3][5]=0;	char_template_i[4][5]=0;
char_template_i[0][6]=1;	char_template_i[1][6]=1;	char_template_i[2][6]=1;	char_template_i[3][6]=1;	char_template_i[4][6]=1;
//j				
char_template_j[0][0]=1;	char_template_j[1][0]=1;	char_template_j[2][0]=1;	char_template_j[3][0]=1;	char_template_j[4][0]=1;
char_template_j[0][1]=0;	char_template_j[1][1]=0;	char_template_j[2][1]=0;	char_template_j[3][1]=0;	char_template_j[4][1]=1;
char_template_j[0][2]=0;	char_template_j[1][2]=0;	char_template_j[2][2]=0;	char_template_j[3][2]=0;	char_template_j[4][2]=1;
char_template_j[0][3]=0;	char_template_j[1][3]=1;	char_template_j[2][3]=1;	char_template_j[3][3]=0;	char_template_j[4][3]=1;
char_template_j[0][4]=1;	char_template_j[1][4]=0;	char_template_j[2][4]=0;	char_template_j[3][4]=0;	char_template_j[4][4]=1;
char_template_j[0][5]=1;	char_template_j[1][5]=0;	char_template_j[2][5]=0;	char_template_j[3][5]=0;	char_template_j[4][5]=1;
char_template_j[0][6]=1;	char_template_j[1][6]=1;	char_template_j[2][6]=1;	char_template_j[3][6]=1;	char_template_j[4][6]=1;
//k				
char_template_k[0][0]=1;	char_template_k[1][0]=0;	char_template_k[2][0]=0;	char_template_k[3][0]=0;	char_template_k[4][0]=1;
char_template_k[0][1]=1;	char_template_k[1][1]=0;	char_template_k[2][1]=0;	char_template_k[3][1]=1;	char_template_k[4][1]=0;
char_template_k[0][2]=1;	char_template_k[1][2]=0;	char_template_k[2][2]=1;	char_template_k[3][2]=0;	char_template_k[4][2]=0;
char_template_k[0][3]=1;	char_template_k[1][3]=1;	char_template_k[2][3]=0;	char_template_k[3][3]=0;	char_template_k[4][3]=0;
char_template_k[0][4]=1;	char_template_k[1][4]=0;	char_template_k[2][4]=1;	char_template_k[3][4]=0;	char_template_k[4][4]=0;
char_template_k[0][5]=1;	char_template_k[1][5]=0;	char_template_k[2][5]=0;	char_template_k[3][5]=1;	char_template_k[4][5]=0;
char_template_k[0][6]=1;	char_template_k[1][6]=0;	char_template_k[2][6]=0;	char_template_k[3][6]=0;	char_template_k[4][6]=1;
//l				
char_template_l[0][0]=1;	char_template_l[1][0]=0;	char_template_l[2][0]=0;	char_template_l[3][0]=0;	char_template_l[4][0]=0;
char_template_l[0][1]=1;	char_template_l[1][1]=0;	char_template_l[2][1]=0;	char_template_l[3][1]=0;	char_template_l[4][1]=0;
char_template_l[0][2]=1;	char_template_l[1][2]=0;	char_template_l[2][2]=0;	char_template_l[3][2]=0;	char_template_l[4][2]=0;
char_template_l[0][3]=1;	char_template_l[1][3]=0;	char_template_l[2][3]=0;	char_template_l[3][3]=0;	char_template_l[4][3]=0;
char_template_l[0][4]=1;	char_template_l[1][4]=0;	char_template_l[2][4]=0;	char_template_l[3][4]=0;	char_template_l[4][4]=0;
char_template_l[0][5]=1;	char_template_l[1][5]=0;	char_template_l[2][5]=0;	char_template_l[3][5]=0;	char_template_l[4][5]=0;
char_template_l[0][6]=1;	char_template_l[1][6]=1;	char_template_l[2][6]=1;	char_template_l[3][6]=1;	char_template_l[4][6]=1;
//m				
char_template_m[0][0]=1;	char_template_m[1][0]=0;	char_template_m[2][0]=0;	char_template_m[3][0]=0;	char_template_m[4][0]=1;
char_template_m[0][1]=1;	char_template_m[1][1]=1;	char_template_m[2][1]=0;	char_template_m[3][1]=1;	char_template_m[4][1]=1;
char_template_m[0][2]=1;	char_template_m[1][2]=0;	char_template_m[2][2]=1;	char_template_m[3][2]=0;	char_template_m[4][2]=1;
char_template_m[0][3]=1;	char_template_m[1][3]=0;	char_template_m[2][3]=0;	char_template_m[3][3]=0;	char_template_m[4][3]=1;
char_template_m[0][4]=1;	char_template_m[1][4]=0;	char_template_m[2][4]=0;	char_template_m[3][4]=0;	char_template_m[4][4]=1;
char_template_m[0][5]=1;	char_template_m[1][5]=0;	char_template_m[2][5]=0;	char_template_m[3][5]=0;	char_template_m[4][5]=1;
char_template_m[0][6]=1;	char_template_m[1][6]=0;	char_template_m[2][6]=0;	char_template_m[3][6]=0;	char_template_m[4][6]=1;
//n				
char_template_n[0][0]=1;	char_template_n[1][0]=0;	char_template_n[2][0]=0;	char_template_n[3][0]=0;	char_template_n[4][0]=1;
char_template_n[0][1]=1;	char_template_n[1][1]=1;	char_template_n[2][1]=0;	char_template_n[3][1]=0;	char_template_n[4][1]=1;
char_template_n[0][2]=1;	char_template_n[1][2]=0;	char_template_n[2][2]=1;	char_template_n[3][2]=0;	char_template_n[4][2]=1;
char_template_n[0][3]=1;	char_template_n[1][3]=0;	char_template_n[2][3]=0;	char_template_n[3][3]=1;	char_template_n[4][3]=1;
char_template_n[0][4]=1;	char_template_n[1][4]=0;	char_template_n[2][4]=0;	char_template_n[3][4]=0;	char_template_n[4][4]=1;
char_template_n[0][5]=1;	char_template_n[1][5]=0;	char_template_n[2][5]=0;	char_template_n[3][5]=0;	char_template_n[4][5]=1;
char_template_n[0][6]=1;	char_template_n[1][6]=0;	char_template_n[2][6]=0;	char_template_n[3][6]=0;	char_template_n[4][6]=1;
//o				
char_template_o[0][0]=1;	char_template_o[1][0]=1;	char_template_o[2][0]=1;	char_template_o[3][0]=1;	char_template_o[4][0]=1;
char_template_o[0][1]=1;	char_template_o[1][1]=0;	char_template_o[2][1]=0;	char_template_o[3][1]=0;	char_template_o[4][1]=1;
char_template_o[0][2]=1;	char_template_o[1][2]=0;	char_template_o[2][2]=0;	char_template_o[3][2]=0;	char_template_o[4][2]=1;
char_template_o[0][3]=1;	char_template_o[1][3]=0;	char_template_o[2][3]=0;	char_template_o[3][3]=0;	char_template_o[4][3]=1;
char_template_o[0][4]=1;	char_template_o[1][4]=0;	char_template_o[2][4]=0;	char_template_o[3][4]=0;	char_template_o[4][4]=1;
char_template_o[0][5]=1;	char_template_o[1][5]=0;	char_template_o[2][5]=0;	char_template_o[3][5]=0;	char_template_o[4][5]=1;
char_template_o[0][6]=1;	char_template_o[1][6]=1;	char_template_o[2][6]=1;	char_template_o[3][6]=1;	char_template_o[4][6]=1;
//p				
char_template_p[0][0]=1;	char_template_p[1][0]=1;	char_template_p[2][0]=1;	char_template_p[3][0]=1;	char_template_p[4][0]=1;
char_template_p[0][1]=1;	char_template_p[1][1]=0;	char_template_p[2][1]=0;	char_template_p[3][1]=0;	char_template_p[4][1]=1;
char_template_p[0][2]=1;	char_template_p[1][2]=0;	char_template_p[2][2]=0;	char_template_p[3][2]=0;	char_template_p[4][2]=1;
char_template_p[0][3]=1;	char_template_p[1][3]=1;	char_template_p[2][3]=1;	char_template_p[3][3]=1;	char_template_p[4][3]=1;
char_template_p[0][4]=1;	char_template_p[1][4]=0;	char_template_p[2][4]=0;	char_template_p[3][4]=0;	char_template_p[4][4]=0;
char_template_p[0][5]=1;	char_template_p[1][5]=0;	char_template_p[2][5]=0;	char_template_p[3][5]=0;	char_template_p[4][5]=0;
char_template_p[0][6]=1;	char_template_p[1][6]=0;	char_template_p[2][6]=0;	char_template_p[3][6]=0;	char_template_p[4][6]=0;
//q				
char_template_q[0][0]=1;	char_template_q[1][0]=1;	char_template_q[2][0]=1;	char_template_q[3][0]=1;	char_template_q[4][0]=1;
char_template_q[0][1]=1;	char_template_q[1][1]=0;	char_template_q[2][1]=0;	char_template_q[3][1]=0;	char_template_q[4][1]=1;
char_template_q[0][2]=1;	char_template_q[1][2]=0;	char_template_q[2][2]=0;	char_template_q[3][2]=0;	char_template_q[4][2]=1;
char_template_q[0][3]=1;	char_template_q[1][3]=0;	char_template_q[2][3]=0;	char_template_q[3][3]=0;	char_template_q[4][3]=1;
char_template_q[0][4]=1;	char_template_q[1][4]=0;	char_template_q[2][4]=1;	char_template_q[3][4]=0;	char_template_q[4][4]=1;
char_template_q[0][5]=1;	char_template_q[1][5]=0;	char_template_q[2][5]=0;	char_template_q[3][5]=1;	char_template_q[4][5]=0;
char_template_q[0][6]=1;	char_template_q[1][6]=1;	char_template_q[2][6]=1;	char_template_q[3][6]=0;	char_template_q[4][6]=1;
//r				
char_template_r[0][0]=1;	char_template_r[1][0]=1;	char_template_r[2][0]=1;	char_template_r[3][0]=1;	char_template_r[4][0]=1;
char_template_r[0][1]=1;	char_template_r[1][1]=0;	char_template_r[2][1]=0;	char_template_r[3][1]=0;	char_template_r[4][1]=1;
char_template_r[0][2]=1;	char_template_r[1][2]=0;	char_template_r[2][2]=0;	char_template_r[3][2]=0;	char_template_r[4][2]=1;
char_template_r[0][3]=1;	char_template_r[1][3]=1;	char_template_r[2][3]=1;	char_template_r[3][3]=1;	char_template_r[4][3]=1;
char_template_r[0][4]=1;	char_template_r[1][4]=1;	char_template_r[2][4]=0;	char_template_r[3][4]=0;	char_template_r[4][4]=0;
char_template_r[0][5]=1;	char_template_r[1][5]=0;	char_template_r[2][5]=1;	char_template_r[3][5]=0;	char_template_r[4][5]=0;
char_template_r[0][6]=1;	char_template_r[1][6]=0;	char_template_r[2][6]=0;	char_template_r[3][6]=1;	char_template_r[4][6]=0;
//s				
char_template_s[0][0]=0;	char_template_s[1][0]=1;	char_template_s[2][0]=1;	char_template_s[3][0]=1;	char_template_s[4][0]=1;
char_template_s[0][1]=1;	char_template_s[1][1]=0;	char_template_s[2][1]=0;	char_template_s[3][1]=0;	char_template_s[4][1]=1;
char_template_s[0][2]=1;	char_template_s[1][2]=0;	char_template_s[2][2]=0;	char_template_s[3][2]=0;	char_template_s[4][2]=0;
char_template_s[0][3]=0;	char_template_s[1][3]=1;	char_template_s[2][3]=1;	char_template_s[3][3]=1;	char_template_s[4][3]=0;
char_template_s[0][4]=0;	char_template_s[1][4]=0;	char_template_s[2][4]=0;	char_template_s[3][4]=0;	char_template_s[4][4]=1;
char_template_s[0][5]=1;	char_template_s[1][5]=0;	char_template_s[2][5]=0;	char_template_s[3][5]=0;	char_template_s[4][5]=1;
char_template_s[0][6]=1;	char_template_s[1][6]=1;	char_template_s[2][6]=1;	char_template_s[3][6]=1;	char_template_s[4][6]=0;
//t				
char_template_t[0][0]=1;	char_template_t[1][0]=1;	char_template_t[2][0]=1;	char_template_t[3][0]=1;	char_template_t[4][0]=1;
char_template_t[0][1]=0;	char_template_t[1][1]=0;	char_template_t[2][1]=1;	char_template_t[3][1]=0;	char_template_t[4][1]=0;
char_template_t[0][2]=0;	char_template_t[1][2]=0;	char_template_t[2][2]=1;	char_template_t[3][2]=0;	char_template_t[4][2]=0;
char_template_t[0][3]=0;	char_template_t[1][3]=0;	char_template_t[2][3]=1;	char_template_t[3][3]=0;	char_template_t[4][3]=0;
char_template_t[0][4]=0;	char_template_t[1][4]=0;	char_template_t[2][4]=1;	char_template_t[3][4]=0;	char_template_t[4][4]=0;
char_template_t[0][5]=0;	char_template_t[1][5]=0;	char_template_t[2][5]=1;	char_template_t[3][5]=0;	char_template_t[4][5]=0;
char_template_t[0][6]=0;	char_template_t[1][6]=0;	char_template_t[2][6]=1;	char_template_t[3][6]=0;	char_template_t[4][6]=0;
//u				
char_template_u[0][0]=1;	char_template_u[1][0]=0;	char_template_u[2][0]=0;	char_template_u[3][0]=0;	char_template_u[4][0]=1;
char_template_u[0][1]=1;	char_template_u[1][1]=0;	char_template_u[2][1]=0;	char_template_u[3][1]=0;	char_template_u[4][1]=1;
char_template_u[0][2]=1;	char_template_u[1][2]=0;	char_template_u[2][2]=0;	char_template_u[3][2]=0;	char_template_u[4][2]=1;
char_template_u[0][3]=1;	char_template_u[1][3]=0;	char_template_u[2][3]=0;	char_template_u[3][3]=0;	char_template_u[4][3]=1;
char_template_u[0][4]=1;	char_template_u[1][4]=0;	char_template_u[2][4]=0;	char_template_u[3][4]=0;	char_template_u[4][4]=1;
char_template_u[0][5]=1;	char_template_u[1][5]=0;	char_template_u[2][5]=0;	char_template_u[3][5]=0;	char_template_u[4][5]=1;
char_template_u[0][6]=1;	char_template_u[1][6]=1;	char_template_u[2][6]=1;	char_template_u[3][6]=1;	char_template_u[4][6]=1;
//v				
char_template_v[0][0]=1;	char_template_v[1][0]=0;	char_template_v[2][0]=0;	char_template_v[3][0]=0;	char_template_v[4][0]=1;
char_template_v[0][1]=1;	char_template_v[1][1]=0;	char_template_v[2][1]=0;	char_template_v[3][1]=0;	char_template_v[4][1]=1;
char_template_v[0][2]=1;	char_template_v[1][2]=0;	char_template_v[2][2]=0;	char_template_v[3][2]=0;	char_template_v[4][2]=1;
char_template_v[0][3]=1;	char_template_v[1][3]=0;	char_template_v[2][3]=0;	char_template_v[3][3]=0;	char_template_v[4][3]=1;
char_template_v[0][4]=1;	char_template_v[1][4]=0;	char_template_v[2][4]=0;	char_template_v[3][4]=0;	char_template_v[4][4]=1;
char_template_v[0][5]=0;	char_template_v[1][5]=1;	char_template_v[2][5]=0;	char_template_v[3][5]=1;	char_template_v[4][5]=0;
char_template_v[0][6]=0;	char_template_v[1][6]=0;	char_template_v[2][6]=1;	char_template_v[3][6]=0;	char_template_v[4][6]=0;
//w				
char_template_w[0][0]=1;	char_template_w[1][0]=0;	char_template_w[2][0]=0;	char_template_w[3][0]=0;	char_template_w[4][0]=1;
char_template_w[0][1]=1;	char_template_w[1][1]=0;	char_template_w[2][1]=0;	char_template_w[3][1]=0;	char_template_w[4][1]=1;
char_template_w[0][2]=1;	char_template_w[1][2]=0;	char_template_w[2][2]=0;	char_template_w[3][2]=0;	char_template_w[4][2]=1;
char_template_w[0][3]=1;	char_template_w[1][3]=0;	char_template_w[2][3]=0;	char_template_w[3][3]=0;	char_template_w[4][3]=1;
char_template_w[0][4]=1;	char_template_w[1][4]=0;	char_template_w[2][4]=0;	char_template_w[3][4]=0;	char_template_w[4][4]=1;
char_template_w[0][5]=1;	char_template_w[1][5]=0;	char_template_w[2][5]=1;	char_template_w[3][5]=0;	char_template_w[4][5]=1;
char_template_w[0][6]=0;	char_template_w[1][6]=1;	char_template_w[2][6]=0;	char_template_w[3][6]=1;	char_template_w[4][6]=0;
//x				
char_template_x[0][0]=1;	char_template_x[1][0]=0;	char_template_x[2][0]=0;	char_template_x[3][0]=0;	char_template_x[4][0]=1;
char_template_x[0][1]=1;	char_template_x[1][1]=0;	char_template_x[2][1]=0;	char_template_x[3][1]=0;	char_template_x[4][1]=1;
char_template_x[0][2]=0;	char_template_x[1][2]=1;	char_template_x[2][2]=0;	char_template_x[3][2]=1;	char_template_x[4][2]=0;
char_template_x[0][3]=0;	char_template_x[1][3]=0;	char_template_x[2][3]=1;	char_template_x[3][3]=0;	char_template_x[4][3]=0;
char_template_x[0][4]=0;	char_template_x[1][4]=1;	char_template_x[2][4]=0;	char_template_x[3][4]=1;	char_template_x[4][4]=0;
char_template_x[0][5]=1;	char_template_x[1][5]=0;	char_template_x[2][5]=0;	char_template_x[3][5]=0;	char_template_x[4][5]=1;
char_template_x[0][6]=1;	char_template_x[1][6]=0;	char_template_x[2][6]=0;	char_template_x[3][6]=0;	char_template_x[4][6]=1;
//y				
char_template_y[0][0]=1;	char_template_y[1][0]=0;	char_template_y[2][0]=0;	char_template_y[3][0]=0;	char_template_y[4][0]=1;
char_template_y[0][1]=1;	char_template_y[1][1]=0;	char_template_y[2][1]=0;	char_template_y[3][1]=0;	char_template_y[4][1]=1;
char_template_y[0][2]=1;	char_template_y[1][2]=0;	char_template_y[2][2]=0;	char_template_y[3][2]=0;	char_template_y[4][2]=1;
char_template_y[0][3]=0;	char_template_y[1][3]=1;	char_template_y[2][3]=1;	char_template_y[3][3]=1;	char_template_y[4][3]=1;
char_template_y[0][4]=0;	char_template_y[1][4]=0;	char_template_y[2][4]=0;	char_template_y[3][4]=0;	char_template_y[4][4]=1;
char_template_y[0][5]=0;	char_template_y[1][5]=0;	char_template_y[2][5]=0;	char_template_y[3][5]=0;	char_template_y[4][5]=1;
char_template_y[0][6]=0;	char_template_y[1][6]=0;	char_template_y[2][6]=0;	char_template_y[3][6]=0;	char_template_y[4][6]=1;
//z				
char_template_z[0][0]=1;	char_template_z[1][0]=1;	char_template_z[2][0]=1;	char_template_z[3][0]=1;	char_template_z[4][0]=1;
char_template_z[0][1]=0;	char_template_z[1][1]=0;	char_template_z[2][1]=0;	char_template_z[3][1]=0;	char_template_z[4][1]=1;
char_template_z[0][2]=0;	char_template_z[1][2]=0;	char_template_z[2][2]=0;	char_template_z[3][2]=1;	char_template_z[4][2]=1;
char_template_z[0][3]=0;	char_template_z[1][3]=1;	char_template_z[2][3]=1;	char_template_z[3][3]=1;	char_template_z[4][3]=0;
char_template_z[0][4]=1;	char_template_z[1][4]=1;	char_template_z[2][4]=0;	char_template_z[3][4]=0;	char_template_z[4][4]=0;
char_template_z[0][5]=1;	char_template_z[1][5]=0;	char_template_z[2][5]=0;	char_template_z[3][5]=0;	char_template_z[4][5]=0;
char_template_z[0][6]=1;	char_template_z[1][6]=1;	char_template_z[2][6]=1;	char_template_z[3][6]=1;	char_template_z[4][6]=1;
//1				
char_template_1[0][0]=0;	char_template_1[1][0]=0;	char_template_1[2][0]=0;	char_template_1[3][0]=1;	char_template_1[4][0]=0;
char_template_1[0][1]=0;	char_template_1[1][1]=0;	char_template_1[2][1]=1;	char_template_1[3][1]=1;	char_template_1[4][1]=0;
char_template_1[0][2]=0;	char_template_1[1][2]=1;	char_template_1[2][2]=0;	char_template_1[3][2]=1;	char_template_1[4][2]=0;
char_template_1[0][3]=0;	char_template_1[1][3]=0;	char_template_1[2][3]=0;	char_template_1[3][3]=1;	char_template_1[4][3]=0;
char_template_1[0][4]=0;	char_template_1[1][4]=0;	char_template_1[2][4]=0;	char_template_1[3][4]=1;	char_template_1[4][4]=0;
char_template_1[0][5]=0;	char_template_1[1][5]=0;	char_template_1[2][5]=0;	char_template_1[3][5]=1;	char_template_1[4][5]=0;
char_template_1[0][6]=0;	char_template_1[1][6]=0;	char_template_1[2][6]=0;	char_template_1[3][6]=1;	char_template_1[4][6]=0;
//2				
char_template_2[0][0]=1;	char_template_2[1][0]=1;	char_template_2[2][0]=1;	char_template_2[3][0]=1;	char_template_2[4][0]=1;
char_template_2[0][1]=0;	char_template_2[1][1]=0;	char_template_2[2][1]=0;	char_template_2[3][1]=0;	char_template_2[4][1]=1;
char_template_2[0][2]=0;	char_template_2[1][2]=0;	char_template_2[2][2]=0;	char_template_2[3][2]=0;	char_template_2[4][2]=1;
char_template_2[0][3]=1;	char_template_2[1][3]=1;	char_template_2[2][3]=1;	char_template_2[3][3]=1;	char_template_2[4][3]=1;
char_template_2[0][4]=1;	char_template_2[1][4]=0;	char_template_2[2][4]=0;	char_template_2[3][4]=0;	char_template_2[4][4]=0;
char_template_2[0][5]=1;	char_template_2[1][5]=0;	char_template_2[2][5]=0;	char_template_2[3][5]=0;	char_template_2[4][5]=0;
char_template_2[0][6]=1;	char_template_2[1][6]=1;	char_template_2[2][6]=1;	char_template_2[3][6]=1;	char_template_2[4][6]=1;
//3				
char_template_3[0][0]=1;	char_template_3[1][0]=1;	char_template_3[2][0]=1;	char_template_3[3][0]=1;	char_template_3[4][0]=1;
char_template_3[0][1]=0;	char_template_3[1][1]=0;	char_template_3[2][1]=0;	char_template_3[3][1]=0;	char_template_3[4][1]=1;
char_template_3[0][2]=0;	char_template_3[1][2]=0;	char_template_3[2][2]=0;	char_template_3[3][2]=0;	char_template_3[4][2]=1;
char_template_3[0][3]=0;	char_template_3[1][3]=1;	char_template_3[2][3]=1;	char_template_3[3][3]=1;	char_template_3[4][3]=1;
char_template_3[0][4]=0;	char_template_3[1][4]=0;	char_template_3[2][4]=0;	char_template_3[3][4]=0;	char_template_3[4][4]=1;
char_template_3[0][5]=0;	char_template_3[1][5]=0;	char_template_3[2][5]=0;	char_template_3[3][5]=0;	char_template_3[4][5]=1;
char_template_3[0][6]=1;	char_template_3[1][6]=1;	char_template_3[2][6]=1;	char_template_3[3][6]=1;	char_template_3[4][6]=1;
//4				
char_template_4[0][0]=1;	char_template_4[1][0]=0;	char_template_4[2][0]=0;	char_template_4[3][0]=0;	char_template_4[4][0]=1;
char_template_4[0][1]=1;	char_template_4[1][1]=0;	char_template_4[2][1]=0;	char_template_4[3][1]=0;	char_template_4[4][1]=1;
char_template_4[0][2]=1;	char_template_4[1][2]=0;	char_template_4[2][2]=0;	char_template_4[3][2]=0;	char_template_4[4][2]=1;
char_template_4[0][3]=0;	char_template_4[1][3]=1;	char_template_4[2][3]=1;	char_template_4[3][3]=1;	char_template_4[4][3]=1;
char_template_4[0][4]=0;	char_template_4[1][4]=0;	char_template_4[2][4]=0;	char_template_4[3][4]=0;	char_template_4[4][4]=1;
char_template_4[0][5]=0;	char_template_4[1][5]=0;	char_template_4[2][5]=0;	char_template_4[3][5]=0;	char_template_4[4][5]=1;
char_template_4[0][6]=0;	char_template_4[1][6]=0;	char_template_4[2][6]=0;	char_template_4[3][6]=0;	char_template_4[4][6]=1;
//5				
char_template_5[0][0]=1;	char_template_5[1][0]=1;	char_template_5[2][0]=1;	char_template_5[3][0]=1;	char_template_5[4][0]=1;
char_template_5[0][1]=1;	char_template_5[1][1]=0;	char_template_5[2][1]=0;	char_template_5[3][1]=0;	char_template_5[4][1]=0;
char_template_5[0][2]=1;	char_template_5[1][2]=0;	char_template_5[2][2]=0;	char_template_5[3][2]=0;	char_template_5[4][2]=0;
char_template_5[0][3]=1;	char_template_5[1][3]=1;	char_template_5[2][3]=1;	char_template_5[3][3]=1;	char_template_5[4][3]=1;
char_template_5[0][4]=0;	char_template_5[1][4]=0;	char_template_5[2][4]=0;	char_template_5[3][4]=0;	char_template_5[4][4]=1;
char_template_5[0][5]=0;	char_template_5[1][5]=0;	char_template_5[2][5]=0;	char_template_5[3][5]=0;	char_template_5[4][5]=1;
char_template_5[0][6]=1;	char_template_5[1][6]=1;	char_template_5[2][6]=1;	char_template_5[3][6]=1;	char_template_5[4][6]=1;
//6				
char_template_6[0][0]=1;	char_template_6[1][0]=1;	char_template_6[2][0]=1;	char_template_6[3][0]=1;	char_template_6[4][0]=1;
char_template_6[0][1]=1;	char_template_6[1][1]=0;	char_template_6[2][1]=0;	char_template_6[3][1]=0;	char_template_6[4][1]=1;
char_template_6[0][2]=1;	char_template_6[1][2]=0;	char_template_6[2][2]=0;	char_template_6[3][2]=0;	char_template_6[4][2]=0;
char_template_6[0][3]=1;	char_template_6[1][3]=1;	char_template_6[2][3]=1;	char_template_6[3][3]=1;	char_template_6[4][3]=1;
char_template_6[0][4]=1;	char_template_6[1][4]=0;	char_template_6[2][4]=0;	char_template_6[3][4]=0;	char_template_6[4][4]=1;
char_template_6[0][5]=1;	char_template_6[1][5]=0;	char_template_6[2][5]=0;	char_template_6[3][5]=0;	char_template_6[4][5]=1;
char_template_6[0][6]=1;	char_template_6[1][6]=1;	char_template_6[2][6]=1;	char_template_6[3][6]=1;	char_template_6[4][6]=1;
//7				
char_template_7[0][0]=1;	char_template_7[1][0]=1;	char_template_7[2][0]=1;	char_template_7[3][0]=1;	char_template_7[4][0]=1;
char_template_7[0][1]=0;	char_template_7[1][1]=0;	char_template_7[2][1]=0;	char_template_7[3][1]=0;	char_template_7[4][1]=1;
char_template_7[0][2]=0;	char_template_7[1][2]=0;	char_template_7[2][2]=0;	char_template_7[3][2]=0;	char_template_7[4][2]=1;
char_template_7[0][3]=0;	char_template_7[1][3]=0;	char_template_7[2][3]=0;	char_template_7[3][3]=0;	char_template_7[4][3]=1;
char_template_7[0][4]=0;	char_template_7[1][4]=0;	char_template_7[2][4]=0;	char_template_7[3][4]=0;	char_template_7[4][4]=1;
char_template_7[0][5]=0;	char_template_7[1][5]=0;	char_template_7[2][5]=0;	char_template_7[3][5]=0;	char_template_7[4][5]=1;
char_template_7[0][6]=0;	char_template_7[1][6]=0;	char_template_7[2][6]=0;	char_template_7[3][6]=0;	char_template_7[4][6]=1;
//8				
char_template_8[0][0]=1;	char_template_8[1][0]=1;	char_template_8[2][0]=1;	char_template_8[3][0]=1;	char_template_8[4][0]=1;
char_template_8[0][1]=1;	char_template_8[1][1]=0;	char_template_8[2][1]=0;	char_template_8[3][1]=0;	char_template_8[4][1]=1;
char_template_8[0][2]=1;	char_template_8[1][2]=0;	char_template_8[2][2]=0;	char_template_8[3][2]=0;	char_template_8[4][2]=1;
char_template_8[0][3]=1;	char_template_8[1][3]=1;	char_template_8[2][3]=1;	char_template_8[3][3]=1;	char_template_8[4][3]=1;
char_template_8[0][4]=1;	char_template_8[1][4]=0;	char_template_8[2][4]=0;	char_template_8[3][4]=0;	char_template_8[4][4]=1;
char_template_8[0][5]=1;	char_template_8[1][5]=0;	char_template_8[2][5]=0;	char_template_8[3][5]=0;	char_template_8[4][5]=1;
char_template_8[0][6]=1;	char_template_8[1][6]=1;	char_template_8[2][6]=1;	char_template_8[3][6]=1;	char_template_8[4][6]=1;
//9				
char_template_9[0][0]=1;	char_template_9[1][0]=1;	char_template_9[2][0]=1;	char_template_9[3][0]=1;	char_template_9[4][0]=1;
char_template_9[0][1]=1;	char_template_9[1][1]=0;	char_template_9[2][1]=0;	char_template_9[3][1]=0;	char_template_9[4][1]=1;
char_template_9[0][2]=1;	char_template_9[1][2]=0;	char_template_9[2][2]=0;	char_template_9[3][2]=0;	char_template_9[4][2]=1;
char_template_9[0][3]=1;	char_template_9[1][3]=1;	char_template_9[2][3]=1;	char_template_9[3][3]=1;	char_template_9[4][3]=1;
char_template_9[0][4]=0;	char_template_9[1][4]=0;	char_template_9[2][4]=0;	char_template_9[3][4]=0;	char_template_9[4][4]=1;
char_template_9[0][5]=0;	char_template_9[1][5]=0;	char_template_9[2][5]=0;	char_template_9[3][5]=0;	char_template_9[4][5]=1;
char_template_9[0][6]=1;	char_template_9[1][6]=1;	char_template_9[2][6]=1;	char_template_9[3][6]=1;	char_template_9[4][6]=1;
//0				
char_template_0[0][0]=1;	char_template_0[1][0]=1;	char_template_0[2][0]=1;	char_template_0[3][0]=1;	char_template_0[4][0]=1;
char_template_0[0][1]=1;	char_template_0[1][1]=0;	char_template_0[2][1]=0;	char_template_0[3][1]=0;	char_template_0[4][1]=1;
char_template_0[0][2]=1;	char_template_0[1][2]=0;	char_template_0[2][2]=0;	char_template_0[3][2]=0;	char_template_0[4][2]=1;
char_template_0[0][3]=1;	char_template_0[1][3]=0;	char_template_0[2][3]=0;	char_template_0[3][3]=0;	char_template_0[4][3]=1;
char_template_0[0][4]=1;	char_template_0[1][4]=0;	char_template_0[2][4]=0;	char_template_0[3][4]=0;	char_template_0[4][4]=1;
char_template_0[0][5]=1;	char_template_0[1][5]=0;	char_template_0[2][5]=0;	char_template_0[3][5]=0;	char_template_0[4][5]=1;
char_template_0[0][6]=1;	char_template_0[1][6]=1;	char_template_0[2][6]=1;	char_template_0[3][6]=1;	char_template_0[4][6]=1;
//nothing				
char_template_nothing[0][0]=0;	char_template_nothing[1][0]=0;	char_template_nothing[2][0]=0;	char_template_nothing[3][0]=0;	char_template_nothing[4][0]=0;
char_template_nothing[0][1]=0;	char_template_nothing[1][1]=0;	char_template_nothing[2][1]=0;	char_template_nothing[3][1]=0;	char_template_nothing[4][1]=0;
char_template_nothing[0][2]=0;	char_template_nothing[1][2]=0;	char_template_nothing[2][2]=0;	char_template_nothing[3][2]=0;	char_template_nothing[4][2]=0;
char_template_nothing[0][3]=0;	char_template_nothing[1][3]=0;	char_template_nothing[2][3]=0;	char_template_nothing[3][3]=0;	char_template_nothing[4][3]=0;
char_template_nothing[0][4]=0;	char_template_nothing[1][4]=0;	char_template_nothing[2][4]=0;	char_template_nothing[3][4]=0;	char_template_nothing[4][4]=0;
char_template_nothing[0][5]=0;	char_template_nothing[1][5]=0;	char_template_nothing[2][5]=0;	char_template_nothing[3][5]=0;	char_template_nothing[4][5]=0;
char_template_nothing[0][6]=0;	char_template_nothing[1][6]=0;	char_template_nothing[2][6]=0;	char_template_nothing[3][6]=0;	char_template_nothing[4][6]=0;




//sharp	= #			
char_template_sharp[0][0]=0;	char_template_sharp[1][0]=1;	char_template_sharp[2][0]=0;	char_template_sharp[3][0]=1;	char_template_sharp[4][0]=0;
char_template_sharp[0][1]=1;	char_template_sharp[1][1]=1;	char_template_sharp[2][1]=1;	char_template_sharp[3][1]=1;	char_template_sharp[4][1]=1;
char_template_sharp[0][2]=0;	char_template_sharp[1][2]=1;	char_template_sharp[2][2]=0;	char_template_sharp[3][2]=1;	char_template_sharp[4][2]=0;
char_template_sharp[0][3]=0;	char_template_sharp[1][3]=1;	char_template_sharp[2][3]=0;	char_template_sharp[3][3]=1;	char_template_sharp[4][3]=0;
char_template_sharp[0][4]=0;	char_template_sharp[1][4]=1;	char_template_sharp[2][4]=0;	char_template_sharp[3][4]=1;	char_template_sharp[4][4]=0;
char_template_sharp[0][5]=1;	char_template_sharp[1][5]=1;	char_template_sharp[2][5]=1;	char_template_sharp[3][5]=1;	char_template_sharp[4][5]=1;
char_template_sharp[0][6]=0;	char_template_sharp[1][6]=1;	char_template_sharp[2][6]=0;	char_template_sharp[3][6]=1;	char_template_sharp[4][6]=0;

//dot .			
char_template_dot[0][0]=0;	char_template_dot[1][0]=0;	char_template_dot[2][0]=0;	char_template_dot[3][0]=0;	char_template_dot[4][0]=0;
char_template_dot[0][1]=0;	char_template_dot[1][1]=0;	char_template_dot[2][1]=0;	char_template_dot[3][1]=0;	char_template_dot[4][1]=0;
char_template_dot[0][2]=0;	char_template_dot[1][2]=0;	char_template_dot[2][2]=0;	char_template_dot[3][2]=0;	char_template_dot[4][2]=0;
char_template_dot[0][3]=0;	char_template_dot[1][3]=0;	char_template_dot[2][3]=0;	char_template_dot[3][3]=0;	char_template_dot[4][3]=0;
char_template_dot[0][4]=0;	char_template_dot[1][4]=0;	char_template_dot[2][4]=0;	char_template_dot[3][4]=0;	char_template_dot[4][4]=0;
char_template_dot[0][5]=0;	char_template_dot[1][5]=0;	char_template_dot[2][5]=1;	char_template_dot[3][5]=1;	char_template_dot[4][5]=0;
char_template_dot[0][6]=0;	char_template_dot[1][6]=0;	char_template_dot[2][6]=1;	char_template_dot[3][6]=1;	char_template_dot[4][6]=0;

//comma				
char_template_comma[0][0]=0;	char_template_comma[1][0]=0;	char_template_comma[2][0]=0;	char_template_comma[3][0]=0;	char_template_comma[4][0]=0;
char_template_comma[0][1]=0;	char_template_comma[1][1]=0;	char_template_comma[2][1]=0;	char_template_comma[3][1]=0;	char_template_comma[4][1]=0;
char_template_comma[0][2]=0;	char_template_comma[1][2]=0;	char_template_comma[2][2]=0;	char_template_comma[3][2]=0;	char_template_comma[4][2]=0;
char_template_comma[0][3]=0;	char_template_comma[1][3]=0;	char_template_comma[2][3]=0;	char_template_comma[3][3]=0;	char_template_comma[4][3]=0;
char_template_comma[0][4]=0;	char_template_comma[1][4]=0;	char_template_comma[2][4]=1;	char_template_comma[3][4]=0;	char_template_comma[4][4]=0;
char_template_comma[0][5]=0;	char_template_comma[1][5]=0;	char_template_comma[2][5]=1;	char_template_comma[3][5]=0;	char_template_comma[4][5]=0;
char_template_comma[0][6]=0;	char_template_comma[1][6]=0;	char_template_comma[2][6]=1;	char_template_comma[3][6]=0;	char_template_comma[4][6]=0;

//bracketopen	(			
char_template_bracketopen[0][0]=1;	char_template_bracketopen[1][0]=1;	char_template_bracketopen[2][0]=1;	char_template_bracketopen[3][0]=0;	char_template_bracketopen[4][0]=0;
char_template_bracketopen[0][1]=1;	char_template_bracketopen[1][1]=0;	char_template_bracketopen[2][1]=0;	char_template_bracketopen[3][1]=0;	char_template_bracketopen[4][1]=0;
char_template_bracketopen[0][2]=1;	char_template_bracketopen[1][2]=0;	char_template_bracketopen[2][2]=0;	char_template_bracketopen[3][2]=0;	char_template_bracketopen[4][2]=0;
char_template_bracketopen[0][3]=1;	char_template_bracketopen[1][3]=0;	char_template_bracketopen[2][3]=0;	char_template_bracketopen[3][3]=0;	char_template_bracketopen[4][3]=0;
char_template_bracketopen[0][4]=1;	char_template_bracketopen[1][4]=0;	char_template_bracketopen[2][4]=0;	char_template_bracketopen[3][4]=0;	char_template_bracketopen[4][4]=0;
char_template_bracketopen[0][5]=1;	char_template_bracketopen[1][5]=0;	char_template_bracketopen[2][5]=0;	char_template_bracketopen[3][5]=0;	char_template_bracketopen[4][5]=0;
char_template_bracketopen[0][6]=1;	char_template_bracketopen[1][6]=1;	char_template_bracketopen[2][6]=1;	char_template_bracketopen[3][6]=0;	char_template_bracketopen[4][6]=0;

//bracketclose	)			
char_template_bracketclose[0][0]=0;	char_template_bracketclose[1][0]=0;	char_template_bracketclose[2][0]=1;	char_template_bracketclose[3][0]=1;	char_template_bracketclose[4][0]=1;
char_template_bracketclose[0][1]=0;	char_template_bracketclose[1][1]=0;	char_template_bracketclose[2][1]=0;	char_template_bracketclose[3][1]=0;	char_template_bracketclose[4][1]=1;
char_template_bracketclose[0][2]=0;	char_template_bracketclose[1][2]=0;	char_template_bracketclose[2][2]=0;	char_template_bracketclose[3][2]=0;	char_template_bracketclose[4][2]=1;
char_template_bracketclose[0][3]=0;	char_template_bracketclose[1][3]=0;	char_template_bracketclose[2][3]=0;	char_template_bracketclose[3][3]=0;	char_template_bracketclose[4][3]=1;
char_template_bracketclose[0][4]=0;	char_template_bracketclose[1][4]=0;	char_template_bracketclose[2][4]=0;	char_template_bracketclose[3][4]=0;	char_template_bracketclose[4][4]=1;
char_template_bracketclose[0][5]=0;	char_template_bracketclose[1][5]=0;	char_template_bracketclose[2][5]=0;	char_template_bracketclose[3][5]=0;	char_template_bracketclose[4][5]=1;
char_template_bracketclose[0][6]=0;	char_template_bracketclose[1][6]=0;	char_template_bracketclose[2][6]=1;	char_template_bracketclose[3][6]=1;	char_template_bracketclose[4][6]=1;

//equal	=			
char_template_equal[0][0]=0;	char_template_equal[1][0]=0;	char_template_equal[2][0]=0;	char_template_equal[3][0]=0;	char_template_equal[4][0]=0;
char_template_equal[0][1]=0;	char_template_equal[1][1]=0;	char_template_equal[2][1]=0;	char_template_equal[3][1]=0;	char_template_equal[4][1]=0;
char_template_equal[0][2]=1;	char_template_equal[1][2]=1;	char_template_equal[2][2]=1;	char_template_equal[3][2]=1;	char_template_equal[4][2]=1;
char_template_equal[0][3]=0;	char_template_equal[1][3]=0;	char_template_equal[2][3]=0;	char_template_equal[3][3]=0;	char_template_equal[4][3]=0;
char_template_equal[0][4]=1;	char_template_equal[1][4]=1;	char_template_equal[2][4]=1;	char_template_equal[3][4]=1;	char_template_equal[4][4]=1;
char_template_equal[0][5]=0;	char_template_equal[1][5]=0;	char_template_equal[2][5]=0;	char_template_equal[3][5]=0;	char_template_equal[4][5]=0;
char_template_equal[0][6]=0;	char_template_equal[1][6]=0;	char_template_equal[2][6]=0;	char_template_equal[3][6]=0;	char_template_equal[4][6]=0;

//plus +				
char_template_plus[0][0]=0;	char_template_plus[1][0]=0;	char_template_plus[2][0]=0;	char_template_plus[3][0]=0;	char_template_plus[4][0]=0;
char_template_plus[0][1]=0;	char_template_plus[1][1]=0;	char_template_plus[2][1]=1;	char_template_plus[3][1]=0;	char_template_plus[4][1]=0;
char_template_plus[0][2]=0;	char_template_plus[1][2]=0;	char_template_plus[2][2]=1;	char_template_plus[3][2]=0;	char_template_plus[4][2]=0;
char_template_plus[0][3]=1;	char_template_plus[1][3]=1;	char_template_plus[2][3]=1;	char_template_plus[3][3]=1;	char_template_plus[4][3]=1;
char_template_plus[0][4]=0;	char_template_plus[1][4]=0;	char_template_plus[2][4]=1;	char_template_plus[3][4]=0;	char_template_plus[4][4]=0;
char_template_plus[0][5]=0;	char_template_plus[1][5]=0;	char_template_plus[2][5]=1;	char_template_plus[3][5]=0;	char_template_plus[4][5]=0;
char_template_plus[0][6]=0;	char_template_plus[1][6]=0;	char_template_plus[2][6]=0;	char_template_plus[3][6]=0;	char_template_plus[4][6]=0;

//minus				
char_template_minus[0][0]=0;	char_template_minus[1][0]=0;	char_template_minus[2][0]=0;	char_template_minus[3][0]=0;	char_template_minus[4][0]=0;
char_template_minus[0][1]=0;	char_template_minus[1][1]=0;	char_template_minus[2][1]=0;	char_template_minus[3][1]=0;	char_template_minus[4][1]=0;
char_template_minus[0][2]=0;	char_template_minus[1][2]=0;	char_template_minus[2][2]=0;	char_template_minus[3][2]=0;	char_template_minus[4][2]=0;
char_template_minus[0][3]=1;	char_template_minus[1][3]=1;	char_template_minus[2][3]=1;	char_template_minus[3][3]=1;	char_template_minus[4][3]=1;
char_template_minus[0][4]=0;	char_template_minus[1][4]=0;	char_template_minus[2][4]=0;	char_template_minus[3][4]=0;	char_template_minus[4][4]=0;
char_template_minus[0][5]=0;	char_template_minus[1][5]=0;	char_template_minus[2][5]=0;	char_template_minus[3][5]=0;	char_template_minus[4][5]=0;
char_template_minus[0][6]=0;	char_template_minus[1][6]=0;	char_template_minus[2][6]=0;	char_template_minus[3][6]=0;	char_template_minus[4][6]=0;

//bang				
char_template_bang[0][0]=0;	char_template_bang[1][0]=0;	char_template_bang[2][0]=1;	char_template_bang[3][0]=0;	char_template_bang[4][0]=0;
char_template_bang[0][1]=0;	char_template_bang[1][1]=0;	char_template_bang[2][1]=1;	char_template_bang[3][1]=0;	char_template_bang[4][1]=0;
char_template_bang[0][2]=0;	char_template_bang[1][2]=0;	char_template_bang[2][2]=1;	char_template_bang[3][2]=0;	char_template_bang[4][2]=0;
char_template_bang[0][3]=0;	char_template_bang[1][3]=0;	char_template_bang[2][3]=1;	char_template_bang[3][3]=0;	char_template_bang[4][3]=0;
char_template_bang[0][4]=0;	char_template_bang[1][4]=0;	char_template_bang[2][4]=0;	char_template_bang[3][4]=0;	char_template_bang[4][4]=0;
char_template_bang[0][5]=0;	char_template_bang[1][5]=0;	char_template_bang[2][5]=0;	char_template_bang[3][5]=0;	char_template_bang[4][5]=0;
char_template_bang[0][6]=0;	char_template_bang[1][6]=0;	char_template_bang[2][6]=1;	char_template_bang[3][6]=0;	char_template_bang[4][6]=0;

//doubledot				
char_template_doubledot[0][0]=0;	char_template_doubledot[1][0]=0;	char_template_doubledot[2][0]=0;	char_template_doubledot[3][0]=0;	char_template_doubledot[4][0]=0;
char_template_doubledot[0][1]=0;	char_template_doubledot[1][1]=1;	char_template_doubledot[2][1]=1;	char_template_doubledot[3][1]=0;	char_template_doubledot[4][1]=0;
char_template_doubledot[0][2]=0;	char_template_doubledot[1][2]=1;	char_template_doubledot[2][2]=1;	char_template_doubledot[3][2]=0;	char_template_doubledot[4][2]=0;
char_template_doubledot[0][3]=0;	char_template_doubledot[1][3]=0;	char_template_doubledot[2][3]=0;	char_template_doubledot[3][3]=0;	char_template_doubledot[4][3]=0;
char_template_doubledot[0][4]=0;	char_template_doubledot[1][4]=0;	char_template_doubledot[2][4]=0;	char_template_doubledot[3][4]=0;	char_template_doubledot[4][4]=0;
char_template_doubledot[0][5]=0;	char_template_doubledot[1][5]=1;	char_template_doubledot[2][5]=1;	char_template_doubledot[3][5]=0;	char_template_doubledot[4][5]=0;
char_template_doubledot[0][6]=0;	char_template_doubledot[1][6]=1;	char_template_doubledot[2][6]=1;	char_template_doubledot[3][6]=0;	char_template_doubledot[4][6]=0;

//underline				
char_template_underline[0][0]=0;	char_template_underline[1][0]=0;	char_template_underline[2][0]=0;	char_template_underline[3][0]=0;	char_template_underline[4][0]=0;
char_template_underline[0][1]=0;	char_template_underline[1][1]=0;	char_template_underline[2][1]=0;	char_template_underline[3][1]=0;	char_template_underline[4][1]=0;
char_template_underline[0][2]=0;	char_template_underline[1][2]=0;	char_template_underline[2][2]=0;	char_template_underline[3][2]=0;	char_template_underline[4][2]=0;
char_template_underline[0][3]=0;	char_template_underline[1][3]=0;	char_template_underline[2][3]=0;	char_template_underline[3][3]=0;	char_template_underline[4][3]=0;
char_template_underline[0][4]=0;	char_template_underline[1][4]=0;	char_template_underline[2][4]=0;	char_template_underline[3][4]=0;	char_template_underline[4][4]=0;
char_template_underline[0][5]=0;	char_template_underline[1][5]=0;	char_template_underline[2][5]=0;	char_template_underline[3][5]=0;	char_template_underline[4][5]=0;
char_template_underline[0][6]=1;	char_template_underline[1][6]=1;	char_template_underline[2][6]=1;	char_template_underline[3][6]=1;	char_template_underline[4][6]=1;

//quest   ?				
char_template_quest[0][0]=0;	char_template_quest[1][0]=1;	char_template_quest[2][0]=1;	char_template_quest[3][0]=1;	char_template_quest[4][0]=0;
char_template_quest[0][1]=1;	char_template_quest[1][1]=0;	char_template_quest[2][1]=0;	char_template_quest[3][1]=0;	char_template_quest[4][1]=1;
char_template_quest[0][2]=1;	char_template_quest[1][2]=0;	char_template_quest[2][2]=0;	char_template_quest[3][2]=0;	char_template_quest[4][2]=1;
char_template_quest[0][3]=0;	char_template_quest[1][3]=0;	char_template_quest[2][3]=0;	char_template_quest[3][3]=1;	char_template_quest[4][3]=0;
char_template_quest[0][4]=0;	char_template_quest[1][4]=0;	char_template_quest[2][4]=1;	char_template_quest[3][4]=0;	char_template_quest[4][4]=0;
char_template_quest[0][5]=0;	char_template_quest[1][5]=0;	char_template_quest[2][5]=0;	char_template_quest[3][5]=0;	char_template_quest[4][5]=0;
char_template_quest[0][6]=0;	char_template_quest[1][6]=0;	char_template_quest[2][6]=1;	char_template_quest[3][6]=0;	char_template_quest[4][6]=0;

//percent   %				
char_template_percent[0][0]=1;	char_template_percent[1][0]=1;	char_template_percent[2][0]=0;	char_template_percent[3][0]=0;	char_template_percent[4][0]=0;
char_template_percent[0][1]=1;	char_template_percent[1][1]=1;	char_template_percent[2][1]=0;	char_template_percent[3][1]=0;	char_template_percent[4][1]=1;
char_template_percent[0][2]=0;	char_template_percent[1][2]=0;	char_template_percent[2][2]=0;	char_template_percent[3][2]=1;	char_template_percent[4][2]=0;
char_template_percent[0][3]=0;	char_template_percent[1][3]=0;	char_template_percent[2][3]=1;	char_template_percent[3][3]=0;	char_template_percent[4][3]=0;
char_template_percent[0][4]=0;	char_template_percent[1][4]=1;	char_template_percent[2][4]=0;	char_template_percent[3][4]=0;	char_template_percent[4][4]=0;
char_template_percent[0][5]=1;	char_template_percent[1][5]=0;	char_template_percent[2][5]=0;	char_template_percent[3][5]=1;	char_template_percent[4][5]=1;
char_template_percent[0][6]=0;	char_template_percent[1][6]=0;	char_template_percent[2][6]=0;	char_template_percent[3][6]=1;	char_template_percent[4][6]=1;

//high   ^				
char_template_high[0][0]=0;	char_template_high[1][0]=0;	char_template_high[2][0]=0;	char_template_high[3][0]=0;	char_template_high[4][0]=0;
char_template_high[0][1]=0;	char_template_high[1][1]=0;	char_template_high[2][1]=1;	char_template_high[3][1]=0;	char_template_high[4][1]=0;
char_template_high[0][2]=0;	char_template_high[1][2]=1;	char_template_high[2][2]=0;	char_template_high[3][2]=1;	char_template_high[4][2]=0;
char_template_high[0][3]=1;	char_template_high[1][3]=0;	char_template_high[2][3]=0;	char_template_high[3][3]=0;	char_template_high[4][3]=1;
char_template_high[0][4]=0;	char_template_high[1][4]=0;	char_template_high[2][4]=0;	char_template_high[3][4]=0;	char_template_high[4][4]=0;
char_template_high[0][5]=0;	char_template_high[1][5]=0;	char_template_high[2][5]=0;	char_template_high[3][5]=0;	char_template_high[4][5]=0;
char_template_high[0][6]=0;	char_template_high[1][6]=0;	char_template_high[2][6]=0;	char_template_high[3][6]=0;	char_template_high[4][6]=0;

char_template_simikolon[0][0]=0;	char_template_simikolon[1][0]=0;	char_template_simikolon[2][0]=0;	char_template_simikolon[3][0]=0;	char_template_simikolon[4][0]=0;
char_template_simikolon[0][1]=0;	char_template_simikolon[1][1]=0;	char_template_simikolon[2][1]=0;	char_template_simikolon[3][1]=0;	char_template_simikolon[4][1]=0;
char_template_simikolon[0][2]=0;	char_template_simikolon[1][2]=0;	char_template_simikolon[2][2]=0;	char_template_simikolon[3][2]=0;	char_template_simikolon[4][2]=0;
char_template_simikolon[0][3]=0;	char_template_simikolon[1][3]=0;	char_template_simikolon[2][3]=1;	char_template_simikolon[3][3]=0;	char_template_simikolon[4][3]=0;
char_template_simikolon[0][4]=0;	char_template_simikolon[1][4]=0;	char_template_simikolon[2][4]=0;	char_template_simikolon[3][4]=0;	char_template_simikolon[4][4]=0;
char_template_simikolon[0][5]=0;	char_template_simikolon[1][5]=0;	char_template_simikolon[2][5]=1;	char_template_simikolon[3][5]=0;	char_template_simikolon[4][5]=0;
char_template_simikolon[0][6]=0;	char_template_simikolon[1][6]=0;	char_template_simikolon[2][6]=1;	char_template_simikolon[3][6]=0;	char_template_simikolon[4][6]=0;

//smaller   <				
char_template_smaller[0][0]=0;	char_template_smaller[1][0]=0;	char_template_smaller[2][0]=0;	char_template_smaller[3][0]=0;	char_template_smaller[4][0]=0;
char_template_smaller[0][1]=0;	char_template_smaller[1][1]=0;	char_template_smaller[2][1]=0;	char_template_smaller[3][1]=1;	char_template_smaller[4][1]=0;
char_template_smaller[0][2]=0;	char_template_smaller[1][2]=0;	char_template_smaller[2][2]=1;	char_template_smaller[3][2]=0;	char_template_smaller[4][2]=0;
char_template_smaller[0][3]=0;	char_template_smaller[1][3]=1;	char_template_smaller[2][3]=0;	char_template_smaller[3][3]=0;	char_template_smaller[4][3]=0;
char_template_smaller[0][4]=0;	char_template_smaller[1][4]=0;	char_template_smaller[2][4]=1;	char_template_smaller[3][4]=0;	char_template_smaller[4][4]=0;
char_template_smaller[0][5]=0;	char_template_smaller[1][5]=0;	char_template_smaller[2][5]=0;	char_template_smaller[3][5]=1;	char_template_smaller[4][5]=0;
char_template_smaller[0][6]=0;	char_template_smaller[1][6]=0;	char_template_smaller[2][6]=0;	char_template_smaller[3][6]=0;	char_template_smaller[4][6]=0;

//bigger   >				
char_template_bigger[0][0]=0;	char_template_bigger[1][0]=0;	char_template_bigger[2][0]=0;	char_template_bigger[3][0]=0;	char_template_bigger[4][0]=0;
char_template_bigger[0][1]=0;	char_template_bigger[1][1]=1;	char_template_bigger[2][1]=0;	char_template_bigger[3][1]=0;	char_template_bigger[4][1]=0;
char_template_bigger[0][2]=0;	char_template_bigger[1][2]=0;	char_template_bigger[2][2]=1;	char_template_bigger[3][2]=0;	char_template_bigger[4][2]=0;
char_template_bigger[0][3]=0;	char_template_bigger[1][3]=0;	char_template_bigger[2][3]=0;	char_template_bigger[3][3]=1;	char_template_bigger[4][3]=0;
char_template_bigger[0][4]=0;	char_template_bigger[1][4]=0;	char_template_bigger[2][4]=1;	char_template_bigger[3][4]=0;	char_template_bigger[4][4]=0;
char_template_bigger[0][5]=0;	char_template_bigger[1][5]=1;	char_template_bigger[2][5]=0;	char_template_bigger[3][5]=0;	char_template_bigger[4][5]=0;
char_template_bigger[0][6]=0;	char_template_bigger[1][6]=0;	char_template_bigger[2][6]=0;	char_template_bigger[3][6]=0;	char_template_bigger[4][6]=0;

//hline   |				
char_template_hline[0][0]=0;	char_template_hline[1][0]=0;	char_template_hline[2][0]=1;	char_template_hline[3][0]=0;	char_template_hline[4][0]=0;
char_template_hline[0][1]=0;	char_template_hline[1][1]=0;	char_template_hline[2][1]=1;	char_template_hline[3][1]=0;	char_template_hline[4][1]=0;
char_template_hline[0][2]=0;	char_template_hline[1][2]=0;	char_template_hline[2][2]=1;	char_template_hline[3][2]=0;	char_template_hline[4][2]=0;
char_template_hline[0][3]=0;	char_template_hline[1][3]=0;	char_template_hline[2][3]=1;	char_template_hline[3][3]=0;	char_template_hline[4][3]=0;
char_template_hline[0][4]=0;	char_template_hline[1][4]=0;	char_template_hline[2][4]=1;	char_template_hline[3][4]=0;	char_template_hline[4][4]=0;
char_template_hline[0][5]=0;	char_template_hline[1][5]=0;	char_template_hline[2][5]=1;	char_template_hline[3][5]=0;	char_template_hline[4][5]=0;
char_template_hline[0][6]=0;	char_template_hline[1][6]=0;	char_template_hline[2][6]=1;	char_template_hline[3][6]=0;	char_template_hline[4][6]=0;

//star   *				
char_template_star[0][0]=0;	char_template_star[1][0]=0;	char_template_star[2][0]=0;	char_template_star[3][0]=0;	char_template_star[4][0]=0;
char_template_star[0][1]=0;	char_template_star[1][1]=1;	char_template_star[2][1]=0;	char_template_star[3][1]=1;	char_template_star[4][1]=0;
char_template_star[0][2]=0;	char_template_star[1][2]=0;	char_template_star[2][2]=1;	char_template_star[3][2]=0;	char_template_star[4][2]=0;
char_template_star[0][3]=0;	char_template_star[1][3]=1;	char_template_star[2][3]=0;	char_template_star[3][3]=1;	char_template_star[4][3]=0;
char_template_star[0][4]=0;	char_template_star[1][4]=0;	char_template_star[2][4]=0;	char_template_star[3][4]=0;	char_template_star[4][4]=0;
char_template_star[0][5]=0;	char_template_star[1][5]=0;	char_template_star[2][5]=0;	char_template_star[3][5]=0;	char_template_star[4][5]=0;
char_template_star[0][6]=0;	char_template_star[1][6]=0;	char_template_star[2][6]=0;	char_template_star[3][6]=0;	char_template_star[4][6]=0;




//at   @				
char_template_at[0][0]=0;	char_template_at[1][0]=1;	char_template_at[2][0]=1;	char_template_at[3][0]=1;	char_template_at[4][0]=0;
char_template_at[0][1]=1;	char_template_at[1][1]=0;	char_template_at[2][1]=0;	char_template_at[3][1]=0;	char_template_at[4][1]=1;
char_template_at[0][2]=0;	char_template_at[1][2]=0;	char_template_at[2][2]=0;	char_template_at[3][2]=0;	char_template_at[4][2]=1;
char_template_at[0][3]=1;	char_template_at[1][3]=1;	char_template_at[2][3]=1;	char_template_at[3][3]=0;	char_template_at[4][3]=1;
char_template_at[0][4]=1;	char_template_at[1][4]=0;	char_template_at[2][4]=0;	char_template_at[3][4]=1;	char_template_at[4][4]=1;
char_template_at[0][5]=1;	char_template_at[1][5]=0;	char_template_at[2][5]=0;	char_template_at[3][5]=0;	char_template_at[4][5]=1;
char_template_at[0][6]=1;	char_template_at[1][6]=1;	char_template_at[2][6]=1;	char_template_at[3][6]=1;	char_template_at[4][6]=1;


}


//----------------------------------------------------ENDE CLOCK----------------------------------------------------
//----------------------------------------------------PONG----------------------------------------------------
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

//----------------------------------------------------ENDE PONG----------------------------------------------------




















String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}


int check_char(char input){
if(input == '@' ||input == '*' ||input == '|' || input == '>' ||input == '<' ||input == ';' ||input == '^' || input == '%' || input == '?' || input == '_' || input == ':' ||input == '#' ||input == '.' ||input == ',' ||input == '!' ||input == '=' ||input == '+' ||input == '-' ||input == '(' ||input == ')' ||input == '[' ||input == ']' ||input == '0' || input == '1' || input == '2' ||input == '3' ||input == '4' ||input == '5' ||input == '6' ||input == '7' ||input == '8' || input == '9' ||input == ' ' || input == 'A' || input == 'B' || input == 'C' || input == 'D' || input == 'E' || input == 'F' || input == 'G' || input == 'H'  || input == 'I' || input == 'J'  || input == 'K' || input == 'L'  || input == 'M' || input == 'N'  ||   input == 'O' || input == 'P'  || input == 'Q' || input == 'R' ||  input == 'S' || input == 'T' || input == 'U' || input == 'V'  || input == 'W' || input == 'X' || input == 'Y' || input == 'Z' || input == 'a' || input == 'b' || input == 'c' || input == 'd' || input == 'e' || input == 'f' || input == 'g' || input == 'h'  || input == 'i' || input == 'j'  || input == 'k' || input == 'l'  || input == 'm' || input == 'n'  ||   input == 'o' || input == 'p'  || input == 'q' || input == 'r' ||  input == 's' || input == 't' || input == 'u' || input == 'v'  || input == 'w' || input == 'x' || input == 'y' || input == 'z'){  

  
  

  
  return 1;
} else{
return 0;
}
}













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
      digitalWrite(relais,HIGH);
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
   digitalWrite(relais,HIGH);   
//DMX


  }else if(mode == 8){  
    digitalWrite(relais,HIGH);  
//SCROLLING TEXT

st_play();



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

server<<"<h2>TABLE TIME :"; if(hour < 10){server<< "0";} server<< hour << ":"; if(minute < 10){server<< "0";} server<< minute << ":";if(second < 10){server<< "0";}  server<< second <<" </h2><br><br>";
server<<".</h2><br><br> <h3> BEIM STARTEN UND WAEHREND DES BETRIEBS DES TISCHES IST EINE INTERNETVERBINDUNG ERFORDERLICH ! <br><br> WENN BEIM STARTEN DIE STANDBYLED LAENGER ALS EINE MINUTE DAUERHAFT ROT LEUCHTET ODER BLINKT: <br>"


"1) GRUENEN RESET SCHALTER DRUECKEN. WENN DANACH DER FEHLER NICHT BEHOBEN IST, SIEHE SCHRITT 2<br>"
"2) NETZWERK-VERBINDUNG PRÜFEN. WENN DANACH DER FEHLER NICHT BEHOBEN IST, SIEHE SCHRITT 3<br>"
"3) MIT EINEM USB-KABEL DEN TISCH UND EINEN PC VERBINDEN. <br>"
"3.1) DIE ARDUINO SOFTWARE (>= 1.5.6-r2) LADEN UND DEN SERIAL-MONITOR AUFRUFEN ("; 
server<<baud_rate;


server<< "BAUD). <br>"
"3.2) GRUENEN RESET SCHALTER DRUECKEN UND AUF AUSGABEN IN DER CONSOLE WARTEN. <br>"
"</h3></p>";

    server.printP(pend);

  }
}



int api_get_value = 0;
void apigetCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
 if (type == WebServer::POST)
  {
    bool repeat;
    char name[32], value[32];
    do
    {
      repeat = server.readPOSTparam(name, 32, value, 32);
if(api_enable == 1){
              if (strcmp(name, "baud_rate") == 0){api_get_value = baud_rate;}
              if (strcmp(name, "fan_state") == 0){api_get_value = fan_state;}
              if (strcmp(name, "mode") == 0){api_get_value = mode;}
              if (strcmp(name, "rainbowspeed") == 0){api_get_value = rainbowspeed;}
              if (strcmp(name, "randomspeed") == 0){api_get_value = randomspeed;}
              if (strcmp(name, "randomefmode") == 0){api_get_value = randomefmode;}
              if (strcmp(name, "use_ethernet") == 0){api_get_value = use_ethernet;}
              if (strcmp(name, "enable_dhcp") == 0){api_get_value = enable_dhcp;}
              if (strcmp(name, "wait_for_DHCP") == 0){api_get_value = wait_for_DHCP;}
              if (strcmp(name, "zeitverschiebung") == 0){api_get_value = zeitverschiebung;}
              if (strcmp(name, "nth") == 0){api_get_value = nth;} 
              if (strcmp(name, "nthe") == 0){api_get_value = nthe;}
              if (strcmp(name, "nthen") == 0){api_get_value = nthen;}
              if (strcmp(name, "nthstate") == 0){api_get_value = nthstate;}
              if (strcmp(name, "nthonmode") == 0){api_get_value = nthonmode;}
              if (strcmp(name, "nthoffmode") == 0){api_get_value = nthoffmode;}
              if (strcmp(name, "clock_orientation") == 0){api_get_value = clock_orientation;}
              if (strcmp(name, "player1score") == 0){api_get_value = player1score;}
              if (strcmp(name, "player2score") == 0){api_get_value = player2score;}
              if (strcmp(name, "pong_game_speed") == 0){api_get_value = pong_game_speed;}
              if (strcmp(name, "paddle1size") == 0){api_get_value = paddle1size;}
              if (strcmp(name, "paddle2size") == 0){api_get_value = paddle2size;}
              if (strcmp(name, "st_speed") == 0){api_get_value = st_speed;}
              if (strcmp(name, "chenp2") == 0){api_get_value = chenp2;}
              if (strcmp(name, "chenp1") == 0){api_get_value = chenp1;}
              if (strcmp(name, "feldx") == 0){api_get_value = feldx;}
              if (strcmp(name, "feldy") == 0){api_get_value = feldy;}
              if (strcmp(name, "second") == 0){api_get_value = second;}
              if (strcmp(name, "minute") == 0){api_get_value = minute;}
              if (strcmp(name, "hour") == 0){api_get_value = hour;}
              if (strcmp(name, "reset_jumper") == 0){api_get_value = reset_jumper;}
              if (strcmp(name, "st_char_count") == 0){api_get_value = st_char_count;}   
              if (strcmp(name, "relais") == 0){api_get_value = relais;}  
              if (strcmp(name, "rss_enable") == 0){api_get_value = rss_enable;}  
              if (strcmp(name, "rss_state") == 0){api_get_value = rss_state;}  
    
    

    
} 
    } while (repeat);
        clear_screen();
        save_settings();
    server.httpSeeOther("/apiget.html");
    return;
  }
  
  
  
  server.httpSuccess();
  if (type == WebServer::GET)
  {

server<<"<html><head><title>LED TABLE API (GET)</title></head><body>";
server<<api_get_value;
server<<"</body></html>";


  }
}



int api_set_value = 0;
void apisetCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
 if (type == WebServer::POST)
  {
    bool repeat;
    char name[32], value[32];
    do
    {
      repeat = server.readPOSTparam(name, 32, value, 32);
            if(api_enable == 1){
              if (strcmp(name, "fan_state") == 0){fan_state= strtoul(value, NULL, 10);}
              if (strcmp(name, "mode") == 0){mode= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "rainbowspeed") == 0){ rainbowspeed= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "randomspeed") == 0){ randomspeed= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "randomefmode") == 0){randomefmode= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "zeitverschiebung") == 0){zeitverschiebung = strtoul(value, NULL, 10) ;}
              if (strcmp(name, "nth") == 0){nth= strtoul(value, NULL, 10) ;} 
              if (strcmp(name, "nthe") == 0){nthe= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "nthen") == 0){nthen= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "nthstate") == 0){ nthstate= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "nthonmode") == 0){nthonmode= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "nthoffmode") == 0){nthoffmode = strtoul(value, NULL, 10) ;}
              if (strcmp(name, "clock_orientation") == 0){clock_orientation= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "player1score") == 0){player1score= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "player2score") == 0){player2score= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "pong_game_speed") == 0){pong_game_speed= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "paddle1size") == 0){paddle1size= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "paddle2size") == 0){ paddle2size= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "st_speed") == 0){st_speed= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "chenp2") == 0){chenp2= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "chenp1") == 0){ chenp1= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "rss_enable") == 0){ rss_enable= strtoul(value, NULL, 10) ;}
              if (strcmp(name, "gettime") == 0){get_ntp_time();}
              if (strcmp(name, "save") == 0){ save_settings();}
              if (strcmp(name, "clearscreen") == 0){ clear_screen();}
            } 
    } while (repeat);
        clear_screen();
        save_settings();
    server.httpSeeOther("/apiset.html");
    return;
  }
  
  
  
  server.httpSuccess();
  if (type == WebServer::GET)
  {

server<<"<html><head><title>LED TABLE API (SET)</title></head><body></body></html>";


  }
}








void apiCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
 if (type == WebServer::POST)
  {
    bool repeat;
    char name[32], value[32];
    do
    {
      repeat = server.readPOSTparam(name, 32, value, 32);
    } while (repeat);
        clear_screen();
        save_settings();
    server.httpSeeOther("/api.html");
    return;
  }
  server.httpSuccess();
  if (type == WebServer::GET)
  {
    server.printP(phead);
    server.printP(pstart);
server.print("<span class='title'>API DOCUMENTATION</span><p><center>");    
server<<"<hr><h2>";
server<<"Mit der LED-Table-API kannst per POST-Request ganz einfach die wichtigsten Status-Variablen abfragen/setzten. <br> In der Tabelle siehst du welche Variablen du abfragen/setzten kannst. <br> Ein Request einer Variable wird dann per POST an /apiget.html und /apiset.html gemacht";
server<<"</h2><br><br>";
server.printP(api_table);
server<<"</center</p>";
server.printP(pend);
  }
}





void tisCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
 if (type == WebServer::POST)
  {
    bool repeat;
    char name[32], value[32];
    do
    {
      repeat = server.readPOSTparam(name, 32, value, 32);
    } while (repeat);
        clear_screen();
        save_settings();
    server.httpSeeOther("/api.html");
    return;
  }
  server.httpSuccess();
  if (type == WebServer::GET)
  {
    server.printP(phead);
    server.printP(pstart);
server.print("<span class='title'>TABLE INFORMATION SYSTEN DOCUMENTATION</span><p><center>");    
server<<"<hr><h2>";
server<<"Mit dem TABLE INFORMATION SYSTEM (TIS) koennen wichtige Informationen auf dem Tisch per Laufschrift angezeigt werden (aehnlich dem Scrolling-Text Mode).<br> Wenn neue Informationen eingehen zeigt der Tisch sie direkt an und wechselt danach wieder zurueck in den vorherigen Modus.<br> Die Infoswerden ueber Serialport 1 an Arduino Due gesendet, und dieser zeigt die Informationen an. <br> Die Anzeigeoptionen findest du in den Settings. <br>";
server<<"</h2><br><br>";

server<<"</center</p>";
server.printP(pend);
  }
}








void rgbCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{

    
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[64], value[64];
    do
    {
      repeat = server.readPOSTparam(name, 64, value, 64);

      if (strcmp(name, "mode") == 0){
        if(mode == 5 && strtoul(value, NULL, 10) != 5){delay(2000);digitalWrite(relais,HIGH); clear_screen();}
         mode = strtoul(value, NULL, 10);    
         if(mode == 1){fillred= 0;fillgreen = 0;fillblue = 0;}else if(mode == 4){pong_main_reset();} 
         clear_screen();
      }
      if (strcmp(name, "red") == 0){ fillred = strtoul(value, NULL, 10);}
      if (strcmp(name, "green") == 0){fillgreen = strtoul(value, NULL, 10);}
      if (strcmp(name, "blue") == 0){fillblue = strtoul(value, NULL, 10);}   
      if (strcmp(name, "rmode") == 0){rainbowmode = strtoul(value, NULL, 10); }  
      if (strcmp(name, "ccm") == 0){clock_fix_color_m = strtoul(value, NULL, 10);}     
      if (strcmp(name, "cch") == 0){clock_fix_color_h = strtoul(value, NULL, 10);}
      if (strcmp(name, "clockcolor") == 0){clockcolormode = strtoul(value, NULL, 10);}    
      if (strcmp(name, "ranmode") == 0){randommode = strtoul(value, NULL, 10);clear_screen();}  
      if (strcmp(name, "ranefmode") == 0){randomefmode = strtoul(value, NULL, 10);}    
      if (strcmp(name, "chenp1") == 0){chenp1 = strtoul(value, NULL, 10);}     
      if (strcmp(name, "chenp2") == 0){ chenp2 = strtoul(value, NULL, 10);}
      if (strcmp(name, "pongenreset") == 0){pongenreset = strtoul(value, NULL, 10);}
      if (strcmp(name, "paddle1size") == 0){paddle1size = strtoul(value, NULL, 10);}
      if (strcmp(name, "paddle2size") == 0){paddle2size = strtoul(value, NULL, 10);}
      if (strcmp(name, "clockor") == 0){clock_orientation = strtoul(value, NULL, 10);}
      if (strcmp(name, "clockspeed") == 0){clock_color_speed = strtoul(value, NULL, 10); }
      if (strcmp(name, "ponginvp2") == 0){pong_invert_p2 = strtoul(value, NULL, 10);}
      if (strcmp(name, "ponginvp1") == 0){pong_invert_p1= strtoul(value, NULL, 10);}
      if (strcmp(name, "pongresetp1") == 0){player1score = 0;}
      if (strcmp(name, "pongresetp2") == 0){player2score = 0;}
      if (strcmp(name, "pong_game_speed") == 0){ pong_game_speed = strtoul(value, NULL, 10);}
      if (strcmp(name, "pongmode") == 0){pongmode = strtoul(value, NULL, 10);}
      if (strcmp(name, "rsp") == 0){rainbowspeed = strtoul(value, NULL, 10);}
      if (strcmp(name, "cb") == 0){clock_bright = strtoul(value, NULL, 10);}
      if (strcmp(name, "ransp") == 0){randomspeed = strtoul(value, NULL, 10);}
      if (strcmp(name, "sts") == 0){st_speed = strtoul(value, NULL, 10);}  
      if (strcmp(name, "stcm") == 0){st_color_mode = strtoul(value, NULL, 10);}   
      if (strcmp(name, "strs") == 0){st_rain_speed = strtoul(value, NULL, 10);}     
      if (strcmp(name, "stb") == 0){st_bright = strtoul(value, NULL, 10);}    
      if (strcmp(name, "stfc") == 0){st_fix_color = strtoul(value, NULL, 10);}     
       if (strcmp(name, "sttext") == 0){
       
         st_char_count = 0;
         for(int i=0; i< st_maxchar; i++) {
           st_chars[i] = 0;
        if( check_char(value[i]) == 1){
     st_char_count++;
            st_chars[i] = value[i];
        Serial.println(value[i]);
           }

}


      st_text_to_arr();
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
server<<"<tr>";
server<<"<td><label for='mode'>TABLE MODE</label> </td>";
server<<"<td scope='col'><input type='radio' name='mode' id='mode' value='5' ";if(mode == 5){server <<"checked";}if(rss_enable == 1 && rss_state == 1){server<<" disabled";}server<<">OFF</td>  ";
server<<"<td scope='col'><input type='radio' name='mode' id='mode' value='0' ";if(mode == 0){server <<"checked";}if(rss_enable == 1 && rss_state == 1){server<<" disabled";}server<<">STANDBY (STILL ALIVE)</td>  ";
server<<"<td scope='col'><input type='radio' name='mode' id='mode'  value='1' ";if(mode == 1){server <<"checked";}if(rss_enable == 1 && rss_state == 1){server<<" disabled";}server<<">CONST COLOR </td>";
server<<"<td scope='col'><input type='radio' name='mode' id='mode'  value='2' ";if(mode == 2){server <<"checked";}if(rss_enable == 1 && rss_state == 1){server<<" disabled";}server<<">RAINBOW</td>";
server<<"<td scope='col'><input type='radio' name='mode' id='mode'  value='3' ";if(mode == 3){server <<"checked";}if(rss_enable == 1 && rss_state == 1){server<<" disabled";}server<<">RANDOM</td>";
server<<"<td scope='col'><input type='radio' name='mode' id='mode'  value='4' ";if(mode == 4){server <<"checked";}if(rss_enable == 1 && rss_state == 1){server<<" disabled";}server<<">PONG (GAME)</td>";
server<<"<td scope='col'><input type='radio' name='mode' id='mode'  value='6' ";if(mode == 6){server <<"checked";}if(rss_enable == 1 && rss_state == 1){server<<" disabled";}server<<">CLOCK</td>";
server<<"<td scope='col'><input type='radio' name='mode' id='mode'  value='8' ";if(mode == 8){server <<"checked";}if(rss_enable == 1 && rss_state == 1){server<<" disabled";}server<<">SCROLLING TEXT</td>";
if(rss_enable == 1 && rss_state == 1){server<<"<td scope='col'><input type='radio' name='mode' id='mode'  value='9' ";if(mode == 9){server <<"checked";}server<<">T.I.S.</td>";}
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
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


}else if(mode == 8){

  server<<"<form id='sttext' name='sttext' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='sts'>TEXT [MAX. 60 CHARS: a-z A-Z 0-9 ( ) [ ] . , + - ! # = : _ ? / ^ ; < > |  @ ]</label></td>";
server<<"<td>";
server<<"</td> ";
server<<"<td scope='col' >";
server<<"<input name='sttext' type='text' id='sttext' value='";

for(int i=0; i< st_maxchar; i++) {
  
  if(check_char(st_chars[i]) == 1){
 server<<st_chars[i];
  }
}

;server <<"' size='20'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE AND CONVERT TEXT TO TABLE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";



  
server<<" <form id='stcm' namestcmopt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='stcm'>COLOR MODE</label> </td>";
server<<"<td scope='col'><input type='radio' name='stcm' id='stcm' value='0' ";if(st_color_mode == 0){server <<"checked";}server<<">RAINBOW</td>  ";
server<<"<td scope='col'><input type='radio' name='stcm' id='stcm'  value='1' ";if(st_color_mode == 1){server <<"checked";}server<<">STATIC COLOR</td>";
server<<"<td scope='col'><input type='radio' name='stcm' id='stcm'  value='2' ";if(st_color_mode == 2){server <<"checked";}server<<">RANDOM</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";




server<<"<form id='stspeed' name='stspeed' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='sts'>SPEED</label></td>";
server<<"<td>";
server<<"    SPEED : <br>";
server<<"</td> ";
server<<"<td scope='col' >";
server<<"<input name='sts' type='number' id='sts' max='1000' min='0' step='1' value='"; server<<st_speed;server <<"' size='20'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";








if(st_color_mode == 1){
server<<"<form id='cch' name='cch' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='stfc'COLOR</label> </td>";
server<<"<td scope='col'><input type='radio' name='stfc' id='stfc' value='0' ";if(st_fix_color == 0){server <<"checked";}server<<">RED </td>  ";
server<<"<td scope='col'><input type='radio' name='stfc' id='stfc'  value='1' ";if(st_fix_color == 1){server <<"checked";}server<<">GREEN</td>";
server<<"<td scope='col'><input type='radio' name='stfc' id='stfc'  value='2' ";if(st_fix_color == 2){server <<"checked";}server<<">BLUE</td>";
server<<"<td scope='col'><input type='radio' name='stfc' id='stfc'  value='3' ";if(st_fix_color == 3){server <<"checked";}server<<">CYAN</td>";
server<<"<td scope='col'><input type='radio' name='stfc' id='stfc'  value='4' ";if(st_fix_color == 4){server <<"checked";}server<<">PINK</td>";
server<<"<td scope='col'><input type='radio' name='stfc' id='stfc'  value='5' ";if(st_fix_color == 5){server <<"checked";}server<<">YELLOW</td>";
server<<"<td scope='col'><input type='radio' name='stfc' id='stfc'  value='6' ";if(st_fix_color == 6){server <<"checked";}server<<">PSEUDO WHITE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";



server<<"<form id='stb' name='stb' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='stb'>COLOR BRIGHTNESS</label></td>";
server<<"<td>";
server<<"</td> ";
server<<"<td scope='col' >";
server<<"<input name='stb' type='number' id='stb' max='255' min='0' step='1' value='"; server<<st_bright;server <<"' size='20'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";


}else if(st_color_mode == 0){
server<<"<form id='strs' name='strs' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='strs'>RAINBOW CYCLE SPEED</label></td>";
server<<"<td>";
server<<"    SPEED : <br>";
server<<"</td> ";
server<<"<td scope='col' >";
server<<"<input name='strs' type='number' id='strs' max='50' min='0' step='1' value='"; server<<st_rain_speed;server <<"' size='20'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";


}


}else if(mode == 2){
server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='rmode'>RAINBOW TYPE</label> </td>";
server<<"<td scope='col'><input type='radio' name='rmode' id='rmode' value='0' ";if(rainbowmode == 0){server <<"checked";}server<<">THEATRE (ROW)</td>  ";
server<<"<td scope='col'><input type='radio' name='rmode' id='rmode'  value='1' ";if(rainbowmode == 1){server <<"checked";}server<<">CYCLE (ROW)</td>";
server<<"<td scope='col'><input type='radio' name='rmode' id='rmode'  value='2' ";if(rainbowmode == 2){server <<"checked";}server<<">COMPLETE (ROW)</td>";
server<<"<td scope='col'><input type='radio' name='rmode' id='rmode'  value='3' ";if(rainbowmode == 3){server <<"checked";}server<<">STACCATO (COL)</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
server<<"<form id='speed' name='speed' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='rsp'>RAINBOW SPEED</label></td>";
server<<"<td>";
server<<"    SPEED : <br>";
server<<"</td> ";
server<<"<td scope='col' >";
server<<"<input name='rsp' type='number' id='rsp' max='100000' min='0' step='1' value='"; server<<rainbowspeed;server <<"' size='5'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
}else if (mode == 3){
server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='ranmode'>RANDOM TYPE</label> </td>";
server<<"<td scope='col'><input type='radio' name='ranmode' id='ranmode' value='0' ";if(randommode == 0){server <<"checked";}server<<">ROW BY ROW</td>  ";
server<<"<td scope='col'><input type='radio' name='ranmode' id='ranmode'  value='1' ";if(randommode == 1){server <<"checked";}server<<">DIRECT</td>";
server<<"<td scope='col'><input type='radio' name='ranmode' id='ranmode'  value='2' ";if(randommode == 2){server <<"checked";}server<<">COMPLETE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
 server<<"<form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='ranmode'>PIXEL APPEAR</label> </td>";
server<<"<td scope='col'><input type='radio' name='ranefmode' id='ranefmode' value='0' ";if(randomefmode == 0){server <<"checked";}server<<">SHIFTING</td>  ";
server<<"<td scope='col'><input type='radio' name='ranefmode' id='ranefmode'  value='1' ";if(randomefmode == 1){server <<"checked";}server<<">RANDOM</td>";
server<<"</table> ";
server<<"</form>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
server<<"<form id='speed' name='speed' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='ransp'>RANDOM SPEED</label></td>";
server<<"<td>";
server<<"    SPEED : <br>";
server<<"</td> ";
server<<"<td scope='col' >";
server<<"<input name='ransp' type='number' id='ransp' max='100000' min='0' step='1' value='"; server<<randomspeed;server <<"' size='5'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
}else if (mode == 6){
server<<"<form id='clockcolor' name='clockcolor' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='fanstate'>CLOCK COLOR MODE</label> </td>";
server<<"<td scope='col'><input type='radio' name='clockcolor' id='clockcolor' value='0' ";if(clockcolormode == 0){server <<"checked";}server<<">RAINBOW </td>  ";
server<<"<td scope='col'><input type='radio' name='clockcolor' id='clockcolor'  value='1' ";if(clockcolormode == 1){server <<"checked";}server<<">FIX</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
if(clockcolormode == 0){
server<<"<form id='speed' name='clockspeed' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='paddle1size'>COLOR FADING SPEED</label></td>";
server<<"<td scope='col' >";
server<<"<input name='clockspeed' type='number' id='clockspeed' max='900' min='0' step='1' value='"; server<<clock_color_speed;server <<"' size='5'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
}else if(clockcolormode == 1){
server<<"<form id='cch' name='cch' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='cch'HOUR COLOR</label> </td>";
server<<"<td scope='col'><input type='radio' name='cch' id='cch' value='0' ";if(clock_fix_color_h == 0){server <<"checked";}server<<">RED </td>  ";
server<<"<td scope='col'><input type='radio' name='cch' id='cch'  value='1' ";if(clock_fix_color_h == 1){server <<"checked";}server<<">GREEN</td>";
server<<"<td scope='col'><input type='radio' name='cch' id='cch'  value='2' ";if(clock_fix_color_h == 2){server <<"checked";}server<<">BLUE</td>";
server<<" <td scope='col'><input type='radio' name='cch' id='cch'  value='3' ";if(clock_fix_color_h == 3){server <<"checked";}server<<">CYAN</td>";
server<<"<td scope='col'><input type='radio' name='cch' id='cch'  value='4' ";if(clock_fix_color_h == 4){server <<"checked";}server<<">PINK</td>";
server<<"<td scope='col'><input type='radio' name='cch' id='cch'  value='5' ";if(clock_fix_color_h == 5){server <<"checked";}server<<">YELLOW</td>";
server<<"<td scope='col'><input type='radio' name='cch' id='cch'  value='6' ";if(clock_fix_color_h == 6){server <<"checked";}server<<">PSEUDO WHITE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<" </tr>  ";
server<<"</table>";
server<<"</form>"; 
server<<"<form id='cch' name='cch' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='ccm'MINUTE COLOR</label> </td>";
server<<"<td scope='col'><input type='radio' name='ccm' id='ccm' value='0' ";if(clock_fix_color_m == 0){server <<"checked";}server<<">RED </td>  ";
server<<"<td scope='col'><input type='radio' name='ccm' id='ccm'  value='1' ";if(clock_fix_color_m == 1){server <<"checked";}server<<">GREEN</td>";
server<<"<td scope='col'><input type='radio' name='ccm' id='ccm'  value='2' ";if(clock_fix_color_m == 2){server <<"checked";}server<<">BLUE</td>";
server<<"<td scope='col'><input type='radio' name='ccm' id='ccm'  value='3' ";if(clock_fix_color_m == 3){server <<"checked";}server<<">CYAN</td>";
server<<"<td scope='col'><input type='radio' name='ccm' id='ccm'  value='4' ";if(clock_fix_color_m == 4){server <<"checked";}server<<">PINK</td>";
server<<"<td scope='col'><input type='radio' name='ccm' id='ccm'  value='5' ";if(clock_fix_color_m == 5){server <<"checked";}server<<">YELLOW</td>";
server<<"<td scope='col'><input type='radio' name='ccm' id='ccm'  value='6' ";if(clock_fix_color_m == 6){server <<"checked";}server<<">PSEUDO WHITE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
server<<"<form id='speed' name='cb' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='cb'>CLOLOR BRIGHTNESS</label></td>";
server<<"<td scope='col' >";
server<<"<input name='cb' type='number' id='cb' max='255' min='0' step='1' value='"; server<<clock_bright;server <<"' size='5'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
}else{
}
server<<" <form id='clock_orientation' name='clockor' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='clockor'>DISPLAY ORIENTATION</label> </td>";
server<<"<td scope='col'><input type='radio' name='clockor' id='clockor' value='0' ";if(clock_orientation == 0){server <<"checked";}server<<">LEFT</td>  ";
server<<"<td scope='col'><input type='radio' name='clockor' id='clockor'  value='1' ";if(clock_orientation == 1){server <<"checked";}server<<">RIGHT</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
}else if (mode == 4){
server<<"<form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='pongmode'>PONG MODE</label> </td>";
server<<"<td scope='col'><input type='radio' name='pongmode' id='pongmode' value='0' ";if(pongmode == 0){server <<"checked";}server<<">2 PLAYER MODE ( with NES Controller)</td>  ";
//server<<"<td scope='col'><input type='radio' name='pongmode' id='pongmode' value='2' ";if(pongmode == 2){server <<"checked";}server<<">2 PLAYER MODE EXTREME ( with NES Controller)</td>  ";
server<<"<td scope='col'><input type='radio' name='pongmode' id='pongmode'  value='1' ";if(pongmode == 1){server <<"checked";}server<<">AUTO PONG</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
if(pongmode == 0 && pongmode == 2){
server<<"<form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='pongmode'>CHEATMODE PLAYER 1</label> </td>";
server<<"<td scope='col'><input type='radio' name='chenp1' id='chenp1' value='0' ";if(chenp1 == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"<td scope='col'><input type='radio' name='chenp1' id='chenp1'  value='1' ";if(chenp1 == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
server<<"<form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='pongmode'>CHEATMODE PLAYER 2</label> </td>";
server<<"<td scope='col'><input type='radio' name='chenp2' id='chenp2' value='0' ";if(chenp2 == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"<td scope='col'><input type='radio' name='chenp2' id='chenp2'  value='1' ";if(chenp2 == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
 server<<"<form id='speed' name='speed' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='paddle1size'>PADDLE SIZE PLAYER 1</label></td>";
server<<"<td>";
server<<"    SPEED : <br>";
server<<"</td> ";
server<<"<td scope='col' >";
server<<"<input name='paddle1size' type='number' id='paddle1size' max='10' min='1' step='1' value='"; server<<paddle1size;server <<"' size='5'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
server<<"<form id='speed' name='speed' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='paddle2size'>PADDLE SIZE PLAYER 2</label></td>";
server<<"<td>";
server<<"    SPEED : <br>";
server<<"</td> ";
server<<"<td scope='col' >";
server<<"<input name='paddle2size' type='number' id='paddle2size' max='10' min='1' step='1' value='"; server<<paddle2size;server <<"' size='5'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
server<<"<form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='pongmode'>INVERT PLAYER 1</label> </td>";
server<<"<td scope='col'><input type='radio' name='ponginvp1' id='ponginvp1' value='0' ";if(pong_invert_p1 == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"<td scope='col'><input type='radio' name='ponginvp1' id='ponginvp1'  value='1' ";if(pong_invert_p1 == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
server<<" <form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='pongmode'>INVERT PLAYER 2</label> </td>";
server<<"<td scope='col'><input type='radio' name='ponginvp1' id='ponginvp2' value='0' ";if(pong_invert_p2 == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"<td scope='col'><input type='radio' name='ponginvp1' id='ponginvp2'  value='1' ";if(pong_invert_p2 == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
server<<"<form id='opt' name='opt' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<" <tr>";
server<<"<td><label for='pongmode'>ALLOW PLAYER RESET</label> </td>";
server<<"<td scope='col'><input type='radio' name='pongenreset' id='pongenreset' value='0' ";if(pongenreset == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"<td scope='col'><input type='radio' name='pongenreset' id='pongenreset'  value='1' ";if(pongenreset == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
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
server<<"<form id='speed' name='speed' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='paddle1size'>START SPEED</label></td>";
server<<"<td>";
server<<"    SPEED : <br>";
server<<"</td> ";
server<<"<td scope='col' >";
server<<"<input name='pong_game_speed' type='number' id='pong_game_speed' max='100000' min='1' step='1' value='"; server<<pong_game_speed;server <<"' size='5'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";




}else{
server<<" - NO OPTIONS FOR THIS MODE - ";
}
server<<"</p>";
    server.printP(pend);
  }
}




void settingsCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
 if (type == WebServer::POST)
  {
    bool repeat;
    char name[32], value[32];
    do
    {
      repeat = server.readPOSTparam(name, 32, value, 32);

      
      
           if (strcmp(name, "dhcp") == 0)
      {
         enable_dhcp = strtoul(value, NULL, 10);
      }
      
        if (strcmp(name, "ts") == 0)  {
         timeServer[0] = getValue(value, '.', 0).toInt();
          timeServer[1] = getValue(value, '.', 1).toInt();
           timeServer[2] = getValue(value, '.', 2).toInt();
            timeServer[3] = getValue(value, '.', 3).toInt();
      }
      
              if (strcmp(name, "ip") == 0)
      {
         ip[0] = getValue(value, '.', 0).toInt();
          ip[1] = getValue(value, '.', 1).toInt();
           ip[2] = getValue(value, '.', 2).toInt();
            ip[3] = getValue(value, '.', 3).toInt();
      }
      
                    if (strcmp(name, "sm") == 0)
      {
         subnet[0] = getValue(value, '.', 0).toInt();
          subnet[1] = getValue(value, '.', 1).toInt();
           subnet[2] = getValue(value, '.', 2).toInt();
            subnet[3] = getValue(value, '.', 3).toInt();
      }
     
                   if (strcmp(name, "gw") == 0)
      {
         gateway[0] = getValue(value, '.', 0).toInt();
          gateway[1] = getValue(value, '.', 1).toInt();
           gateway[2] = getValue(value, '.', 2).toInt();
            gateway[3] = getValue(value, '.', 3).toInt();
      }
      
      
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
 
 
                         if (strcmp(name, "apien") == 0){
         api_enable = strtoul(value, NULL, 10);
      }
 
 
                          if (strcmp(name, "rssen") == 0){
         rss_enable = strtoul(value, NULL, 10);
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
server.print("<span class='title'>NIGHTMODE SETTINGS</span><p>");    
server<<"<hr>";
server<<"<form id='nthen' name='nthen' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='nthen'>NIGHTMODE STATE</label> </td>";
server<<"<td scope='col'><input type='radio' name='nthen' id='nthen' value='0' ";if(nthen == 0){server <<"checked";}server<<">DISABLE</td>";
server<<"<td scope='col'><input type='radio' name='nthen' id='nthen'  value='1' ";if(nthen == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
server<<"<form id='speed' name='nth' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='nth'>NIGHTMODE START</label></td>";
server<<"<td scope='col' >";
server<<"<input name='nth' type='number' id='nth' max='23' min='0' step='1' value='"; server<<nth;server <<"' size='5'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
server<<"<form id='speed' name='nth' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='nthe'>NIGHTMODE STOP</label></td>";
server<<"<td scope='col' >";
server<<"<input name='nthe' type='number' id='nthe' max='23' min='0' step='1' value='"; server<<nthe;server <<"' size='5'><br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
server<<" <form id='colorsettings' name='nthonmode' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='mode'>NIGHTMODE ON MODE</label> </td>";
server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode' value='5' ";if(nthonmode == 5){server <<"checked";}server<<">OFF</td>  ";
server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode' value='0' ";if(nthonmode == 0){server <<"checked";}server<<">STANDBY (STILL ALIVE)</td>  ";
server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='1' ";if(nthonmode == 1){server <<"checked";}server<<">CONST COLOR </td>";
server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='2' ";if(nthonmode == 2){server <<"checked";}server<<">RAINBOW</td>";
server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='3' ";if(nthonmode == 3){server <<"checked";}server<<">RANDOM</td>";
server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='4' ";if(nthonmode == 4){server <<"checked";}server<<">PONG (GAME)</td>";
server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='6' ";if(nthonmode == 6){server <<"checked";}server<<">CLOCK</td>";
//server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='7' ";if(nthonmode == 7){server <<"checked";}server<<">DMX</td>";
server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='8' ";if(nthonmode == 8){server <<"checked";}server<<">SCROLLING TEXT</td>";
//server<<"<td scope='col'><input type='radio' name='nthonmode' id='nthonmode'  value='9' ";if(nthonmode == 9){server <<"checked";}server<<">RSS-TICKER</td>";
server<<" <td><input type='submit' value='SAVE' /></td> ";
server<<"  </tr>  ";
server<<"</table>";
server<<"</form>";
server<<"<form id='colorsettings' name='nthoffmode' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='mode'>NIGHTMODE OFF MODE</label> </td>";
server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode' value='5' ";if(nthoffmode == 5){server <<"checked";}server<<">OFF</td>  ";
server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode' value='0' ";if(nthoffmode == 0){server <<"checked";}server<<">STANDBY (STILL ALIVE)</td>  ";
server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='1' ";if(nthoffmode == 1){server <<"checked";}server<<">CONST COLOR </td>";
server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='2' ";if(nthoffmode == 2){server <<"checked";}server<<">RAINBOW</td>";
server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='3' ";if(nthoffmode == 3){server <<"checked";}server<<">RANDOM</td>";
server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='4' ";if(nthoffmode == 4){server <<"checked";}server<<">PONG (GAME)</td>";
server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='6' ";if(nthoffmode == 6){server <<"checked";}server<<">CLOCK</td>";
//server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='7' ";if(nthoffmode == 7){server <<"checked";}server<<">DMX</td>";
server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='8' ";if(nthoffmode == 8){server <<"checked";}server<<">SCROLLING TEXT</td>";
//server<<"<td scope='col'><input type='radio' name='nthoffmode' id='nthoffmode'  value='9' ";if(nthoffmode == 9){server <<"checked";}server<<">RSS-TICKER</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
server<<"<br><br> <hr><br>";
server.print("<span class='title'>CLOCK SETTINGS</span><p>"); 
server<<"<form id='zz' name='zz' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='paddle1size'>TimeZone</label></td>";
server<<"<td scope='col' >";
server<<"   + <input name='zz' type='number' id='zz' max='23' min='0' step='1' value='"; server<<zeitverschiebung;server <<"' size='5'>h<br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='REFRESH' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
server<<"<form id='ts' name='ts' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='ts'>TimeServer-IP ( Stratum 0 ONLY)</label></td>";
server<<"<td scope='col' >";
server<<"<input name='ts' type='text' id='ts'  value='"; server<<timeServer[0];server<<".";server<<timeServer[1];server<<".";server<<timeServer[2];server<<".";server<<timeServer[3];     ;server <<"'<br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
server<<"<form id='setDate' name='setDate' action=''  method='post'>";
server<<"<input type='hidden' id='setDate' name='setDate' value='1'>";
server<<"<input type='submit' value='GET NTP TIME' />";
server<<"</form>";
server<<"<br><br> <hr><br>";
server.print("<span class='title'>NETWORK SETTINGS</span><p>"); 
server<<" <form id='fanstate' name='fanstate' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='dhcp'>DHCP</label> </td>";
server<<"<td scope='col'><input type='radio' name='dhcp' id='dhcp' value='0' ";if(enable_dhcp == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"<td scope='col'><input type='radio' name='dhcp' id='dhcp'  value='1' ";if(enable_dhcp == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";
server<<"<form id='ip' name='ip' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='ip'>IP</label></td>";
server<<"<td scope='col' >";
server<<"<input name='ip' type='text' id='ip'  value='"; server<<ip[0];server<<".";server<<ip[1];server<<".";server<<ip[2];server<<".";server<<ip[3];     ;server <<"'<br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
server<<"<form id='gw' name='gw' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='gw'>GATEWAY</label></td>";
server<<"<td scope='col' >";
server<<"<input name='gw' type='text' id='gw'  value='"; server<<gateway[0];server<<".";server<<gateway[1];server<<".";server<<gateway[2];server<<".";server<<gateway[3];     ;server <<"'<br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
server<<"<form id='sm' name='sm' action=''  method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td scope='col'> <label for='sm'>SUBNETMASK</label></td>";
server<<"<td scope='col' >";
server<<"<input name='sm' type='text' id='sm'  value='"; server<<subnet[0];server<<".";server<<subnet[1];server<<".";server<<subnet[2];server<<".";server<<subnet[3];     ;server <<"'<br>";
server<<"</td>  ";
server<<"<td colspan='2'><input type='submit' value='SAVE' /></td>";
server<<"</tr>";
server<<"</table> ";
server<<"</form>";
server<<"<br><br> <hr><br>";
server.print("<span class='title'>FURTHER SETTINGS</span><p>"); 
server<<"<form id='fanstate' name='fanstate' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='fanstate'>FAN STATE</label> </td>";
server<<"<td scope='col'><input type='radio' name='fanstate' id='fanstate' value='0' ";if(fan_state == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"<td scope='col'><input type='radio' name='fanstate' id='fanstate'  value='1' ";if(fan_state == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";


server<<"<form id='apien' name='apien' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='apien'>API STATE</label> </td>";
server<<"<td scope='col'><input type='radio' name='apien' id='apien' value='0' ";if(api_enable == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"<td scope='col'><input type='radio' name='apien' id='apien'  value='1' ";if(api_enable == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
server<<"</table>";
server<<"</form>";

server<<"<form id='rssen' name='rssen' action='' method='post'>";
server<<"<table width='50%' border='0'>";
server<<"<tr>";
server<<"<td><label for='rssen'>T.I.S. STATE</label> </td>";
server<<"<td scope='col'><input type='radio' name='rssen' id='rssen' value='0' ";if(rss_enable == 0){server <<"checked";}server<<">DISABLE </td>  ";
server<<"<td scope='col'><input type='radio' name='rssen' id='rssen'  value='1' ";if(rss_enable == 1){server <<"checked";}server<<">ENABLE</td>";
server<<"<td><input type='submit' value='SAVE' /></td> ";
server<<"</tr>  ";
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
timeServer[0] = dueFlashStorage.read(26);
timeServer[1] = dueFlashStorage.read(27);
timeServer[2] = dueFlashStorage.read(28);
timeServer[3] = dueFlashStorage.read(29);
enable_dhcp= dueFlashStorage.read(30);
ip[0] = dueFlashStorage.read(31);
ip[1] = dueFlashStorage.read(32);
ip[2] = dueFlashStorage.read(33);
ip[3] = dueFlashStorage.read(34);

gateway[0] = dueFlashStorage.read(35);
gateway[1] = dueFlashStorage.read(36);
gateway[2] = dueFlashStorage.read(37);
gateway[3] = dueFlashStorage.read(38);
subnet[0] = dueFlashStorage.read(39);
subnet[1] = dueFlashStorage.read(40);
subnet[2] = dueFlashStorage.read(41);
subnet[3] = dueFlashStorage.read(42);



 st_chars[0] = dueFlashStorage.read(43);
  st_chars[1] = dueFlashStorage.read(44);
   st_chars[2] = dueFlashStorage.read(45);
    st_chars[3] = dueFlashStorage.read(46);
     st_chars[4] = dueFlashStorage.read(47);
        st_char_count = dueFlashStorage.read(48);
         st_text_to_arr();   
       st_color_mode  = dueFlashStorage.read(49);
         st_fix_color= dueFlashStorage.read(50);
         st_rain_speed = dueFlashStorage.read(51);
         
         
         api_enable= dueFlashStorage.read(52);
         
         rss_enable =  dueFlashStorage.read(53);
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
dueFlashStorage.write(26,timeServer[0]);
dueFlashStorage.write(27,timeServer[1]);
dueFlashStorage.write(28,timeServer[2]);
dueFlashStorage.write(29,timeServer[3]);
dueFlashStorage.write(30,enable_dhcp);
dueFlashStorage.write(31,ip[0]);
dueFlashStorage.write(32,ip[1]);
dueFlashStorage.write(33,ip[2]);
dueFlashStorage.write(34,ip[3]);

dueFlashStorage.write(35,gateway[0]);
dueFlashStorage.write(36,gateway[1]);
dueFlashStorage.write(37,gateway[2]);
dueFlashStorage.write(38,gateway[3]);
dueFlashStorage.write(39,subnet[0]);
dueFlashStorage.write(40,subnet[1]);
dueFlashStorage.write(41,subnet[2]);
dueFlashStorage.write(42,subnet[3]);



dueFlashStorage.write(43,st_chars[0]);
dueFlashStorage.write(44,st_chars[1]);
dueFlashStorage.write(45,st_chars[2]);
dueFlashStorage.write(46,st_chars[3]);
dueFlashStorage.write(47,st_chars[4]);
dueFlashStorage.write(48,st_char_count);
dueFlashStorage.write(49,st_color_mode);
dueFlashStorage.write(50,st_fix_color);
dueFlashStorage.write(51,st_rain_speed);


dueFlashStorage.write(52,api_enable);


dueFlashStorage.write(53,rss_enable);


Serial.println("SAVE SETTINGS");

}

void restore_settings(int with_save){
nth = 22;
nthe = 8;
nthen = 1;
nthonmode = 5;
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
fan_state = 1;
clock_fix_color_h = 0;
clock_fix_color_m = 0;
clock_bright = 255;
clockcolormode = 0;
timeServer[0] = 132;
timeServer[1] = 163;
timeServer[2] = 4;
timeServer[3] = 103;

enable_dhcp = 1;
ip[0] = 192;
ip[1] = 168;
ip[2] = 178;
ip[3] = 210;
gateway[0] = 192;
gateway[1] = 168;
gateway[2] = 178;
gateway[3] = 1;
subnet[0] = 255;
subnet[1] = 255;
subnet[2] = 255;
subnet[3] = 0;




 st_chars[0] = 'h';
 st_chars[1] = 'e';
 st_chars[2] = 'l';
 st_chars[3] = 'l';
 st_chars[4] = 'o';
 st_char_count = 5;
 st_speed = 70;
 st_text_to_arr();
 st_rain_speed = 5;
 

st_color_mode = 0;
st_fix_color = 0;

api_enable = 1;
rss_enable = 1;
if(with_save == 1){save_settings();}
delay(100);
Serial.println("SETTINGS RESTORED");
}


void setup() {
  Serial.begin(baud_rate);
  Serial1.begin(baud_rate);
   analogReadResolution(12); // 12 BIT ADC
  Serial.println("START BOOT");
 pinMode(relais,OUTPUT); 
  pinMode(fan,OUTPUT); 
    pinMode(reset_jumper,INPUT); 
  if(digitalRead(reset_jumper) == HIGH){
  Serial.println("RESET JUMPER HIGH");
   delay(100);
  restore_settings(1);
   delay(200);
  }else{
    Serial.println("RESET JUMPER LOW");
  }
 //digitalWrite(relais,LOW);
 //digitalWrite(fan,LOW);
 create_fonttemplate();
   Serial.println("INIT LEDs");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
 standby_strip.begin();
  standby_strip.show(); // Initialize all pixels to 'off'
  Serial.println("I2C START");
    Wire.begin();
      zero=0x00;
randomSeed(analogRead(7));
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
Serial.println("LOAD SETTINGS");
  load_settings();
      Serial.println("DHCP ENAVBLED : Trying to set up a ETHERNET CONNECTION");
    if(use_ethernet == 1){
   if(enable_dhcp == 1){
     Serial.println("DHCP ENABLED : Trying to get an IP address using DHCP");
  if (Ethernet.begin(mac) == 0) {
 show_error("Failed to configure Ethernet using DHCP // TRYING TO USE ALTERNATIVE IP CONFIGURATION");
  Ethernet.begin(mac, ip, gateway, subnet);
  }
   }else{
     Serial.println("DHCP DISABLED : TRYING TO USE ALTERNATIVE IP CONFIGURATION");
     Ethernet.begin(mac, ip, gateway, subnet); 
   }
  Serial.print("My IP address: ");
  ip = Ethernet.localIP();
  for (byte thisByte = 0; thisByte < 4; thisByte++) {Serial.print(ip[thisByte], DEC);Serial.print("."); }
  Serial.println("START WEBSERVER");
  webserver.setDefaultCommand(&defaultCmd);
   webserver.setFailureCommand(&defaultCmd);
  webserver.addCommand("rgb", &rgbCmd);
  webserver.addCommand("index.html", &defaultCmd);
  webserver.addCommand("settings.html", &settingsCmd);
    webserver.addCommand("api.html", &apiCmd);
     webserver.addCommand("tis.html", &tisCmd);
    
       webserver.addCommand("apiget.html", &apigetCmd);
       webserver.addCommand("apiset.html", &apisetCmd);
       
  webserver.begin();
  Serial.println("START UPD CLIENT");
   Udp.begin(localPort);
  }
Serial.println("BOOT FINISHED");
}


void rss_process(){

}



void main_process(){
 if(use_ethernet == 1){webserver.processConnection();}
 getDateDs1307();
 if(fan_state == 1){digitalWrite(fan,HIGH);}else{digitalWrite(fan,LOW);}
 
 
 if(rss_enable == 1){rss_process();}
 
 
 }
}


