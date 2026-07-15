/*************************************************************
  Smart Plant Monitor with ESP32 + Blynk
*************************************************************/

// Blynk Credentials
#define BLYNK_TEMPLATE_ID "TMPL2Ve-yQb9x"
#define BLYNK_TEMPLATE_NAME "Plant Monitor"
#define BLYNK_AUTH_TOKEN "pkmnzbWdjQu0Hj40EOn_1t4MEaSeq7KH"

// Libraries
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

// Wi-Fi Credentials
char ssid[] = "...";
char pass[] = "...";

// Soil moisture sensor pin
const int sensorPin = 34;

// Dry threshold
const int dryThreshold = 2200;

// Prevent repeated notifications
bool lastDryState = false;

// Timer
unsigned long lastReadTime = 0;
const unsigned long interval = 2000; // Read every 2 seconds

void setup() 
{
  Serial.begin(115200);

  Serial.println();
  Serial.println("Starting Plant Monitor...");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("Connected!");
}

void loop()
{
  Blynk.run();

  if (millis() - lastReadTime >= interval)
  {
    lastReadTime = millis();

    int sensorValue = analogRead(sensorPin);

    Serial.print("Raw Value: ");
    Serial.println(sensorValue);

    bool isDry = sensorValue > dryThreshold;

    if (isDry)
    {
      Serial.println("⚠️ Soil is DRY!");

      // Send notification only once
      if (!lastDryState)
      {
        Blynk.logEvent("soil_dry", "🌱 Your plant needs water!");
      }
    }
    else
    {
      Serial.println("✅ Soil is WET");
    }

    lastDryState = isDry;

    Serial.println("----------------------------");
  }
}