**Alsa Volume Controller**


This is a GUI frontend to control ALSA Volume.


*How to Compile:*


$ gcc -o alsa_controller Vol_Controller.c \`pkg-config --libs --cflags gtk+-2.0\`



*How To Use this Application:*


It is very simple to use this application. 

To increase the System Volume, click on the '+' button.

To decrease the System Volume, click on the '-' button.

To maximize the System Volume, click on the 'MAX' button.

To mute the System Volume, click on the 'MUTE' button.

*Screenshot*

![ALSA Volume Controller](https://raw.github.com/sandeepsinghmails/alsa_vol_controller/master/images/screenshot.jpg)