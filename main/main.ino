#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <TFT_eSPI.h>
#include <sstream>

#include "config.h"
#include "wifiControl.h"
#include "mqttControl.h"
#include "displayControl.h"

int value = initialPwmValue;
unsigned long previousMillis10000Cycle = 0;
unsigned long interval10000Cycle = 10000;

IPAddress local_ip;
WiFiClient espClient;

static TFT_eSPI tft = TFT_eSPI();
static PubSubClient client(mqttServer, mqttPort, callback, espClient);

void setup() {
  Serial.begin(115200);
  Serial.println("");

  tft.init();

  setup_tft(&tft);

  // connect with WiFi
  setup_wifi();

  client.setClient(espClient);
  client.setServer(mqttServer, mqttPort);

  setup_mqtt(&client, &tft);

  // pwm initialize
  initPWMptc();
  
  Serial.printf("Setting done, have fun.\r\n");
}

void loop() {
  Serial.println("Loop working...");
  if(WiFi.status() != WL_CONNECTED) {
    setup_wifi();
  }

  if(!client.connected()) {
    reconnect();
  }

  client.loop();

  unsigned long currentMillis = millis();

  if ((currentMillis - previousMillis10000Cycle) >= interval10000Cycle) {
    previousMillis10000Cycle = currentMillis;

    value = random(20, 26);
    updateMQTTwithPWM(value, true);

  }
  
  delay(3000);
}