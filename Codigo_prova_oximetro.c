

#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <LiquidCrystal.h>

#define REPORTING_PERIOD_MS     1000


PulseOximeter pox;

uint32_t tsLastReport = 0;


void onBeatDetected()
{
    Serial.println("B:1");
}


const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup()
{

  lcd.begin(16, 2);
  
    Serial.begin(115200);

    if (!pox.begin(PULSEOXIMETER_DEBUGGINGMODE_PULSEDETECT)) {
        Serial.println("ERROR: Failed to initialize pulse oximeter");
        for(;;);
    }

    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{

    pox.update();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("H:");
        Serial.println(pox.getHeartRate());

        Serial.print("O:");
        Serial.println(pox.getSpO2());

        lcd.clear();
        lcd.setCursor(0,0);
    
        lcd.print("HR: ");
        lcd.print(pox.getHeartRate());
       lcd.print(" bpm");
 
        lcd.setCursor(0,1);
    
        lcd.print("SpO2: ");
        lcd.print(pox.getSpO2());
        lcd.print("%");

        tsLastReport = millis();
  
    }
}
