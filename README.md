WiFiPhot0
===================================

Firmware for [esp8266](https://nurdspace.nl/ESP8266) to remote control over wifi a camera's shutter. 
 
For more details on the development I explain it over in my blog mkthings on the post WiFi Remote Shutter Release //insert link// 


Features
--------------
- Remote trigger shutter over wifi
- Timer Shutter
- Intervalometer  (useful for time lapses) 
 


Flash firmware
----

1. If needed, Setup the build environment for the esp8266. Follow [this tuturial](https://github.com/esp8266/esp8266-wiki/wiki/Toolchain)  
2. git clone this repository
3. `make`
3. `make flash`
4. `make htmlflash`



How to use it
---

0. Connect your camera to the esp8266 circuit (this will be different for each case, [check how I did it](mkthings.wordpress.com) )
1. Connect for mobile to the hotspot created the esp8266 default ssid 
2. On your browser, go to [http://192.164.4.1](http://192.164.4.1 "http://192.164.4.1") 
3. Click on the shutter button to take a photo.

![](https://raw.githubusercontent.com/bacl/WiFiPhot0/art/ui/Screenshot.png)
 

### Change Wifi Settings ###
1. Connect for mobile to the hotspot created the esp8266 default ssid 
2. On your browser go, to [http://192.164.4.1/config.tpl](http://192.164.4.1/config.tpl "http://192.164.4.1/config.tpl")
3. Modify SSID and Key pass to your chose and click Apply

![](https://raw.githubusercontent.com/bacl/WiFiPhot0/art/ui/Screenshot-2.png)

Circuit Diagram
----
**Disclamer:** just a simple diagram that I sketched, my knowledge of circuits is basic.

![](https://raw.githubusercontent.com/bacl/WiFiPhot0/art/circuit/Picture1.png)

- A. Sockect to connect the esp8266 module
- B. Jumper to enable firmware upload
- C. Serial data pins
- D. Power pins (3.3V)
- E. Camera shutter pins

Designed using [Fritzing App](http://fritzing.org/download/)

 

About
---- 

I developed back in December 2014.

It was built on top of `esphttpd` by sprite_tm at
[http://git.spritesserver.nl/esphttpd.git/](http://git.spritesserver.nl/esphttpd.git/ "http://git.spritesserver.nl/esphttpd.git/") 
The `esphttpd` base code is from December 2014


License
-------
"[THE BEER-WARE LICENSE](https://en.wikipedia.org/wiki/Beerware)"