#include <Adafruit_NeoPixel.h>
#include <IRLibAll.h>

IRrecv myReceiver(2);//receiver on pin 2
IRdecode myDecoder;//Decoder object

int SPD = 50;
int BGN = [] {0, 100, 150, 190, 225, 245, 255}
int b = 4

//One NeoPixel connected to pin 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60,6,NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(BGN[b])
  strip.show(); // Initialize all pixels to 'off'
  myReceiver.enableIRIn(); // Start the receiver
  
}

void loop() {
  if (myReceiver.getResults()) {
    myDecoder.decode();
    if (myDecoder.protocolNum == NEC) {
      switch(myDecoder.value) {
        case 0xFF9867:  //Red
          colorWipe(strip.Color(255, 0, 0), SPD); // Red
          break;
        case 0xFFD827:  //Green
          colorWipe(strip.Color(0, 255, 0), SPD); // Green
          break;
        case 0xFF8877:  //Blue
          colorWipe(strip.Color(0, 0, 255), SPD); // Blue
          break;
        case 0xFDA05F:
          if (SPD < 99){ SPD=SPD+10;} // Speed Up
          break;
        case 0xFDB04F:
          if (SPD > 10){ SPD=SPD-10;} // Speed Down
          break;
        case 0xFF906F: // Brightness Up
          if (b < 6){
            b++
            strip.setBrightness(BGN[b])
          }
          strp.show();
          break;
        case 0xFFB847: // Brightness Down
          if (b > 0){
            b--
            strip.setBrightness(BGN[b])
          }
          strp.show();
          break;
      }
    strip.show();
    myReceiver.enableIRIn(); //Restart the receiver
    }
  }
}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}
