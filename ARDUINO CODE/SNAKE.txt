#include <FastSPI_LED.h>

#define NUM_LEDS 200


const unsigned int feldx = 20;
const unsigned int feldy = 10;

const int maxSnakelengh = 20;
int snakeIndex = 0; //wie lang ist die schlagne
int snake[maxSnakelengh][3]; //0 = x 1 = y  2 = dir 
const int snake_start_lengh = 15;
int foodPosX = 0;
int foodPosY = 0;
bool foodVisible; //wird das essen angezeigz
// Sometimes chipsets wire in a backwards sort of way
struct CRGB { unsigned char b; unsigned char r; unsigned char g; };
// struct CRGB { unsigned char r; unsigned char g; unsigned char b; };
struct CRGB *leds;


int p1_latch = A1; // set the latch pin
int p1_clock = A0; // set the clock pin
int p1_datin = A2;// set the data in pin
byte p1_controller_data = 0;

#define PIN 4

void setup()
{
  pinMode(p1_latch,OUTPUT);
pinMode(p1_clock,OUTPUT);
pinMode(p1_datin,INPUT);
digitalWrite(p1_latch,HIGH);
digitalWrite(p1_clock,HIGH);

  randomSeed(analogRead(0));
  FastSPI_LED.setLeds(NUM_LEDS);
  FastSPI_LED.setChipset(CFastSPI_LED::SPI_TM1809);
  FastSPI_LED.setPin(PIN);
  FastSPI_LED.setDataRate(1);
  FastSPI_LED.init();
  FastSPI_LED.start();
  leds = (struct CRGB*)FastSPI_LED.getRGBData(); 


        snakeIndex = 1;
	snake[0][0] =  feldx/2;
	snake[0][1] = feldy/2;
	snake[0][2] = 2; 

//FOOD KONFIG
	foodPosX = random(feldx -2);
	foodPosY = random(feldy -2);
	foodVisible = true;
}



void moveSnake(){
	for (int i = snakeIndex; i > 1; i--){snake[i][2] = snake[i-1][2];} //damit die snake auch kurven machen kann
	for (int i = 1; i < snakeIndex; i++){ //f¸r jedes segemtn der schalnge
		switch (snake[i][2]){//hier neue schlangenpos errechnen
		case 0: //nicht
			snake[i][0] = snake[i][0]; //X
			snake[i][1] = snake[i][1];//Y
			break;	
		case 1: //oben
			snake[i][0] = snake[i][0]; //X
			snake[i][1] += 1;//Y
			break;
		case 2://rechts
			snake[i][0] += 1; //X
			snake[i][1] = snake[i][1];//Y
			break;
		case 3: //unten
			snake[i][0] = snake[i][0]; //X
			snake[i][1] -= 1;//Y
			break;
		case 4://links
			snake[i][0] -= 1; //X
			snake[i][1] = snake[i][1];//Y
			break;
		default: //nicht
			snake[i][0] = snake[i][0]; //X
			snake[i][1] = snake[i][1];//Y
			break;
		}
	}
}


void checkWallColl(){
	for (int i = 1; i < snakeIndex; i++){ //f¸r jedes segemtn der schalnge
		if(snake[i][0] == 0 && snake[i][2] == 4){snake[i][0] = feldx -0;} // links
		if(snake[i][0] == feldx - 1 && snake[i][2] == 2){snake[i][0] = -1;} //rechts
		if(snake[i][1] == 0 && snake[i][2] == 3){snake[i][1] = feldy -0;} //oben
		if(snake[i][1] == feldy -1 && snake[i][2] == 1){snake[i][1] = -1;}//unten
	} 
}


void checkFoodColl(){

	if(snake[1][0] == foodPosX && snake[1][1] == foodPosY && foodVisible){//nur wenn der kopf auf das eesen trifft und das essen sichbar ist
leds[get_led_number(foodPosX,foodPosY)].r = 0;
leds[get_led_number(foodPosX,foodPosY)].g = 0;
leds[get_led_number(foodPosX,foodPosY)].b = 0;
		addOneToSnakeIndex(); //schlange wachsten lassen
		foodVisible = false;
		foodPosX = random(feldx -2); //NEU POS randomm‰ssig
		foodPosY = random(feldy -2);
		foodVisible = true;
	}
}

