#include <EEPROM.h>
#include "SIM900.h"
#include <SoftwareSerial.h>

#define SIMULATE  1
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


#define PHONE_NUM_LEN  20
#if (SIMULATE)
  #define SMS_TEXT_LEN    60
#else
  #define SMS_TEXT_LEN    130
#endif 

#define LED_CONNECTED   7
#define LED_RECEIVE     4
#define LED_ON_OFF      8

uint8_t sw1 = LOW;
boolean master_active = false;

char master_num[PHONE_NUM_LEN]; // array for the phone number string
char phone_num[PHONE_NUM_LEN]; // array for the phone number string
char base_text[PHONE_NUM_LEN + SMS_TEXT_LEN]; // array for the SMS text string
char *sms_text = base_text + PHONE_NUM_LEN;
void Save()
{
  uint8_t start = 0;
  
  EEPROM.write(start++, sw1);

  EEPROM.write(start++, master_active);

  for(uint8_t i = 0; i < PHONE_NUM_LEN; i++)
  {
    EEPROM.write(start++, master_num[i]);
  }
}
void Load()
{
  uint8_t start = 0;

  sw1 = EEPROM.read(start++);

  master_active = EEPROM.read(start++);

  for(uint8_t i = 0; i < PHONE_NUM_LEN; i++)
  {
    master_num[i] = EEPROM.read(start++);
  }
}
#if (SIMULATE)
uint8_t ReadSerial(char* result, uint8_t size)
{
  uint8_t i = 0;
  while (1)
  {
    while (Serial.available() > 0)
    {
      char inChar = Serial.read();
      if (inChar == '\n')
      {
        result[i] = '\0';
        Serial.flush();
        return 0;
      }
      if (inChar != '\r')
      {
        if(i < size - 1)
        {
          result[i++] = inChar;
        }
        else
        {
          result[i] = '\0';
        }
      }
    }
  }
}
#endif
void GETSMS(char position, char *phone_num, char *msg, uint8_t len)
{
#if (SIMULATE)
  ReadSerial(msg, len);
  strcpy(phone_num, "+84000000000");
#else
  sms.GetSMS(position, phone_num, msg, len);
#endif  
}
void SENDSMS(char *phone_num, char *msg)
{
#if (SIMULATE)
  Serial.println("<<<<<<<<<<");
  Serial.print(phone_num);
  Serial.print(": ");
  Serial.println(msg);
  Serial.println(">>>>>>>>>>\r\n");
#else
  sms.SendSMS(phone_num, msg);
#endif  
}
void setup()
{
  pinMode(LED_CONNECTED, OUTPUT);
  pinMode(LED_ON_OFF, OUTPUT);
  pinMode(LED_RECEIVE, OUTPUT);

#if (SIMULATE)
  Serial.begin(9600);
#else
  while (1) 
  {
    if (gsm.begin(9600)) 
    {
      break;
    }
    delay(1000);
  }
#endif  
  digitalWrite(LED_CONNECTED, HIGH);

  Load();

  digitalWrite(LED_ON_OFF, sw1);
  if (sw1 == LOW) 
  {
    strcpy(sms_text, "Cong tac 1 OFF");
  } 
  else 
  {
    strcpy(sms_text, "Cong tac 1 ON");
  }  

  if (master_active == true) 
  {
    SENDSMS(master_num, "He thong da khoi dong xong.");
    SENDSMS(master_num, sms_text);
    };
};

void SendSMSToMaster(char* msg) 
{
  if ((master_active == true) && (strcmp(phone_num, master_num) != 0)) 
  {
    SENDSMS(master_num, msg);
  }
  
}
void loop()
{
  char temp_text[60];
  char position;
#if (SIMULATE)
  position = 1;
#else
  position = sms.IsSMSPresent(SMS_ALL);
#endif
  if (position) 
  {
    digitalWrite(LED_RECEIVE, HIGH);
    GETSMS(position, phone_num, sms_text, SMS_TEXT_LEN);

    if (strcmp(sms_text, "#M1") == 0) 
    {
      sw1 = HIGH;
      digitalWrite(LED_ON_OFF, sw1);
      Save();
      SENDSMS(phone_num, "Cong tac 1 ON");
    }
    else if (strcmp(sms_text, "#T1") == 0) 
    {
      sw1 = LOW;
      digitalWrite(LED_ON_OFF, sw1);
      Save();
      SENDSMS(phone_num, "Cong tac 1 OFF");
    } 
    else if (strcmp(sms_text, "#Q1") == 0) 
    {
      if (sw1 == LOW) 
      {
        strcpy(sms_text, "Cong tac 1 hien dang OFF");
      } else {
        strcpy(sms_text, "Cong tac 1 hien dang ON");
      }
      SENDSMS(phone_num, sms_text);
    }
    else if ((sms_text[0] == '#') && (sms_text[1] == 'R')) 
    {
      master_active = true;
      sprintf(master_num, "+84%s", sms_text + 3);
      Save();
      sprintf(temp_text, "Dang ky master number %s thanh cong.", master_num);
      SENDSMS(phone_num, temp_text);
    } 
    else if (strcmp(sms_text, "#D") == 0) 
    {
      master_active = false;
      Save();
      sprintf(temp_text, "Xoa master number %s thanh cong.", master_num);
      SENDSMS(phone_num, temp_text);
    } 
    else if (strcmp(sms_text, "#N") == 0) 
    {
      if (master_active == false)
      {
        SENDSMS(phone_num, "Master number bi tat.");
      }
      else
      {
        sprintf(temp_text, "Master number %s dang hoat dong.", master_num);
        SENDSMS(phone_num, temp_text);
      }
    } 
    else if (strcmp(sms_text, "#H") == 0) 
    {
      SENDSMS(phone_num, "#M1: cong tac 1 ON. #T1: cong tac 1 OFF. #Q1: Trang thai cong tac 1. #Rxyz: Dang ky master number xyz. #D: Xoa master number. #N: Trang thai master number. #H: Goi nho.");
    } 
    else 
    {
      SENDSMS(phone_num, "Yeu cau khong hop le...");
    }

    sprintf(base_text, "%s gui: %s", phone_num, sms_text);
    SendSMSToMaster(base_text);

    sms.DeleteSMS(position);
    digitalWrite(LED_RECEIVE, LOW);
  }
  delay(1000);
};
