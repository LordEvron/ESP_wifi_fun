# ESP8266 Deauther and SSID flooding. 
Wide band Deauthentication attack and other attacks using an ESP8266.

This is a derivation of the work from spacehuhn and other sources!! (https://github.com/spacehuhn/esp8266_deauther) With his code, you could basically select one client from a list and manually deauthenticate it. 

I tried to enhance his code by making the system deauthenticate all the clients that are around. Also I added a new attack mode and is a fake SSID flooding. Basically it creates 150 Fake networks. However I did not want to spent hours on that, so i just added few more function and called the one that i needed from the main, leaving the other code moslty untouched. This lead to shitty looking code, but that works.

THIS IS FOR TESTING PURPOSE ONLY. I AM not RESPONSIBLE FOR ANY MISSUSE OF THE CODE. USE IT ONLY IN ISOLATED ENVIRONMENT AND FOR TESTING AND UNDERSTANDING THE 802.11 PROTOCOL. 
The effect of this code can be easily reproduced with a simple command in AirCrack-ng tool, so there is nothing new on the table. Just another way to do it. 



### What it is

Is a device that can perform TWO type of attacks:
The device does not need any controll or start. Just power it up and it start working right away. By having GPIO16 to GND or to VCC you can select one of the two attack modes:

	1- Wide Band Death attack (Selected with GPIO16 to GND) ... This will make deautenticate all the client within few meters from the devices. Until the device is powered, no client is able to connect to any network.
	2- Fake SSID flooder (Selected with the GPIO16 to VCC) ... This will create 150 different fake access points. The fake access points will be visible from any client around it.   

### How to use it.
	0- Flash the code to a ESP8266 device
	1- Connect GPIO16 to GND or VCC based on the type of attack you want to perform.
	2- Power up the ESP8266. 
	3- Look at the results. 


### FAQ
General:
	Q.This code looks like SHIT, why? --> A. Because it	was a quick test, i just twicked existing code enough to make it work! Mostly of the functions can be removed, but i do not care, because I am not bringing this project forward. 
	Q.How to flash the code? --> A. Look at spacehuhn readme or at my blog (https://lukelogbook.tech/2018/02/08/flash-code-to-esp8266-esp-12-module-step-by-step-guide/)
	Q.The ESP8266 is not able to sent deauthentication packages --> A. Make sure that you installed the correct set of libraries and you are using the board manager version 2.0. Other version does not include the "wifi_send_pkt_freedom()" function (wich is required by this attacks)
	Q. I get the warning "Low memory available, stability problems may occur" when i compile the code --> A. You are running out of RAM and this can lead to system restart. Reduce the footprint of the function. Mostly likely you addded more access points, or more MAc addresses. 
	Q. Can i reuse this code? --> A. From my side, yes, do whatever you want. However, you should mainly ask spacehuhn, since he wrote a lot of the code.
Death attack: 
	Q. Deathentication does not work! --> A. notice that the device only work with 2.4GHz and not with 5GHz!
SSID Flooding: 
	Q. I only See less than 150 networks. -->A. The device has limited speed capabilities. It take around 1.3 seconds to loop around all 150 SSIDs. This means that the client will get 2 beacon every 1.3 seconds for each fake SSID. This 10 time lower frequencis than what is normal.
