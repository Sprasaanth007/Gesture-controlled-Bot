#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>

const char* ssid = "VIT7G";
const char* password = "9445110110";
const char* host = "maker.ifttt.com";

Adafruit_ADXL345_Unified test_one = Adafruit_ADXL345_Unified();

float a0,b0,c0;

void setup()
{
  
  Serial.begin(115200);

  test_one.begin(); 
  
  sensors_event_t test_two;
  
  test_one.getEvent(&test_two);
  
  a0 = test_two.acceleration.x;
  b0 = test_two.acceleration.y;
  c0 = test_two.acceleration.z;
  
  Serial.print(a0);
  Serial.print(",");
  Serial.print(b0);
  Serial.print(",");
  Serial.print(c0);
   Serial.println("Email from Node Mcu");
    delay(100);

    Serial.print("Connecting to ");
    Serial.println(ssid);
    
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial.println("");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

}

void loop() 
{
  WiFiClient client; 
           const int httpPort = 80;  
            if (!client.connect(host, httpPort)) {  
                  Serial.println("connection failed");  
            return;}

  float a1;
  float b1;
  float c1;

  sensors_event_t test_three;
  
  test_one.getEvent(&test_three);


  a1 = test_three.acceleration.x;
  b1 = test_three.acceleration.y;
  c1 = test_three.acceleration.z;
 Serial.print("X: "); Serial.print(test_three.acceleration.x); Serial.print("  ");
 Serial.print("Y: "); Serial.print(test_three.acceleration.y); Serial.print("  ");
 Serial.print("Z: "); Serial.print(test_three.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
  if (c1>20)
  {
    Serial.println("Fall Detected");
     String url = "/trigger/Fall_detection/with/key/dc5i3Z9nrI--xJ0EQMdga4"; 

   
                    Serial.print("Requesting URL: ");
                    Serial.println(url);
                 
                     client.print(String("GET ") + url + " HTTP/1.1\r\n" + 
                                    "Host: " + host + "\r\n" +   
                                           "Connection: close\r\n\r\n"); 
    
  }
}
