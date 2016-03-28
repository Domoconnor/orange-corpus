<style>
	.todo{ color:red }
</style>

[toc]

<a name="networking"></a>
##Networking [cont.](#contents)
###Description

Our network is a robust low powered mesh that has a coordinator handling as many routers and end points as we need. The coordinator is capable of addressing each node on the network as well as the nodes being able to address the coordinator. The hardware used to handle interaction on the network is the XBee S2 module using the ZigBee protocol communicating to our devices using serial. XBee S2 have sleep functionality and only draw 40mA upon transmitting making them ideal for a low powered solution. 

Due to the configuration behind each XBee module we were able to have full control over our own network as well as control features such as sleep modes and firmware. We are using API mode when handling XBee modules on our network, as this firmware allows us to have much more control over the network.

The sensors were programmed in C++ and the Hub was programmed in Python, so we have written two Libraries to be able to communicate in the format the XBee modules expected. Using these libraries we can have greater control over the API mode letting us know when nodes disappear on the network, or that a packet failed to transmit to name a few.

<p class="todo">Might need to change to fit format ^

IMAGE 1

IMAGE 2

###Previous Work

####Iteration 1

#####What We Need

Based on how we aim to solve the problem, with multiple sensors sending data back to a hub. <span class="todo">reference initial ideas page</span> Our networking solution needs to allow us to have a hub that can have multiple sensors connected wirelessly. The network needs to allow us to communicate data reliably. The data we are expecting to be sending between the sensors and the hub is only going to be ≈ 2000 bits an hour based on the fact that we are going to send a timestamp and an averaged hourly value as a 'long' and an 'int'. 

#####Researching Technologies

Because we decided that we were working with a wireless network based on our aims<span class="todo"> link to why we chose to use wireless</span> Investigating potential solutions considerations of strength, distance, maximum payload size and power usage have to be made. The most obvious solution is WiFi.

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

<br>
*WiFi*

WiFi is widely used and accepted as a way to wirelessly transmit data. This means our clients should be familiar with it in some sense. However WiFi is not really intended to be used in devices that need to be situated in one place for an extended amount of time. This is because WiFi can use a lot of power when sending and receiving data. Hence why smartphones can lose power quickly while connected to a WiFi network.

Because we shouldn't be sending anything more than ≈7 kilobytes a day, therefore the ability to send upwards of 10 megabytes might be overkill. 

However, the main reasons why we would want to use WiFi comes in two forms. Not only can we transmit reasonable distances but we can directly connect devices to the clients home WiFi.<span class="todo"> do we want to link to where the client said we could use wifi?</span> This could, in theory, lead to the elimination of the hubs which would result in problems regarding data processing. The sensor would have to do all of its data processing onboard meaning it could effect the timing of the capture of our data.

One of our mains goals for the sensor is to make the battery as long as possible . WiFi is one of the more power consuming options, so using WiFi with or without a hub our sensor would have to use much more power when receiving and transmitting data making the battery life less than desirable. 

Another one of the more problematic issues of WiFi would be the encryption, the data we are sending is not of national security nor anything that could be any real use to anyone aside our clients and in the event that our clients change their WiFi credentials (Encryption key, SSID etc) then we risk jeopardising the sensors.

<br>
*Bluetooth and Bluetooth Low Energy*

Bluetooth is also a viable alternative for transferring over a low bandwidth where speed is not too key an issue. Depending on how often we schedule the device to transmit data. Since the range on this is considerably lower (5-30 meters) so we would have to consider integrating this with a hub of some kind to forward our data. Fortunately some of the properties across Orange Street feature flat rooftops; upon which we could attach peripherals such as antennas if we need to.  

Bluetooth smart devices have a typically very low sleep current which equates to low power consumption when it isn’t being used. This is ideal as the device will have periods of inactivity once we decide upon which kind of timeframe it should be operating over. 

Bluetooth works on a dynamic network topology called PAN, which supports up to 8 other devices and a minimum of two, although we don’t plan on having an abundance of sensors in one house (Minimum most likely 3) 

<br>
*XBee S2 and XSC*

We found that the S2 in particular was more than adequate for our desires, having one of the lower current draws for transmitting/receiving data, especially that of in sleep with a good data rate (250kbps) and working on a mesh network topology.  Not only this, but the XBee offered full configurable settings on its usage and setup, allowing us greater control of the network than other alternatives.

The XBee can also be programmed manually to work on its own meaning in theory we could eliminate the Microcontroller entirely, however this solution leads to problems involving working out the current time and large packet payloads. We may come back to it at a later point, but for now we decided to use it purely for as means for A-B for our data. 

#####Conclusion, Configuring the XBee

Testing the range of the XBee S2 revealed some problems that were unseen before such as the range being weaker than expected when facing an urban environment. The shed being the receiver's location is simply a building in an open courtyard surrounded by other buildings. The moment we entered another building the Xbee’s communication would experience huge packet loss and eventually fail entirely. This lead to a new problem, how could we guarantee data's arrival. If the nodes on the network were out of range how could we display this to our client in a meaningful manner?

