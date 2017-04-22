/*
** Author: Pranav Cherukupalli <cherukupallip@gmail.com>
** Author: Vamsy Durvasula     <vamsydvjk@gmail.com>
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
WiFiClient client;
ESP8266WiFiMulti WiFiMulti;

float default_temp;
float req_temp;
bool firstTime=true;
String send="100";

void setup() {
    pinMode(D6,INPUT);
    pinMode(D5,INPUT);
    Serial.begin(9600);
    delay(10);
    lcd.begin(16,2);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Connecting To WiFi");
    // We start by connecting to a WiFi network
    WiFiMulti.addAP("Your_WiFi_SSID", "your_passkey");

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        lcd.setCursor(0,1);
        lcd.print(".");
        delay(500);
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("WiFi Connected");
    lcd.setCursor(0,1);
    lcd.print("IP: " + String(WiFi.localIP()));
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("RYUU HEATER");
    lcd.setCursor(0, 1);
    lcd.print("INITIALISING...");
    /*
    **Button placed at D6 will increase the temperature
    **Button placed at D5 will decrease the temperature
    */
    attachInterrupt(digitalPinToInterrupt(D6), handleInterrupt1, FALLING);
    attachInterrupt(digitalPinToInterrupt(D5), handleInterrupt2, FALLING);
}

void handleInterrupt1(){
   if(req_temp<=50)
   {
    req_temp=++req_temp;
    Serial.print("Required Temp :");
    Serial.println(req_temp);
    send=String(req_temp);
   }
}

void handleInterrupt2(){
   if(req_temp>=default_temp)
   {
    req_temp=--req_temp;
    Serial.print("Required Temp :");
    Serial.println(req_temp);
    send=String(req_temp);
   }
}

void loop() {
    const uint16_t port = 80;
    const char * host = "192.168.137.118";
    Serial.print("connecting to ");
    Serial.println(host);

    if(!client.connect(host, port)){
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }

    String line;
    client.print(send);
    if(firstTime)
    {
        line= client.readStringUntil('\r');
        default_temp=line.toFloat();
        req_temp=default_temp;
        Serial.println(default_temp);
        firstTime=false;
    }
    else
    {
        line= client.readStringUntil('\r');
        if(line.endsWith("JOB DONE"))
        {
          Serial.println("Have a nice bath!");
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Have a nice bath");
          lcd.setCursor(5,1);
          lcd.print("Goodbye!");
          ESP.deepSleep(0);
        }
        Serial.println("Current Temp :"+line);
    }
    delay(500);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Curr Temp: " + line);
    lcd.setCursor(0,1);
    lcd.print("Reqd Temp: " + send);

}
