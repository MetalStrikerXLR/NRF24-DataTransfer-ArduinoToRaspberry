>>>> Copy code in Raspberry Pi
>>>> Run following commands in terminal:


1- sudo apt-get update

2- wget http://tmrh20.github.io/RF24Installer/RPi/install.sh

3- chmod +x install.sh

4- cd rf24libs/RF24/examples_linux

5- make


>>>> Close terminal and open a fresh one again. Run following commands:
>>>> you can follow this guide as well: https://github.com/nRF24/RF24/blob/master/docs/python_wrapper.md

6- sudo apt-get install python3-dev libboost-python-dev python3-pip python3-rpi.gpio

7- python3 -m pip install --upgrade pip setuptools

8- sudo ln -s $(ls /usr/lib/$(ls /usr/lib/gcc | tail -1)/libboost_python3*.so | tail -1) /usr/lib/$(ls /usr/lib/gcc | tail -1)/libboost_python3.so

>>>> Navigate to pyRF24 directory in the RF24 cloned repository

9- python3 setup.py build (will take some time)

10- sudo python3 setup.py install (will take some time)

>>>> Run code