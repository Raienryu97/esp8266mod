/*
** Author: Pranav Cherukupalli <cherukupallip@gmail.com>
** Author: Vamsy Durvasula     <vamsydvjk@gmail.com>
*/

#include <ESP8266WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5

bool first_time = true;
String temp = "Reading...";
float received_temp = 0.0;
float current_temp = -1;
const char* ssid = "Your_WiFi_SSID";
const char* password = "your_passkey";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(9600);
  delay(10);
  pinMode(D5,OUTPUT);
  digitalWrite(D5,HIGH);
  sensors.begin();

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  IPAddress ip(192, 168, 137, 118); // 192.168.137.118
  IPAddress gateway(192, 168, 137, 1); // set gateway to match your network
  Serial.println(("Setting static ip to : "));
  Serial.println(ip);
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }

  // Read the first line of the request
  String req = client.readStringUntil('\r');

  // Match the request
    Serial.println("Received: " + req);
  // Send the response to the client
  if(first_time)
  first_time = false;
  client.print(temp);
  sensors.requestTemperatures();
  current_temp = sensors.getTempCByIndex(0);
  temp = String(current_temp);
  Serial.println("Sending: " + temp);
  delay(1);
  Serial.println("Client disonnected");
  received_temp = req.toFloat();
  if(received_temp <= current_temp && received_temp > 25)
  {
    Serial.println("Going to Sleep");
    client.print("JOB DONE");
    digitalWrite(D5,LOW);
    ESP.deepSleep(0);
  }
}
