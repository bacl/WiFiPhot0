

export PATH=/opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin:$PATH
export XTENSA_TOOLS_ROOT=/opt/Espressif/crosstool-NG/builds/xtensa-lx106-elf/bin
export SDK_BASE=/opt/Espressif/ESP8266_SDK/
export SDK_EXTRA_INCLUDES=/opt/Espressif/esp_iot_sdk_novm_unpacked/usr/xtensa/XtDevTools/install/builds/RC-2010.1-win32/lx106/xtensa-elf/include/
export ESPTOOL=/opt/Espressif/esptool-py/esptool.py
export ESPPORT=/dev/ttyACM0

echo ""
echo ""
echo "Available ports:"
ls /dev/ttyU*
ls /dev/ttyA*
echo ""

export ESPPORT=$(ls /dev/ttyA*)
echo "export ESPPORT=$ESPPORT"
echo Config port:
echo $ESPPORT
 
 
