#include<SoftwareSerial.h>
SoftwareSerial gsm_Serial(11,12);
#include "DHT.h"
#define DHTPIN 8
#define DHTTYPE DHT11 
DHT dht(DHTPIN,DHTTYPE);
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
//#define BMP_SCK  (13)
//#define BMP_MISO (12)
//#define BMP_MOSI (11)
//#define BMP_CS   (10)
Adafruit_BMP280 bmp; // I2C
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);
#include <LiquidCrystal.h>
const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int mq2=A0;
int mq135=A1;
int mq5=A2;
int mq6=A3;
int mq7=10;
int buz=13;
int ef=10;
int t,h,s1,s2,s3,s4,s5;
void setup()
{  
  dht.begin();
  pinMode(ef,OUTPUT);
  pinMode(buz,OUTPUT);
  pinMode(mq2,INPUT);
  pinMode(mq135,INPUT);
  pinMode(mq5,INPUT);
  pinMode(mq6,INPUT);
  pinMode(mq7,INPUT);
  pinMode(buz,OUTPUT);
  Serial.begin(115200);
  gsm_Serial.begin(9600);
  gsm_Serial.println("AT");
  delay(1500);
  gsm_Serial.println("AT+CMGF=1");
  lcd.begin(16, 2);
  lcd.print("  WELCOME");
  delay(1500);
  pinMode(buz,OUTPUT);
  wifi_init();
  digitalWrite(buz,0);
  //delay(2000);
//  Serial.println(F("BMP280 test"));
//  if (!bmp.begin()) {
//    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
//    while (1);
//  }
//  /* Default settings from datasheet. */
//  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
//                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
//                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
//                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
//                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}
void loop()
{ 
   delay(200);
  lcd.clear();
  s1=analogRead(mq2);
  s2=analogRead(mq135);
  s3=analogRead(mq5);
  s4=analogRead(mq6);
  s5=analogRead(mq7);
  t = dht.readTemperature();
  h=dht.readHumidity();
 int  pval = bmp.readPressure();
//  Serial.print(F("Pressure = "));
//  Serial.print(bmp.readPressure());
//  Serial.println(" Pa");
//  Serial.print(F("Approx altitude = "));
//  Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
//  Serial.println(" m");
  lcd.setCursor(0,0);
  lcd.print("S1:");
  lcd.setCursor(3,0);
  lcd.print(s1);
  lcd.setCursor(6,0);
  lcd.print("T:");
  lcd.setCursor(8,0);
  lcd.print(t);
  lcd.setCursor(11,0);
  lcd.print("H:");
  lcd.setCursor(13,0);
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print("S2:");
  lcd.setCursor(3,1);
  lcd.print(s2);
  lcd.setCursor(6,1);
  lcd.print("S:");
  lcd.setCursor(8,1);
  lcd.print(s3);
  lcd.setCursor(11,1);
  lcd.print("G:");
  lcd.setCursor(13,1);
  lcd.print(s4);
if((s1>300)||(s2>300)||(s3>500)||(s4>500)||(s5>500)||(t>40)||(h>90))
{
      digitalWrite(buz,1);
      digitalWrite(ef,1);
      send_sms();
      upload_iot(s1,s2,s3,s4,s5,t,h,1023);
      digitalWrite(buz,0);   
  } 
else
{
  digitalWrite(buz,0);
   digitalWrite(ef,0);
}

  }
void send_sms()
{
gsm_Serial.println("Sending SMS...");
gsm_Serial.println("AT");    
delay(1000);  
gsm_Serial.println("ATE0");    
delay(1000);  
gsm_Serial.println("AT+CMGF=1");    
delay(1000);  
gsm_Serial.print("AT+CMGS=\"6301578276\"\r\n");// Replace x with mobile number
delay(1000);
//if(sts==1)
gsm_Serial.println("Abnormal AQ Parameters: ");
gsm_Serial.println("G1");
gsm_Serial.println(s1);
gsm_Serial.println("G2");
gsm_Serial.println(s2);
gsm_Serial.println("G3");
gsm_Serial.println(s3);
gsm_Serial.println("G4");
gsm_Serial.println(s4);
gsm_Serial.println("G5");
gsm_Serial.println(s5);
gsm_Serial.println("T");
gsm_Serial.println(t);
gsm_Serial.println("H");
gsm_Serial.println(h);
gsm_Serial.println("pressure");
gsm_Serial.println("1023");
gsm_Serial.println("Take necessaary Actions");
delay(100);
gsm_Serial.println((char)26);// ASCII code of CTRL+Z
delay(2000);
gsm_Serial.println("AT");    
delay(1000);  
gsm_Serial.println("ATE0");    
delay(1000);  
gsm_Serial.println("AT+CMGF=1");    
delay(1000);  
gsm_Serial.print("AT+CMGS=\"9347130040\"\r\n");// Replace x with mobile number
delay(1000);
//if(sts==1)
gsm_Serial.println("Abnormal AQ Parameters: ");
gsm_Serial.println("G1");
gsm_Serial.println(s1);
gsm_Serial.println("G2");
gsm_Serial.println(s2);
gsm_Serial.println("G3");
gsm_Serial.println(s3);
gsm_Serial.println("G4");
gsm_Serial.println(s4);
gsm_Serial.println("G5");
gsm_Serial.println(s5);
gsm_Serial.println("T");
gsm_Serial.println(t);
gsm_Serial.println("H");
gsm_Serial.println(h);
gsm_Serial.println("pressure");
gsm_Serial.println("1023");
gsm_Serial.println("Take necessaary Actions");
delay(100);
gsm_Serial.println((char)26);// ASCII code of CTRL+Z
delay(2000);
}

void wifi_init()
 {
   Serial.println("AT+RST");
  delay(2000);
  Serial.println("AT+CWMODE=1");
  delay(1000);
  Serial.print("AT+CWJAP=");
  Serial.write('"');
  Serial.print("mahesh"); // ssid/user name
  Serial.write('"');
  Serial.write(',');
  Serial.write('"');
  Serial.print("12345678"); //password
  Serial.write('"');
  Serial.println();
  delay(1000);
 }
void upload_iot(int x,int y,int z,int p,int q,int r,int s,int t) //ldr copied int to - x   and gas copied into -y
{
  
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  Serial.println(cmd);
  delay(1500);
 String getStr ="GET /update?api_key=LNNOFC6JGB5HNAU9&field1=";
  getStr += String(x);
  getStr +="&field2=";
  getStr += String(y);
  getStr +="&field3=";
  getStr += String(z);
  getStr +="&field4=";
  getStr += String(p);
  getStr +="&field5=";
  getStr += String(q);
  getStr +="&field6=";
  getStr += String(r);
  getStr +="&field7=";
  getStr += String(s);
  getStr +="&field8=";
  getStr += String(t);
  getStr += "\r\n\r\n";
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  Serial.println(cmd);
  delay(1500);
  Serial.println(getStr);
  delay(1500);
}
