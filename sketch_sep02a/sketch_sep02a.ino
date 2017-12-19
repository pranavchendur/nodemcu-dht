#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>
 
String apiKey = "THINGSPEAK_API_KEY";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "SSID_NAME";     // replace with your wifi ssid and wpa2 key
const char *pass =  "SSID_PASSWORD";
const char* server = "api.thingspeak.com";

#define DHTPIN 4
 
DHT dht(DHTPIN, DHT11);

WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}

double analogValue = 0.0;
double analogValueInv = 0.0;
double analogVolts = 0.0;
double chartValue = 0.0;

void loop() 
{
  
      float h = dht.readHumidity();
      float t = dht.readTemperature();
      analogValue = analogRead(A0); // read the analog signal
      analogVolts = (analogValue * 3.08) / 1024;
      analogValueInv = 1024-analogValue;
      chartValue = map(analogValueInv,0,750,0,100);
      
      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                     delay(50);
                 }

                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(t);
                             postStr +="&field2=";
                             postStr += String(h);
                             postStr +="&field3=";
                             postStr += String(chartValue);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.print(" degrees Celcius, Humidity: ");
                             Serial.print(h);
                             Serial.print(" ChartValue :  ");
                             Serial.print(chartValue);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(300000);
}
