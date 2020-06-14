#include <DHT.h>
#include <ESP8266WiFi.h>
String apiKey="################"; //fill in your API Key
const char *ssid= "######"; //fill in your Network SSID
const char *pass="######";  //fill in your Wi-Fi Password
const char *server ="api.thingspeak.com";
#define DHTPIN 0  //define PIN D3 GPIO0
DHT dht(DHTPIN,DHT11);
WiFiClient client;
void setup() {
 
Serial.begin(115200);
delay(10);
dht.begin();
Serial.println("connecting to....");
Serial.println("ssid");
WiFi.begin(ssid,pass);
while (WiFi.status()!=WL_CONNECTED)
{
  delay(500);
  Serial.print("....");
  }
Serial.println("....");
Serial.println("wifi connected");
}

void loop() {
  float h=dht.readHumidity();
  float t=dht.readTemperature();
  Serial.print("humidity");
  Serial.print(h);
  Serial.print("temp");
  Serial.println(t );
  
  delay(2000);
 
 if(client.connect(server,80))
 {
  String postStr = apiKey;
 postStr += "&field1=";
 postStr += String(t);
 postStr +="&field2=";
 postStr += String(h);
 postStr +="\r\n\r\n";
 client.print("POST/update HTTP/1.1\n");
 client.print("Host:api.thingspeak.com\n");
 client.print("Connection: close\n");
 client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
 client.print("Content-Type: application/x-www-form-urlencoded\n");
 client.print("Content-Length: ");
 client.print(postStr.length());
 client.print("\n\n");
 client.print(postStr);
 Serial.print (postStr);
 Serial.print("temperature:");
 Serial.print(t);
 Serial.print("degree celcius;humidity: ");
 Serial.print(h);
 Serial.println("% send to thingspeak");
 }
  client.stop();
  Serial.println("waiting........");
  delay(20000);
  

}
