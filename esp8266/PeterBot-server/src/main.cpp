#include <Arduino.h>
#ifdef ESP32
  #include <AsyncTCP.h>
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
#include <string>

#define TIMEOUT 60000

AsyncWebServer server(80);

const char* wifi_ssid = "COSMOTE-593676";
const char* wifi_password = "h9c3c4sc37gppn38b278";

int extract_move_command(const String& url){

  if(url.indexOf("/move/1") != -1) {
    return 1;
  }
  if(url.indexOf("/move/2") != -1) {
    return 2;
  }
  if(url.indexOf("/move/3") != -1) {
    return 3;
  }
  if(url.indexOf("/move/4") != -1) {
    return 4;
  }
  return -1;
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(wifi_ssid, wifi_password);
  if (WiFi.waitForConnectResult(TIMEOUT) != WL_CONNECTED) {
    Serial.println("Failed to connect to WiFi");
    return;
  }
    Serial.println(WiFi.localIP());

  server.on("/move", HTTP_GET, [](AsyncWebServerRequest *request){
    int move_command = extract_move_command(request->url());
    if (move_command == -1) {
      request->send(422, "text/plain", "Invalid move command");
      return;
    }
    Serial.println(move_command);
    request->send(200, "text/plain", "Moved");
  });

  server.onNotFound([](AsyncWebServerRequest *request){
      request->send(404, "text/plain", "Not found");
    } 
  );
  server.begin();
}


void loop() {
  // Nothing to do here
}

