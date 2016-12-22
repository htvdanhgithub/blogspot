#include <EEPROM.h>
#include "SIM900.h"
#include "call.h"
#include <SoftwareSerial.h>

#define SIMULATE        0
#define FOR_MOTORBIKE   0
#define DEBUG           0


//If not used, is better to exclude the HTTP library,
//for RAM saving.
//If your sketch reboots itself proprably you have finished,
//your memory available.
//#include "inetGSM.h"

//If you want to use the Arduino functions to manage SMS, uncomment the lines below.
#include "sms.h"
SMSGSM sms;
CallGSM call;
//To change pins for Software Serial, use the two lines in GSM.cpp.

//GSM Shield for Arduino
//www.open-electronics.org
//this code is based on the example of Arduino Labs.

//Simple sketch to send and receive SMS.


#define PHONE_NUM_LEN  20
#if (SIMULATE)
#define SMS_TEXT_LEN    40
#else
#define SMS_TEXT_LEN    80
#endif

#define LED_CONNECTED   7  // Green
#define LED_RECEIVED    4  // Red
#define LED_BAT_TAT      8  // Blue
// #define SW_MANUAL      15  // Manual sw

#if (DEBUG)
char* STR_HELP = "";
#else
#if (FOR_MOTORBIKE)
char* STR_HELP = "#K1: KHOA nguon. #M1: MO nguon. #Q1: Trang thai nguon. #Rxyz: Dang ky SDT may chu xyz. #D: Xoa SDT may chu. #N: Trang thai SDT may chu. #H: Goi nho.";
#else
char* STR_HELP = "#M1: O cam 1 BAT. #T1: O cam 1 TAT. #Q1: Trang thai o cam 1. #Rxyz: Dang ky SDT may chu xyz. #D: Xoa SDT may chu. #N: Trang thai SDT may chu. #H: Goi nho.";
#endif
#endif

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

  for (uint8_t i = 0; i < PHONE_NUM_LEN; i++)
  {
    EEPROM.write(start++, master_num[i]);
  }
}
void Load()
{
  uint8_t start = 0;

  sw1 = EEPROM.read(start++);
  master_active = EEPROM.read(start++);

  for (uint8_t i = 0; i < PHONE_NUM_LEN; i++)
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
        if (i < size - 1)
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
void CALL(char *phone_num)
{
#if (SIMULATE)
  Serial.println("<<<<<<<<<<");
  Serial.print("Calling to ");
  Serial.print(phone_num);
  Serial.println(">>>>>>>>>>\r\n");
#else
#if (DEBUG)
  Serial.println("<<<<<<<<<<");
  Serial.print("Calling to ");
  Serial.print(phone_num);
  Serial.println(">>>>>>>>>>\r\n");
#endif  
  call.Call(phone_num);
#endif
}

void GETSMS(char position, char *phone_num, char *msg, uint8_t len)
{
#if (SIMULATE)
  ReadSerial(msg, len);
  strcpy(phone_num, "+84000000000");
#else
  sms.GetSMS(position, phone_num, msg, len);
#if (DEBUG)
  Serial.println("<<<<<<<<<<Received from:");
  Serial.print(phone_num);
  Serial.print(": ");
  Serial.println(msg);
  Serial.println(">>>>>>>>>>\r\n");
#endif
#endif

}
void SENDSMS(char *phone_num, char *msg)
{
  char ret;
#if (SIMULATE)
  Serial.println("<<<<<<<<<<");
  Serial.print(phone_num);
  Serial.print(": ");
  Serial.println(msg);
  Serial.println(">>>>>>>>>>\r\n");
#else
  ret = sms.SendSMS(phone_num, msg);
#if (DEBUG)
  if (ret == 1) {
    Serial.println("<<<<<<<<<<Successfully Sent to:");
  } else {
    Serial.println("<<<<<<<<<<Not successfully Sent to:");
  }
  Serial.print(phone_num);
  Serial.print(": ");
  Serial.println(msg);
  Serial.println(">>>>>>>>>>\r\n");
#endif
#endif
}
bool is_valid_phone(const char* phone_num) {
#if (DEBUG)
  Serial.println(phone_num);
#endif  
  uint8_t i = 0;
  while (phone_num[i] != 0) {
    if (!((phone_num[i] == '+') || ((phone_num[i] >= '0') && (phone_num[i] <= '9')))) {
#if (DEBUG)
      Serial.println("Not digit");
#endif  
      return false;
    }
    i++;
  }
  if (i < 10) {
#if (DEBUG)
    Serial.println("< 10");
#endif  
    return false;
  }
#if (DEBUG)
  Serial.println("Valid");
#endif  
  return true;
}
void setup()
{
  pinMode(LED_CONNECTED, OUTPUT);
  pinMode(LED_BAT_TAT, OUTPUT);
  pinMode(LED_RECEIVED, OUTPUT);
//  pinMode(SW_MANUAL, INPUT);

  digitalWrite(LED_RECEIVED, HIGH);
#if (SIMULATE)
  Serial.begin(9600);
#else
#if (DEBUG)
  Serial.begin(9600);
#endif

  while (1)
  {
    if (gsm.begin(9600))
    {
      break;
    }
    delay(1000);
  }
#endif
  digitalWrite(LED_RECEIVED, LOW);
  delay(1000);
#if (DEBUG)
  Serial.println("Connected.");
#endif  
  digitalWrite(LED_CONNECTED, HIGH);

  Load();
#if (FOR_MOTORBIKE)
  sw1 = LOW;
#endif
  digitalWrite(LED_BAT_TAT, sw1);

  if (master_active == true)
  {
    SENDSMS(master_num, "He thong da khoi dong xong");

#if (FOR_MOTORBIKE)
    sprintf(sms_text, "Xe da duoc %s nguon", (sw1 == LOW) ? "MO" : "KHOA");
#else
    sprintf(sms_text, "O cam 1 %s", (sw1 == LOW) ? "TAT" : "BAT");
#endif
    SENDSMS(master_num, sms_text);
  };
};

void SendSMSToMaster(char* msg)
{
  if ((master_active == true) && (strstr(phone_num, master_num + 1) == NULL))
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
  position = sms.IsSMSPresent(SMS_UNREAD);
#if (DEBUG)
  sprintf(temp_text, "Received position = %d", position);
  Serial.println(temp_text);
#endif  

#endif
  if ((char)position > 0)
  {
#if (DEBUG)
  sprintf(temp_text, "Received position1 = %d", position);
  Serial.println(temp_text);
#endif     
    digitalWrite(LED_RECEIVED, HIGH);
    memset(sms_text, 0, SMS_TEXT_LEN);
    GETSMS(position, phone_num, sms_text, SMS_TEXT_LEN);
#if (DEBUG)
  Serial.print("Received sms: ");
  Serial.println(phone_num);
  Serial.println(sms_text);
#endif  
    if (is_valid_phone(phone_num) == false) {
      goto __exit;
    }

#if (FOR_MOTORBIKE)
    if (strcmp(sms_text, "#K1") == 0)
#else
    if (strcmp(sms_text, "#M1") == 0)
#endif
    {
      if (sw1 == HIGH)
      {
#if (FOR_MOTORBIKE)
        SENDSMS(phone_num, "Xe da duoc KHOA nguon");
#else
        SENDSMS(phone_num, "O cam 1 hien dang BAT");
#endif
      } else {
        sw1 = HIGH;
        digitalWrite(LED_BAT_TAT, sw1);
        Save();
#if (FOR_MOTORBIKE)
        SENDSMS(phone_num, "Xe da duoc KHOA nguon");
#else
        SENDSMS(phone_num, "O cam 1 BAT");
#endif
      }
    }
#if (FOR_MOTORBIKE)
    else if (strcmp(sms_text, "#M1") == 0)
#else
    else if (strcmp(sms_text, "#T1") == 0)
#endif
    {
      if (sw1 == LOW)
      {
#if (FOR_MOTORBIKE)
        SENDSMS(phone_num, "Xe da duoc MO nguon");
#else
        SENDSMS(phone_num, "O cam 1 hien dang TAT");
#endif
      } else {
        sw1 = LOW;
        digitalWrite(LED_BAT_TAT, sw1);
        Save();
#if (FOR_MOTORBIKE)
        SENDSMS(phone_num, "Xe da duoc MO nguon");
#else
        SENDSMS(phone_num, "O cam 1 TAT");
#endif
      }
    }
    else if (strcmp(sms_text, "#Q1") == 0)
    {
#if (FOR_MOTORBIKE)
      sprintf(temp_text, "Xe dang duoc %s nguon", (sw1 == LOW) ? "MO" : "KHOA");
#else
      sprintf(temp_text, "O cam 1 hien dang %s", (sw1 == LOW) ? "TAT" : "BAT");
#endif
      SENDSMS(phone_num, temp_text);
    }
    else if ((sms_text[0] == '#') && (sms_text[1] == 'R'))
    {
      master_active = true;
      sprintf(master_num, "%s", sms_text + 2);
      Save();
      sprintf(temp_text, "Dang ky SDT may chu %s thanh cong", master_num);
      SENDSMS(phone_num, temp_text);
    }
    else if (strcmp(sms_text, "#D") == 0)
    {
      master_active = false;
      Save();
      sprintf(temp_text, "Xoa SDT may chu %s thanh cong", master_num);
      SENDSMS(phone_num, temp_text);
    }
    else if (strcmp(sms_text, "#N") == 0)
    {
      if (master_active == false)
      {
        SENDSMS(phone_num, "SDT may chu bi tat.");
      }
      else
      {
        sprintf(temp_text, "SDT may chu %s dang hoat dong", master_num);
        SENDSMS(phone_num, temp_text);
      }
    }
    else if (strcmp(sms_text, "#H") == 0)
    {
      SENDSMS(phone_num, STR_HELP);
    }
    else
    {
      SENDSMS(phone_num, "Yeu cau khong hop le...");
    }

    sprintf(base_text, "%s gui: %s", phone_num, sms_text);
    SendSMSToMaster(base_text);
__exit:
    char ret = sms.DeleteSMS(position);
#if (DEBUG)
    if (ret == 1) {
      sprintf(temp_text, "Sucessfully deleted position = %d", position);
    } else {
      sprintf(temp_text, "NOT sucessfully deleted position = %d", position);
    }
    Serial.println(temp_text);
#endif  
    digitalWrite(LED_RECEIVED, LOW);
  }
  delay(1000);
};
