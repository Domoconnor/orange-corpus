<a name="networking"></a>
##Networking 
[Back to contents](#contents)
###Description

Our network is a robust low powered mesh that has a coordinator handling as many routers and end points as we require. The coordinator is capable of addressing each node on the network, with the nodes only ever addressing the coordinator. The hardware used to handle interaction on the network is the XBee S2 module using the ZigBee protocol and communicating to our devices using serial. XBee S2 have sleep functionality and only draw 40mA upon transmitting making them ideal for a low powered solution. 

Due to the configuration behind each XBee module we were able to have full control over our own network as well as control features such as sleep modes and addressing. We are using API mode when handling XBee modules on our network, as this firmware allows us to  create and format packets to the style we require. The network lets us determine useful information from traffic such as delivery status, fragmentation and assembly of packets. 

The sensors were programmed in C++ and the Hub was programmed in Python. We have two Libraries to be able to communicate in the format the XBee modules expected while working with these languages. Using these libraries offer us the full potential of API mode and allow control over a mini network of low powered wireless devices.

The libraries were designed so that one line of code would be required to send a message across the network while abstracting all heavy processing on traffic. The benefit of this was that the library could change and not require a whole body of code to change for the other sections of the project. To give an example of this:  

Hub without API:

~~~python
# Write hello world down to serial
serial.write("Hello world!");
~~~

Hub with API:

~~~python
# Send message with API, sensor1 lets the API know which 64bit
# address we're looking for, returns successful 0 if successful
response = xbee.sendMessage("sensor1", "Hello world!")
~~~

Sensors/Clock without API:

~~~c++
void helloWorld(){
	// Write hello world down to serial
	Serial.print("Hello world!");
}
~~~

Sensors/Clock with API:

~~~c++
void helloWorld(){
	// Send message with API, will transmit to the coordinator
	// Returns 0 if successful
	int response = xbee.sendMessage("Hello world!"); 
}
~~~

As seen, the single line change adds more functionality to the nodes on the network. The libraries provide functions to retrieve messages that have been collected and return status codes from transmissions. This supports the other nodes in such a manner that they can then recover from network failures easily.

![13](Images/Networking/IMAGE14.PNG) 

###Previous Work

####Iteration 1, Researching Wireless Solutions

#####The Solution we need

Based on how we aim to solve the problem (see [Initial Ideas](#initial-ideas), with multiple sensors sending data back to a hub, our networking solution needs to allow us to have a hub that can have multiple sensors connected wirelessly. The network needs to allow us to communicate reliably. The data we are expecting to be sending between the sensors and the hub is only going to be ≈ 2000 bits an hour based on that we are going to send a timestamp and an averaged hourly value as a 'long' and an 'int'. This demand may change over different iterations and we must be prepared to change our requirements for networking if so.

#####Researching Technologies

We needed to nvestigate potential solutions with considerations of strength, distance, maximum payload size and power usage. Our initial solution is WiFi, but we need to research whether this was an accurate choice to make.

Here is a table that we formulated over common wireless solutions: 
 
<table>
	<tr>
		<td></td>
		<td>Range (line of sight)</td>
		<td>Range (Urban)</td>
		<td>Frequency</td>
		<td>Current Consumption (max)</td>
		<td>Power Consumption (sleep)</td>
		<td>Voltage</td>
		<td>Data Rate (s)</td>
	</tr>
	<tr>
		<td>WiFi</td>
		<td>100m</td>
		<td>20m</td>
		<td>2.4GHz/5GHz</td>
		<td>300mA</td>
		<td>Varies</td>
		<td>>= 5v</td>
		<td>Varies</td>
	</tr>
	<tr>
		<td>Bluetooth</td>
		<td>100m</td>
		<td>20 - 30m</td>
		<td>2.4GHz</td>
		<td>30mA</td>
		<td>Varies</td>
		<td>N/A</td>
		<td>1 - 3Mbits</td>
	</tr>
	<tr>
		<td>Bluetooth Low Energy</td>
		<td>100m</td>
		<td>< 100m</td>
		<td>2.4GHz</td>
		<td>15mA</td>
		<td>Varies</td>
		<td>N/A</td>
		<td>1Mbit</td>
	</tr>
	<tr>
		<td>XBee XSC</td>
		<td>9500m</td>
		<td>610m</td>
		<td>902 - 928MHz</td>
		<td>60mA(R) 265mA(T)</td>
		<td>45uA</td>
		<td>3.3v</td>
		<td>10Kbits</td>
	</tr>
	<tr>
		<td>XBee Series 2</td>
		<td>120m</td>
		<td>40m</td>
		<td>2.4GHz</td>
		<td>40mA (R & T)</td>
		<td>< 1uA</td>
		<td>3.3v</td>
		<td>250Kbits</td>
	</tr>
</table>

Values taken from [Wifi vs Bluetooth power consumption](http://science.opposingviews.com/bluetooth-vs-wifi-power-consumption-17630.html), [Bluetooth power consumption](http://www.digikey.com/en/articles/techzone/2011/dec/bluetooth-goes-ultra-low-power), [XBee power consumption](https://www.sparkfun.com/datasheets/Wireless/Zigbee/XBee-Datasheet.pdf).


<br>
**WiFi**

WiFi is widely used and accepted as a way to wirelessly transmit data. This means our clients should be familiar with it in some sense. However WiFi is not really intended to be used in devices that need to be situated in one place for an extended amount of time with limited power. This is because WiFi can use a lot of power when sending and receiving data, hence why smartphones can lose power quickly while connected to a WiFi network.

Because we shouldn't be sending anything more than ≈7 kilobytes a day, therefore the ability to send upwards of 10 megabytes might be overkill. 

However, the main reasons why we would want to use WiFi comes in two forms. Not only can we transmit reasonable distances but we can directly connect devices to the clients home WiFi.<span class="todo"> do we want to link to where the client said we could use wifi?</span> This could, in theory, lead to the elimination of the hubs which would result in problems regarding data processing. The sensor would have to do all of its data processing onboard meaning it could effect the timing of the capture of our data.

One of our mains goals for the sensor is to make the battery as long as possible . WiFi is one of the more power consuming options, so using WiFi with or without a hub our sensor would have to use much more power when receiving and transmitting data making the battery life less than desirable. 

Another one of the more problematic issues of WiFi would be the encryption, the data we are sending is not of national security nor anything that could be any real use to anyone aside our clients. In the event that our clients change their WiFi credentials (Encryption key, SSID etc) then we risk jeopardising the sensors as they can't change these details once the network changes. 

<br>
**Bluetooth and Bluetooth Low Energy**

Bluetooth is also a viable alternative for transferring over a low bandwidth where speed is not too key an issue. Depending on how often we schedule the device to transmit data. Since the range on this is considerably lower (5-30 meters) so we would have to consider integrating this with a hub of some kind to forward our data. Fortunately some of the properties across Orange Street feature flat rooftops; upon which we could attach peripherals such as antennas if we need to.  

Bluetooth smart devices have a typically very low sleep current which equates to low power consumption when it isn’t being used. This is ideal as the device will have periods of inactivity once we decide upon which kind of timeframe it should be operating over. 

Bluetooth works on a dynamic network topology called PAN, which supports up to 8 other devices and a minimum of two, although we don’t plan on having an abundance of sensors in one house (Minimum most likely 3) 

<br>
**XBee S2 and XSC**

We found that the S2 in particular was more than adequate for our desires, having one of the lower current draws for transmitting/receiving data, especially that of in sleep with a good data rate (250kbps) and working on a mesh network topology.  Not only this, but the XBee offered full configurable settings on its usage and setup, allowing us greater control of the network than other alternatives.

The XBee can also be programmed manually to work on its own meaning in theory we could eliminate the Microcontroller entirely, however this solution leads to problems involving working out the current time and large packet payloads. We may come back to it at a later point, but for now we decided to use it purely for as means for A-B for our data. 

#####Results of Iteration

We've decided to choose the XBee S2 as our solution. Due to its customisability and low powered nature its perfect for having our own control on a network. If we utilised WiFi for example then we would have to concern ourselves with high power usage and lacking full control of the network. The XBee offers a multitude of different possibilites and fits closest to our goals of a low powered networking solution. 

####Iteration 2, XBee AT Mode

XBees have microcontrollers onboard that store and control the instructions that let them know where data is being sent, sleep functionality, node hopping, retry attempts and much more. For our network we needed to configure each XBee to work within our desired parameters.

In order to configure these settings we required software and hardware to interface into the XBee, software created by Digit International called XCTU. We had to make our own programmer however as we hadn't received our own programmer as of yet. With this we have started altering the settings on the firmware to adapt the XBees to our desired network structure.

![5](Images/Networking/IMAGE5.PNG)

When programming the XBees over serial, there are many different options for installing new firmware settings. We've been working with ZNet 2.5 AT for both coordinators and end routers on the network as this is the recommended starting firmware as provides all functionality we currently need. Although we could end changing at a later date depending on what functionality we require.

XBees share one trait across all networks, that is the requirement for them to be able to communicate; using a PANID. The PANID is a 64 bit integer that is unique on a network and separates other networks in close proximity from each other, unless you unluckily both choose the same PANID - however with the options available that is a very slim chance.

![6](Images/Networking/IMAGE6.PNG)

Using AT Command mode we've had to specifically set values on the XBee. These have ranged from 64bit destination address to encryption being enabled. This information is used in creating packets, we can't change this information without reprogramming the XBees which could cause a problem. However we know which nodes need to address each other, so none of these details need changing for the time being. 

After we set the two XBee devices to be on the same personal network (sharing PANID), aligning their firmware (ZNet 2.5 AT), and finally setting them as coordinator and router - they were able to communicate. In AT mode we could send bytes down serial to the XBee and the firmware of that XBee would create a packet based on what we’ve set as predefined instructions. The XBee constructed these packets based on their programmed firmware, which we had configured. 

We ideally need one hub per house which could communicate and route data between nodes. The hubs are going to be powered by mains as opposed to sensors which are powered by batteries and in varying locations. The sensors communicate using XBees to the Hub on a mesh topology, in theory allowing us to have as many sensors as we may need.

#####Setting up AT Mode

We’ve been using AT mode so far with XBees. AT Mode is designed to be very straightforward to use, the device connects to the XBee module on serial and sends any data in a form of bytes to be used in a packet and transmitted on the network. We’ve been using XCTU to talk between XBee modules, making sure we understand the concepts of how they are designed to communicate and parameters for addressing each other. 

![7](Images/Networking/IMAGE7.1.PNG)

Setting the XBees up involves us requiring two major pieces of information, the PANID and Address. The coordinators destination points to 0x000000000000FFFF while any end points or routers need to point their destinations to the coordinator's address. That can be achieved in two ways, one way is using 0x0000000000000000 or actually specifying its address.

![7.2](Images/Networking/IMAGE7.2.PNG)
#####AT Mode and Hardware

We’ve started using FRDM-K64Fs to talk to one another as they provide an application shield and libraries alongside which are full compatibility with a hardware ‘installation’ of the XBee (installation being the XBee has dedicated pins, rather than soldering it to the board). The K64Fs had simple programs designed purely to send data to one another.

![0](Images/Networking/IMAGE0..PNG)

#####Testing Range

We know roughly the distance of an XBee from its datasheet, however our clients home and in particular Canterbury has very old structures. These structures have very thick walls, we need to know whether our XBees can transmit through these obstacles or whether we need to boost the signal. We modified the previous code used to test between FRDM K64Fs to calculate latency between packets and then walked around parts of campus determining if we had enough packet loss for concern.

We used ‘The Shed’ as the coordinators base station while moving through different parts of the School of Computing while the coordinator was making note of whether it was receiving any data or not. We’ve mapped our findings and calculated distances to determine whether we are going to struggle with walled structures or not.

![4](Images/Networking/IMAGE4.PNG)

As shown above the XBees are capable of travelling around 30m and only suffer complete packet loss when passing multiple walls, which is most likely unavoidable in our project. We will definitely need some form low powered communications network so boosting the power will be a trade off we most likely can’t afford.

######Results of Iteration
 
The FRDM-K64F is the current choice for the Hub but not for the sensor, so at some point we will need to test the capability of using an FRDM-K64F to talk to an Arduino style board. This has furthered our understand of using XBees with AT mode, specifically how to progress further and utilise these modules in our future components. 

* <a href="MBEDXbeeTest/receiver.cpp">Code for FRDM-K64F receiver</a>
* <a href="MBEDXbeeTest/transmitter.cpp">Code for FRDM-K64F transmitter</a>

####Iteration 3, AT Mode with Hub, Sensor and Clock

Our next role is to implement the Hub, Clock and the sensor(s) on the network. For this to work all nodes need to be able to communicate with one another.

![7.3](Images/Networking/IMAGE7.3.PNG)

The sensor is planning to send around 700 bytes of data an hour to the hub, the hub then processes that data. If the clock sends a request to the hub then the hub processed that and responds with data back to the clock. Using AT mode it is simply a matter of writing down to serial the bytes you wish to send across the network, all the nodes are configured to talk to one another. The clock and sensor both have their destination addresses set 0x0 pointing to the coordinator while the coordinator has its address set to 0x000000000000FFFF. This allows it to broadcast, the sensor won’t respond as it will not be needed and will be utilising sleep mode on the XBee whereas the clock will respond as the broadcast will directed at the clock.

#####Problems

In theory the solution was fine, however a problem we did not account for was payload size. For unknown reasons the coordinator would lose segments of incoming data and then just carry on until it received the next transmission. This meant that data was becoming malformed and mixed up which meant it was completely useless to us. Upon further investigation, we found that the internal buffers of the XBees are that of 202 bytes. The XBee datasheet offers flow-control through the use of pins CTS and RTS but in fact it's very likely the XBee doesn’t support fragmentation of packets as we haven’t found anything to prove it does. Using the CTS and RTS pins could prove interesting, but it would only solve the problem of knowing when the XBees internal buffers are almost full or empty.

So we’re likely to be able to send around 150 bytes in a single packet (RF data and packet header), we circumvented this for the time being by purposely delaying and breaking up the data the sensor had. This took advantage of the internal hardware on the XBee which has timers dedicated to calculating when to stop listening on serial, form a packet and send it. By breaking the message down we effectively caused the XBee to send multiple packets across the network in one go.

The other solution to this problem could be to transmit more frequently, every minute over an hour but battery usage would be the main concern. 

A concern was raised regarding the issue of multiple sensors, as of right now we have no way of knowing who is sending data to the hub as well as data becoming malformed and merged due to AT mode. With one sensor this won’t be an issue:

![7.73](Images/Networking/IMAGE7.73.PNG)

However with multiple sensors, data becomes inoperable:

![7.75](Images/Networking/IMAGE7.75.PNG)

Making this an issue to tackle in the next iteration.

For more information on these particular systems and how they process data see their respective sections.

######Results of Iteration
AT mode worked well for our initial task however we need to solve the problem of large payloads and multiple sensors as these will become more apparent later in our project. With this iteration passed we have successfully created the prototype project as a whole, the network allows for all components to successfully communicate with one another.

For information regarding the datasheet for the XBee S2, see this document.
https://www.sparkfun.com/datasheets/Wireless/Zigbee/XBee-Datasheet.pdf
* Page 12 refers to data input buffers of size 202 bytes
* Page 11 refers to ‘Packetization Timeout’ from serial to RF

Code used for Hub with AT Mode can be found <a href="XbeeAPI/Hub/HubAT.py">here</a>.

####Iteration 4, API Mode 
#####Issues with previous Iteration
On our previous iteration we discovered a few problems with using AT mode and the XBee modules themselves. We can’t fragment packets without having some form of intervention ourselves and we can’t determine who is sending data which will cause issues for multiple sensors. A simple fix to this is to prefix all incoming data with an identifying name and delimiter, for example "clock:message". However this is most likely overhead as further research has shown that by using API mode we won’t need to do this as source addresses are passed with packets. We did manage to confirm that fragmentation is not possible on XBee S2 networks, see [here] ( www.digi.com/wiki/developer/index.php/Determine_MTU).

#####API Mode

API mode is the more advanced version of AT in a lot of ways. The XBee will function the same and you can transmit data to the XBee in the same manner, that’s serial down to the XBee RX pin. However, just sending a stream of bytes won’t make the XBee transmit data. With API mode you have to make the packets as opposed to having them made for you. This has required a lot of research into formats and to do so accurately with good use of examples, we used “Building Wireless Sensor Networks” by Robert Faludi. Faludi provides excellent examples and technical details on the use of API mode.

![7.4](Images/Networking/IMAGE7.4.PNG)

API mode has many different packets you can create, from investigating the formats of these packets we can see specifically how to form and send data. We will only need 3 different packets format for our system to be fully utilised, those of:

* 0x10 TRANSMIT REQUEST
* 0x90 RECEIVE PACKET
* 0x8B TRANSMIT REQUEST

The typical format of one these packets, for example the transmit request appears as follows:

Transmit (“Hello world”): “7E 00 19 10 01 00 00 00 00 00 00 00 00 FF FE 00 00 48 65 6C 6C 6F 20 57 6F 72 6C 64 D5”
Receive (“Hello world”): “7E 00 19 10 01 00 00 00 00 00 00 00 00 FF FE 00 00 48 65 6C 6C 6F 20 57 6F 72 6C 64 D5”
Status (“Hello world”): 7E 00 07 8B 01 00 00 00 00 00 73

These hexadecimal values while alien looking are relatively straightforward to identify as again they are following a format. The packets we will form will be a transmit packet while the packets we receive will be a status and receive packet. 

The transmit packet must follow this format when being created:

![7.5](Images/Networking/IMAGE7.5.png)

The receive packet will follow this format, so we know the offset of each byte:

![7.6](Images/Networking/IMAGE7.6.png)

The status packet will follow this format, again we know the offset of each byte:

![7.7](Images/Networking/IMAGE7.7.PNG)

These formats are important because when we wish to send or receive data to the XBee it will need to be in this format. Instead of:

~~~python
self.serial.write(“Hello world!”) # AT method
~~~

We would use:

~~~python
self.serial.write(bytearray.fromhex('7E 00 17 10 01 00 13 A2 00 40 C1 FD 49 FF FE 00 00 48 65 79 20 57 6F 72 6C 64 A7')) # API method
~~~

However for true implementation we would want this to return some indicator of whether the message was transmitted successfully or not. For example:

~~~python
response = transmit(bytearray.fromhex('7E 00 17 10 01 00 13 A2 00 40 C1 FD 49 FF FE 00 00 48 65 79 20 57 6F 72 6C 64 A7')) # API method
if response == x:
       # do something ...
~~~

If we had this, then we could use this within our existing components to implement a form of error awareness and resolution.

#####API Mode System Benefits
API mode offers a lot more in utility at the cost of more effort on implementation. The benefit of using it, is that you can access all data in a packet header. This would allow us to see all sorts of ranging information from source address to checksums and would solve our problem of needing to identify nodes on the network. It also comes with a lot of added benefits, using API mode we could determine whether a node is out of range, what nodes are on the network and whether packets have been successfully delivered or not. 

For API mode to be implemented we need to build two libraries capable of handling the underlying functions of the XBee. One library would need to utilise Python and the other C++, the Python library would be used by the Hub while any other nodes would use the C++ library. The Hub had its own requirements and so the library would need to reflect that.

######Hub API requirements
* Node discovery (Locate any new nodes)
* Heartbeat requests (Determine whether a node is still active)
* Individual node addressing (Address any node on the network as opposed to broadcasting each time)
* Fragmentation (Break large payloads down)
* Assembly (Reassemble large payloads)
* Message storing (If multiple sensors are sending their payloads at the same time, the hub needs to be able identify and reassemble separate messages at the same time)
* Status awareness (Was a packet received?)

######Sensor and clock API requirements
* Fragmentation (Break large payloads down)
* Assembly (Reassemble large payloads)
* Respond to heartbeat requests (Respond to hubs request to see if they are ‘alive’)
* Single message storing (The hub will only ever send one message, to the clock it will be requests or a heartbeat but never at the same time. To the sensor it will be a heartbeat.)
* Status awareness (Was a packet received?) 

######Multiple Sensors Solution
Initially we used AT mode for working with one sensor, however problems soon arose when we planned to add multiple sensors to our network. The problem was that it would become impossible to identify who was sending data causing different sensor readings to become mixed up across transmissions. Using one sensor was fine because only one source of traffic with sensor readings was expected, the clock wouldn’t interfere as this was a different format of data. Using API mode has let us identify each node on the network and where each stream of traffic is coming from, fixing this problem for us.

![7.76](Images/Networking/IMAGE7.76.PNG)

######Fragmenting Packets
As show in our previous iteration the XBee didn't support packet fragmentation, so in order for this to work we need to manually number each frame in a packet from each source. We also need to be able to determine which is the final frame of a packet, we’ve decided to use an ‘!’ character, which would never naturally appear in any of our normal packets.

![7.8](Images/Networking/IMAGE7.8.PNG)

######Arduino String vs Char Array
When working with the Arduino IDE its been very tempting to use the 'String' class. A class that offers useful functionality similar to that of Java. With it we can work out the length of a string, split it, concat it and do general operations on it. However, this functionality comes as the cost of efficiency. In C, strings don't exist in the format of other languages rather they exist as char arrays and are handled very differently. Arduinos IDE dumbs down the char array into a string. The lack of efficiency comes at the cost of memory, with such a small amount of RAM, the nodes could potentially crash if we are not careful. 

For us, we want total efficieny above all else. Although it might be easier to implement a string over a char array, we have decided with the later. 

~~~c++
  char char_array_hello[20] = "Hello world!"; // Using char array to store sentence
  String string_hello = "Hello world!"; // Using String to store sentence
~~~

#####XBee Sleep Settings
Amongst many of the settings available on the XBee, sleep is a must have for our sensors. There are many options available to us when configuring sleep mode. Most importantly how often does the module stay asleep for and then how often to stay awake for. In terms of reserving power this feature is invaluable for the sensor. 

The sensor currently uses a set of pins on the XBee to command it to enter sleep mode, or awake from sleep mode - thus limiting its power consumption.

######Results of Iteration
These requirements will allow us to build a robust network capable of recovery upon failure, if a packet isn’t received for example then retransmit it. We will be able to also provide more feedback to the client such as if a node is no longer within range, if they moved the sensor too far away from the Hub for example.

* For implementations of our node code (C++), see <a href="XbeeAPI/Nodes">here</a>.
* For implementations of our Hub code (Python), see <a href="XbeeAPI/Hub">here</a>.

####Iteration 5, Implementing API Mode

#####Sensor out of range

![10](Images/Networking/IMAGE10.PNG)

Building off the last iteration, we can now offer more information to the client and to the network. This includes node discovery, a very powerful feature for our network which determines whether nodes are now out of range or have disappeared. Using this information we could alert the client that the sensor has run out of battery and thus died or been moved too far away from the Hub.  

We decided to construct a dummy sensor in order to demonstrate range testing and how to show the client this information in a meaningful manner. The dummy was created using an Arduino Uno, a set of LEDs (Green and Red) as well as a XBee breakout board. It was transmitting random floating values from one of its analog pins in the same format expected of the actual sensor. The sensor was initially given a set of LEDs; green and red. These LEDs would turn on or off depending on the circumstance, if the sensor was within range of the coordinator (The hub) the green LED would light up, else if the sensor was out of range the red LED would light up. 

Although simple in principle, this was not possible with the use of AT mode (Without doing some serious and inefficient modifications). Using status packets we can determine whether a sensor was within range or not and then use this information to alert the client. We’ve decided that this information could be made easier to understand if the Hub was to alert the web server when a sensor was out of range, as this information can be displayed on the website for easier access rather than flashing LEDs.

* For implementations of the dummy sensor code (C++), see <a href="XbeeAPI/Nodes/DummySensor/XbeeAPI.cpp">here</a>.

#####Library for coordinator (Hub)

The hubs library is much more extensive than the nodes library. It has to offer the hub the ability to address any node, as well node discovery and heartbeats. These features are cruicial in order to maintain network stability and determine missing nodes, which can reported back to the webserver. 

For more information regarding the Hub and API mode, see [**Hub**](#hub).

#####Library for nodes (Clock and Sensors)

The library created for the nodes on the network was simpler than that of the coordinator. The nodes only need to talk to the coordinator on the network as opposed to each other. The coordinators address is constant, set at 0x00, which means no complicated addressing or node discovery.

######Packet Fragmentation and Assembly

Packet fragmentation and assembly are supported along with responding to heartbeats automatically when received. This library will only support one stored message however, it only expects one message at a time from one node - the coordinator. Response codes and transmission status packets are available with the library allowing for us to determine successful packet transmission.

######Different Serial Ports

The actual serial connection on the clock and sensor are different, the Flora board has two serial ports whereas the Rocket Scream only has one. This meant that the serial connection the Flora board used was different to the Rocket Scream and they send data down serial in different ways. To accomodate this the HardwareSerial class was used a reference in the API, allowing us to choose which serial port we wanted the API to use. 

For the Rocket Scream, initialising the API can be done as:

~~~c++
XbeeAPI xbee(&Serial, 0, "test");
~~~

Whereas for the Flora:

~~~c++
XbeeAPI xbee(&Serial1, 0, "test");
~~~

The library handles this construction as follows:

~~~c++
XbeeAPI::XbeeAPI(HardwareSerial *pserial, const char* name) : name(name)
{
  serial = pserial;
  serial->begin(9600);
  serial->setTimeout(1000);
}
~~~

######Polling

The ATMega architecture struggles with some forms of interrupt handling, due to this storing packets when data is received becomes difficult. When a packet is received the XBee will store it internally and wait to send over serial, it can only send when the board is ready to receive. The sensors are often asleep and won't be listening on serial for incoming data, except for when they wake up. When they wake up to sample sound, they can call a method called 'poll' in the library. This method reads in everything it can from serial and then forms messages for the program to use. This method is designed to bypass the problem of interrupt handling and work within the parameters of a device that may need to be sleeping for a long period of time.

An example of polling:

~~~c++
// awakening from sleep...
// take a sample
bool messageAvailable = poll(3); 
if(messageAvailable){
	// respond, read etc ...
}
~~~

The parameter passed to the poll function relates to how many times the program wants to poll, each call waits 250 milliseconds before reading everything it can in from serial. The example above would poll 3 times and would take 750 milliseconds to execute, not including time for atomic operations. 

The poll function:

~~~c++
bool XbeeAPI::poll(uint8_t timesToPoll)
{

    unsigned char input[INPUT_SIZE + 1]; // Total length of data expected, including + 1 for termination \0
    unsigned char packet[INPUT_SIZE + 1]; // Total length of data expected, including + 1 for termination \0

    // How many times we want to check for incoming data
    for(int i = 0; i < timesToPoll; i++){
    	
      // Clear arrays with 0
      memset(input, 0, INPUT_SIZE+1);
      memset(packet, 0, INPUT_SIZE+1);
      delay(250);
      // Read in all data we can up to INPUT_SIZE and store in 'input'
      uint8_t size = serial->readBytes(input, INPUT_SIZE);
      input[size] = 0; // Final termination of array \0


      unsigned char pos = 0;
      unsigned char checkPacket = 0;   
      for(int i = 0; i < size; i++){
        if(input[i] == 0x7E){
          if(!checkPacket){
            checkPacket = 1;
          // If the packet is valid, we want to continue checking serial data for other packets
          }else if (validatePacket(packet)){
            memset(packet, 0, INPUT_SIZE); // Reset packet
            pos = 0;
            checkPacket++;
          // If invalid packet and not checking packet then break 
          }else{
            break;
          }
        }
        packet[pos++] = input[i];
      }

      if(checkPacket == 1){
        validatePacket(packet);
      }

      if(message != NULL && message->hasTerminated()){
        return true;
      }else{
        return false;
      }
  }
    }
~~~

#####Results of Iteration
With our recent iteration we've managed to successfully test the sensor out of range, create working libraries to interface with our nodes without changing any existing code to the systems. Overall this iteration has been a massive success towards the structure of the network and ensuring the strength of it. 
