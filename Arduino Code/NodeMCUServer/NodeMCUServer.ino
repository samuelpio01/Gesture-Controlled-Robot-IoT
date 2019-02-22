#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "DESD-LAB1";
const char *password = "tetra";

// create the web server process
// and make it listen on port 80
ESP8266WebServer server(80);

void handleRoot() {
  Serial.println("Request is received for /");

  // send hello message
  server.send(200, "text/plain", "Hello client");
}


void handleCartActivity() {
  Serial.println("Request is received for /cart");
  
  String message = "Cart Movement in ";
  String ledState = server.arg("state");
  Serial.print("LED state = ");
  Serial.println(ledState);
  message+= ledState;
  message+= " direction";

  
  if (ledState == "front") {
    digitalWrite(16, HIGH); //code to go front
    digitalWrite(16, HIGH);
  } else if (ledState == "back") {
    digitalWrite(16, LOW);  //code to go back
    digitalWrite(16, HIGH);
  } else if (ledState == "right") {
    digitalWrite(16, LOW);  //code to go right
    digitalWrite(16, HIGH);
  } else if (ledState == "left") {
    digitalWrite(16, LOW);  //code to go left
    digitalWrite(16, HIGH);
  } else if (ledState == "stop") {
    digitalWrite(16, LOW);  //code to stop
    digitalWrite(16, HIGH);
  }
  
  
  
  //server.send(200, "text/html", "<h1>Cart Movement in </h1>");
  server.send(200, "text/html", message);
    
}
/*
void handleYellowLED() {
  Serial.println("Request is received for /yellowled");
  
  String ledState = server.arg("state");
  if (ledState == "on") {
    digitalWrite(5, HIGH);
  } else if (ledState == "off") {
    digitalWrite(5, LOW);
  }
  
  server.send(200, "text/html", "<h1>YELLOW LED toggled</h1>");
}
*/

void setup() {
  Serial.begin(115200);

  pinMode(16, OUTPUT);
  pinMode(5, OUTPUT);

  Serial.println("welcome to my web server");
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(" . ");
  }
  
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/cart", handleCartActivity);
 // server.on("/yellowled", handleYellowLED);
  
  server.begin();
  
  Serial.println("Server started listening on port 80");
}

void loop() {
  server.handleClient();
}
