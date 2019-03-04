# Gesture-Controlled-Robot-IoT
Controling a Robotic cart via Gesture sensor(ADXL335) and an Android Application over the Network. The main intention behind this project is to allow the bot to go into areas where Human intervention is not possible. For example in applications of remote surveillance.
******************************************************************************************************************

__Block diagram:__
![alt text](https://github.com/samuelpio01/Gesture-Controlled-Robot-IoT/blob/master/block_diagram.png)

*****************************************************************************************************************


## Working:

__Trasmitting End__

The ADXL335 is a small, thin, low power, complete 3-axis accelerometer with signal conditioned voltage outputs. This product
measures acceleration with a minimum full-scale range of ±3 g. It can measure the static acceleration of gravity in tilt-sensing applications, as well as dynamic acceleration resulting from motion, shock, or vibration.

The ADXL335 works on a 3V power supply and it consists of 3 output pins that you'd have something to do with. 
 
    1. X_OUT
    2. Y_OUT
    3. Z_OUT
 
These 3 output pins are analog in nature and their outputs are proportional to the tilt. They represent the Magnitude and Direction of Acceleration in their respective axes.
 Magnitude will be decided on the value that you receive as output and the positive or negative sign will indicate it's direction for a particular axis.
 
 The ATmega32A microcontroller board we used was made by Embedded Market. 
 
 The Output of the ADXL335 was fed to the ADC of the ATmega32A micro-controller. This is a 8 channel 10-bit successive approximation ADC.
 
 In this project we did not consider the Z_OUT output of the ADXL335 because we wanted to only transmit the forward, backward, left and right direction and did not find the need for an extra axis as of now.
 
 The X_OUT and Y_OUT values were transmitted to the ESP8266 module via UART in the following terms:
 
    -  0 ->  which meant no tilt of the accelerometer (STOP)
    -  1 ->  which meant tilt of the accelerometer in the positive x-direction (FORWARD)
    -  2 ->  which meant tilt of the accelerometer in the negative x-direction (REVERSE)
    -  3 ->  which meant tilt of the accelerometer in the positive y-direction (LEFT)
    -  4 ->  which meant tilt of the accelerometer in the negative y-direction (RIGHT)
 
 Along with sending the directions, the ATmega32A will also send the details of the WiFi connection details by using AT-Commands. The ESP8266 will connect to the network and will call a HTTP GET method which will send a request to the Server which is hosted on a machine in the same network. This Server will accept the request if valid and update the value (direction value) into the database.
 We used a MYSQL database for cost reasons. 
 
 The Server was created using NodeJS and the Express Framework. Whenever any client (Accelerometer via ATmega32A and ESP8266  or Android Application or Browser) requests the Server by calling a URL the server will respond with a payload, and this is how we have used it to Update the direction value in the database.
 
 The Android Application consists of 2 activities. The first is just a welcome page and the second has the buttons for moving the cart by sending a request to the server. These are image buttons. There are 5 buttons as mentioned before for 5 diffferent functions (STOP, FORWARD, REVERSE, LEFT, RIGHT). There is also an area which shows the last actioned performed by the cart which gets updated via _Firebase Cloud Messaging(FCM)_ earlier known as Google Cloud Messaging (GCM). Whenever there is an update in value into the database by the Accelerometer or the App, it is reflected back on the App via FCM.
 
 __Receiving End__
 
 On the Receiving end we have the NodeMCU module which is programmed via Arduino IDE. This NodeMCU will fetch the updated direction value from the database and will move accordingly based on what the value is. Fetching of the direction value from the database is done by calling the HTTP GET method. This call is done every one second. Based on the received response from the Server the NodeMCU will make the bot move in that direction.
 
 Most microprocessors/microcontrollers operate at low voltages and require a small amount of current to operate while  the motors require a relatively higher voltages and current . Thus current cannot be supplied to the motors from the microprocessor/microcontroller and if connected directly the motor will sink in too much currently which the microprocessor/microcontroller cannot provide and may damage the microprocessor/microcontroller. That is why we need a motor driver to control the motors. We have used the H-bridged L293D motor driver IC for this.
 
 The L293D controls the cart based on the inputs received by the NodeMCU which in turns receives the values from the database.
 
 ********************************************************************************************************
 
 
 
 _This is basically how we have looked at this project and have successfully implemented it. Feel free to shoot in any questions in case of any doubt at __samuelpio01@gmail.com__ and dont forget to mention your views and ideas about it and what would you look as improvements/enhancements. We're open to suggestions._
