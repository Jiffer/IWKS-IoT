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
      const size_t capacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(8) + 370;
      DynamicJsonDocument doc(capacity);

      String json = http.getString();

      deserializeJson(doc, json);

      int id = doc["id"]; // 1
      const char* name = doc["name"]; // "Leanne Graham"
      const char* username = doc["username"]; // "Bret"
      const char* email = doc["email"]; // "Sincere@april.biz"

      JsonObject address = doc["address"];
      const char* address_street = address["street"]; // "Kulas Light"
      const char* address_suite = address["suite"]; // "Apt. 556"
      const char* address_city = address["city"]; // "Gwenborough"
      const char* address_zipcode = address["zipcode"]; // "92998-3874"

      const char* address_geo_lat = address["geo"]["lat"]; // "-37.3159"
      const char* address_geo_lng = address["geo"]["lng"]; // "81.1496"

      const char* phone = doc["phone"]; // "1-770-736-8031 x56442"
      const char* website = doc["website"]; // "hildegard.org"

      JsonObject company = doc["company"];
      const char* company_name = company["name"]; // "Romaguera-Crona"
      const char* company_catchPhrase = company["catchPhrase"]; // "Multi-layered client-server neural-net"
      const char* company_bs = company["bs"]; // "harness real-time e-markets"

    }

    http.end();   //Close connection
  }
  // Delay
  delay(60000);
}
