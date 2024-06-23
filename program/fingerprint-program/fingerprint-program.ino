#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Fingerprint.h>


#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__)
SoftwareSerial mySerial(2, 3);
#else
#define mySerial Serial1
#endif
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);


#define RELAY_1 4
#define BUZZER_1 5




void setup()
{
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  digitalWrite(RELAY_1, 1);
  digitalWrite(BUZZER_1, 0);  
  Serial.begin(9600);
  Serial.println("LABEL,Name,Info");
  while (!Serial);  // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit finger detect test");
  // set the data rate for the sensor serial port
  finger.begin(57600);
  delay(5);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
  finger.getTemplateCount();
  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
    Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
}


void loop()                     // run over and over again
{
  getFingerprintID();
  delay (1000);
}


uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }


  // OK success!


  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }


  // OK converted!
 
 
  p = finger.fingerFastSearch();
 
  //percabangan logika buka tutup brankas
  if(p == FINGERPRINT_OK && finger.fingerID == 1)
    {
      digitalWrite(BUZZER_1,1);
      delay(200);
      digitalWrite(BUZZER_1,0);
      Serial.print("DATA,");
      Serial.print("David Erikson Simbolon");
      Serial.print(",");
      Serial.println("brankas terbuka");
      delay(2000);
      digitalWrite(RELAY_1,0);
      delay(7000);
      digitalWrite(RELAY_1,1);
    }      
  else if(p == FINGERPRINT_OK && finger.fingerID == 2)
    {
      digitalWrite(BUZZER_1,1);
      delay(200);
      digitalWrite(BUZZER_1,0);
      Serial.print("DATA,");
      Serial.print("David Erikson Simbolon");
      Serial.print(",");
      Serial.println("brankas terbuka");
      delay(2000);
      digitalWrite(RELAY_1,0);
      delay(7000);
      digitalWrite(RELAY_1,1);
    }
  else if (p == FINGERPRINT_OK && finger.fingerID == 3)
    {
      digitalWrite(BUZZER_1,1);
      delay(200);
      digitalWrite(BUZZER_1,0);
      Serial.print("DATA,");
      Serial.print("David Erikson Simbolon");
      Serial.print(",");
      Serial.println("brankas terbuka");
      delay(2000);
      digitalWrite(RELAY_1,0);
      delay(7000);
      digitalWrite(RELAY_1,1);
    }
  //================================================================================================
  //================================================================================================
  //================================================================================================


  else if (p == FINGERPRINT_NOTFOUND)
    {
      digitalWrite(RELAY_1,1);      
      digitalWrite(BUZZER_1,1);
      delay(500);
      digitalWrite(BUZZER_1,0);
      delay(500);
      digitalWrite(BUZZER_1,1);
      Serial.println("sidik jari salah");
      delay(1000);
      digitalWrite(BUZZER_1,0);
    }
  //=====================================================================================================
  //=====================================================================================================  
  //=====================================================================================================
 
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);


  return finger.fingerID;
}


// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;


  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;


  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;


  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  return finger.fingerID;
}
