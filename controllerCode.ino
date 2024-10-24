#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti WiFiMulti;
const char* ssid = "Kidsquad_car";
const char* password = "";
String door;
const char* up = "http://192.168.4.1/u";
const char* down = "http://192.168.4.1/d";
const char* left = "http://192.168.4.1/l";
const char* right = "http://192.168.4.1/r";
const char* freeRide = "http://192.168.4.1/f";
const char* done = "http://192.168.4.1/done";
const char* ping = "http://192.168.4.1/ping";
int count = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(0, INPUT);
  pinMode(1, FUNCTION_3);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, FUNCTION_3);
  pinMode(3, INPUT);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
  while((WiFiMulti.run() == WL_CONNECTED)) { 
    delay(500);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
   // Check WiFi connection status
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    door = httpGETRequest(ping);
    if(digitalRead(0) == LOW){
      while (digitalRead(0) == LOW){
        if (digitalRead(1) == LOW){
          if (digitalRead(2) == LOW){
            if (digitalRead(3) == LOW){
              door = httpGETRequest(freeRide);
            }
          }
        }
        door = httpGETRequest(up);
      }
      door = httpGETRequest(done);
    }
    if (digitalRead(1) == LOW){
      while (digitalRead(1) == LOW){
        door = httpGETRequest(down);
      }
      door = httpGETRequest(done);
    }
    if (digitalRead(2) == LOW){
      while (digitalRead(2) == LOW){
        door = httpGETRequest(left);
      }
      door = httpGETRequest(done);
    }
    if (digitalRead(3) == LOW){
      while (digitalRead(3) == LOW){
        door = httpGETRequest(right);
      }
      door = httpGETRequest(done);
    }
  }
}
String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;
    
  // Your IP address with path or Domain name with URL path 
  http.begin(client, serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();
  
  String payload = "--"; 
  
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
