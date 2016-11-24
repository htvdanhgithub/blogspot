#include <EEPROM.h>
#include "SIM900.h"
#include <SoftwareSerial.h>

//If not used, is better to exclude the HTTP library,
//for RAM saving.
//If your sketch reboots itself proprably you have finished,
//your memory available.
//#include "inetGSM.h"

//If you want to use the Arduino functions to manage SMS, uncomment the lines below.
#include "sms.h"
SMSGSM sms;

//To change pins for Software Serial, use the two lines in GSM.cpp.

//GSM Shield for Arduino
//www.open-electronics.org
//this code is based on the example of Arduino Labs.

//Simple sketch to send and receive SMS.


#define MASTER_NUM_LEN  20
#define SMS_TEXT_LEN    180

#define LED_CONNECTED   7
#define LED_RECEIVE     4
#define LED_ON_OFF      8

uint8_t sw1 = LOW;
boolean master_active = false;

char master_num[MASTER_NUM_LEN]; // array for the phone number string
char phone_num[MASTER_NUM_LEN]; // array for the phone number string
char sms_text[SMS_TEXT_LEN]; // array for the SMS text string

void Save()
{
  uint8_t start = 0;
  
  EEPROM.write(start++, sw1);

  EEPROM.write(start++, master_active);

  for(uint8_t i = 0; i < MASTER_NUM_LEN; i++)
  {
    EEPROM.write(start++, master_num[i]);
  }
}
void Load()
{
  uint8_t start = 0;

  sw1 = EEPROM.read(start++);

  master_active = EEPROM.read(start++);

  for(uint8_t i = 0; i < MASTER_NUM_LEN; i++)
  {
    master_num[i] = EEPROM.read(start++);
  }
}
void setup()
{
  pinMode(LED_CONNECTED, OUTPUT);
  pinMode(LED_ON_OFF, OUTPUT);
  pinMode(LED_RECEIVE, OUTPUT);

  while (1) {
    if (gsm.begin(9600)) {
      break;
    }
    delay(1000);
  }
  digitalWrite(LED_CONNECTED, HIGH);

  Load();

  digitalWrite(LED_ON_OFF, sw1);
  if (sw1 == LOW) {
    strcpy(sms_text, "Cong tac 1 OFF");
  } else {
    strcpy(sms_text, "Cong tac 1 ON");
  }  

  if (master_active == true) {
    sms.SendSMS(master_num, "He thong da khoi dong xong.");
    sms.SendSMS(master_num, sms_text);
    };
};

void SendSMSToMaster(char* msg) {
  if ( (master_active == true) && (strcmp(phone_num, master_num) != 0)) {
    sms.SendSMS(master_num, msg);
  }
  
}
void loop()
{
  char position;
  position = sms.IsSMSPresent(SMS_ALL);
  if (position) {
    digitalWrite(LED_RECEIVE, HIGH);
    sms.GetSMS(position, phone_num, sms_text, SMS_TEXT_LEN);
    if (strcmp(sms_text, "#M1") == 0) {
      sw1 = HIGH;
      digitalWrite(LED_ON_OFF, sw1);
      Save();
      sms.SendSMS(phone_num, "Cong tac 1 ON");
      sprintf(sms_text, "%s gui: #M1", phone_num);
      SendSMSToMaster(sms_text);
    } else if (strcmp(sms_text, "#T1") == 0) {
      sw1 = LOW;
      digitalWrite(LED_ON_OFF, sw1);
      Save();
      sms.SendSMS(phone_num, "Cong tac 1 OFF");
      sprintf(sms_text, "%s gui: #T1", phone_num);
      SendSMSToMaster(sms_text);
    } else if (strcmp(sms_text, "#Q1") == 0) {
      if (sw1 == LOW) {
        strcpy(sms_text, "Cong tac 1 OFF");
      } else {
        strcpy(sms_text, "Cong tac 1 ON");
      }
      sms.SendSMS(phone_num, sms_text);
      sprintf(sms_text, "%s gui: #Q1", phone_num);
      SendSMSToMaster(sms_text);

    } else if ((sms_text[0] == '#') && (sms_text[1] == 'R')) {
      master_active = true;
      sprintf(master_num, "+84%s", sms_text + 3);
      Save();
      sms.SendSMS(phone_num, "Dang ky master number thanh cong.");
      char s[32];
      memset(s, 0, 32);
      strncpy(s, sms_text, 32);
      sprintf(sms_text, "%s gui: %s", phone_num, s);
      SendSMSToMaster(sms_text);
    } else if (strcmp(sms_text, "#D") == 0) {
      master_active = false;
      Save();
      sms.SendSMS(phone_num, "Xoa master number thanh cong.");
      sprintf(sms_text, "%s gui: #D", phone_num);
      SendSMSToMaster(sms_text);
    } else if (strcmp(sms_text, "#H") == 0) {
      sms.SendSMS(phone_num, "1. #M1: cong tac 1 ON.\r\n2. #T1: cong tac 1 OFF.\r\n3. #Q1: Trang thai cong tac 1.\r\n4. #RXYZ: Dang ky master number XYZ.\r\n5. #D: Xoa master number.\r\n6. #H: Goi nho.");
      sprintf(sms_text, "%s gui: #H", phone_num);
      SendSMSToMaster(sms_text);
    } else {
      sms.SendSMS(phone_num, "Yeu cau khong hop le...");
      SendSMSToMaster(phone_num);
      SendSMSToMaster(sms_text);
    }

    sms.DeleteSMS(position);
    digitalWrite(LED_RECEIVE, LOW);
  }
  delay(1000);
};