IMAGE 4

Although we didn’t need XBee’s to be able to communicate huge distances (beyond 25m) it did raise concerns - causing us to later research API mode and ways of ensuring packet robustness.

####Setting up the XBee

XBees have microcontrollers onboard that store and control the instructions that let them know where data is being sent, sleep functionality, node hopping, retry attempts and much more. For our network we needed to configure each XBee to work within our desired parameters.

In order to configure these settings we required software and hardware to interface into the XBee. XCTU,software created by Digit International and a makeshift serial programmer. With this we could then start altering the settings on the firmware and adapt the XBees to our desired network structure.

IMAGE 5

When programming the XBees over serial, there are many different options for installing new firmware settings. Initially we worked with ZNet 2.5 AT for both coordinators and end routers on the network, however we later changed to working with ZNet 2.5 API as this offered more configurability.

XBees share one trait across all networks that is a requirement for them to be all to communicate, this is their PANID. The PANID is a 64 bit integer that is ideally unique on a network and separates other networks in close proximity from each other.

IMAGE 6

Using AT Command mode we had to specifically set values on the XBee. These ranged from 64bit destination address to encryption being enabled. This information was used in creating packets, however in API mode you were able to change this information at will by creating your own packets.

After we set the two XBee devices to be on the same personal network (sharing PANID), aligning their firmware (ZNet 2.5 AT), and finally setting them as coordinator and router - they were able to communicate. In AT mode we could send bytes down serial to the XBee and the firmware of that XBee would create a packet based on what we’ve set as predefined instructions. In API mode we would have to send down each individual element of the packet structure ourselves, however this allowed us to have a huge amount more control over network structure.

We needed one hub per house which could communicate and route data between sensors. The hubs were powered by mains as opposed to sensors which were powered by batteries and in varying locations. The sensors communicated using XBees to the Hub on a mesh topology, in theory allowing us to have as many sensors as we may have needed.

IMAGE 7

####API vs AT

We used API mode over AT mode in the end as this offered more configurability for our network, however it was more overhead in terms of setting up. We would need to account for packet formats, error checking and versatility. With AT mode a lot of this is covered for you, however nearly all of it is hidden away and meant that we couldn’t use it.

For API mode to work in our favour, we had to create two APIs one for the sensors and the Hub. These APIs had to be able to interpret the packet format expected from the XBees (see for formatting: Hub)

IMAGE 8

The written APIs for API mode

The premise of the APIs was to create libraries that would not force the other components to be completely recoded, instead replacing one line would effectively have the same result. With AT mode, sending data was a simple matter of writing that data out to serial and we needed to keep that format. In actuality, with API mode it was not that straightforward. We needed to recreate the packet structure every time a packet was to be sent.

We needed a way to change one line into a whole new function but without changing more than just that line.

IMAGE 9

Both APIs were different and not just in language. The end point/router API was written in C++ and was only ever designed to talk to the coordinator, so when sending a message using this API - it will address the coordinator. Whereas the Python API for the Hub had to allow for the addressing of any node on the network, and had to be able to store multiple incoming packets from different sources. The end point/routers only needed to store one message at a time, and those messages were always from the coordinator who would never send more than one at a time. Due to this requirement, our written APIs did not have to accommodate for every possibility, only the ones that expect and want. 

XBees couldn’t support large packet fragmentation, which meant large payloads would simply drop. Since we were transmitting a lot of data in one go, this lead to problems arising as we had to implement our own fragmentation of packets.

For more information regarding the Hub API and packet fragmentation, see Hub.

Sleep Settings

Amongst many of the settings available on the XBee, sleep was a must have. The XBee actually had the ability to act independently as a sensor with settings being provided for polling data from pins, but due to lack of functionality we sided against using this feature. 

There were many options available to us when configuring sleep mode. Most importantly how often does the module stay asleep for and then how often to stay awake for. In terms of reserving power this feature is invaluable for the sensor. 

The sensor used a set of pins on the XBee to command it to enter sleep mode, or awake from sleep mode - thus limiting its power consumption.

Sensor out of range

We constructed a dummy sensor in order to demonstrate range testing and how to show the client this information in a meaningful manner. The dummy was created using an Arduino Uno, a set of LEDs (Green and Red) as well as a XBee breakout board. It was transmitting random floating values from one of its analog pins in the same format expected of the actual sensor. The sensor was initially given a set of LEDs; green and red. These LEDs would turn on or off depending on the circumstance, if the sensor was within range of the coordinator (The hub) the green LED would light up, else if the sensor was out of range the red LED would light up. 

Although simple in principle, this was not possible with the use of AT mode (Without doing some serious and inefficient modifications). Using status packets we could determine whether a sensor was within range or not and then use this information to alert the client. We later decided that this information could be made easier to understand if the Hub was to alert the web server when a sensor was out of range, as this information could be displayed on the website. 

IMAGE 10

###Conclusion

After testing the XBees on multiple platforms, their range and customizability make them perfect for a small mesh network of sensors to hubs. For our IOT based project they seem more than suitable to fit the role for low-powered sensors reporting back. 
