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
#define SMS_TEXT_LEN    40
#endif

#define LED_CONNECTED   7  // Green
#define LED_RECEIVED    4  // Red
#define LED_BAT_TAT     8  // Blue
// #define SW_MANUAL    15  // Manual sw

#if (DEBUG)
char* STR_HELP = "";
#else
#if (FOR_MOTORBIKE)
char* STR_HELP = "#K1: KHOA nguon. #M1: MO nguon. #Q1: Trang thai nguon. #Rxyz: Dang ky SDT may chu xyz. #D: Xoa SDT may chu. #N: Trang thai SDT may chu. #H: Tro giup.";
#else
char* STR_HELP = "#M1: BAT thiet bi. #T1: TAT thiet bi. #Q1: Trang thai thiet bi. #Axyz: dat ten thiet bi xyz. #Rxyz: Dang ky SDT may chu xyz. #D: Xoa SDT may chu. #N: Trang thai SDT may chu. #H: Tro giup.";
#endif
#endif

uint8_t sw1 = LOW;
boolean master_active = false;
#if !(FOR_MOTORBIKE)
#define DEVICE_LEN    16
boolean device_name_active = false;
char device_name[DEVICE_LEN] =    "O cam 1";
#endif

#define BASE_TEXT_LEN (PHONE_NUM_LEN + SMS_TEXT_LEN)

char master_num[PHONE_NUM_LEN]; // array for the phone number string
char phone_num[PHONE_NUM_LEN]; // array for the phone number string
char base_text[BASE_TEXT_LEN]; // array for the SMS text string
char *sms_text = base_text + PHONE_NUM_LEN;

uint32_t second_count = 0;
void Save()
{
  uint8_t start = 0;

//  EEPROM.write(start++, sw1);
#if !(FOR_MOTORBIKE)
  EEPROM.write(start++, device_name_active);

  for (uint8_t i = 0; i < DEVICE_LEN; i++)
  {
    EEPROM.write(start++, device_name[i]);
  }
#endif

  EEPROM.write(start++, master_active);

  for (uint8_t i = 0; i < PHONE_NUM_LEN; i++)
  {
    EEPROM.write(start++, master_num[i]);
  }
}
void Load()
{
  uint8_t start = 0;

//  sw1 = EEPROM.read(start++);
#if !(FOR_MOTORBIKE)
  device_name_active = EEPROM.read(start++);

  for (uint8_t i = 0; i < DEVICE_LEN; i++)
  {
    device_name[i] = EEPROM.read(start++);
  }
#endif
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
  strncpy(phone_num, "+84000000000", PHONE_NUM_LEN - 1);
  phone_num[PHONE_NUM_LEN - 1] = 0;
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
      Serial.println("Invalid");
#endif  
      return false;
    }
    i++;

    if (i >= PHONE_NUM_LEN) {
#if (DEBUG)
      Serial.println("Invalid");
#endif  
      return false;      
    }
  }
  if (i < 10) {
#if (DEBUG)
    Serial.println("Invalid");
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

#if !(FOR_MOTORBIKE)
  if (device_name_active == false) {
    strncpy(device_name, "O cam 1", DEVICE_LEN - 1); 
    device_name[DEVICE_LEN - 1] = 0; 
  }
#if (DEBUG)
  Serial.print("Device name: ");
  Serial.println(device_name);
#endif 
#endif

  
  if (master_active == true)
  {
    if (is_valid_phone(master_num) == true) {
      SENDSMS(master_num, "He thong da khoi dong xong");

#if (FOR_MOTORBIKE)
      snprintf(sms_text, SMS_TEXT_LEN, "Xe da duoc %s nguon", (sw1 == LOW) ? "MO" : "KHOA");
#else
      snprintf(sms_text, SMS_TEXT_LEN,  "%s duoc %s", device_name, (sw1 == LOW) ? "TAT" : "BAT");
#endif
      SENDSMS(master_num, sms_text);
    } else {
      master_active = false;
    }
  };
#if (DEBUG)
  Serial.print("Master number: ");
  Serial.println(master_num);
#endif 
};

void SendSMSToMaster(char* msg)
{
  if ((master_active == true) && (strstr(phone_num, master_num + 1) == NULL))
  {
    SENDSMS(master_num, msg);
  }

}

