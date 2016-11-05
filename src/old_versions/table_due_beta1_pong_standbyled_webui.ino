#include <Adafruit_NeoPixel.h>
#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"

// CHANGE THIS TO YOUR OWN UNIQUE VALUE
static uint8_t mac[6] = { 0x02, 0xAA, 0xBB, 0xCC, 0x00, 0x22 };


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
const int relais = 51;
Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, 53, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel standby_strip = Adafruit_NeoPixel(1, 49, NEO_RGB + NEO_KHZ800);
//FÜR SERVER << "";
 template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }
#define PREFIX ""
WebServer webserver(PREFIX, 80);

int fillred = 0;            //integer for red darkness
int fillblue = 0;           //integer for blue darkness
int fillgreen = 0;          //integer for green darkness

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

int use_ethernet = 1, enable_dhcp = 1,wait_for_DHCP = 0;

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
int pong_invert_p1 = 0;
int pong_invert_p2 = 0;

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
//"<a href='settings.html'>SETTINGS</a>"
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

  uint16_t i, j;
void rainbowCycleCol() {
      i++;
       for(int x=0; x< feldx; x++) {
       for(int y=0; y< feldy; y++) {
       strip.setPixelColor(get_led_number(x,y),Wheel(i));
       if(i > 255){
      i = 0;
      }else{
      i++;
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
}

server<<".</h2></p>";

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
      
      
          if (strcmp(name, "reset_pong") == 0)
      {
        
         
         
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
      
      
               if (strcmp(name, "ransp") == 0)
      {
     randomspeed = strtoul(value, NULL, 10);
      }
    } while (repeat);
        clear_screen();
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



void setup() {
 pinMode(relais,OUTPUT); 
 digitalWrite(p2_clock,LOW);
 
 standby_strip.begin();
  standby_strip.show(); // Initialize all pixels to 'off'
  
  
  Serial.begin(9600);
randomSeed(analogRead(7));
   //CONTROLLER INIT
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
  /* start the server to wait for connections */
  webserver.begin();

 
  }
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void main_process(){
 if(use_ethernet == 1){webserver.processConnection();}

}



