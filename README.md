
# MPU6050-display-rotate<br />
Pc display automatic ratation using arduino and MPU6050 accelerometer<br />
this project was adapted from [this article](https://www.allaboutcircuits.com/projects/build-an-automatic-computer-display-rotator-with-an-arduino/) to use MPU-6050(GY521) accelerometer instead of MMA7455.<br />
## Materials
- Arduino, I used a nano, but any other will work
- GY-521 (aka mpu 6050) accelerometer
- Dupont cables or regular wires
- usb cable for arduino
- soldering iron & supplies
- VHB tape or other mounting solution
## Assembly
arduino nano schematics
![enter image description here](https://github.com/GunbleR/MPU6050-display-rotate/blob/db499c142907f51ce3399571b8514c8ffe1d624f/Pics/Arduino%20Gyro%20nano.png)arduino uno schematics
![enter image description here](https://github.com/GunbleR/MPU6050-display-rotate/blob/bf1b099404d6214be6fe0d375fdf6e11def74991/Pics/Arduino%20Gyro%20uno.png)MPU6050 can use 3-5V. i preferred to use 3.3.
<ins>pinout:</ins>

    MPU	| Arduino (nano/uno)
    ----  |--------
    SDA	| A4
    SCL	| A5
    VCC	| 3.3V
    GND	| GND

![enter image description here](https://github.com/GunbleR/MPU6050-display-rotate/blob/bf1b099404d6214be6fe0d375fdf6e11def74991/Pics/arduino_photo.jpg)
## Software
Arduino IDE suggested. [link](https://www.arduino.cc/en/software/)<br />
Connect arduino to PC with usb cable<br />
Open the "arduino/screen_rotate_6050/screen_rotate_6050.ino" with Arduino IDE<br />
Install library "Adafruit MPU6050" using library manager.<br />
Select your board, COM port and processor and upload the code to arduino<br />
(to find out com port use "device manager", in "Ports" category see which device connects when you connect arduino)<br />
You can use built-in serial monitor to see the changes in orientation arduino reports. **make sure to close it afterwards**.<br />
## PC side software<br />
In general, you can follow the original article ([link](https://www.allaboutcircuits.com/projects/build-an-automatic-computer-display-rotator-with-an-arduino/)).<br />
Basicly you need to install python3 and python module "pyserial" ('pip install pyserial')<br />
### Linux
Follow original article
### Windows:
i did move configurable settings for windows script to the top of the script<br />
script uses display.exe from http://noeld.com/programs.asp#Display (taken from original guide),<br />
i did see some ps scripts and py modules to do the same, if you dont trust it.<br />
command : `'\"D:\Program Files\Display_exe\display.exe"'`<br />
if you got multiple displays, you can check its id using :<br />
`.\display.exe /listdevices`<br />
and add it to the line:<br />
`'\"D:\Program Files\Display_exe\display.exe" -device 2'`<br /><br />
**autostart**<br />
to autostart in windows you can use:<br />
1.<br />
open start folder by openning run (WIN+R) and typing  `shell:startup`<br />
create shortcut : <br />
target: `pythonw "path\to\python\script.py"`(keep the quotes)<br />
start in: `path\to\display.exe\dir`<br />
2.<br />
using task schedule with the same parameters.<br />

### stoping the process in windows
- task manager
- find python (pythonw.exe)
- kill it
## Mounting
i used 3d printed bracket and VHB tape.<br />
just make sure not to hit it with the monitor arm<br />
![enter image description here](https://github.com/GunbleR/MPU6050-display-rotate/blob/1cc11f187d16b9b3bd1a2b26f43d5701d8524ad5/Pics/arduino_mounted.jpg)
#  Todo list
 - add limiter when monitor looking directly up/down.
 - add windows tray icon (prob will never happen)
 - swith to python rotatescreen
