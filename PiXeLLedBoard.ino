// Adafruit_NeoMatrix example for single NeoPixel Shield.
// Scrolls 'Howdy' across the matrix in a portrait (vertical) orientation.

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


#include <SPI.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAD };
//byte ip[] = { 172, 24, 21, 6 }; // ip in lan assigned to arduino
//byte gateway[] = { 172, 24, 21, 1 }; // internet access via router
//byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
byte server[] = { 10,13,37,2 };
#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif

#define PIN 2

EthernetClient client;

int brightness;
String data = "";
int GETINTERVAL = 2000;
unsigned long lastchecked = millis();

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(35, 7, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

int x    = matrix.width();
int pass = 0;
boolean useethernet = true;
boolean demo = true;
boolean dogetrequest = false;

void setup() {
  Serial.begin(19200);
  
  brightness = 100;
  
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(brightness);
  matrix.setTextColor(colors[2]);
  matrix.fillScreen(0);
  matrix.show();
  matrix.print(" miep ");
  matrix.show();
  if(useethernet == true) {
  Ethernet.begin(mac);//,ip,subnet,gateway);
  delay(1000);
  matrix.fillScreen(0);
  
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    matrix.fillScreen(0);
    matrix.setCursor(0, 0);
    matrix.print(Ethernet.localIP()[thisByte], DEC);
    matrix.show();
    delay(500);
    
  }
  Serial.println();
  }
  matrix.fillScreen(0);
  matrix.show();
}

void loop() {
    
  if(millis() - lastchecked > GETINTERVAL) {
    dogetrequest = true;
  }
  if(dogetrequest == true) {  
    if (client.connect(server, 80)) {
        Serial.println("Server Connect");
        client.println("GET /LedBoard/index.php HTTP/1.0");
        client.println("Connection: close");
        client.println();
      }
      data = "";
      while(client.available()) {
        Serial.println("Client Available");
        char c = client.read();
        data = data + c;
        
        if(data.endsWith("Content-Type: text/html"))
        {
          //data="";
        }
        Serial.println(data);
      }
    lastchecked = millis();
    if(!client.connected()){
      Serial.println("Client not Available");
      client.stop();
    }
    dogetrequest = false;
  }
    
  Serial.println(data);
  
  Scroller(data);
  

 if(demo == true) {
    PacManComplete();
    delay(50);
    BordParkeer(5);
    BordStop(18);
    BordVoorrang(29);
    delay(2000);
    BordPijl(5);
    BordPijl(18);
    BordPijl(29);
    delay(2000);
    Cisco(18);
    delay(2000);
 }
}


uint16_t Color333(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0x7) << 13) | ((r & 0x6) << 10) |
         ((g & 0x7) <<  8) | ((g & 0x7) <<  5) |
         ((b & 0x7) <<  2) | ((b & 0x6) >>  1);
}


uint16_t Color444(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF) << 12) | ((r & 0x8) << 8) |
         ((g & 0xF) <<  7) | ((g & 0xC) << 3) |
         ((b & 0xF) <<  1) | ((b & 0x8) >> 3);
}

uint16_t Color888(uint8_t r, uint8_t g, uint8_t b) {
  return ((r & 0xF8) << 11) | ((g & 0xFC) << 5) | (b >> 3);
}

void Cisco(int center) {
    matrix.fillScreen(0);
    matrix.drawLine(center-5,4,center+5,4,Color888(100,255,128));
    
    matrix.drawLine(center-2,1,center-2,6,Color888(100,255,100));
    matrix.drawLine(center+2,1,center+2,6,Color888(100,255,100));
    
    matrix.drawLine(center-1,2,center-1,4,Color888(100,255,100));
    matrix.drawLine(center+1,2,center+1,4,Color888(100,255,100));
    matrix.drawLine(center-3,2,center-3,4,Color888(100,255,100));
    matrix.drawLine(center+3,2,center+3,4,Color888(100,255,100));
    matrix.drawLine(center-4,3,center-4,4,Color888(100,255,100));
    matrix.drawLine(center+4,3,center+4,4,Color888(100,255,100));
    matrix.drawLine(center,3,center,4,Color888(100,255,100));

    matrix.show();
}

void PacManComplete() {
  int r = random(100-255);
  int g = random(100-255);
  int b = random(100-255);
  
  for(int i = -4; i < 49; i++){

    matrix.fillScreen(0);
    matrix.drawPixel(1,3,Color888(255,255,255));
    matrix.drawPixel(4,3,Color888(255,255,255));
    matrix.drawPixel(7,3,Color888(255,255,255));
    matrix.drawPixel(10,3,Color888(255,255,255));
    matrix.drawPixel(13,3,Color888(255,255,255));
    matrix.drawPixel(16,3,Color888(255,255,255));
    matrix.drawPixel(19,3,Color888(255,255,255));
    matrix.drawPixel(22,3,Color888(255,255,255));
    matrix.drawPixel(25,3,Color888(255,255,255));
    matrix.drawPixel(28,3,Color888(255,255,255));
    matrix.drawPixel(31,3,Color888(255,255,255));
    matrix.drawPixel(34,3,Color888(255,255,255));
    PacmanGhost(i,r,g,b);
    Pacman(i-10);
    
    delay(100);
    //matrix.fillRect(i+7,0,7,7,Color888(0,0,0));
    matrix.show();
  }
}

