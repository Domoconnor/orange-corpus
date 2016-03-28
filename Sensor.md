<style>
	.todo{ color:red }
</style>

#Orange Street

### <a name="sensor"></a>Sensor [cont.](#contents)
The sensor samples sound every minute. The microphone in the sensor starts collecting sound data every minute it produces data that represents a sine wave. The data is then put through an ADC (Analogue to Digital Converter) that amplifies the analogue data (sine wave) and removes any voltage noise. It is then analysed by the sensor, taking fifty points along the wave, in this minute time period, to find the amplitude of the wave (how loud the sound is).  

The sensor is comprised of multiple parts, [Microphone](#mic), [ADC](#adc), [Board](#sensor_board), [Clock](#sensor_clock), [Battery](#battery), [XBee](#sensor_xbee), [Case](#sensor_case).  
###### <a name="mic"></a>Microphone
###### <a name="adc"></a>ADC
###### <a name="sensor_board"></a>Board
###### <a name="sensor_clock"></a>Clock
###### <a name="battery"></a>Battery
###### <a name="sensor_xbee"></a>XBee <span class="todo">unnecessary?</span>
###### <a name="sensor_case"></a>Case
The Case was designed in a way that was intended to aim our microphone at the noisy street and protect the electronics from the elements. It was 3D printed at a high fidelity (high infill of plastic) with a thickness of 3mm as not to allow water in through the printed plastic. It was then sanded and sprayed with a high fill primer to fill any pores left int the plastic left from the printing process. As the case had to be closed around the electronics of the sensor a seam was built in that was filled with a neoprene strip as to stop any water from getting through said seam.

#### Sensor Development/Iterations

Based on our [client interaction](#client_interaction) we decided that we had to make a device that measured the volume of the sound in Orange Street, collecting the data and sending it back to a server so that it is stored and can be accessed by the client to use.

The specification for the sensor meant that it had to accurately collect sound data, last for a reasonable amount of time (around a month) without being charged and be weatherproof.

##### Microphone Iteration 1

######The Microphone Amplifying Circuit

After talking to the client the important part of the diagram would remain constant throughout the process, which was the amplifying circuit. For a microphone to be able to produce a voltage signal able to be processed for data it must be amplified, we know for certain we are measuring noise levels in this project and so this is a crucial step.

###IMAGE 1

The basic place to start is a non-inverting amplifying circuit, used with any op-amp it effectively calculates the gain based on two resistor values going into an inverting and non-inverting input. (Gain= 1+ (R2/R1)

The OP-AMP IC we’ve been using is the MCP 6002, the datasheet can be found here. (http://ww1.microchip.com/downloads/en/DeviceDoc/21733j.pdf)

###IMAGE 2

It’s an IC with two OP-AMPS and isn’t designed for anything too complicated, for the time being it’s perfect to get a basic amplifying circuit built.

Looking at the microphone itself, it’s a very basic condenser microphone that a lot of products (Mostly cheap ones) use in manufacturing. For the time being it’s ideal, however later on we might consider modifying the microphone as this can have great benefits without changing much of the circuit let alone power requirements (Direction, pop filters, windscreens etc).

Most microphones that feed into a amplifying circuit are biased by a resistor value and then thrown down to ground (0v), one could use a potential to guarantee the voltage level applied to a microphone also.

So far, we’re looking at a circuit like this.

###IMAGE 3

Other solutions that can be found on the web include using a different IC (As opposed to the MCP 6002) and modifying the circuit above. 

List of other IC’s and amplifiers we looked into.

<table>
	<tr>
		<td>IC Chip</td>
		<td>Link</td>
	</tr>
	<tr>
		<td>NE5535, TL071, OPA 371</td>
		<td>http://www.zen22142.zen.co.uk/Circuits/Audio/lf071_mic.htm</td>
	</tr>
	<tr>
		<td>LM386</td>
		<td>http://www.learningaboutelectronics.com/Articles/Microphone-amplifier-circuit.php</td>
	</tr>
	<tr>
		<td>MCP 6002</td>
		<td>http://www.aiscube.com/main/downloads/RVHS/RV_lesson_301112.pdf</td>
	</tr>
</table>

Although some may seem more suitable than others, as of right now we’ve focused on having a working circuit. In the long term, once we are happy with this solution we will most likely have a pre-built circuit instead of designing the non-inverting amplifier ourselves and choosing which OP-AMP to use. 

######Processing the Data

The next step was to process the data, there were many ways to handle this from Microcontrollers to all-in-one IOT boards. We researched the following methods of taking data from a microphone to then process.

<table>
	<tr>
		<td> Potential Idea </td>
		<td> Description </td>
		<td> Pros </td>
		<td> Cons </td>
	</tr>
	<tr>
		<td> IOT Microcontroller Boards </td>
		<td> A whole board designed to handle multiple functions, such as Wifi/3G/Bluetooth with sensors, a built in microcontroller and more.</td>
		<td> 
			<ul>
				<li>A lot of built in features to reduce complexity of building communications between chips.</li>
				<li>Widely available, often designed for IOT solutions.</li>
			</ul>
		</td>
		<td> 
			<ul>
				<li>Often a lot of unneeded accessories (such as temperature sensor)</li>
				<li>Increase the physical size of the device based on unneeded extras</li>
			</ul>
		</td>
	</tr>
	<tr>
		<td> Microcontrollers  </td>
		<td>Singular processors, adjustable clock speeds, do not have the functionality of some of the features present on a microcontroller.</td>
		<td> 
			<ul>
				<li>A lot more freedom in deciding how to run the device.</li>
				<li>Removes any unnecessary features.</li>
				<li>Allows to scale down size of the sensor considerably.</li>
			</ul>
		</td>
		<td> 
			<ul>
				<li>Longer to produce and build together as can take more components.</li>
				<li>More complicated, requires further electronics knowledge.</li>
			</ul>
		</td>
	</tr>
	<tr>
		<td> Barebones  </td>
		<td>Using only modules to handle the work, avoiding any form of major processing.</td>
		<td> 
			<ul>
				<li>Potentially reduce power usage.</li>
				<li>Removes any unnecessary features of a Microcontroller.</li>
				<li>Allows to scale down size of the sensor considerably.</li>
				<li>A lot more freedom in deciding how to run the device.</li>
			</ul>
		</td>
		<td> 
			<ul>
				<li>Longer to produce and build together as can take more components.</li>
				<li>Much more complicated, requires further electronics knowledge.</li>
				<li>Difficult to prototype a sensor without a Microcontroller.</li>
			</ul>
		</td>
	</tr>
</table>

For the purpose of a prototype we decided to work with a IOT Microcontroller, we need to investigate common IOT Microcontroller modules, ones that are ideal for our implementation of this IOT device. 

######Arduino Microcontroller Boards

Arguably one of the most popular development boards commercially available, has a full function IDE written in C++. Multiple different boards designed for different purposes, all having sharing the basic functionality (such as analog inputs) while offering unique differences. They allow for shields to be placed into them which add even further adaptability, allowing for 3rd party hardware to be interfaced easily into the device. This functionality can be as simple as an SD card reader, a WiFi chip or even an external clock. 

Which one suited our best needs? What did we need in a device?
<ul>
	<li>Low power</li>
	<li>Within reasonable price range</li> 
	<li>Relatively small</li>
	<li>Ability to interface with certain components (Backup mediums if network is down, an external clock to keep track of time, an ADC input and form of digital output to transfer data to a wireless module).</li>
</ul>

This narrowed down our choices to the following Arduino devices.
<ul>
	<li>Arduino Nano</li>
	<li>Arduino Pro Mini</li>
	<li>Arduino Macro</li>
	<li>Arduino Uno</li>
</ul>

###IMAGE 4

######Arduino Nano

###IMAGE 5

(https://www.arduino.cc/en/uploads/Main/ArduinoNanoManual23.pdf)

“The ATmega168 has 16 KB of flash memory for storing code (of which 2 KB is used for the bootloader); the ATmega328has 32 KB, (also with 2 KB used for the bootloader). The ATmega168 has 1 KB of SRAM and 512 bytes of EEPROM (which can be read and written with the EEPROM library); the ATmega328 has 2 KB of SRAM and 1 KB of EEPROM” (Arduino.cc, n.d.)
<ul>
	<li>Serial: 0 (RX) and 1 (TX). Used to receive (RX) and transmit (TX) TTL serial data. These pins are connected to the corresponding pins of the FTDI USB-to-TTL Serial chip.</li>
	<li>External Interrupts: 2 and 3. These pins can be configured to trigger an interrupt on a low value, a rising or falling edge, or a change in value. See the attachInterrupt() function for details.</li>
	<li>PWM: 3, 5, 6, 9, 10, and 11. Provide 8-bit PWM output with the analogWrite() function.</li>
	<li>SPI: 10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK). These pins support SPI communication, which, although provided by the underlying hardware, is not currently included in the Arduino language.</li>
	<li>LED: 13. There is a built-in LED connected to digital pin 13. When the pin is HIGH value, the LED is on, when the pin is LOW, it's off.</li>
</ul>

The nano is a small device that has all the functionality that we ideally would want, it has connections over Serial, I2C and SPI (Although supported by hardware, not supported by Arduino libraries).

It requires a minimum of 5v operating power, anything below and functionality is lost and we run the risk of disabling features.

It can run the ATMega 168 or 328, we would ideally use the 328 as it offers much more space (EEPROM, SRAM and Flash memory) and is a later iteration over the 168. The dimensions of the device are 0.73” x 1.70”.

######Arduino Pro Mini 

###IMAGE 6

(http://www.atmel.com/images/Atmel-8271-8-bit-AVR-Microcontroller-ATmega48A-48PA-88A-88PA-168A-168PA-328-328P_datasheet_Complete.pdf)

Essentially the Pro Mini is identical to the Arduino Nano except for the added ability of lower bootloader space and the ability to run at 3.3v over 5v and other small differences that do not add much to our required project.

“There are two version of the Pro Mini. One runs at 3.3V and 8 MHz, the other at 5V and 16 MHz... The ATmega328 has 32 kB of flash memory for storing code (of which 0.5kB is used for the bootloader). It has 2 kB of SRAM and 1kBs of EEPROM.“ (Arduino.cc, n.d.)

######Arduino Macro

###IMAGE 7

The macros dimensions come to 48cm x 18mm, it takes a minimum of 6v volts however this is not recommended as the device may become unresponsive due to low power, ideal voltage is 7-12v.

It takes up 4KB of its bootloader, leaving 28KB for programmable memory. The microcontroller used is the ATmega32U4 at a clock frequency of 16MHz, it offers all the same functionality as the previous two boards.

######Arduino Uno

###IMAGE 8

The Uno sticks out in this comparison due to its size difference against the previous 3, which begs the question - why then? Simply put, the Arduino Uno is a very friendly board to use, and for prototyping would be ideal as we would not need to worry about many problems that we could face when going straight in with one of the other solutions. It also shares a lot of common ground with the other 3, except for its size.

It runs the ATmega328P, which has slight differences to the ATmega328 (Slight power reduction). Only uses 0.5KB of the Flash memory for the bootloader, runs at 16MHz and needs at least 6v operating voltage which like the macro can cause instability if run at this low a voltage. 

The biggest benefit for us, was that the Uno would offer easy adaptability and help quickly work with a prototype while we decide which microcontrollers to use, their frequency, and work on breadboards instead of soldering straight away. 

######MBED FRDM-K64F

###IMAGE 9

Another popular developer of IOT boards, using ARM based architecture instead of AVRs. The argument between these two processor architecture is often put down to ARM is powerful, and AVR is not so much. There are variants on the processors but otherwise they tend to stick to those groups. MBEDs have an online compiler and IDE, which works in a similar fashion to Arduinos but is effectively always online which comes with its own problems such as requiring internet access. 

The most ideal MBED board we found was the FRDM-K64F which is regarded as the flagship board, it’s perfectly ideal for prototyping - but in the long run most likely would be too much of a power killer. It’s compatible with most Arduino shields too. In the long run however, the FRDM-K64F while having many features, especially when combined with the MBED application shield - is too much functionality for what we need bundled down, even in a prototype we do not need such complexity. 

Even with all its functionality switched off the device consumes more amps than one of the arduino boards. However we decided that this board would be ideal if used for our hub, as during that period power will not be a concern. 

######Rocket Scream

....

######Conclusion

We did experiment with the FRDM K64F, but for a functioning sensor we used the Uno for power management efficiency. Our experiments with the FRDM K64F consisted of testing the circuit we had made (Amplifying Microphone circuit) already and then calculating a sound wave based on those values.



### Bibliography

Arduino.cc, (n.d.). Arduino - ArduinoBoardProMini. [online] Available at: https://www.arduino.cc/en/Main/ArduinoBoardProMini [Accessed 16 Jan. 2016].
