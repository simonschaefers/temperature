# define datapin 2
# include <SD.h>
# include <SPI.h>
# include <RTClib.h>
# include <OneWire.h>

void setup() {
    Serial.begin(9600);
    pinMode(datapin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
