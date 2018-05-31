#include "Settings.h"

Settings::Settings(){

}

void Settings::load(){ 
  ssidLen = EEPROM.read(ssidLenAdr);
  passwordLen = EEPROM.read(passwordLenAdr);
  
  if(ssidLen < 1 || ssidLen > 32 || passwordLen < 8 && passwordLen != 0  || passwordLen > 32) reset();
  else{
    ssid = "";
    password = "";
    for(int i=0;i<ssidLen;i++) ssid += (char)EEPROM.read(ssidAdr+i);
    for(int i=0;i<passwordLen;i++) password += (char)EEPROM.read(passwordAdr+i);
    
    ssidHidden = (bool)EEPROM.read(ssidHiddenAdr);

    if((int)EEPROM.read(apChannelAdr) >= 1 && (int)EEPROM.read(apChannelAdr) <= 14){
      apChannel = (int)EEPROM.read(apChannelAdr);
    } else {
      apChannel = 1;
    }
    
    apScanHidden = (bool)EEPROM.read(apScanHiddenAdr);
    
    deauthReason = EEPROM.read(deauthReasonAdr);
    attackTimeout = eepromReadInt(attackTimeoutAdr);
    attackPacketRate = EEPROM.read(attackPacketRateAdr);
    clientScanTime = EEPROM.read(clientScanTimeAdr);
    attackEncrypted = (bool)EEPROM.read(attackEncryptedAdr);
    useLed = (bool)EEPROM.read(useLedAdr);
    channelHop = (bool)EEPROM.read(channelHopAdr);
  }
}

void Settings::reset(){
  if(debug) Serial.print("reset settings...");
  
  ssid = "AndroidAP";
  password = "deauther"; //must have at least 8 characters
  ssidHidden = true;
  apChannel = 1;

  ssidLen = ssid.length();
  passwordLen = password.length();
  
  apScanHidden = true;
    
  deauthReason = 0x01;
  attackTimeout = 5*60;
  attackPacketRate = 1000;
  clientScanTime = 5;
  attackEncrypted = true;
  useLed = true;
  channelHop = true;
  
  if(debug) Serial.println("done");
  
  save();
}

void Settings::save(){
  ssidLen = ssid.length();
  passwordLen = password.length();
  
  EEPROM.write(ssidLenAdr, ssidLen);
  EEPROM.write(passwordLenAdr, passwordLen);
  for(int i=0;i<ssidLen;i++) EEPROM.write(ssidAdr+i,ssid[i]);
  for(int i=0;i<passwordLen;i++) EEPROM.write(passwordAdr+i,password[i]);

  EEPROM.write(ssidHiddenAdr, ssidHidden);
  EEPROM.write(apChannelAdr, apChannel);

  EEPROM.write(apScanHiddenAdr, apScanHidden);
  
  EEPROM.write(deauthReasonAdr, deauthReason);

  eepromWriteInt(attackTimeoutAdr, attackTimeout);

  EEPROM.write(attackPacketRateAdr, attackPacketRate);
  EEPROM.write(clientScanTimeAdr, clientScanTime);
  EEPROM.write(attackEncryptedAdr, attackEncrypted);
  EEPROM.write(useLedAdr, useLed);
  EEPROM.write(channelHopAdr, channelHop);
  EEPROM.commit();
  
  if(debug){
    info();
    Serial.println("settings saved");
  }
}

void Settings::info(){

}

String Settings::get(){
  if(debug) Serial.println("getting settings json");
  String json = "{";
  return json;
}
