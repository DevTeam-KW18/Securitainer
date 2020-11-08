#include <DHT11.h>
#include <Debug.h>
#include <JSN270.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <math.h>
#include <Servo.h>
#include "DHT.h"

#define SSID      "blank"      // your wifi network SSID
#define KEY       "1234gogogo1289"      // your wifi network password
#define AUTH       "WPA2"     // your wifi network security (NONE, WEP, WPA, WPA2)

#define USE_DHCP_IP 1

#if !USE_DHCP_IP
#define MY_IP          "192.168.1.133"
#define SUBNET         "255.255.255.0"
#define GATEWAY        "192.168.1.254"
#endif

#define HOST_IP        "54.180.65.150"
#define REMOTE_PORT    80
#define PROTOCOL       "TCP"
uint8_t _hour, _minute, _second, _year, _month, _day; // GPS로부터 시간값 읽기


static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

SoftwareSerial mySerial(11, 10); // RX, TX
 
JSN270 JSN270(&mySerial);

int DHTPIN = A1;
#define DHTTYPE DHT11
int sensorPin = A0; // select the input pin for the potentiometer
int potpin = 0;  // analog pin used to connect the potentiometer
int angle=0;    // variable to read the value from the analog pin

DHT dht(DHTPIN, DHTTYPE);
Servo myservo;  // create servo object to control a servo
Servo myservo2; 


void setup()
{
  char c;

  mySerial.begin(9600);
  myservo.attach(5); 

  Serial.println("--------- JSN270 TCP Client with WPA2 Test --------");


  Serial.begin(9600);
  while(!Serial);
  Serial1.begin(GPSBaud);

  // wait for initilization of JSN270
  delay(5000);
  //JSN270.reset();
  delay(1000);

  //JSN270.prompt();
  JSN270.sendCommand("at+ver\r");
  delay(5);
  while(JSN270.receive((uint8_t *)&c, 1, 1000) > 0) {
    Serial.print((char)c);
  }
  delay(1000);

  #if USE_DHCP_IP
  JSN270.dynamicIP();
#else
  JSN270.staticIP(MY_IP, SUBNET, GATEWAY);
#endif    
    
  if (JSN270.join(SSID, KEY, AUTH)) {
    Serial.println("WiFi connect to " SSID);
  }
  else {
    Serial.println("Failed WiFi connect to " SSID);
    Serial.println("Restart System");

    return;
  }
  delay(1000);

  JSN270.sendCommand("at+wstat\r");
  delay(5);
  while(JSN270.receive((uint8_t *)&c, 1, 1000) > 0) {
    Serial.print((char)c);
  }
  delay(1000);        

  JSN270.sendCommand("at+nstat\r");
  delay(5);
  while(JSN270.receive((uint8_t *)&c, 1, 1000) > 0) {
    Serial.print((char)c);
  }
  delay(1000);

  if (!JSN270.client(HOST_IP, REMOTE_PORT, PROTOCOL)) {
    Serial.println("Failed connect to " HOST_IP);
    Serial.println("Restart System");
  } else {
    Serial.println("Socket connect to " HOST_IP);
    delay(2000);
    
    // Enter data mode
    JSN270.sendCommand("at+exit\r");
    delay(5);
  }

  Serial.println(F("FullExample.ino"));
  Serial.println(F("An extensive example of many interesting TinyGPS++ features"));
  Serial.print(F("Testing TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  Serial.println(F("by Mikal Hart"));
  Serial.println();
  Serial.println(F("Sats HDOP Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum"));
  Serial.println(F("          (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail"));
  Serial.println(F("---------------------------------------------------------------------------------------------------------------------------------------"));



}

void loop()
{
  char gps_val[512] = "37.513055,127.058608";
  char my_lat[512];
  char my_lng[512];
  
  
  static const double LONDON_LAT = 51.508131, LONDON_LON = -0.128002;

  printInt(gps.satellites.value(), gps.satellites.isValid(), 5);
  printInt(gps.hdop.value(), gps.hdop.isValid(), 5);
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printInt(gps.location.age(), gps.location.isValid(), 5);
  printDateTime(gps.date, gps.time);
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);
  printStr(gps.course.isValid() ? TinyGPSPlus::cardinal(gps.course.value()) : "*** ", 6);

  unsigned long distanceKmToLondon =
    (unsigned long)TinyGPSPlus::distanceBetween(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON) / 1000;
  printInt(distanceKmToLondon, gps.location.isValid(), 9);

  double courseToLondon =
    TinyGPSPlus::courseTo(
      gps.location.lat(),
      gps.location.lng(),
      LONDON_LAT, 
      LONDON_LON);

  printFloat(courseToLondon, gps.location.isValid(), 7, 2);

  const char *cardinalToLondon = TinyGPSPlus::cardinal(courseToLondon);

  printStr(gps.location.isValid() ? cardinalToLondon : "*** ", 6);

  printInt(gps.charsProcessed(), true, 6);
  printInt(gps.sentencesWithFix(), true, 10);
  printInt(gps.failedChecksum(), true, 9);
  Serial.println();
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));

  if (gps.location.isValid()){
    dtostrf(gps.location.lat() , 9, 6, my_lat);
    dtostrf(gps.location.lng() , 10, 6, my_lng);
    sprintf(gps_val, "%s,%s", my_lat, my_lng);
  }
   if(JSN270.available()) {

   

    int readVal=analogRead(sensorPin);

 //temperature and humid sensing
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print("\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" C");

  //smoke sensing 
  Serial.print("\t");
  Serial.print("gas: ");
  Serial.println(readVal);
  delay(1000);

  //servo motor sensing
  if(h>50 || t>25)
  {
     for(angle=0; angle<180 ; angle++)
    {
      myservo.write(angle);
      delay(30);
    }
     for(angle=180; angle>0 ; angle--)
    {
      myservo.write(angle);
      delay(30);
    }
     for(angle=0; angle<180 ; angle++)
    {
      myservo.write(angle);
      delay(30);
    }
      for(angle=180; angle>0 ; angle--)
    {
      myservo.write(angle);
      delay(30);
    }
    mySerial.print("fan is working\n");
  }

  mySerial.print("GET /arduino.php?id_code=A0001&item=melon&temp=");
  mySerial.print(t);
  mySerial.print("&humi=");
  mySerial.print(h);
  mySerial.print("&gas=");
  mySerial.print(readVal);
  mySerial.print("&gps=");
    mySerial.print(gps_val);
    mySerial.println(" HTTP/1.1");
    mySerial.print("Host: ");
    mySerial.println(HOST_IP);
    mySerial.println();
    //prev_time = current_time;
    Serial.print("debug");
    Serial.println(gps_val);


    delay(1000);
    
    JSN270.sendCommand("+++\r");
    delay(11000);
    //delay(50000);
    JSN270.sendCommand("at+socket\r");
    delay(1000);
    
    JSN270.sendCommand("at+exit\r");
    delay(1000);



  }

}

static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (Serial1.available())
      gps.encode(Serial1.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
//printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}  
