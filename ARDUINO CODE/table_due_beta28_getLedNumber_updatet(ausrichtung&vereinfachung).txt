#include <Adafruit_NeoPixel.h>
#include <Scheduler.h>
#include "Wire.h"
#include "SPI.h"
#include "Ethernet.h"
#include "WebServer.h"


// no-cost stream operator as described at 
// http://sundial.org/arduino/?page_id=119
template<class T>
inline Print &operator <<(Print &obj, T arg)
{ obj.print(arg); return obj; }

#define PREFIX ""
WebServer webserver(PREFIX, 80);
static uint8_t mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xBD };


/* CHANGE THIS TO MATCH YOUR HOST NETWORK.  Most home networks are in
 * the 192.168.0.XXX or 192.168.1.XXX subrange.  Pick an address
 * that's not in use and isn't going to be automatically allocated by
 * DHCP from your router. */
static uint8_t ip[] = { 192, 168, 178, 210 };



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
int pir_delay = 10000;
int bad_delay = 10000;


int nth = 22;
int nthe = 12;
int nthen = 1;
int nthstate = 0;
int nthswstate = 0;
int nthswstate1 = 0;

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}











const int pir_amount = 4;
int pir_enable[pir_amount] = {1,1,1};
int pir_list[pir_amount] = {1,1,1};
String pir_name[pir_amount] = {"Flur Kueche", "Alk-Schrank", "Wohnzimmer"};
int pir_pins[pir_amount] = {3,6,7,8};

