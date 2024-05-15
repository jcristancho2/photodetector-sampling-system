#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <Wire.h>
#include "time.h"

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "RAUCROW"
#define WIFI_PASSWORD "1234567890"

#define API_KEY "AIzaSyDAzzoBjWGZv8ZD-CdRhCjHd3qoLccfV0g"

#define USER_EMAIL "jocristanchool@gmail.com"
#define USER_PASSWORD "core0626"

#define DATABASE_URL "https://argl2-1f5c9-default-rtdb.firebaseio.com/"

const int sensor1 = 35;
const int sensor2 = 34;

int sen1 = 0;
int sen2 = 0;
float division = 0;

const int steppin = 13 ;
const int dirpin = 12;
const int t1 = 1;
const int t2 = 5;
const int tmuestra = 10000;

const int Nmuestra = 51; 

int MT = 0;
int flag1 = 0;
int flag2 = 0;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

String uid;

String databasePath;

String muestra = "/MT";
String senso1 = "/sen1";
String senso2 = "/sen2";
String s2s1 = "/division";
String timePath = "/timestamp";

String parentPath;

int timestamp;
FirebaseJson json;

const char* ntpServer = "pool.ntp.org";

unsigned long sendDataPrevMillis = 0;
unsigned long timerDelay = 1800;

void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("CONECTANDO A WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return(0);
  }
  time(&now);
  return now;
}

void setup(){
  Serial.begin(115200);

  pinMode(steppin, OUTPUT);
  pinMode(dirpin, OUTPUT);

  initWiFi();
  configTime(0, 0, ntpServer);

  config.api_key = API_KEY;

  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  config.database_url = DATABASE_URL;

  Firebase.reconnectWiFi(true);
  fbdo.setResponseSize(4096);

  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  // Initialize the library with the Firebase authen and config
  Firebase.begin(&config, &auth);

  // Getting the user UID might take a few seconds
  Serial.println("Getting User UID");
  while ((auth.token.uid) == "") {
    Serial.print('.');
    delay(1000);
  }
  // Print user UID
  uid = auth.token.uid.c_str();
  Serial.print("User UID: ");
  Serial.println(uid);

  // Update database path
  databasePath = "/UsersData/" + uid + "/readings";
}

void loop(){
      if(flag1 == 0){
  digitalWrite(dirpin, LOW);

for(int x=0; x<20000; x++){

  digitalWrite(steppin, HIGH);
  delay(t1);
  digitalWrite(steppin, LOW);
  delay(t1);
}

delay(100);

//retroceder rectificacion 
digitalWrite(dirpin, HIGH);

for(int x=0; x<20000; x++){

  digitalWrite(steppin, HIGH);
  delay(t1);
  digitalWrite(steppin, LOW);
  delay(t1);
}

delay(100);

//avanzar centro
digitalWrite(dirpin, LOW);

for(int x=0; x<10000; x++){

  digitalWrite(steppin, HIGH);
  delay(t1);
  digitalWrite(steppin, LOW);
  delay(t1);
}

delay(100);


digitalWrite(dirpin, HIGH);

for(int x=0; x<2460; x++){

  digitalWrite(steppin, HIGH);
  delay(t1);
  digitalWrite(steppin, LOW);
  delay(t1);
}

delay(100);
flag1=1;
}
  
  while (MT >= Nmuestra) {
    Serial.println("Finalizado");
      digitalWrite(dirpin, HIGH);

        for(int x=0; x<13460; x++){

          digitalWrite(steppin, HIGH);
          delay(t1);
          digitalWrite(steppin, LOW);
          delay(t1);
        }
    while (true) {
    }
  }

    sen1 = analogRead(sensor1);
    sen2 = analogRead(sensor2);
    division = (float)sen1 / sen2;

    Serial.print(MT + 1);
    Serial.print("\t");
    Serial.print(sen1);
    Serial.print("\t");
    Serial.print(sen2);
    Serial.print("\t");
    Serial.println(division, 4);
    MT++;

    digitalWrite(dirpin, LOW);
    for (int x = 0; x < 98.4; x++) {
      digitalWrite(steppin, HIGH);
      delay(t2);
      digitalWrite(steppin, LOW);
      delay(t2);
    }

        delay(tmuestra);

  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    timestamp = getTime();
    Serial.print ("time: ");
    Serial.println (timestamp);

    parentPath= databasePath + "/" + String(timestamp);


    json.set(muestra.c_str(), String(MT));
    json.set(senso1.c_str(), String(sen1));
    json.set(senso2.c_str(), String(sen2));
    json.set(s2s1.c_str(), String(division));
    json.set(timePath, String(timestamp));
    Serial.printf("Set json... %s\n", Firebase.RTDB.setJSON(&fbdo, parentPath.c_str(), &json) ? "ok" : fbdo.errorReason().c_str());
  }
}






