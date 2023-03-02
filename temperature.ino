# include <SD.h>    // uses pin 10
# include <SPI.h>   // uses pin 13
# include <RTClib.h>
# include <OneWire.h>
# include "commands_and_variables.h"

const String logfile = "tsensor.log"
RTC_DS1307 rtc;
OneWire ow(4);

void setup() {
  Serial.begin(9600);
  pinMode(datapin,INPUT);
    
  if(!rtc.begin()){
    Serial.println("ERROR RTC is not running");
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  }
  else {Serial.println("RTC Working");
  }
  if (!SD.begin(10)) {
    Serial.println("ERROR SD module initialization failed or card is not present");
  }   
  else {Serial.println("SD Working");
  }
}

void loop() {
  byte rom_code[8]; // creates array of 8bytes for the rom code 
  
  // Start sequence to read out rom code (sensor family (8 bit), serial number (48 bit), CRC (8 bit))
  ow.reset();
  ow.write(READ_ROM); 
  for (int i=0; i<8; i++){
    rom_code[i] = ow.read();
  }
}
