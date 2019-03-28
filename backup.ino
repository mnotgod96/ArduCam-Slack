//trigBoard Sample Code with Arducam Uploading to server and posting to slack
// 3/29/17  Kevin Darrah
// RELEASED

// Includes - may not all be needed
#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson
#include "Wire.h"
#include <ArduCAM.h>// Arducam library //https://github.com/ArduCAM/Arduino
#include <SPI.h>
#include "memorysaver.h"
#include <time.h>

extern const unsigned char caCert[] PROGMEM;
extern const unsigned int caCertLen;

//camera variables
const int CS = 16;// NOTE THIS IS SHARED WITH EXT WAKE PIN!!!

ArduCAM myCAM( OV2640, CS );//setup for ArduCam mini 2MP


// PINS!!!
#define LEDpin 0
#define EXTWAKEpin 16 

//FUNCTIONS
void PushSlack(const char *MessageBody, const char *MessageTitle, const char *MessageType, ...);//for slack messages

void saveConfigCallback ();
boolean WiFiConnection();

//camera functions
void takePicture();
void uploadPicture();

char filename[30];//used for the name we save the picture as

//globals for credentials
char tokenKey[100];
char trigBoardName[40];
char triggerMessage[100];
char fileURL[100];//where we send the image - new for the Arducam version

boolean resetFlag = false;

//flag for saving data
bool shouldSaveConfig = false;

boolean externalWake = false;// to figure out who woke up the board

void setup() {
  Serial.begin(115200);//debug
  strcpy(tokenKey,"https://hooks.slack.com/services/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");
  strcpy(trigBoardName,"myLocker");
  strcpy(triggerMessage,"myLocker triggered");
  strcpy(fileURL,"http://mnotgod.a2hosted.com/testForCapture/");
  takePicture();//take the picture
  WiFiConnection();//connect and send data (in provisioning tab)

}

void loop() {
  
}
