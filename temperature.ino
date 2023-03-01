# define datapin 2
# include <SD.h>
# include <SPI.h>
# include <RTClib.h>
# include <OneWire.h>
# include "commands_and_variables.h"
 
RTC_DS1307 rtc;

OneWire ow(4);

void setup() {
    Serial.begin(9600);
    pinMode(datapin,INPUT);
    
    if(!rtc.begin()){
      Serial.println("ERROR RTC is not running");
      rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
    }
    else {Serial.println("RTC Working");}
    if   (!SD.begin(10)) {
      Serial.println("ERROR SD module initialization failed or card is not present");
    }   
    else {Serial.println("SD Working");}
}

void loop() {

// Start first sequence
ow.reset();
ow.write(0x44); //
}