const int zones_amount = 4;
int led_can_change[led_amount] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
int led_can_change_zones[zones_amount][led_amount] = {{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
                                                      {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                      {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0},
                                                    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0}};
int zone_blocked[zones_amount] = {0,0,0,0};




P(phead) =
  "<!DOCTYPE html><html><head>"
  "<title>RBN SmartHome</title>"
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

P(pstart) = "<body style='font-size:62.5%;'>"
            "<div class='sidebar'>"
            "<div class='logo'>"
            "<span class='title'>SmartHome</span>"
            "<span class='subtitle'>- Backend -</span>"
            "</div>"
            "<div class='menu'>"
            "<a href='index.html'>Dashboard</a>"
            "</div>"
            "</div>"
            "<div class='right'>"
            "<div class='content'>";

P(pend) = "</div>"
          "</div>"
          "</body>"
          "</html>";







/* commands are functions that get called by the webserver framework
 * they can read any posted data from client, and they output to the
 * server to send data back to the web browser. */
void helloCmd(WebServer &server, WebServer::ConnectionType type, char *, bool)
{
  if (type == WebServer::POST)
  {
    bool repeat;
    char name[64], value[64];
    do{
      repeat = server.readPOSTparam(name, 64, value, 64);
     
       if (strcmp(name, "nthen") == 0) {
        nthen = strtoul(value, NULL, 10);
      }
      if (strcmp(name, "nth") == 0) {
        nth = strtoul(value, NULL, 10);
      }
      if (strcmp(name, "nthe") == 0) {
        nthe = strtoul(value, NULL, 10);
      }

     for (int ipira = 0; ipira < pir_amount; ipira++) {
        char st_chars[5];
     String tmp = "pir"+String(ipira);
      tmp.toCharArray(st_chars, 5);
      
     if (strcmp(name, st_chars) == 0 && pir_list[ipira] == 1) {
        pir_enable[ipira] = strtoul(value, NULL, 10);
      }
     }
   
     
     
    } while (repeat);

    server.httpSeeOther("index.html");
    return;
  }
  server.httpSuccess();
  if (type == WebServer::GET)
  {
    server.printP(phead);
    server.printP(pstart);
    server << "</p>";
    server.print("<span class='title'>NIGHTMODE SETTINGS</span><p>");
    server << "<hr>";
    server << "<form id='nthen' name='nthen' action='' method='post'>";
    server << "<table width='50%' border='0'>";
    server << "<tr>";
    server << "<td><label for='nthen'>NIGHTMODE STATE</label> </td>";
    server << "<td scope='col'><input type='radio' name='nthen' id='nthen' value='0' "; if (nthen == 0) {
      server << "checked";
    } server << ">DISABLE</td>";
    server << "<td scope='col'><input type='radio' name='nthen' id='nthen'  value='1' "; if (nthen == 1) {
      server << "checked";
    } server << ">ENABLE</td>";
    server << "<td><input type='submit' value='SAVE' /></td> ";
    server << "</tr>  ";
    server << "</table>";
    server << "</form>";
    server << "<form id='speed' name='nth' action=''  method='post'>";
    server << "<table width='50%' border='0'>";
    server << "<tr>";
    server << "<td scope='col'> <label for='nth'>NIGHTMODE START</label></td>";
    server << "<td scope='col' >";
    server << "<input name='nth' type='number' id='nth' max='23' min='0' step='1' value='"; server << nth; server << "' size='5'><br>";
    server << "</td>  ";
    server << "<td colspan='2'><input type='submit' value='SAVE' /></td>";
    server << "</tr>";
    server << "</table> ";
    server << "</form>";
    server << "<form id='speed' name='nth' action=''  method='post'>";
    server << "<table width='50%' border='0'>";
    server << "<tr>";
    server << "<td scope='col'> <label for='nthe'>NIGHTMODE STOP</label></td>";
    server << "<td scope='col' >";
    server << "<input name='nthe' type='number' id='nthe' max='23' min='0' step='1' value='"; server << nthe; server << "' size='5'><br>";
    server << "</td>  ";
    server << "<td colspan='2'><input type='submit' value='SAVE' /></td>";
    server << "</tr>";
    server << "</table> ";
    server << "</form>";



 server << "</p>";
    server.print("<span class='title'>PIR SETTINGS</span><p>");
    server << "<hr>";


 for (int ipir = 0; ipir < pir_amount; ipir++) {
if(pir_list[ipir] == 1){
server << "<form id='pir"+ String(ipir)+"' name='pir"+ String(ipir)+"' action='' method='post'>";
    server << "<table width='50%' border='0'>";
    server << "<tr>";
    server << "<td><label for='pir"+ String(ipir)+"'>"+ pir_name[ipir] +"</label> </td>";
    server << "<td scope='col'><input type='radio' name='pir"+ String(ipir)+"' id='pir"+ String(ipir)+"' value='0' "; if (pir_enable[ipir] == 0) {
      server << "checked";
    } server << ">DISABLE</td>";
    server << "<td scope='col'><input type='radio' name='pir"+ String(ipir)+"' id='pir"+ String(ipir)+"'  value='1' "; if (pir_enable[ipir] == 1) {
      server << "checked";
    } server << ">ENABLE</td>";
    server << "<td><input type='submit' value='SAVE' /></td> ";
    server << "</tr>  ";
    server << "</table>";
    server << "</form>";
    
}//ende if  
 }

//const int pir_amount = 3;
//int pir_enable[pir_amount] = {1,1,1};
//int pir_name[pir_amount] = {"Flur Kueche", "Wohnzimmer", "Alc-Schrank"};

    server.printP(pend);
  }
}











void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();
  Wire.begin();
  
  
  
  
  
   for (int ipirp = 0; ipirp < pir_amount; ipirp++) {pinMode(pir_pins[ipirp], INPUT);}
  
  
    /* initialize the Ethernet adapter */
  Ethernet.begin(mac, ip);
  /* setup our default command that will be run when the user accesses
   * the root page on the server */
  webserver.setDefaultCommand(&helloCmd);
  /* run the same command if you try to load /index.html, a common
   * default page name */
  webserver.addCommand("index.html", &helloCmd);
  /* start the webserver */
  webserver.begin();
  
  
  Scheduler.startLoop(loop1);
  Scheduler.startLoop(loop2);
  Scheduler.startLoop(loop3);
  Scheduler.startLoop(loop4);
  Scheduler.startLoop(loop_webserver);
  
  
  
  zero = 0x00;
  
}

