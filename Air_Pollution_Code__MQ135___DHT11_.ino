#define BLYNK_TEMPLATE_ID "*****************"
#define BLYNK_DEVICE_NAME "**************************"
#define BLYNK_AUTH_TOKEN "***************************"

#include <DHT.h>                                      //Declarate DHT Library
#include <WiFi.h>                                     //Declarate ESP8266 Board Library
#include <BlynkSimpleEsp32.h>
#define DHTPIN 14                                     //Pin of DHT 22
#define DHTTYPE DHT11                                 //Type of DHT
#define MQ 35
                                      
DHT dht(DHTPIN, DHTTYPE);                             //Declarate dht

int val = 0;                                          //Declarate val variable
char auth[] = "*******************";                 //Put your blink token
char ssid[] = "***************";                            //Put your SSID of your connection
char pass[] = "*****************";                            //Put your Password of your connection
 
void setup() {  
  Blynk.begin(auth, ssid, pass);                      //Connect the blynk to esp8266 board                          
  dht.begin();                                        //Start DHT sensor                                              
  Serial.begin(115200);
}

void loop() {
  Blynk.run();                                        //Run the Blynk
                                                                                
  float h = dht.readHumidity();                       //Read humidity and put it in h variable                             
  float t = dht.readTemperature();                    //Read temperature and put it in t variable                        
  float q = analogRead(MQ);                           //Read air quality and put it into q variable                                  
  Blynk.virtualWrite(V5, t);                          //Send t value to blynk in V5 virtual pin                                 
  Blynk.virtualWrite(V6, h);                          //Send h value to blynk in V6 virtual pin                                 
  Blynk.virtualWrite(V1, q);                          //Send q value to blynk in V0 virtual pin        
  if (q>100) {                                              
    Blynk.notify("The Quailty of air is bad !!");     //Blynk will send notify if q>70
  }
  if (t>40) {
    Blynk.notify("The Temperature is too high");      //Blynk will send notify if t>40
  }
}
