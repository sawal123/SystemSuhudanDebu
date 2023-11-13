
#include <SPI.h>
#include <ESP8266WiFi.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);


#include <DHT.h>

int dustPin = A0; // dust sensor - Wemos A0 pin
int ledPin = 12;  //PinD6

float voltsMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

char ssid[] = "hotspothpku";
char pass[] = "123456789";

//#define DHTPIN 0
int DHTPIN = 0;
int h;
int t;

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);



void setup()
{
  lcd.init();                      // initialize the lcd
  lcd.init();
  lcd.clear();
  lcd.noCursor();
  Serial.begin(9600);
  dht.begin();

  pinMode(ledPin, OUTPUT);
  Serial.print("Start Sensor Debu");

}


void loop()
{

  h = dht.readHumidity();
  t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  digitalWrite(ledPin, LOW); // power on the LED
  delayMicroseconds(280);

  voltsMeasured = analogRead(dustPin); // read the dust value

  delayMicroseconds(40);
  digitalWrite(ledPin, HIGH); // turn the LED off
  delayMicroseconds(9680);

  //measure your 5v and change below
  calcVoltage = voltsMeasured * (5.0 / 1024.0);
  dustDensity = 0.166 * calcVoltage;

  lcd.setCursor(0, 0);
  Serial.print("Suhu: ");
  Serial.println(t);

  lcd.setCursor(0, 0);
  lcd.print("mg/m3: ");
  Serial.print("Debu: ");
  Serial.println(dustDensity);
  lcd.print(dustDensity);
  lcd.print("    ");


   koneksi_database();
    String Link;
    HTTPClient http;
    Link = "http://" + String(host) + ":8080" + "/add/sensor.php?idfinger=" + String(jari);
    http.begin(client, Link);
    http.GET();
    String responWeb = http.getString();
     delay(1000);
    http.end();

}

void koneksi_database()
{
  if (!client.connect(host, 8080)) {
    Serial.println("Gagal Konek");
    return;
  }
  else {
    Serial.println("Berhasil Konek");
    return;
  }
}
