//I, Arya Bhoiwala, student number 000828466, certify that this material is my original work. 
//No other person's work has been used without due acknowledgment and I have not made my work available to anyone else.
 
// Dallas Semiconductor DS18B20 Temperature Sensor Demo Program 
// COMP-10184 
// Mohawk College 


// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

DeviceAddress sensorAddress;
 
 // Converting the sensor address to a valid form.
void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
      Serial.print(deviceAddress[i], HEX);
  }
}

void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin(); 
  int numberOfDevices = DS18B20.getDeviceCount();
  for(int i=0;i<numberOfDevices; i++) {
    // Searching the address for the wire.
    if(DS18B20.getAddress(sensorAddress, i)){
      Serial.println(""); 
      Serial.println("Temperature Application"); 
      Serial.print("Found DS18B20 sensor address with: ");
      printAddress(sensorAddress);
      Serial.println(" ");
    }
  }

} 

void loop() { 
  float fTemp; 
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 

  // Diffrentiating the temperature by using if else condition.
  if(fTemp>0){

  if(fTemp<10){
    Serial.println("Current temperature is: " + String(fTemp)+  "deg. Celsius or very Cold");}

  else if (fTemp>=10 && fTemp<=15){
    Serial.println("Current temperature is: " + String(fTemp) +  "deg. Celsius or very Cool");}

  else if (fTemp>=15 && fTemp<=25){ 
    Serial.println("Current temperature is: " + String(fTemp) +  "deg. Celsius or very Perfect"); }

  else if (fTemp>=25 && fTemp<=30){ 
    Serial.println("Current temperature is: " + String(fTemp) +  "deg. Celsius or very Warm");}

  else if (fTemp>=30 && fTemp<=35){ 
    Serial.println("Current temperature is: " + String(fTemp) +  "deg. Celsius or very Hot");}

  else { 
    Serial.println("Current temperature is: " + String(fTemp)+" deg. Celsius or very Too Hot");}
 
  }
  // if DS18B20 sensor is not there or if there is no temp it will print the below statement.
   else{
    Serial.println(""); 
    Serial.println("Temperature Application");
    Serial.println("No DS18B20 sensors are installed");
  }
  
  //wait of 5s
  delay(5000); 
}