void addOneToSnakeIndex(){
	if(snakeIndex < maxSnakelengh){
		snakeIndex++; //die schlagne muss ja auch im system wachsen
		switch (snake[snakeIndex - 2][2]){ //position des neuen s¸ckes bestimmen
		case 1:
			snake[snakeIndex-1][2] = snake[snakeIndex - 2][2];
			snake[snakeIndex-1][0] =   snake[snakeIndex - 2][0];
			snake[snakeIndex-1][1] =  snake[snakeIndex - 2][1] -1;
			break;
		case 3:
			snake[snakeIndex-1][2] = snake[snakeIndex - 2][2];
			snake[snakeIndex-1][0] =   snake[snakeIndex - 2][0];
			snake[snakeIndex-1][1] =  snake[snakeIndex - 2][1] +1;
			break;
		case 2:
			snake[snakeIndex-1][2] = snake[snakeIndex - 2][2];
			snake[snakeIndex-1][0] =   snake[snakeIndex - 2][0] - 1;
			snake[snakeIndex-1][1] =  snake[snakeIndex - 2][1];
			break;
		case 4:
			snake[snakeIndex-1][2] = snake[snakeIndex - 2][2];
			snake[snakeIndex-1][0] =   snake[snakeIndex - 2][0] + 1;
			snake[snakeIndex-1][1] =  snake[snakeIndex - 2][1];
			break;
		default:
			break;
		}
	}	
}


void loop() { 
//DELETE

for (int i=1; i < snakeIndex; i++){
leds[get_led_number(snake[i][0],snake[i][1])].r = 0;
leds[get_led_number(snake[i][0],snake[i][1])].g = 0;
leds[get_led_number(snake[i][0],snake[i][1])].b = 0;

} 
  
  
  //HIER CONTROL PER          snake[0][2] = 3; da hier die dir des kopfes gändert wird
  
  
  controllerRead();
                checkWallColl();
		checkFoodColl();
		moveSnake();


		if(snakeIndex < snake_start_lengh){addOneToSnakeIndex();}
 //GAME LOGIC
for (int i = 1; i < snakeIndex; i++){//alle segmente durchgehen
			for (int j = 1; j < snakeIndex; j++){
				if(i != j && i > 0 && j > 0){ //das eigene Element und das steuerelement 0 auslassen
					if(snake[i][0] == snake[j][0] && snake[i][1] == snake[j][1]){ //wenn es 2 elemente mit den selben COORDs gibt hat man verloren
						//LOOSER
                                          snakeIndex = 1;
					}
				}
			}
		}
 
 
 
 
 
 //FOOD MALEN
leds[get_led_number(foodPosX,foodPosY)].r = 255;
leds[get_led_number(foodPosX,foodPosY)].g = 0;
leds[get_led_number(foodPosX,foodPosY)].b = 0;  

int colorvalue = 255 /snakeIndex;  
  
for (int i=1; i < snakeIndex; i++){
  



switch (i) {
    case 1:
     leds[get_led_number(snake[i][0],snake[i][1])].r = 0;
leds[get_led_number(snake[i][0],snake[i][1])].g = 0;
leds[get_led_number(snake[i][0],snake[i][1])].b = 255;

    
      break;
      
     
    default: 
leds[get_led_number(snake[i][0],snake[i][1])].r = 0;
leds[get_led_number(snake[i][0],snake[i][1])].g = 255;
leds[get_led_number(snake[i][0],snake[i][1])].b = 255-(colorvalue*i);

      break;
  }




}
 FastSPI_LED.show();
 
 delay(100);
}

unsigned int get_led_number(int x, int y){
 if (y % 2) {
  return (y*feldx)+feldx-1-x; //ungerade
} else {
  return (y*feldx)+x; //y=1; //GERADE
} 
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
interpret_controller();
}



void interpret_controller(){
if(p1_controller_data==B01111111){ }//A   
if(p1_controller_data==B10111111){ }// B
if(p1_controller_data==B11110111){snake[0][2] = 1; } //UP
if(p1_controller_data==B11111011){ snake[0][2] = 2;}// DOWN
if(p1_controller_data==B11111110){snake[0][2] = 3; }//RIGHT
if(p1_controller_data==B11111101){snake[0][2] = 4;}//LEFT
if(p1_controller_data==B11011111){}//SELCET
if(p1_controller_data==B11101111){}//START


}


