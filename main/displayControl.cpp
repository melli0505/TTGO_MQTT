#include <Arduino.h>
#include <sstream>
#include <string.h>
#include <TFT_eSPI.h> 
#include <SPI.h>

static TFT_eSPI* tft;

void setup_tft(TFT_eSPI* tft_instance) {
    tft = tft_instance;
}

bool display_mqtt(String payload){
    tft->fillScreen(TFT_BLACK);
    tft->setTextSize(2);
    tft->setCursor(15, 5, 7);
    tft->drawString(payload, 15, 5, 7);
}