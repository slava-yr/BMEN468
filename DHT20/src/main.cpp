#include <Arduino.h>
#include <DHT20.h>

#define tmpPIN 15
DHT20 DHT;


void setup()
{
  DHT.begin();
  Serial.begin(115200);

  Wire.begin();
  DHT.begin();    //  ESP32 default pins 21 22

  delay(1000);
  Serial.println("Ready");
}

void loop()
{
  int status = DHT.read(); 
  float temp = DHT.getTemperature();
  float hum = DHT.getHumidity();
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  switch (status)
    {
      case DHT20_OK:
        Serial.print("OK");
        break;
      case DHT20_ERROR_CHECKSUM:
        Serial.print("Checksum error");
        break;
      case DHT20_ERROR_CONNECT:
        Serial.print("Connect error");
        break;
      case DHT20_MISSING_BYTES:
        Serial.print("Missing bytes");
        break;
      case DHT20_ERROR_BYTES_ALL_ZERO:
        Serial.print("All bytes read zero");
        break;
      case DHT20_ERROR_READ_TIMEOUT:
        Serial.print("Read time out");
        break;
      case DHT20_ERROR_LASTREAD:
        Serial.print("Error read too fast");
        break;
      default:
        Serial.print("Unknown error");
        break;
    }
  
  Serial.print("\n-------------\n\n");
  delay(1000);
} 

void readTempTMP()
{
  int reading = analogRead(tmpPIN);

  // Convert that reading into voltage
  float voltage = reading * (3.3 / 4095.0);

  // Convert the voltage into the temperature in Celsius
  float temperatureC = (voltage - 0.5) * 100;
|
  // Print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.print("\xC2\xB0"); // shows degree symbol
  Serial.println("C");
}