#define TEMP_TEXT_LEN 60
void loop()
{
  char temp_text[TEMP_TEXT_LEN];
  char position;
  uint8_t sms_len = 0;
#if (SIMULATE)
  position = 1;
#else
  position = sms.IsSMSPresent(SMS_UNREAD);
#if (DEBUG)
  snprintf(temp_text, TEMP_TEXT_LEN, "Received position = %d", position);
  Serial.println(temp_text);
#endif  

#endif
  if ((char)position > 0)
  {
#if (DEBUG)
  snprintf(temp_text, TEMP_TEXT_LEN, "Received position = %d", position);
  Serial.println(temp_text);
#endif     
    digitalWrite(LED_RECEIVED, HIGH);
    memset(sms_text, 0, SMS_TEXT_LEN);
    GETSMS(position, phone_num, sms_text, SMS_TEXT_LEN);
    sms_len = strlen(sms_text);
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
        snprintf(temp_text, TEMP_TEXT_LEN, "%s hien da duoc BAT", device_name);
        SENDSMS(phone_num, temp_text);
#endif
      } else {
        sw1 = HIGH;
        digitalWrite(LED_BAT_TAT, sw1);
        Save();
#if (FOR_MOTORBIKE)
        SENDSMS(phone_num, "Xe da duoc KHOA nguon");
#else
        snprintf(temp_text, TEMP_TEXT_LEN, "%s duoc BAT", device_name);
        SENDSMS(phone_num, temp_text);
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
        snprintf(temp_text, TEMP_TEXT_LEN, "%s hien da duoc TAT", device_name);
        SENDSMS(phone_num, temp_text);
#endif
      } else {
        sw1 = LOW;
        digitalWrite(LED_BAT_TAT, sw1);
        Save();
#if (FOR_MOTORBIKE)
        SENDSMS(phone_num, "Xe da duoc MO nguon");
#else
        snprintf(temp_text, TEMP_TEXT_LEN, "%s duoc TAT", device_name);
        SENDSMS(phone_num, temp_text);
#endif
      }
    }
    else if (strcmp(sms_text, "#Q1") == 0)
    {
#if (FOR_MOTORBIKE)
      snprintf(temp_text, TEMP_TEXT_LEN, "Xe dang duoc %s nguon", (sw1 == LOW) ? "MO" : "KHOA");
#else
      snprintf(temp_text, TEMP_TEXT_LEN, "%s hien dang duoc %s", device_name, (sw1 == LOW) ? "TAT" : "BAT");
#endif
      SENDSMS(phone_num, temp_text);
    }
    else if ((sms_text[0] == '#') && (sms_text[1] == 'R') && (sms_len > 2))
    {
      if (is_valid_phone(sms_text + 2) == false) {
        snprintf(temp_text, TEMP_TEXT_LEN, "SDT %s khong hop le.", sms_text + 2);
      } 
      else
      {
        master_active = true;
        snprintf(master_num, PHONE_NUM_LEN, "%s", sms_text + 2);
        Save();
        snprintf(temp_text, TEMP_TEXT_LEN, "Dang ky SDT may chu %s thanh cong", master_num);
      }
      
      SENDSMS(phone_num, temp_text);
    }
    else if (strcmp(sms_text, "#D") == 0)
    {
      master_active = false;
      Save();
      snprintf(temp_text, TEMP_TEXT_LEN, "Xoa SDT may chu %s thanh cong", master_num);
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
        snprintf(temp_text, TEMP_TEXT_LEN, "SDT may chu %s dang hoat dong", master_num);
        SENDSMS(phone_num, temp_text);
      }
    }
#if !(FOR_MOTORBIKE)
    else if ((sms_text[0] == '#') && (sms_text[1] == 'A') && (sms_len > 2))
    {
      strncpy(device_name, sms_text + 2, DEVICE_LEN - 1);
      device_name[DEVICE_LEN - 1] = 0;
      device_name_active = true;
      Save();
      snprintf(temp_text, TEMP_TEXT_LEN, "Thiet bi duoc dat ten: %s", device_name);
      SENDSMS(phone_num, temp_text);
    }
#endif
    else if ((sms_text[0] == '#') && (sms_text[1] == 'S') && (sms_len > 2))
    {
      char *s = strchr(sms_text, ':');
      if (s == NULL)
      {
        SENDSMS(phone_num, "Yeu cau khong hop le...");
      }
      else
      {
        sms_text[s - sms_text] = 0;
        SENDSMS(sms_text + 2, s + 1);
        sms_text[s - sms_text] = ':';
      }
    }
    else if ((sms_text[0] == '#') && (sms_text[1] == 'C') && (sms_len > 2))
    {
      CALL(sms_text + 2);
    }
    else if (strcmp(sms_text, "#H") == 0)
    {
      SENDSMS(phone_num, STR_HELP);
    }
    else
    {
      SENDSMS(phone_num, "Yeu cau khong hop le...");
    }

    snprintf(base_text, BASE_TEXT_LEN, "%s gui: %s", phone_num, sms_text);
    SendSMSToMaster(base_text);
__exit:
    char ret = sms.DeleteSMS(position);
#if (DEBUG)
    if (ret == 1) {
      snprintf(temp_text, TEMP_TEXT_LEN, "Sucessfully deleted position = %d", position);
    } else {
      snprintf(temp_text, TEMP_TEXT_LEN, "NOT sucessfully deleted position = %d", position);
    }
    Serial.println(temp_text);
#endif  
    digitalWrite(LED_RECEIVED, LOW);
  }
  delay(1000);

  if (second_count == 604800) {// one week  60*60*24*7
    SendSMSToMaster("Toi van khoe ne. Ong/Ba chu co khoe khong?");
    second_count = 0;
  }
  second_count++;
#if (DEBUG)
    snprintf(temp_text, TEMP_TEXT_LEN, "second_count: %ld", second_count);
    Serial.println(temp_text);
#endif
};
