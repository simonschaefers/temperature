# include <SD.h>    // uses pin 10
# include <SPI.h>   // uses pin 13
# include <RTClib.h>
# include <OneWire.h>
# include "commands_and_variables.h"

const String logfile = "tsensor.log";
RTC_DS1307 rtc;
OneWire ow(4);

void setup() {
  Serial.begin(9600);
    
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
  delay(1000);
  byte rom_code[8]; // creates array of 8bytes for the rom code 
  
  // Start sequence to read out rom code (sensor family (8 bit), serial number (48 bit), CRC (8 bit))
  ow.reset();
  ow.write(READ_ROM); 
  for (int i=0; i<8; i++){
    rom_code[i] = ow.read();
  }
  if (rom_code[0] != IS_DS18B20_SENSOR) {
    Serial.print("ERROR Sensor is not a DS18B20 sensor!");
    Serial.println(rom_code[0],HEX);
  }
  String serial_number;
  for (int i=1;i<7;i++){
    serial_number += String(rom_code[i],HEX);
  }
  // End of sequence

  // Start sequence to convert temperatures 
  ow.reset();
  ow.write(SKIP_ROM);
  ow.write(CONVERT_T);
  // End of sequence
  // Start sequence to read data from scratchpad
  ow.reset();
  ow.write(SKIP_ROM);
  ow.write(READ_SCPAD);
  byte scpad_data[9];
  for (int i=0; i<9; i++){
    scpad_data[i] = ow.read();
  }
  int16_t tempRead = scpad_data[1] <<8 | scpad_data[0]   ;
  float tempCelsius = tempRead/16.0 ;
  
  // End of sequence

  // Write data to file and terminal
  printOutput(getISOtime());
  printOutput(", ");
  printOutput(serial_number);
  printOutput(", ");
  printOutputln(String(tempCelsius));
  

}
