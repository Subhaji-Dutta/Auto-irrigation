#define BLYNK_TEMPLATE_ID "TMPLV6FbLxVJ"
#define BLYNK_DEVICE_NAME "AFFRObot"
#define BLYNK_AUTH_TOKEN "PAqjSE0mId0_yL3kdB5NuyDTAUqdTBPa"

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "#VEER";  // type your wifi name
char pass[] = "12345678";  // type your wifi password

#include <ESP8266WiFi.h> 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <BlynkSimpleEsp8266.h>



#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char auth[] = BLYNK_AUTH_TOKEN;

#define relay1 14
#define relay2 12
#define Led1 13
#define Z A0

int setmoisture = 0 ;


void setup() {
  Serial.begin(115200);
 pinMode (relay1, OUTPUT);
 pinMode (relay2, OUTPUT);
 pinMode (Led1, OUTPUT);
 pinMode (Z, INPUT);


Blynk.begin(auth, ssid, pass);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {
  delay(1000);
  Blynk.run();
  //read temperature and humidity
  float t = analogRead(Z);
  
 
  Serial.println(t);

  // clear display
  display.clearDisplay();
  
  // display temperature
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("Soil Moisture");
  display.setTextSize(2);
  display.setCursor(0,10);
  display.print(t);
  display.print(" ");
  display.setTextSize(1);
  display.cp437(true);
  display.write(167);
  display.setTextSize(2);
  display.print("%"); 
  
  display.display(); 
  Blynk.virtualWrite(V0, t);
  
  if (t <= setmoisture){
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, HIGH);
    digitalWrite(Led1,HIGH);
    
  }
    else
    {
      
       digitalWrite(relay1, HIGH);
    digitalWrite(relay2, LOW);
    digitalWrite(Led1,LOW);
     
  }
}
BLYNK_WRITE(V1) // To set soil moisture
{
   setmoisture = param.asInt(); // assigning incoming value from pin V2 to a variable
    
}
