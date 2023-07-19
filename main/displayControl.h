#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
#include <string.h>

void setup_tft(TFT_eSPI* tft_instance);
bool display_mqtt(String payload);//, TFT_eSPI* tft_instance);