void loop() {

  getDateDs1307();



  //Serial.print(hour); Serial.print(":"); Serial.print(minute); Serial.print(":"); Serial.println(second);
  for (int i = 0; i < led_amount; i++) {
    led_can_change[i] = 1;



//led_can_change_zones[][]
//zones_amount = 4
 for (int m_zones = 0; m_zones < zones_amount; m_zones++) {
    if (led_can_change_zones[m_zones][i] == 1 && zone_blocked[m_zones] >= 1) {led_can_change[i] = 0;}
 }
   // if (led_can_change_z1[i] == 1 && led_blocked_z1 == 1) {led_can_change[i] = 0;}
   // if (led_can_change_z2[i] == 1 && led_blocked_z2 == 1) {led_can_change[i] = 0;}
   // if (led_can_change_z3[i] == 1 && led_blocked_z3 == 1) {led_can_change[i] = 0;}
   // if (led_can_change_zones[3][i] == 1 && zone_blocked[3] >= 1) {led_can_change[i] = 0;}

    if (led_can_change[i] == 1) {


      if (nthstate == 1 && nthen == 1) {
        strip.setPixelColor(i, getColor(0, 0, 0)); strip.show();}else{strip.setPixelColor(i, getColor(0, 255, 0)); strip.show();}


    } else { //sensor an
      if (i == 12 && zone_blocked[3] == 1) strip.setPixelColor(i, getColor(255, 0, 0));
      else if (i == 12 && zone_blocked[3] == 2) strip.setPixelColor(i, getColor(255, 0, 255));
      else strip.setPixelColor(i, getColor(255, 0, 255));

      strip.show();



    }









  }//ende for





  yield();
}






void loop1() {
  if (digitalRead(pir_pins[0]) == HIGH && pir_enable[0] == 1 && pir_list[0] == 1) {
    Serial.println("kueche aktiv");
    zone_blocked[0] = 1;
    delay(pir_delay);
  } else {
    zone_blocked[0] = 0;
  }
  yield();
}


void loop2() {
  if (digitalRead(pir_pins[1]) == HIGH && pir_enable[1] == 1 && pir_list[1] == 1) {
    Serial.println("alk aktiv");
    zone_blocked[1] = 1;
    delay(pir_delay);
  } else {
    zone_blocked[1] = 0;
  }
  yield();
}

void loop3() {
  if (digitalRead(pir_pins[2]) == HIGH && pir_enable[2] == 1&& pir_list[2] == 1) {
    Serial.println("wohnzimmer aktiv");
    zone_blocked[2] = 1;
    delay(pir_delay);
  } else {
    zone_blocked[2] = 0;
  }
  yield();
}

void loop4() {
  if (digitalRead(pir_pins[3]) == HIGH) {
    Serial.println("Bad geschlossen");
    zone_blocked[3] = 1;
  } else if (zone_blocked[3] == 1) {
    zone_blocked[3] = 2;
    delay(bad_delay);
  } else {
    zone_blocked[3] = 0;
  }
  yield();
}



//get Color (weil R und G vertauscht
uint32_t getColor(int r, int g, int b) {
  return strip.Color(g, r, b);
}






























void setDateDs1307(){
  dayOfWeek = 1;
  dayOfMonth = 1;
  month = 1;
  year = 1;
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  I2C_WRITE(zero);
  I2C_WRITE(decToBcd(0) & 0x7f);    // 0 to bit 7 starts the clock
  I2C_WRITE(decToBcd(36));//m
  I2C_WRITE(decToBcd(22));      // hour If you want 12 hour am/pm you need to set
  I2C_WRITE(decToBcd(dayOfWeek));
  I2C_WRITE(decToBcd(dayOfMonth));
  I2C_WRITE(decToBcd(month));
  I2C_WRITE(decToBcd(year));
  Wire.endTransmission();
}







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


  if (nthen == 1) {
    //LIEGT DIE ZEIT ZWISCHEN DEN BEIDEN GERENDZEN
    if (nth > nthe) {
      //WENN ANFANG > ALS ENDE
      if (hour <= nth && hour <= nthe) {
        nthstate = 1;
      } else if (hour >= nth && hour >= nthe) {
        nthstate = 1;
      } else {
        nthstate = 0;
      }
    } else if (nth < nthe) {
      //WENN ANFANG > ALS ENDE
      if (hour <= nth && hour >= nthe) {
        nthstate = 1;
      } else if (hour >= nth && hour <= nthe) {
        nthstate = 1;
      } else {
        nthstate = 0;
      }
    } else if ( nth == nthe) {
      if (hour == nth || hour == nthe) {
        nthstate = 1;
      } else {
        nthstate = 0;
      }
    } else {
      nthstate = 0;
    }
  } else {
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



void loop_webserver(){



  /* process incoming connections one at a time forever */
  webserver.processConnection();
    yield();

}



