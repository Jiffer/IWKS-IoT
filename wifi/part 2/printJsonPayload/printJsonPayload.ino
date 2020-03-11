#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Parameters
const char* ssid = "Inworks-IoT2";
const char* password = "MakeItMatter";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  // after successful connection, print:
  Serial.print("Connected to: ");
  Serial.println(ssid);
}

////////////////////////////////////
// main loop
////////////////////////////////////
void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    
    //Object of class HTTPClient
    HTTPClient http;  
    http.begin("http://jsonplaceholder.typicode.com/users/1");
    int httpCode = http.GET();
    
    //Check the returning code
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      Serial.println(payload);
      // TODO: Parsing

    }

    http.end();   //Close connection
  }
  // Delay
  delay(60000);
}
