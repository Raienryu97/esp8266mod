/*
 * This program aims to set up an Access Point on the ESP8266 
 * and start a server which can be used to turn on either of 
 * the three RED, BLUE, GREEN LEDs  present on the device 
 * remotely from any device connected to the hotspot or turn
 * all of them off. 
 */

#include<ESP8266WiFi.h>
#include<WiFiClient.h>
#include<ESP8266WebServer.h>

//GPIO's of the corresponding LEDs on board of AI THINKER ESP8266MOD
const int red = 15;
const int blue = 13;
const int green = 12;

//*******Change the SSID and Password As Per Your Wish*******\\

const char *ssid = "ESP_AP";
const char *password = "qwertyuiop";


ESP8266WebServer server(80);    //We start the server at port 80, the default port.

//*******Custom Function Declarations To Turn On Either LEDs Or Turn All Of Them Off*******\\

void turnoff(void);
void turnon1(void);
void turnon2(void);
void turnon3(void);

//Begin Setup

void setup() {
  
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);
  
  Serial.begin(115200);
  
  WiFi.softAP(ssid,password);  //Set as WiFi.softAP(ssid) syntax type to create an open AP
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("My IP address: ");
  Serial.println(myIP);

  /*
   * By default server is set at the IP http://192.168.4.1 . Anything after
   * that can be set through the following <server.on(__,__)> syntax where
   * the first parameter would be the address that appends to default IP and
   * the second parameter would be used to call a function of type
   * void function(void). Thus we aim to call function turnon1 when
   * http://192.168.4.1/red is typed into the browser of any device connected
   * to the AP of this module.
   */
   
  server.on("/red",turnon1);
  server.on("/green",turnon2);
  server.on("/blue",turnon3);
  server.on("/off",turnoff);

  //Begin the server now
  server.begin();
}

/*
 * Handle all the client(browser) requests by calling the
 * appropriate function in loop so it always does its job
 */
 
void loop() {
  server.handleClient();
}

//*******The Bottom Functions Are Definitions For Above Declared Functions*******\\


void turnoff()
{   
    digitalWrite(red, LOW);
    digitalWrite(green,LOW);
    digitalWrite(blue,LOW);  
}

void turnon1()
{
    turnoff();
    server.send(200, "text/html", "<h1>RED LED ON</h1>");
    digitalWrite(red, HIGH);
  }
void turnon2()
{
    turnoff();
    server.send(200, "text/html", "<h1>GREEN LED ON</h1>");    
    digitalWrite(green, HIGH);
  }

void turnon3()
{
    turnoff();
    server.send(200, "text/html", "<h1>BLUE LED ON</h1>");
    digitalWrite(blue, HIGH);
  }    


