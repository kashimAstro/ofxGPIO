Openframeworks Raspberry PI GPIO interfaces, SPI (Serial Peripheral Interface), I2C (Inter Integrated Circuit), IO Pin read/write.

![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/Raspberry-Pi-logo.jpg)
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/Raspberry-Pi-GPIO-pinouts.png)

Example simple Button Read state:
	<ul>
		<li>Raspberry pi (2/3/Zero/A/A+/B+)
		<li>Button</li>
	</ul>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/button_example.png)


Example simple Led Blink:
	<ul>
		<li>Raspberry pi (2/3/Zero/A/A+/B+)
		<li>Led</li>
	</ul>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/led_example.png)

Example simple Relay on / off Light:
	<ul>
		<li>Raspberry pi (2/3/Zero/A/A+/B+)
		<li>Relay 5v</li>
		<li>Lamp</li>
	</ul>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/relaylight_example.png)


Example GPS UART:
	http://aprs.gids.nl/nmea/
	<ul>
		<li>Raspberry pi (2/3/Zero/A/A+/B+)
		<li>GPS breakout v3</li>
	</ul>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/gps_example.png)


Example i2c multiple byte read MPU6050:
	<ul>
		<li>Raspberry pi (2/3/Zero/A/A+/B+)
		<li>MPU6050</li>
	</ul>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/mpu6050_example.png)

Example Led Matrix8x8:
        <ul>
                <li>Raspberry pi (2/3/Zero/A/A+/B+)
                <li>Led Matrix</li>
        </ul>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/led_matrix_i2c.png)

Example Servo motor(Attention raspberry not to have pin PWM, for this we use a CLK pin, advice integrated pwm):
        <ul>
                <li>Raspberry pi (2/3/Zero/A/A+/B+)
                <li>Servo Motor</li>
        </ul>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/servo_example.png)


Example GPIO read/write stepper rotation:
	<ul>
	<li>Raspberry PI</li>
	<li>Stepper Motor bipolar</li>
	<li>sn754410ne H-Bridge</li>
	<li>Button</li>
	<li>wiring</li>
	</ul>
<br>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/raspberry_motor_bb.jpg)
sn754410ne H-Bridge:
<br>
![alt tag](http://42bots.com/wp-content/uploads/2014/12/bipolar_stepper_four_pins.jpg)
<br>
video: <a href="http://www.youtube.com/watch?v=lwRd5D9EuU0">http://www.youtube.com/watch?v=lwRd5D9EuU0</a>
[![video](http://img.youtube.com/vi/lwRd5D9EuU0/maxresdefault.jpg)](http://www.youtube.com/watch?v=lwRd5D9EuU0)
<br><br>

Example GPIO I2C communication:
	<ul>
	<li>Raspberry PI</li>
	<li>Arduino</li>
	<li>LED</li>
	<li>Resistor 75 ohm</li>
	<li>wiring</li>
	</ul>
<br>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/i2c_raspberry_bb.jpg)
<br>
video: <a href="http://www.youtube.com/watch?v=SRz750EdjfY">http://www.youtube.com/watch?v=SRz750EdjfY</a>
[![video](http://img.youtube.com/vi/SRz750EdjfY/maxresdefault.jpg)](http://www.youtube.com/watch?v=SRz750EdjfY)
<br><br>

Example GPIO SPI add Analog pin MCP3008 potentiometer:
	<ul>
	<li>Raspberry</li>
	<li>MCP3008</li>
	<li>Potentiometer</li>
	<li>wiring</li>
	</ul>
<br>
fritzing example:
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/spi_mcp_raspberry_bb.jpg)
MCP3008 8-Channel 10-Bit ADC
<br>
![alt tag](https://github.com/kashimAstro/ofxGPIO/blob/master/screen/mcp3008pin.gif)
<br>
video: <a href="http://www.youtube.com/watch?v=PkDkCJyZ2go">http://www.youtube.com/watch?v=PkDkCJyZ2go</a>
[![video](http://img.youtube.com/vi/PkDkCJyZ2go/maxresdefault.jpg)](http://www.youtube.com/watch?v=PkDkCJyZ2go)

<BR>
for i2c and SPI configuration visit this page:

https://learn.adafruit.com/adafruits-raspberry-pi-lesson-4-gpio-setup/configuring-spi
<br>
https://learn.adafruit.com/adafruits-raspberry-pi-lesson-4-gpio-setup/configuring-i2c

