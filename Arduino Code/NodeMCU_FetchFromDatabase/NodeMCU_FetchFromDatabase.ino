#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

    Serial.begin(115200);

    Serial.println();
    Serial.println();
    Serial.println();
    Serial.flush();

    for(uint8_t t = 3; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    WiFiMulti.addAP("DESD-LAB1", "tetra");
  
  pinMode(5,OUTPUT); //left wheel +
  pinMode(4,OUTPUT); //left wheel -
  
  pinMode(0,OUTPUT); //right wheel +
  pinMode(2,OUTPUT); //right wheel -
}

void halt(){
  digitalWrite(5, LOW);
  digitalWrite(4, LOW);
        
  digitalWrite(0, LOW);
  digitalWrite(2, LOW);
}

void forward(){
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
        
  digitalWrite(0, HIGH);
  digitalWrite(2, LOW);
}

void reverse(){
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
        
  digitalWrite(0, LOW);
  digitalWrite(2, HIGH);
}

void left(){
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);

  digitalWrite(0, HIGH);
  digitalWrite(2, LOW);
}

void right(){
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
        
  digitalWrite(0, LOW);
  digitalWrite(2, HIGH);
}

void cart_driver(String response){
  
    //format of response ::::::>   {"data":[{"value":0}]}


  int value = response.substring(18,19).toInt();
  Serial.flush();
  Serial.printf("Direction Value = %d",value);
  if(value == 0){             //stop
    halt();
    
  } else if(value == 1){    //forward
    forward();
    
  } else if(value == 2){    //reverse
    reverse();   
    
  } else if(value == 3){    //left
    left();
    delay(1000);
    //forward();    
  } 
  else if(value == 4){      //right
    right();
    delay(1000);
    //forward();   
  }
}

void loop() {
    // wait for WiFi connection
    if((WiFiMulti.run() == WL_CONNECTED)) {
      
  Serial.println("Wifi Connected");
        HTTPClient http;

        Serial.print("Configuring http.begin() \n");
        // configure server and url
        http.begin("http://172.0.3.5:4500/cart");


        Serial.print("Calling http.GET() method \n");
        // start connection and send HTTP header
        int httpCode = http.GET();
        Serial.flush();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("http.GET() method sent and handled, http code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String response = http.getString();
                Serial.println("Response = "+response);

                cart_driver(response);
            }
        } else {
            Serial.printf("http.GET() method failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

    delay(1000);
}
