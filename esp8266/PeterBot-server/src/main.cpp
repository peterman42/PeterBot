#include <Arduino.h>
#ifdef ESP32
  #include <AsyncTCP.h>
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#define TIMEOUT 60000

AsyncWebServer server(80);

const char* wifi_ssid = "COSMOTE-593676";
const char* wifi_password = "h9c3c4sc37gppn38b278";

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  if (WiFi.waitForConnectResult(TIMEOUT) != WL_CONNECTED) {
    Serial.println("Failed to connect to WiFi");
    return;
  }
    Serial.println(WiFi.localIP());

      server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
        Serial.println(request->pathArg(0));
        request->send(200, "text/plain", "Moved");
      } );
}


void loop() {
  // Nothing to do here
}
