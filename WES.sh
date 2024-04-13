# PATH to project:
cd /home/teo/Documents/WES
# Environmental variables:
. /home/teo/esp/v5.0.4/esp-idf/export.sh
# Build:
idf.py build
# FLASH:
idf.py -p /dev/ttyUSB1 flash
# Monitor output:
# idf.py -p /dev/ttyUSB1 monitor