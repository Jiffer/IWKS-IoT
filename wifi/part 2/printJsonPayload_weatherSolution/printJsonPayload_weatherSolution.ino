#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi Parameters
const char* ssid = "SSID";
const char* password = "PWD";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

void loop() {
  // Check WiFi Status
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;  //Object of class HTTPClient
    http.begin("http://api.openweathermap.org/data/2.5/weather?q=Boulder&units=imperial&APPID=2766afd92bbcd1446ef143934c241f39");
    int httpCode = http.GET();
    //Check the returning code
    if (httpCode > 0) {
      // Get the request response payload
      String payload = http.getString();
      Serial.println(payload);

      // Parsing
      const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2 * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(13) + 280;
      DynamicJsonDocument doc(capacity);

      // const char* json = "{\"coord\":{\"lon\":-105.35,\"lat\":40.08},\"weather\":[{\"id\":800,\"main\":\"Clear\",\"description\":\"clear sky\",\"icon\":\"01d\"}],\"base\":\"stations\",\"main\":{\"temp\":56.16,\"feels_like\":47.59,\"temp_min\":41,\"temp_max\":64.4,\"pressure\":1024,\"humidity\":21},\"visibility\":16093,\"wind\":{\"speed\":5.82,\"deg\":10},\"clouds\":{\"all\":1},\"dt\":1583522997,\"sys\":{\"type\":1,\"id\":3958,\"country\":\"US\",\"sunrise\":1583501186,\"sunset\":1583542732},\"timezone\":-25200,\"id\":5574999,\"name\":\"Boulder\",\"cod\":200}";

      deserializeJson(doc, payload);

      float coord_lon = doc["coord"]["lon"]; // -105.35
      float coord_lat = doc["coord"]["lat"]; // 40.08

      JsonObject weather_0 = doc["weather"][0];
      int weather_0_id = weather_0["id"]; // 800
      const char* weather_0_main = weather_0["main"]; // "Clear"
      const char* weather_0_description = weather_0["description"]; // "clear sky"
      const char* weather_0_icon = weather_0["icon"]; // "01d"

      const char* base = doc["base"]; // "stations"

      JsonObject main = doc["main"];
      float main_temp = main["temp"]; // 56.16
      float main_feels_like = main["feels_like"]; // 47.59
      int main_temp_min = main["temp_min"]; // 41
      float main_temp_max = main["temp_max"]; // 64.4
      int main_pressure = main["pressure"]; // 1024
      int main_humidity = main["humidity"]; // 21

      int visibility = doc["visibility"]; // 16093

      float wind_speed = doc["wind"]["speed"]; // 5.82
      int wind_deg = doc["wind"]["deg"]; // 10

      int clouds_all = doc["clouds"]["all"]; // 1

      long dt = doc["dt"]; // 1583522997

      JsonObject sys = doc["sys"];
      int sys_type = sys["type"]; // 1
      int sys_id = sys["id"]; // 3958
      const char* sys_country = sys["country"]; // "US"
      long sys_sunrise = sys["sunrise"]; // 1583501186
      long sys_sunset = sys["sunset"]; // 1583542732

      int timezone = doc["timezone"]; // -25200
      long id = doc["id"]; // 5574999
      const char* name = doc["name"]; // "Boulder"
      int cod = doc["cod"]; // 200

      Serial.print("current temp in ");
      Serial.print(name);
      Serial.print(" is ");
      Serial.println(main_feels_like);
    }

    http.end();   //Close connection
  }
  // Delay
  delay(60000);
}
