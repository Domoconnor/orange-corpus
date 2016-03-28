## <a name="hub"></a>Hub [cont.](#contents)

Image Here
(The finished Hub, requiring only ethernet and power it is capable of coordinating the entire network.)

The Hub uses a Raspberry Pi Model B+ running Raspbian Jessie Lite, the Pi offers GPIO pins to connect external boards to it. Using these pins, an XBee module is connected on serial and provides the Pi with its position on the network as coordinator. The Pi only requires three connections for it to function, an ethernet connection, the serial connection to the XBee and finally power. The programs controlling the network are written in Python 3.

The hub is comprised of multiple parts: [Board](#hub_board), [Communication / XBee](#hub_xbee), [Case](#hub_case)

#####<a name="hub_board"></a>Board

The Hub uses a Raspberry Pi Model B+ running Raspbian Jessie Lite, the Pi offers GPIO pins to connect external boards to it. Using these pins, an XBee module is connected on serial and provides the Pi with its position on the network as coordinator. The Pi only requires three connections for it to function, an ethernet connection, the serial connection to the XBee and finally power. The programs controlling the network are written in Python 3.

#####<a name="hub_xbee"></a>Communication / XBee

The XBee module is configured as coordinator on the network, giving the Hub its status and control on the network. The XBee can address any other XBee module on the network or broadcast to all of them. All other XBees address the coordinator as it is the centre point of the network. Sensors forward their data through the XBees to the Hub the Clock makes requests using its XBee to the Hub also.

#####<a name="hub_processing"></a>Processing Role

It handles data coming in from the sensor and requests from the clock. The clock can request decibel averages of the past 24 hours using the Hub as a middleman, the Hub then forwards this request to the web server and returns the result to the clock. The sensors submit their sampled data to the hub in order for this to then be sent forward to the web server. 
The Hub takes into account that it may not be able to reach the web server for various reasons, and will try multiple times to connect. If it fails with sensor data it will save this in the SD card on the Pi, if it cannot request data for the clock it will return an error instead and the clock can react accordingly. 

Upon a series of failed attempts, once a successful attempt is made the Hub will transmit all previous stored data and delete it afterwards to clear space in memory. 

#####<a name="hub_case"></a>Case

The case was a 3D printed design that was required due to the extra components that the Hub required. The Pi has many off the shelf cases that can be used, however due to our requirement of fitting an XBee module these cases would not suffice. The 3D printed case was capable of fitting the XBee module as well as the Pi.

### Initial Premise

Unlike the sensor, power consumption was not an issue as the client told us that we could connect to a power outlet. It didn't need to be outside the clients premisses either. This meant we could use any feasible board for this role. We needed a board that could offer the most useful functionality towards our project.

The hub was required to be a middleman between sensors and the web server, forwarding traffic onto the website over ethernet and handling any heavy processing. Initially we planned on using an FRDM-K64F board due to familiarity and easy access to them within the University. 

### Hub Hardware
####Iteration ONE
#####FRDM K64F

Image Here
(FRDM K64F Board)

The FRDM-K64F board has a lot of unneeded functionality. It has an unnecessary amount of sensors on the board itself (temperature sensor and accelerometer for example) which wouldn't add to our project benefits. Although as previously stated we are testing this board because of its availability and our familiarity with it. We are familiar with this board and we know that it has a shield that has the ability to interface with an XBee which is what we decided to use for our networking. <span class="todo">(insert link to networking decisions)</span> Using the board would not be an issue, as we have had extensive skill in handling and programming it. Including the MBED Application shield would benefit us in providing pins designed for an XBee module to interface with. It also offers an LCD display for reporting information back to the client, which could be useful for showing basic messages. However the shield does offer a lot of useless additions as well. Introducing more sensors and obstructing every pin on the FRDM makes it unlikely to be a realistic option for our Hub.

<p class="todo">Here I was going to include my case design implementation for the hub, but it went on for a while, would you like me to do that in its own page?</p>

###Research Into other Boards

####Arduino Uno

Considering the Arduino Uno for the hub as a likely candidate for the fact that the board itself does not have any sensors that would be considered unnecessary like on the FRDM K64F. It is programmable in C much like the K64F so will essentially use the same code. The main reason for choosing this board would be to trim the unessential things from our current solution. The Uno is also a well known board that is vastly documented. 

Unlike the K64F the Uno lacks an ethernet port built in. To remedy this we would have to add an Arduino shield capable of offering ethernet such as the Arduino Ethernet shield. The shield while similar to the MBED Application shield provides the ability to transmit more than just data along ethernet, it could provide power too, although this means adding the PoE (Power over Ethernet) component. This added functionality means the possibility for less wires, this means easier instillation for the client as only one connection would be required. There are libraries that exist to help use the shield and it’s functionality and the board offers a lot of useful debug information regarding current status with sending data, making it easier to work with.

With the problem of ethernet solved this only leaves connection to XBee out. In order to fix this we would have to either, include another [shield](http://uk.rs-online.com/web/p/products/6961670/?grossPrice=Y&cm_mmc=UK-PLA-_-google-_-PLA_UK_EN_Semiconductors-_-Semiconductor_Development_Kits&mkwid=s8484M9Xf_dc|pcrid|88057061283|pkw||pmt||prd|6961670&gclid=Cj0KEQjwid63BRCswIGqyOubtrUBEiQAvTol0WdagHobLZ9zO5iXOsR0-jdPUrM43OJ-dTZv86HIMcgaAkHy8P8HAQ) that had a breakout for the XBee or physically wiring up an XBee. Wiring up an XBee would require soldering the required pins on the XBee to wires that we could plug into the headers of the ethernet shield. If we choose to have the ethernet shield with the PoE module the XBee shield would probably not fit and therefore we would have to solder the XBee to the board. In circumstance of soldering the XBee it would also lead to being unable to then modify the firmware settingson the module without desoldering first leading to more spendature of time. Otherwise we could use the shield on its own, meaning we could reconfigure the XBee at any time.

####Arduino Yun

INSERT IMAGE OF YUN AND SYSTEM DIAGRAM (IMAGE 0)

The Arduino Yun is a very unique Arduino board, as it offers two processors. The AR9331 handles a Linux distribution while the ATMega32U4 handles the board. This means we can run an Operating System with all the benefits that brings on this board. The board comes with an ethernet port and WiFi as well, making it immediately more ideal than the previous two boards mentioned. The board also comes with an SD card port for supplying the Operating System, so in theory a large SD card would allow data logging and more storage in general. The board itself can run Arduino sketches which can interface with shell scripts running on the Linux distro, although the two processors are kept separate; bridging is possible due to a library provided.

However the Yun lacks a great deal of hardware support in terms of volatile memory only offering  64MB of DDR2 ram with 16MB of flash, 9 of which is taken by the Linux distribution. With this considered a better alternative would be something like a Raspberry Pi which could offer more memory and more Operating Systems varieties. The price of a Yun is higher than previous entries, averaging around £50 which is more than double the price of an Uno. 

####Micro Server

It is plausible to use a Micro Server in place of the Hub. The server could have a serial programmer connected to a XBee and use programs to read and access the data coming in. Using a Micro server would give huge benefits in terms of processing power, data storage and security. We could have our own choice of operating system and hardware. Data could come in and be backed up internally, then processed to be sent off. However price and size could cause issues, as these servers do not often come cheap and are a lot larger than other potential solutions. They can also become quite loud and considering noise is what we are trying to help our client with it is probably not an ideal solution furthermore it would draw a lot more power than a development board meaning it could have a visible cost impact on the client.

####Raspberry Pi

The Raspberry Pi is a well known mini computer in its own right and full of IoT uses too. Following on from the Microserver idea, the premise of having an operating system was very appealing. Especially the idea of being able to remotely access the Hub, in which both the Microserver, Yun and Pi could provide this. The Pi while being smaller and considerably cheaper than its Microserver counterpart did lack internal hardware to boot, but for the purpose we had planned it was more than adequate. It would’t be noisy either. 

The Pi was a good middleground between the Yun and the Microserver. It didn’t have as many Operating Systems to chose from compared to the Microserver (due to its Arm architecture) but it did offer a good selection of Operating Systems in terms of networking and much more compared to the Arudino Yun. Its price was not as expensive as the Yun or the Microserver, averaging around £25. 

Internal storage could be managed using a SD card of any size meaning data logging was possible as well. With this being built in as well as an ethernet port it has many advantages over previous entries. The only piece of hardware that is lacking for what we need is an XBee connection. Although solutions are the same as the Arduino Uno, either we use a shield with XBee breakouts or we physically wire an XBee up.

However with all this, the Pi did lack the speed of other boards that didn’t require a OS to maintain. It also didn't offer built in WiFi unlike the Yun, but we were unlikely to use this anyway due to potentially changing security of a WiFi network. 

####Conclusion

We decided to use a Raspberry Pi (Model B+ 512MB) over other solutions. While the Arduino and FRDM K64F boards offered speed, they lacked remote accessing and long term storage and would require more adaptions to work around this. The Microserver was too large, expensive and potentially noisy. The Yun while very promising lacked internal hardware to match the Pi as well being double the price. The Pi offered a full operating system while maintaining a small size, better secure networking and remote access for updating on the network. This meant that if a bug was found in our code we could remotely update in on the hub, we would also be able to access any logged debug information from the program. 

####Iteration Two (FINAL)
#####Raspberry Pi (Model B+)
We decided to use a Raspberry Pi (Model B+ 512MB). The Pi offered a full operating system, better secure networking and remote access for updating on the network. This means that if a bug is found in our code while the hub is deployed in our clients house we could remotely update in on said hub. In the same way we would also be able to access any logged debug information from the program.

#####How to move forward with the pi

The Model B+ will be supplied by the university. The operating system of choice was Raspbian Jessie Lite because it is the officially supported OS of the Pi therefore, recommended by the developers of the Pi. The Pi will have to be connected to the XBee over serial, however in order to use these ports they have to be masked by systemd to force them to be free on startup. 

Then we need to write a program capable of handling incoming AT packets from serial, interpret them and respond accordingly. <span class="todo"><- link to code for this</span> 

The program will be written in Python 3 as its easily available on the Pi and offers all the functionality required to create a robust networking program. We will have to modify /etc/rc.local to contain “sudo python hub.py” so that the script will start every time the Operating System starts. If the network was down, or errors occurred on transmit then the Pi will save data locally, and retry on its next attempt.

###Language of Choice: Python <span class="todo">is this description of code or why python was chosen?</span>

Why Python

We chose Python because it was easily available on the Pi, had plenty of documentation supporting it and is a very easy language to read from another developers standing. In terms of interfacing it with serial and the network there are plenty of libraries that exist to make this as simple and efficient as possible, we have decided to use PySerial and Requests to handle these requirements. 

Python Libraries

PySerial and Requests simplified any complications we may have had from writing our own initial libraries as well as having organised documentation to support them. They abstracted a lot of complicated hardware tasks (such as interrupt handling on GPIO pins) and communicating over the network. Other libraries we plan on using are those standard to Python, time for handling timing operations, random for random calculations, threading to handle multiple tasks to name a few.

###Coordinator on Network

The Hubs most important role will be that of the coordinator on the network, it is the centre point. Due to how XBees address each other, it is very easy to send data straight to coordinator using its predefined 64bit address (0x0000000000000000).  The Hub could address any node on the network and with this could determine which nodes were which and if they were still within range.

<p class="todo">insert picture system diagram pi with zigbee</p>

###AT Mode 
Image Here
(a single sensor to Hub to the server. Hub reads in all data it receives which is only from one source, no errors.)

Initially we used AT mode for working with one sensor, however problems would soon arise when we planned to add multiple sensors to our network. The problem was that it would become impossible to identify who was sending data causing different sensor readings to become mixed up across transmissions. Using one sensor was fine because only one source of traffic with sensor readings was expected, the clock wouldn’t interfere as this was a different format of data. The solution to this was to expand into API mode, which allowed us to identify individual sensors on the network and solve this particular problem

Image HERE
(Multiple sensors to Hub to server, Hub reads in data without knowing sources, data is merged together and becomes inoperable.)


###API Mode

With AT mode packets were formed for us and the payload was the only part we submitted in forming it. This lead us into problems as we would not be able to access information in the packet header that could be crucial to determining who sent the packet and other details. 

With API mode we were able to form the packets entirely ourselves, however this meant we required an API to handle this for us, which is what we set out to create. The API we created was able to determine different destinations, sources, error checking and packet fragmentation We had to work with the packet format the XBee expected which was found in its data sheet. This also gave us the ability to work with different types of packets such as status packets which gave us the insight of knowing whether a packet was received or not. 

The written API could handle multiple packets at once and organise them according to their sources. We could also handle packet assembly and fragmentation, so large payloads would no longer be an issue.

(Multiple sensors to Hub to server, Hub reads in data using API provided and is able to distinguish incoming packets and sources.)
 
However the XBee did not accommodate packet fragmentation itself, so in order for this to work we had to manually number each packet from each source when being fragmented and sent across the network. We also needed to be able to determine which was the final frame, this was done using an ‘!’ character, which would never naturally appear in any of our normal packets. 

Image Here
(Showing simple-flow approach to packet fragmentation. Message is split into frames, each frame is acknowledged when received and the process repeats until all frames are received successfully.)

###Node Discovery 

Being able to determine what sensors already exist on a network would offer us much more functionality. We would be able to ping nodes on the network and offer more functionality in the written API to message individual nodes. 

On startup the program running on the hub would find every current node on the network and save them. It will also load from memory any nodes it has previously found. This way, it could determine if a node was missing (Maybe a sensor was moved) and could report this back to the client. The hub would periodically send heartbeats across the network to see any changes on the nodes. If a change was detected (such as a node disappearing) it would report this back to the server, this way we could display on the website that a sensor was out of range or had run out for battery. 

With node discovery it simplified sending messages from the coordinator to sensors, instead of requiring individuals addresses. You could pass names of nodes into the “sendMessage” function and it will conclude the address based on this.

~~~python
# Send message with API, sensor1 lets the API know which 64bit
# address we’re looking for, returns successful or not
response = xbee.sendMessage("sensor1", "Hello World")
~~~

Sending ‘sensor1’ - “Hello world!”, the program will fetch the associated 64bit address of sensor1.






