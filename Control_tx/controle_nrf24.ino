 
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
RF24 radio(7,8);

int data[4] ; //buffer to store received data
const uint8_t buffer_size = sizeof(data);

// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;


//
// Setup
//

void setup(void)
{

  Serial.begin(57600);
  printf_begin();

  radio.begin();
  //radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipe);

  radio.printDetails();


}

//
// Loop
//
bool ok;
int motort1,motort2,joy1;
int motord1,motord2,joy2;
int ft,sw;
void loop(void)
{
  Serial.println("teste");

    joy1 = map(analogRead(0),0,1023,0,255);
    
    if(joy1 >= 130){
      motort1 = map(joy1,130,255,0,255);;
      motort2 = 0;
    }else if(joy1 <= 120){
      motort1 = 0;
      motort2 = map(joy1,120,0,0,255);
    }else{
       motort1 = 0;
       motort2 = 0;
    }

joy2 = map(analogRead(1),0,1023,0,255);
 
   
    if(joy2 >= 130){
      motord1 = map(joy2,130,255,0,255);
      motord2 = 0;
    }else if(joy2 <= 120){
      motord1 = 0;
      motord2 = map(joy2,120,0,0,255);
    }else{
       motord1 = 0;
       motord2 = 0;
    }
    
    
   data[0]=motord1;
   data[1]=motord2;
   
   data[2]=motort1;
   data[3]=motort2;
  
   ok = radio.write( data, buffer_size );
   delay(20);
}
