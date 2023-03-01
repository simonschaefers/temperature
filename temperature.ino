# define datapin 2
# include <SD.h>
# include <SPI.h>
# include <RTClib.h>
# include <OneWire.h>

RTC_DS1307 rtc;

OneWire ow(4);

void setup() {
    Serial.begin(9600);
    pinMode(datapin,INPUT);
    
    if(!rtc.begin()){
      Serial.println("ERROR RTC is not running");
      rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
    }
    
}

void loop() {
  // put your main code here, to run repeatedly:

}
