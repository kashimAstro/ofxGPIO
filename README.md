Openframeworks Raspberry PI GPIO interfaces, SPI (Serial Peripheral Interface), I2C (Inter Integrated Circuit), IO Pin read/write.

<img src="screen/14mtz6kkrVLUPe.gif"/><br>
<img src="screen/dVBS2AwaDFGa4.gif"/><br>  
<img src="screen/Uqvo9WQ8X1RTO.gif"/><br>
<img src="screen/3SJ2Lc9EO9KSs.gif"/><br>
<img src="screen/uRLtiGKjNqFwY.gif"/><br>

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

<br><br><br>
<b><h1>Datasheet integrated list:</h1></b>

<b>Drive motor:</b><br>
http://www.ti.com/lit/ds/symlink/l293.pdf<br>
http://www.ti.com/lit/ds/symlink/sn754410.pdf<br>
http://www.ti.com/lit/ds/symlink/uln2003a.pdf<br>
http://www.st.com/content/ccc/resource/technical/document/datasheet/f3/6e/c8/64/4d/b3/4e/38/CD00001244.pdf/files/CD00001244.pdf/jcr:content/translations/en.CD00001244.pdf
<br><br>

<b>Motor stepper Bipolar / Unipolar:</b><br>
http://motion.schneider-electric.com/downloads/datasheets/14_mtr.pdf<br>
http://www.mitsumi.co.jp/latest/Catalog/pdf/motor_m35sp_9_e.pdf
<br><br>

<b>A/D Converters:</b><br>
https://cdn-shop.adafruit.com/datasheets/MCP3008.pdf<br>
http://ww1.microchip.com/downloads/en/DeviceDoc/21295C.pdf
<br><br>

<b>ATmega48A/PA/88A/PA/168A/PA/328/P:</b><br>
http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf
<br><br>

<b>MPU-6000 / MPU-6050:</b><br>
https://www.cdiweb.com/datasheets/invensense/MPU-6050_DataSheet_V3%204.pdf
<br><br>

<b>Adafruit Ultimate GPS:</b><br>
https://cdn-learn.adafruit.com/downloads/pdf/adafruit-ultimate-gps.pdf
<br><br>

<b>Adafruit LED Backpacks:</b><br>
https://cdn-learn.adafruit.com/downloads/pdf/adafruit-led-backpack.pdf
<br><br>

<b>EEPROM</b><br>
http://www.bucek.name/pdf/24c16.pdf
http://www.st.com/content/ccc/resource/technical/document/datasheet/5c/df/52/a5/15/f2/48/bd/CD00259166.pdf/files/CD00259166.pdf/jcr:content/translations/en.CD00259166.pdf


