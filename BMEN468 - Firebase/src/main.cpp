#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <DHT20.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Salvador"
#define WIFI_PASSWORD "candy123"
#define API_KEY "AIzaSyDHcJmpHM6pFtUQfq1X1cd5VB8HyWatCHg" // Insert Firebase project API Key
#define DATABASE_URL "https://bmen-468-default-rtdb.firebaseio.com/" // Insert RTDB URLefine the RTDB URL */

// DHT20 sensor
DHT20 DHT;


// Define Firebase objects
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// Variable to save USER UID
String uid;

// Variables to save database paths
String tempPath = "test/Temperature";
String humPath = "test/Humidity";

unsigned long sendDataPrevMillis = 0;
int timerDelay = 3000; // 3 seconds between readings
bool signupOK = false;

// Initialize WiFi
void initWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  Serial.println();
}

// Write float values to the database
void sendFloat(String path, float value){
  if (Firebase.RTDB.setFloat(&fbdo, path.c_str(), value)){
    Serial.print("Writing value: ");
    Serial.print (value);
    Serial.print(" on the following path: ");
    Serial.println(path);
    Serial.println("PASSED");
    Serial.println("PATH: " + fbdo.dataPath());
    Serial.println("TYPE: " + fbdo.dataType());
  }
  else {
    Serial.println("FAILED");
    Serial.println("REASON: " + fbdo.errorReason());
  }
}

void setup(){
  Wire.begin();
  DHT.begin(); // Initialize DHT sensor
  Serial.begin(115200); 
  initWiFi(); // Initialize Wifi

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
  delay(1000);
  Serial.println("Setup done");
}

float temperature, humidity;

void loop(){
  // Send new readings to database
  if (Firebase.ready() && (millis() - sendDataPrevMillis > timerDelay || sendDataPrevMillis == 0)){
    sendDataPrevMillis = millis();

    // Read from the sensor
    int status = DHT.read(); 
    temperature = DHT.getTemperature();
    humidity = DHT.getHumidity();

    temperature = floor(temperature * 10) / 10;
    humidity = floor(humidity * 10) / 10;
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Send readings to database:
    sendFloat(tempPath, temperature);
    sendFloat(humPath, humidity);
  }
}