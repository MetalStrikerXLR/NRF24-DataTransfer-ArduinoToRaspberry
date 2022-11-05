from __future__ import print_function
import time
from RF24 import *
import RPi.GPIO as GPIO
irq_gpio_pin = None

########### USER CONFIGURATION ###########
# CE Pin, CSN Pin, SPI Speed
# CE Pin uses GPIO number with BCM and SPIDEV drivers, other platforms use their own pin numbering
# CS Pin addresses the SPI bus number at /dev/spidev<a>.<b>
# ie: RF24 radio(<ce_pin>, <a>*10+<b>); spidev1.0 is 10, spidev1.1 is 11, spidev0.0 is 0 etc..
radio = RF24(22, 0);  

# Radio pipe addresses
pipes = [0xF0F0F0F0E1, 0xF0F0F0F0D2]    # This address should be same on transmission side (Arduino)
print('pyRF24/examples/pingpair_dyn/')

#  Initialize nRF24L01
radio.begin()
radio.setAutoAck(False);
radio.enableDynamicPayloads()   # Set Dynamic Payload capability
radio.setRetries(5,15)          # Set Retries

# Print Radio details for confirmation
radio.printDetails()

radio.openReadingPipe(1, pipes[0]) # Setting the address
radio.startListening()
    
# Loop to check incomming data
while True: 
    if radio.available():
        while radio.available():
            len = radio.getDynamicPayloadSize()
            receive_payload = radio.read(len)

            try:
                receive_payload.decode('utf-8')

                # print received data
                print(receive_payload)

            except Exception as e:
                pass

