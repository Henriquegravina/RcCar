 
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

RF24 radio(7,8);


// Single radio pipe address for the 2 nodes to communicate.
const uint64_t pipe = 0xE8E8F0F0E1LL;


int received_data[4];
int num_received_data =sizeof(received_data);


void setup(void)
{
  delay(3000);

  Serial.begin(57600);
  printf_begin();

  //
  // Setup and configure rf radio
  //

  radio.begin(); //Begin operation of the chip.
  //radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  radio.printDetails(); 
}


void loop(void)
{
  if ( radio.available() )
  {
    bool done = false;
    int ESC_value;
    
    while(radio.available()){
      radio.read(received_data,sizeof(received_data));
      
      analogWrite(2,received_data[0]);
      analogWrite(3,received_data[1]);
      
      analogWrite(5,received_data[2]);
      analogWrite(6,received_data[3]);
      
      Serial.println("Recebi!");
      Serial.print("data0: ");
      Serial.println(received_data[0]);
      Serial.print("data1: ");
      Serial.println(received_data[1]);
      Serial.print("data2: ");
      Serial.println(received_data[2]);
      Serial.print("data3: ");
      Serial.println(received_data[3]);
    }
    
  }
}
