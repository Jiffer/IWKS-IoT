/*  web server hosts simple page to control LED
  Modified from the example here:
  https://42bots.com/tutorials/esp8266-example-wi-fi-access-point-web-server-static-ip-remote-control/

*/

#include <WiFi.h>
#include <WebServer.h>

/* WiFi access point settings. Update them as needed */
const char *ssid = "theHarrimans";
const char *password = "andSadie2";

// Define a web server at port 800 for HTTP
// NOTE: if 80 is used your web browser 
// doesn't need to specify the port
WebServer server(800);

const int ledPin = 5; // output LED toggle with HTML

// keep track of current value
bool ledState = false;

// ***************************
// Initialization
// ***************************
void setup() {
  pinMode ( ledPin, OUTPUT );
  // the built in LED is wired so that 0 turns it on
  digitalWrite ( ledPin, 0 );

  delay(100);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting...");

  // Connect to WiFi network (set network name and pw above)
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  Serial.print("my IP address: ");
  Serial.println(WiFi.localIP());

  server.on ( "/", handleRoot );
  server.on ( "/led=1", handleRoot);
  server.on ( "/led=0", handleRoot);
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well.");
  } );
  server.onNotFound ( handleNotFound );

  server.begin();
  Serial.println("HTTP server started");
}

// ***************************
// main
// ***************************
void loop() {
  //  digitalWrite(ledPin, ledState);
  server.handleClient();
}

// ***************************
// when root page is accessed
// ***************************
void handleRoot() {

  // capture any value passed into the led argument and assign to ledState
  ledState = server.arg("led").toInt();
  digitalWrite (ledPin, ledState);
  //Serial.println(ledState);

  /* Dynamically generate the LED toggle link, based on its current state (on or off)*/
  char ledText[80];

  if (ledState) {
    strcpy(ledText, "LED is on. <a href=\"/?led=0\">Turn it OFF!</a>");
  }

  else {
    strcpy(ledText, "LED is OFF. <a href=\"/?led=1\">Turn it ON!</a>");
  }


  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  
  // between 0:255
  int red = map(analogRead(A0), 0, 4095, 0, 255);
  int green = 200;
  int blue = 200;
  // calculate background color
  unsigned long bgVal = red * 65536 + green * 256 + blue ;// (0xffffff); // r << 16 + g << 8 + b

  // read value
  int analogVal = analogRead(A0);
  analogVal = (int)(analogVal + 5) / 10; //converting the 0-1024 value to a (approximately) percentage value

  // Build an HTML page to display on the web-servesr root address
  char html[1000];
  snprintf ( html, 1000,

             "<html>\
  <head>\
    <meta http-equiv='refresh' content='10'/>\
    <title>ESP8266 WiFi Network</title>\
    <style>\
      body { background-color: %0x%; font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
      h1 { Color: #FFF000; }\
    </style>\
  </head>\
  <body>\
    <h1>ESP8266 Wi-Fi Access Point and Web Server Demo</h1>\
    <p>Uptime: %02d:%02d:%02d</p>\
    <p>Analog in: %d%</p>\
    <p>%s<p>\
    <p>This page refreshes every 10 seconds. Click <a href=\"javascript:window.location.reload();\">here</a> to refresh the page now.</p>\
  </body>\
</html>",
             bgVal, // https://stackoverflow.com/questions/14733761/printf-formatting-for-hex
             hr, min % 60, sec % 60,
             analogVal,
             ledText
           );
  server.send ( 200, "text/html", html );
  //  digitalWrite ( ledPin, 1 );
}

// ***************************
// when not found on server
// ***************************
void handleNotFound() {
  digitalWrite ( ledPin, 0 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  //  digitalWrite ( ledPin, 1 ); //turn the built in LED on pin DO of NodeMCU off
}