void BordParkeer(int center) {
  matrix.drawCircle(center,3,3,Color888(255,0,0));
  matrix.fillCircle(center,3,2,Color888(0,0,255));
  matrix.drawLine(center+2,1,center-2,5,Color888(255,0,0));
  matrix.show();
}
void BordStop(int center) { 
  matrix.drawCircle(center,3,3,Color888(255,0,0));
  matrix.fillCircle(center,3,2,Color888(255,0,0));
  matrix.drawLine(center-2,3,center+2,3,Color888(255,255,255));
  matrix.show();
}
void BordVoorrang(int center){
  matrix.drawLine(center-3,3,center,0,Color888(255,255,255));
  matrix.drawLine(center,0,center+3,3,Color888(255,255,255));
  matrix.drawLine(center+3,3,center,6,Color888(255,255,255));
  matrix.drawLine(center,6,center-3,3,Color888(255,255,255));
  matrix.drawPixel(center,1,Color888(255,255,0));
  matrix.drawPixel(center-2,3,Color888(255,255,0));
  matrix.drawPixel(center+2,3,Color888(255,255,0));
  matrix.drawPixel(center,5,Color888(255,255,0));
  matrix.fillRect(center-1,2,3,3,Color888(255,255,0));
  matrix.show();
}

void BordPijl(int center){
  matrix.fillRect(center-3,0,7,7,Color888(0,0,255));
  matrix.drawLine(center,1,center,5,Color888(255,255,255));
  matrix.drawLine(center-1,2,center+1,2,Color888(255,255,255));
  matrix.drawLine(center-2,3,center+2,3,Color888(255,255,255));
  matrix.show();
}

void Smiley(int center) {
  matrix.drawCircle(center,3,3,Color888(255,255,0));
  matrix.fillCircle(center,3,2,Color888(255,255,0));
  matrix.drawPixel(center-2,2,Color888(0,0,0));
  matrix.drawPixel(center+2,2,Color888(0,0,0));
  matrix.drawPixel(center-2,4,Color888(0,0,0));
  matrix.drawPixel(center+2,4,Color888(0,0,0));
  matrix.drawPixel(center-1,5,Color888(0,0,0));
  matrix.drawPixel(center,5,Color888(0,0,0));
  matrix.drawPixel(center+1,5,Color888(0,0,0));
  matrix.show();
}

void PacmanOpen(int center){
  matrix.drawCircle(center,3,3,Color888(255,255,0));
  matrix.fillCircle(center,3,2,Color888(255,255,0));
  matrix.drawPixel(center-1,1,Color888(0,0,0));
  matrix.drawPixel(center+2,2,Color888(0,0,0));
  matrix.drawPixel(center+2,4,Color888(0,0,0));
  matrix.drawPixel(center+2,3,Color888(0,0,0));
  matrix.drawPixel(center+3,2,Color888(0,0,0));
  matrix.drawPixel(center+3,3,Color888(0,0,0));
  matrix.drawPixel(center+3,4,Color888(0,0,0));
  matrix.drawPixel(center+1,3,Color888(0,0,0));
}

void PacmanHalf(int center) {
  matrix.drawCircle(center,3,3,Color888(255,255,0));
  matrix.fillCircle(center,3,2,Color888(255,255,0));
  matrix.drawPixel(center-1,1,Color888(0,0,0));
  matrix.drawPixel(center+2,3,Color888(0,0,0));
  matrix.drawPixel(center+3,2,Color888(0,0,0));
  matrix.drawPixel(center+3,3,Color888(0,0,0));
  matrix.drawPixel(center+3,4,Color888(0,0,0)); 
  matrix.drawPixel(center+1,3,Color888(0,0,0));
}
void PacmanClosed(int center){
  matrix.drawCircle(center,3,3,Color888(255,255,0));
  matrix.fillCircle(center,3,2,Color888(255,255,0));
  matrix.drawPixel(center-1,1,Color888(0,0,0));
}

void PacmanGhost(int center,uint8_t r, uint8_t g, uint8_t b) {
  matrix.drawLine(center-3,1,center-3,6,Color888(r,g,b)); //center 17
  matrix.drawLine(center,0,center,6,Color888(r,g,b));
  matrix.drawLine(center+3,1,center+3,6,Color888(r,g,b));
  
  matrix.drawLine(center-2,3,center+2,3,Color888(r,g,b));
  matrix.drawLine(center-2,4,center+2,4,Color888(r,g,b));
  matrix.drawLine(center-2,0,center+2,0,Color888(r,g,b));
  
  matrix.drawPixel(center-2,5,Color888(r,g,b));
  matrix.drawPixel(center+2,5,Color888(r,g,b));
  matrix.show();
}

void Pacman(int center) {
  PacmanOpen(center);
  matrix.show();
  delay(70);
  matrix.fillRect(center-3,0,7,7,Color888(0,0,0));
  PacmanHalf(center);
  matrix.show();
  delay(70);
  matrix.fillRect(center-3,0,7,7,Color888(0,0,0));
  PacmanClosed(center);
  matrix.show();
  delay(70);
  matrix.fillRect(center-3,0,7,7,Color888(0,0,0));
}

void Scroller(String text) {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(text);
  int y = text.length();
  y = y * 6;
  y = y - 1;
  
  if(--x < -y ) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
  delay(50);
}

void Demo() {
  matrix.fillScreen(0);
  BordParkeer(17);
  delay(200);
  matrix.fillScreen(0);
  BordStop(17);
  delay(200);
  matrix.fillScreen(0);
  BordVoorrang(17);
  delay(200);
  matrix.fillScreen(0);
  BordPijl(17);
  delay(600);
  matrix.fillScreen(0);
  BordStop(4);
  BordStop(17);
  BordStop(30);
  delay(500);
  matrix.fillScreen(0);
  BordPijl(4);
  BordPijl(17);
  BordPijl(30);
  delay(500);
}

void Clear() {
  matrix.fillScreen(0);
  matrix.show();
}

