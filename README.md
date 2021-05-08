# E-INK-Google-Calendar
## E-ink display based google calendar

E-ink display that connects to your google calendar and retrieves the data from the next few 6 days updating every 24 hours.

![](E-Ink%20Display.jpeg)

## Parts used:

 -  https://www.waveshare.com/wiki/E-Paper_ESP32_Driver_Board
 -  https://www.waveshare.com/product/7.5inch-e-paper.htm
 
## Explanation:
 
 - We use google scripts to connect to our google calendar and retrieve the needed information.
 - After doing such, from our esp32 we connect to the scripts application and retrieve the data from the html reponse.
 - We give format to the response to have a better integrationwith the e-ink display.
 - We print it to the display using the waveshare library for arduino. (Make sure you have all libraries and drivers download and installed correctly to be able to connect to the display)
 - The data will update every 24 Hours, restarting the device will force an update at any time.

## Example of data retrieved from google scripts:

Sat May 08 2021
Lunch with friends                  14:30:00-15:30:00
Dinner with friends                 21:00:00-22:00:00
|
Sun May 09 2021
Breakfast                           9:30:00-10:30:00
|
Mon May 10 2021
Going to class                      All day
|
Tue May 11 2021
Computer Science Exam               10:00:00-12:00:00
|
Wed May 12 2021
Studying for next exam              All day
|
Thu May 13 2021
Reading                             21:30:00-22:00:00

## Credits:
 
 - https://www.waveshare.com/wiki/E-Paper_ESP32_Driver_Board
